/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2016 - 2017 Intel Corp.
 * Copyright (C) 2017 Online SAS.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <cbmem.h>
#include <cf9_reset.h>
#include <intelblocks/rtc.h>
#include <console/console.h>
#include <cpu/x86/mtrr.h>
#include <soc/iomap.h>
#include <soc/pci_devs.h>
#include <soc/pcr.h>
#include <soc/pmc.h>
#include <soc/romstage.h>
#include <soc/smbus.h>
#include <soc/smm.h>
#include <soc/soc_util.h>
#include <soc/skxsp_util.h>

int rtc_failure(void);

#if 0
static void early_pmc_init(void)
{
	/* PMC (B0:D31:F2). */
	pci_devfn_t dev = PCH_PMC_DEV;

	/* Is PMC present */
	if (pci_read_config16(dev, 0) == 0xffff) {
		printk(BIOS_ERR, "PMC controller (B0:D31:F2) does not present!\n");
		return;
	}

	uint32_t pwrm_base =
		pci_read_config32(dev, PMC_PWRM_BASE) & MASK_PMC_PWRM_BASE;
	if (!pwrm_base) {
		printk(BIOS_ERR, "PWRM base address is not configured!\n");
		return;
	}
}

static void early_tco_init(void)
{
	/* SMBUS (B0:D31:F4). */
	pci_devfn_t dev = PCI_DEV(0, SMBUS_DEV, SMBUS_FUNC);

	/* Configure TCO base address */
	if (pci_read_config16(dev, TCOBASE) == 0xffff) {
		printk(BIOS_ERR, "SMBus controller (B0:D31:F4) does not present!\n");
		return;
	}
	uint16_t tco_ctl = pci_read_config16(dev, TCOCTL);
	if (tco_ctl & TCOBASE_LOCK) {
		printk(BIOS_ERR, "TCO base register already has been locked!\n");
	} else {
		pci_write_config16(dev, TCOCTL, tco_ctl & (~TCOBASE_EN));
		pci_write_config16(dev, TCOBASE, DEFAULT_TCO_BASE | 0x1);
		pci_write_config16(dev, TCOCTL, tco_ctl | TCOBASE_EN);
	}

	uint16_t tco_base = pci_read_config16(dev, TCOBASE) & MASK_TCOBASE;
	printk(BIOS_DEBUG, "TCO base address set to 0x%x!\n", tco_base);

	/* Disable the TCO timer expiration from causing a system reset */
	MMIO32_OR(PCH_PCR_ADDRESS(PID_SMB, PCR_SMBUS_GC),
		(uint32_t)PCR_SMBUS_GC_NR);

	/*  Halt the TCO timer */
	uint16_t reg16 = inw(tco_base + TCO1_CNT);
	reg16 |= TCO_TMR_HLT;
	outw(reg16, tco_base + TCO1_CNT);

	/* Clear the Second TCO status bit */
	reg16 = inw(tco_base + TCO2_STS);
	reg16 |= TCO2_STS_SECOND_TO;
	outw(reg16, tco_base + TCO2_STS);
}
#endif

int rtc_failure(void)
{
	return 0;
}

asmlinkage void car_stage_entry(void)
{

	struct postcar_frame pcf;
	uintptr_t top_of_ram;

#if IS_ENABLED(CONFIG_HAVE_SMI_HANDLER)
	void *smm_base;
	size_t smm_size;
	uintptr_t tseg_base;
#endif

	console_init();

	printk(BIOS_DEBUG, "FSP TempRamInit was successful...\n");

	mainboard_config_gpios();

  rtc_init();

#if 0
	early_tco_init();
	early_pmc_init();
#endif

	fsp_memory_init(false);

	printk(BIOS_DEBUG, "coreboot fsp_memory_init finished...\n");

	unlock_pam_regions();

	if (postcar_frame_init(&pcf, 1 * KiB))
		die("Unable to initialize postcar frame.\n");

	/*
	 * We need to make sure ramstage will be run cached. At this point exact
	 * location of ramstage in cbmem is not known. Instruct postcar to cache
	 * 16 megs under cbmem top which is a safe bet to cover ramstage.
	 */
	top_of_ram = (uintptr_t)cbmem_top();
	printk(BIOS_DEBUG, "top_of_ram: 0x%lx\n", top_of_ram);
	postcar_frame_add_mtrr(&pcf, top_of_ram - 16 * MiB, 16 * MiB,
			       MTRR_TYPE_WRBACK);

	/* Cache the memory-mapped boot media. */
	postcar_frame_add_romcache(&pcf, MTRR_TYPE_WRPROT);

#if IS_ENABLED(CONFIG_HAVE_SMI_HANDLER)
	/*
	 * Cache the TSEG region at the top of ram. This region is
	 * not restricted to SMM mode until SMM has been relocated.
	 * By setting the region to cacheable it provides faster access
	 * when relocating the SMM handler as well as using the TSEG
	 * region for other purposes.
	 */
	smm_region(&smm_base, &smm_size);
	tseg_base = (uintptr_t)smm_base;
	postcar_frame_add_mtrr(&pcf, tseg_base, smm_size, MTRR_TYPE_WRBACK);
#endif

	printk(BIOS_DEBUG, "coreboot run_postcar_phase begin\n");
	run_postcar_phase(&pcf);
	printk(BIOS_DEBUG, "coreboot run_postcar_phase complete\n");

  outb(0xa, 0x70);
  printk(BIOS_DEBUG, "^^^ %s:%s CMOS read: 0x%x\n", __FILE__, __func__, inb(0x71));
}

static void soc_memory_init_params(FSPM_CONFIG *m_cfg)
{
}

void platform_fsp_memory_init_params_cb(FSPM_UPD *mupd, uint32_t version)
{
	FSPM_CONFIG *m_cfg = &mupd->FspmConfig;

	mupd->FspmUpdVersion = FSP_UPD_VERSION;
	m_cfg->SafetyConfig.disable_SNI_BIOS_flc = 1;
	m_cfg->BoardId = AndersonLakeRvp48G;
	//m_cfg->BoardId = UnknownBoardType;
	//m_cfg->PcdFspMrcDebugPrintErrorLevel = 2;
	//m_cfg->PcdFspKtiDebugPrintErrorLevel = 8;
	m_cfg->PcdFspMrcDebugPrintErrorLevel = 8;
	m_cfg->PcdFspKtiDebugPrintErrorLevel = 8;

	soc_memory_init_params(m_cfg);

	mainboard_memory_init_params(mupd);
}

__weak void mainboard_config_gpios(void)
{
	/* Do nothing */
}
__weak void mainboard_memory_init_params(FSPM_UPD *mupd)
{
	/* Do nothing */
}

