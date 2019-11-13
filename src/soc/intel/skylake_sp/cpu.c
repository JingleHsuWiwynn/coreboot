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
//#include <soc/smm.h>
#include <soc/soc_util.h>
#include <soc/skxsp_util.h>
#include <assert.h>


//static char processor_name[64];
//static struct smm_relocation_attrs relo_attrs;

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

	/* TODO(adurbin): This should only be done on a cold boot. Also, some
	   of these banks are core vs package scope. For now every CPU clears
	   every bank. */
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

/*
 * MP and SMM loading initialization.
 */

#if 0
static void relocation_handler(int cpu, uintptr_t curr_smbase,
			       uintptr_t staggered_smbase)
{
	msr_t smrr;
	em64t100_smm_state_save_area_t *smm_state;
	(void)cpu;

	FUNC_ENTER();
	/* Set up SMRR. */
	smrr.lo = relo_attrs.smrr_base;
	smrr.hi = 0;
	wrmsr(IA32_SMRR_PHYS_BASE, smrr);
	smrr.lo = relo_attrs.smrr_mask;
	smrr.hi = 0;
	wrmsr(IA32_SMRR_PHYS_MASK, smrr);
	smm_state = (void *)(SMM_EM64T100_SAVE_STATE_OFFSET + curr_smbase);
	smm_state->smbase = staggered_smbase;
	FUNC_EXIT();
}

static void get_smm_info(uintptr_t *perm_smbase, size_t *perm_smsize,
			 size_t *smm_save_state_size)
{
	void *smm_base;
	size_t smm_size;
	void *handler_base;
	size_t handler_size;

	FUNC_ENTER();
	/* All range registers are aligned to 4KiB */
	const uint32_t rmask = ~((1 << 12) - 1);

	/* Initialize global tracking state. */
	smm_region(&smm_base, &smm_size);
	smm_subregion(SMM_SUBREGION_HANDLER, &handler_base, &handler_size);

	relo_attrs.smbase = (uint32_t)smm_base;
	relo_attrs.smrr_base = relo_attrs.smbase | MTRR_TYPE_WRBACK;
	relo_attrs.smrr_mask = ~(smm_size - 1) & rmask;
	relo_attrs.smrr_mask |= MTRR_PHYS_MASK_VALID;

	*perm_smbase = (uintptr_t)handler_base;
	*perm_smsize = handler_size;
	*smm_save_state_size = sizeof(em64t100_smm_state_save_area_t);
	FUNC_EXIT();
}
#endif

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

	/* ./src/cpu/x86/mtrr/mtrr.c */
	/*
		x86_setup_mtrrs_with_detect();
	*/
	x86_setup_fixed_mtrrs();

#if 0
  struct memranges *addr_space;
  addr_space = get_physical_address_space();
	print_physical_address_space(addr_space, __func__);
	x86_mtrr_check();

	int fixed_msrs[] = {0x250, 0x258, 0x259, 0x268, 0x269, 0x26a, 0x26b, 0x26c, 0x26d, 0x26e, 0x26f};
	for (int i=0; i < 11; ++i) {
		msr_t msr = rdmsr(fixed_msrs[i]);
		printk(BIOS_DEBUG, "fixed msr: 0x%x, value: 0x%08x%08x\n", fixed_msrs[i], msr.hi, msr.lo);
	}

	for (int i=0; i < 10; ++i) {
		printk(BIOS_DEBUG, "IA32_MTRR_PHYSBASE%d (msr: 0x%x): 0x%08x%08x, IA32_MTRR_PHYSMASK0%d (msr: 0x%x): 0x%08x%08x\n",
					 i, 512 + 2*i, rdmsr(512+2*i).hi, rdmsr(512+2*i).lo, i, 513 + 2*i, rdmsr(513+2*i).hi, rdmsr(513+2*i).lo);
	}
#endif

	FUNC_EXIT();
}

static void post_mp_init(void)
{
	FUNC_ENTER();
	/* Set Max Ratio */
	set_max_turbo_freq();

	/*
	 * Now that all APs have been relocated as well as the BSP let SMIs
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
