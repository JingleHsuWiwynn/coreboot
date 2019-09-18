/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2014 Google Inc.
 * Copyright (C) 2015-2016 Intel Corporation.
 * Copyright (C) 2017-2018 Online SAS.
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


#ifndef _SKYLAKESP_HOB_MEM_H
#define _SKYLAKESP_HOB_MEM_H

#include <fsp/util.h>

#pragma pack(1)

#define MAX_CH        6   /* Maximum Number of Memory Channels */
#define MAX_DIMM      2   /* Maximum Number of DIMMs PER Memory Channel */
#define MAX_SPD_BYTES 512 /* Maximum Number of SPD bytes */

#if 0
/*
 * Memory Down structures.
 */
typedef enum {
	STATE_MEMORY_SLOT = 0, /* No memory down and a physical memory slot. */
	STATE_MEMORY_DOWN = 1, /* Memory down and not a physical memory slot. */
} MemorySlotState;

typedef struct {
	MemorySlotState SlotState[MAX_CH][MAX_DIMM]; /* Memory Down state of
							each DIMM in each
							Channel */
	UINT16 SpdDataLen; /* Length in Bytes of a single DIMM's SPD Data */
	UINT8 *SpdDataPtr[MAX_CH][MAX_DIMM]; /* Pointer to SPD Data for each
						DIMM in each Channel */
} MEMORY_DOWN_CONFIG;
#endif

/*
* SMBIOS Memory Info structures.
*/
typedef struct {
	UINT8 DimmId;
	UINT32 SizeInMb;
	UINT16 MfgId;
	UINT8
	    ModulePartNum[20]; /* Module part number for DDR3 is 18 bytes
				  however for DRR4 20 bytes as per JEDEC Spec,
				  so reserving 20 bytes */
} DIMM_INFO;

typedef struct {
	UINT8 ChannelId;
	UINT8 DimmCount;
	DIMM_INFO DimmInfo[MAX_DIMM];
} CHANNEL_INFO;

typedef struct {
	UINT8 Revision;
	UINT16 DataWidth;
	/** As defined in SMBIOS 3.0 spec
	Section 7.18.2 and Table 75
	**/
	UINT8 MemoryType;
	UINT16 MemoryFrequencyInMHz;
	/** As defined in SMBIOS 3.0 spec
	Section 7.17.3 and Table 72
	**/
	UINT8 ErrorCorrectionType;
	UINT8 ChannelCount;
	CHANNEL_INFO ChannelInfo[MAX_CH];
} FSP_SMBIOS_MEMORY_INFO;

#pragma pack()

void soc_display_fsp_smbios_memory_info_hob(
		const FSP_SMBIOS_MEMORY_INFO *memory_info_hob);

void soc_save_dimm_info(void);

#define FSP_SMBIOS_MEMORY_INFO_GUID	\
{	\
	0x8c, 0x10, 0xa1, 0x01, 0xee, 0x9d, 0x84, 0x49,	\
	0x88, 0xc3, 0xee, 0xe8, 0xc4, 0x9e, 0xfb, 0x89	\
}

static inline const FSP_SMBIOS_MEMORY_INFO *
soc_get_fsp_smbios_memory_info_hob(void)
{
	size_t hob_size;
	const FSP_SMBIOS_MEMORY_INFO *memory_info_hob;
	const uint8_t smbios_memory_info_guid[16] =
			FSP_SMBIOS_MEMORY_INFO_GUID;

	/* Locate the memory info HOB */
	memory_info_hob = fsp_find_extension_hob_by_guid(
				smbios_memory_info_guid,
				&hob_size);
	if (memory_info_hob == NULL || hob_size == 0) {
		printk(BIOS_ERR, "SMBIOS MEMORY_INFO_DATA_HOB not found\n");
		return NULL;
	}

	return memory_info_hob;
}

#endif // _SKYLAKESP_HOB_MEM_H
