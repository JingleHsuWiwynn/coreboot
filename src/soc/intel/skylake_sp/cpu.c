/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2015 - 2017 Intel Corp.
 * Copyright (C) 2018 Online SAS
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <console/console.h>
#include <device/device.h>
#include <device/pci.h>
#include <intelblocks/cpulib.h>
#include <reg_script.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <bootstate.h>
#include <console/console.h>
#include <device/device.h>
#include <device/pci_ids.h>
#include <cpu/cpu.h>
#include <cpu/x86/msr.h>
#include <cpu/x86/mtrr.h>
#include <cpu/x86/cache.h>
#include <cpu/x86/lapic.h>
#include <cpu/x86/name.h>
#include <cpu/x86/mp.h>
#include <cpu/intel/turbo.h>
#include <arch/acpi.h>
#include <memrange.h>
#include <soc/msr.h>
#include <soc/cpu.h>
#include <soc/iomap.h>
#include <soc/soc_util.h>
#include <soc/skxsp_util.h>
#include <assert.h>


static void skx_configure_mca(void)
{
	msr_t msr;
	int num_banks;
	struct cpuid_result cpuid_regs;

	/* Check feature flag in CPUID.(EAX=1):EDX[7]==1  MCE
	 *                   and CPUID.(EAX=1):EDX[14]==1 MCA*/
	cpuid_regs = cpuid(1);
	if ((cpuid_regs.edx & (1<<7 | 1<<14)) != (1<<7 | 1<<14))
		return;

	msr = rdmsr(IA32_MCG_CAP);
	num_banks = msr.lo & IA32_MCG_CAP_COUNT_MASK;
	if (msr.lo & IA32_MCG_CAP_CTL_P_MASK) {
		/* Enable all error logging */
		msr.lo = msr.hi = 0xffffffff;
		wrmsr(IA32_MCG_CTL, msr);
	}

	mca_configure();
}

static void skylake_sp_core_init(struct device *cpu)
{
	msr_t msr;

	printk(BIOS_DEBUG, "Init Skylake-SP SoC cores.\n");

	/* Clear out pending MCEs */
	skx_configure_mca();

	/* Enable Fast Strings */
	msr = rdmsr(IA32_MISC_ENABLE);
	msr.lo |= FAST_STRINGS_ENABLE_BIT;
	wrmsr(IA32_MISC_ENABLE, msr);

	/* Enable Turbo */
	enable_turbo();

	/* Enable speed step. */
	if (get_turbo_state() == TURBO_ENABLED) {
		msr = rdmsr(IA32_MISC_ENABLE);
		msr.lo |= SPEED_STEP_ENABLE_BIT;
		wrmsr(IA32_MISC_ENABLE, msr);
	}
}

static struct device_operations cpu_dev_ops = {
	.init = skylake_sp_core_init,
};

static const struct cpu_device_id cpu_table[] = {
	{X86_VENDOR_INTEL, CPUID_SKYLAKESP_A0_A1},		/* Skylake-SP A0/A1 CPUID 0x506f0*/
	{X86_VENDOR_INTEL, CPUID_SKYLAKESP_B0}, /* Skylake-SP B0 CPUID 0x506f1*/
	{X86_VENDOR_INTEL, CPUID_SKYLAKESP_4}, /* Skylake-SP 4 CPUID 0x50654*/
	{0, 0},
};

static const struct cpu_driver driver __cpu_driver = {
	.ops = &cpu_dev_ops,
	.id_table = cpu_table,
};

static void set_max_turbo_freq(void)
{
	msr_t msr, perf_ctl;

	FUNC_ENTER();
	perf_ctl.hi = 0;

	/* Check for configurable TDP option */
	if (get_turbo_state() == TURBO_ENABLED) {
		msr = rdmsr(MSR_TURBO_RATIO_LIMIT);
		perf_ctl.lo = (msr.lo & 0xff) << 8;

	} else if (cpu_config_tdp_levels()) {
		/* Set to nominal TDP ratio */
		msr = rdmsr(MSR_CONFIG_TDP_NOMINAL);
		perf_ctl.lo = (msr.lo & 0xff) << 8;

	} else {
		/* Platform Info bits 15:8 give max ratio */
		msr = rdmsr(MSR_PLATFORM_INFO);
		perf_ctl.lo = msr.lo & 0xff00;
	}
	wrmsr(IA32_PERF_CTL, perf_ctl);

	printk(BIOS_DEBUG, "cpu: frequency set to %d\n",
	       ((perf_ctl.lo >> 8) & 0xff) * CPU_BCLK);
	FUNC_EXIT();
}

/*
 * Do essential initialization tasks before APs can be fired up
 *
 * 1. Prevent race condition in MTRR solution. Enable MTRRs on the BSP. This
 * creates the MTRR solution that the APs will use. Otherwise APs will try to
 * apply the incomplete solution as the BSP is calculating it.
 */
static void pre_mp_init(void)
{
	FUNC_ENTER();
	printk(BIOS_DEBUG, "pre_mp_init entry\n");

	x86_setup_fixed_mtrrs();

	FUNC_EXIT();
}

static void post_mp_init(void)
{
	FUNC_ENTER();
	/* Set Max Ratio */
	set_max_turbo_freq();

	/*
	 * TODO: Now that all APs have been relocated as well as the BSP let SMIs
	 * start flowing.
	 */
	//southcluster_smm_enable_smi();
	FUNC_EXIT();
}

/*
 * CPU initialization recipe
 *
 * Note that no microcode update is passed to the init function. CSE updates
 * the microcode on all cores before releasing them from reset. That means that
 * the BSP and all APs will come up with the same microcode revision.
 */
static const struct mp_ops mp_ops = {
	.pre_mp_init = pre_mp_init,
	.get_cpu_count = get_platform_thread_count,
	//.get_smm_info = get_smm_info, /* TODO */
	.get_smm_info = NULL,
	//.pre_mp_smm_init = southcluster_smm_clear_state, /* TODO */
	.pre_mp_smm_init = NULL,
	//.relocation_handler = relocation_handler, /* TODO */
	.relocation_handler = NULL,
	.post_mp_init = post_mp_init,
};


void skylake_sp_init_cpus(struct device *dev)
{
	FUNC_ENTER();

  /* calls src/cpu/x86/mp_init.c */
	if (mp_init_with_smm(dev->link_list, &mp_ops) < 0)
		printk(BIOS_ERR, "MP initialization failure.\n");

	/* update numa domain for all cpu devices */
	xeonsp_init_cpu_config();

	FUNC_EXIT();
}
