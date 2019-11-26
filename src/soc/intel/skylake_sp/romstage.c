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

#include <arch/romstage.h>
#include <cbmem.h>
#include <cpu/x86/smm.h>
#include <cf9_reset.h>
#include <intelblocks/rtc.h>
#include <console/console.h>
#include <cpu/x86/mtrr.h>
#include <soc/iomap.h>
#include <soc/pci_devs.h>
#include <soc/pcr.h>
#include <soc/pm.h>
#include <soc/pmc.h>
#include <soc/romstage.h>
#include <soc/smbus.h>
#include <soc/smm.h>
#include <soc/soc_util.h>
#include <soc/skxsp_util.h>

int rtc_failure(void)
{
	return 0;
}

asmlinkage void car_stage_entry(void)
{

	struct postcar_frame pcf;
	uintptr_t top_of_ram;

#if CONFIG(HAVE_SMI_HANDLER)
	void *smm_base;
	size_t smm_size;
	uintptr_t tseg_base;
#endif

	console_init();

	printk(BIOS_DEBUG, "FSP TempRamInit was successful...\n");

	mainboard_config_gpios();

  rtc_init();

	/*TODO: tco/pmc init in early romstage */

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

#if CONFIG(HAVE_SMI_HANDLER)
	/*
	 * Cache the TSEG region at the top of ram. This region is
	 * not restricted to SMM mode until SMM has been relocated.
	 * By setting the region to cacheable it provides faster access
	 * when relocating the SMM handler as well as using the TSEG
	 * region for other purposes.
	 */
	smm_region((uintptr_t *)(&smm_base), &smm_size);
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
  // ErrorLevel - 0 (disable) to 8 (verbose)
	m_cfg->PcdFspMrcDebugPrintErrorLevel = 0;
	m_cfg->PcdFspKtiDebugPrintErrorLevel = 0;

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
