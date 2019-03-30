/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2016 - 2017 Intel Corp.
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
#include <fsp/util.h>
#include <lib.h>

/* Display the UPD parameters for MemoryInit */
void soc_display_fspm_upd_params(
	const FSPM_UPD *fspm_old_upd,
	const FSPM_UPD *fspm_new_upd)
{
	const FSP_M_CONFIG *new;
	const FSP_M_CONFIG *old;

	old = &fspm_old_upd->FspmConfig;
	new = &fspm_new_upd->FspmConfig;

	printk(BIOS_DEBUG, "UPD values for MemoryInit:\n");

	#define DISPLAY_UPD(field) \
		fsp_display_upd_value(#field, sizeof(old->field), \
			old->field, new->field)

	DISPLAY_UPD(PcdFspMrcDebugPrintErrorLevel);
	DISPLAY_UPD(PcdFspKtiDebugPrintErrorLevel);
	DISPLAY_UPD(PcdHsuartDevice);
#if 0
	DISPLAY_UPD(PcdCustomerRevision);
	DISPLAY_UPD(GpioConfig);
	DISPLAY_UPD(IioBifurcationConfig);
	DISPLAY_UPD(IioSlotConfig);
	DISPLAY_UPD(KtieParamConfig);
#endif

	#undef DISPLAY_UPD

	hexdump(fspm_new_upd, sizeof(*fspm_new_upd));
}

/* Display the UPD parameters for SiliconInit */
void soc_display_fsps_upd_params(
	const FSPS_UPD *fsps_old_upd,
	const FSPS_UPD *fsps_new_upd)
{
	const FSPS_CONFIG *new;
	const FSPS_CONFIG *old;

	old = &fsps_old_upd->FspsConfig;
	new = &fsps_new_upd->FspsConfig;

	printk(BIOS_DEBUG, "UPD values for SiliconInit:\n");

	#define DISPLAY_UPD(field) \
		fsp_display_upd_value(#field, sizeof(old->field), \
			old->field, new->field)

	DISPLAY_UPD(PcdBifurcationPcie0);
	DISPLAY_UPD(PcdBifurcationPcie1);
	DISPLAY_UPD(PcdActiveCoreCount);
	DISPLAY_UPD(PcdCpuMicrocodePatchBase);
	DISPLAY_UPD(PcdCpuMicrocodePatchSize);
	DISPLAY_UPD(PcdEnablePcie0);
	DISPLAY_UPD(PcdEnablePcie1);
	DISPLAY_UPD(PcdEnableEmmc);
	DISPLAY_UPD(PcdEnableGbE);
	DISPLAY_UPD(PcdFiaMuxConfigRequestPtr);
	DISPLAY_UPD(PcdPcieRootPort0DeEmphasis);
	DISPLAY_UPD(PcdPcieRootPort1DeEmphasis);
	DISPLAY_UPD(PcdPcieRootPort2DeEmphasis);
	DISPLAY_UPD(PcdPcieRootPort3DeEmphasis);
	DISPLAY_UPD(PcdPcieRootPort4DeEmphasis);
	DISPLAY_UPD(PcdPcieRootPort5DeEmphasis);
	DISPLAY_UPD(PcdPcieRootPort6DeEmphasis);
	DISPLAY_UPD(PcdPcieRootPort7DeEmphasis);
	DISPLAY_UPD(PcdEMMCDLLConfigPtr);

	#undef DISPLAY_UPD

	hexdump(fsps_new_upd, sizeof(*fsps_new_upd));
}
