/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2017 Intel Corp.
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
#include <assert.h>
#include <soc/hob_mem.h>
#include <soc/hob_iiouds.h>

static const uint8_t fsp_hob_iio_universal_data_guid[16] = FSP_HOB_IIO_UNIVERSAL_DATA_GUID;

struct guid_name_map {
	const void *guid;
	const char *name;
};

static const struct guid_name_map  guid_names[] = {
	{ fsp_hob_iio_universal_data_guid,
		"FSP_HOB_IIO_UNIVERSAL_DATA_GUID" },
};

const char *soc_get_hob_type_name(
	const struct hob_header *hob)
{
	return NULL;
}

const char *soc_get_guid_name(const uint8_t *guid)
{
	size_t index;

	/* Compare the GUID values in this module */
	for (index = 0; index < ARRAY_SIZE(guid_names); index++)
		if (fsp_guid_compare(guid, guid_names[index].guid))
			return guid_names[index].name;

	return NULL;
}

void soc_display_hob(const struct hob_header *hob)
{
	/* hexdump(hob, hob->length); */
}

void soc_display_fsp_smbios_memory_info_hob(
		const FSP_SMBIOS_MEMORY_INFO *memory_info_hob)
{
	int channel, dimm;
	const DIMM_INFO *dimm_info;
	const CHANNEL_INFO *channel_info;

	/* Display the data in the FSP_SMBIOS_MEMORY_INFO HOB */
	printk(BIOS_DEBUG, "FSP_SMBIOS_MEMORY_INFO HOB\n");
	printk(BIOS_DEBUG, "    0x%02x: Revision\n",
		memory_info_hob->Revision);
	printk(BIOS_DEBUG, "    0x%02x: MemoryType\n",
		memory_info_hob->MemoryType);
	printk(BIOS_DEBUG, "    %d: MemoryFrequencyInMHz\n",
		memory_info_hob->MemoryFrequencyInMHz);
	printk(BIOS_DEBUG, "    %d: DataWidth in bits\n",
		memory_info_hob->DataWidth);
	printk(BIOS_DEBUG, "    0x%02x: ErrorCorrectionType\n",
		memory_info_hob->ErrorCorrectionType);
	printk(BIOS_DEBUG, "    0x%02x: ChannelCount\n",
		memory_info_hob->ChannelCount);
	for (channel = 0; channel < memory_info_hob->ChannelCount;
		channel++) {
		channel_info = &memory_info_hob->ChannelInfo[channel];
		printk(BIOS_DEBUG, "  Channel %d\n", channel);
		printk(BIOS_DEBUG, "      0x%02x: ChannelId\n",
			channel_info->ChannelId);
		printk(BIOS_DEBUG, "      0x%02x: DimmCount\n",
			channel_info->DimmCount);
		for (dimm = 0; dimm < channel_info->DimmCount;
			dimm++) {
			dimm_info = &channel_info->DimmInfo[dimm];
			printk(BIOS_DEBUG, "   DIMM %d\n", dimm);
			printk(BIOS_DEBUG, "      0x%02x: DimmId\n",
				dimm_info->DimmId);
			printk(BIOS_DEBUG, "      %d: SizeInMb\n",
				dimm_info->SizeInMb);
			printk(BIOS_DEBUG, "    0x%04x: MfgId\n",
				dimm_info->MfgId);
			printk(BIOS_DEBUG, "%*.*s: ModulePartNum\n",
				(int)sizeof(dimm_info->ModulePartNum),
				(int)sizeof(dimm_info->ModulePartNum),
				dimm_info->ModulePartNum);
		}
	}
}

void soc_display_iio_universal_data_hob(void) 
{
  size_t hob_size;
  const IIO_UDS *hob = fsp_find_extension_hob_by_guid(
													fsp_hob_iio_universal_data_guid,
													&hob_size);
	printk(BIOS_DEBUG, "hob: %p, hob_size: 0x%lx 0x%lx\n", hob, hob_size, sizeof(IIO_UDS));
  printk(BIOS_DEBUG, "^^^^ IIO_UDS size: 0x%lx, MC_MAX_NODE: %d, MAX_SOCKET: %d, MAX_CH: %d, MAX_IMC: %d, "
		      "CONFIG_TDP_MAX_LEVEL: %d, MaxIIO: %d, MAX_IIO_STACK: %d, NUMBER_PORTS_PER_SOCKET: %d, MAX_KTI_PORTS: %d\n", 
		      sizeof(IIO_UDS), MC_MAX_NODE, MAX_SOCKET, MAX_CH, MAX_IMC, CONFIG_TDP_MAX_LEVEL, MaxIIO, MAX_IIO_STACK, 
		      NUMBER_PORTS_PER_SOCKET, MAX_KTI_PORTS);

  printk(BIOS_DEBUG, "^^^^ SYSTEM_STATUS: 0x%lx, PLATFORM_DATA: 0x%lx, IIO_RESOURCE_INSTANCE: 0x%lx, STACK_RES: 0x%lx, "
		      "IIO_DMI_PCIE_INFO: 0x%lx, QPI_IIO_DATA: 0x%lx, QPI_CPU_DATA: 0x%lx, QPI_PEER_DATA: 0x%lx, "
		      "IIO_PORT_INFO: 0x%lx, UINT64_STRUCT: 0x%lx\n",
		      sizeof(SYSTEM_STATUS), sizeof(PLATFORM_DATA), sizeof(IIO_RESOURCE_INSTANCE), sizeof(STACK_RES), 
		      sizeof(IIO_DMI_PCIE_INFO), sizeof(QPI_IIO_DATA), sizeof(QPI_CPU_DATA), sizeof(QPI_PEER_DATA), 
		      sizeof(IIO_PORT_INFO), sizeof(UINT64_STRUCT));


	assert(hob != NULL && hob_size != 0);
	//assert(hob != NULL && hob_size != 0 && hob_size == sizeof(IIO_UDS));
	
  printk(BIOS_DEBUG, "===================== IIO_UDS HOB DATA =====================\n");

  printk(BIOS_DEBUG, "\t===================== SYSTEM STATUS =====================\n");
	printk(BIOS_DEBUG, "\tcpuType: 0x%x\n", hob->SystemStatus.cpuType);
	printk(BIOS_DEBUG, "\tcpuSubType: 0x%x\n", hob->SystemStatus.cpuSubType);
	printk(BIOS_DEBUG, "\tSystemRasType: 0x%x\n", hob->SystemStatus.SystemRasType);
	printk(BIOS_DEBUG, "\tnumCpus: 0x%x\n", hob->SystemStatus.numCpus);
	for (int x=0; x < MAX_SOCKET; ++x) {
		printk(BIOS_DEBUG, "\tSocket %d FusedCores: 0x%x, ActiveCores: 0x%x, MaxCoreToBusRatio: 0x%x, MinCoreToBusRatio: 0x%x\n",
					 x, hob->SystemStatus.FusedCores[x], hob->SystemStatus.ActiveCores[x], hob->SystemStatus.MaxCoreToBusRatio[x],
				   hob->SystemStatus.MinCoreToBusRatio[x]); 
	}
	printk(BIOS_DEBUG, "\tCurrentCoreToBusRatio: 0x%x\n", hob->SystemStatus.CurrentCoreToBusRatio);
	printk(BIOS_DEBUG, "\tIntelSpeedSelectCapable: 0x%x\n", hob->SystemStatus.IntelSpeedSelectCapable);
	printk(BIOS_DEBUG, "\tIssConfigTdpLevelInfo: 0x%x\n", hob->SystemStatus.IssConfigTdpLevelInfo);
	for (int x=0; x < CONFIG_TDP_MAX_LEVEL; ++x) {
		printk(BIOS_DEBUG, "\t\tTDL Level %d IssConfigTdpTdpInfo: 0x%x, IssConfigTdpPowerInfo: 0x%x, IssConfigTdpCoreCount: 0x%x\n",
					 x, hob->SystemStatus.IssConfigTdpTdpInfo[x], hob->SystemStatus.IssConfigTdpPowerInfo[x], 
					 hob->SystemStatus.IssConfigTdpCoreCount[x]);
	}
	printk(BIOS_DEBUG, "\tsocketPresentBitMap: 0x%x\n", hob->SystemStatus.socketPresentBitMap);
	printk(BIOS_DEBUG, "\ttolmLimit: 0x%x\n", hob->SystemStatus.tolmLimit);
	printk(BIOS_DEBUG, "\ttohmLimit: 0x%x\n", hob->SystemStatus.tohmLimit);
	printk(BIOS_DEBUG, "\tmmCfgBase: 0x%x\n", hob->SystemStatus.mmCfgBase);
	printk(BIOS_DEBUG, "\tnumChPerMC: 0x%x\n", hob->SystemStatus.numChPerMC);
	printk(BIOS_DEBUG, "\tmaxCh: 0x%x\n", hob->SystemStatus.maxCh);
	printk(BIOS_DEBUG, "\tmaxIMC: 0x%x\n", hob->SystemStatus.maxIMC);

  printk(BIOS_DEBUG, "\t===================== PLATFORM DATA =====================\n");
	printk(BIOS_DEBUG, "\tPlatGlobalIoBase: 0x%x\n", hob->PlatformData.PlatGlobalIoBase);
	printk(BIOS_DEBUG, "\tPlatGlobalIoLimit: 0x%x\n", hob->PlatformData.PlatGlobalIoLimit);
	printk(BIOS_DEBUG, "\tPlatGlobalMmiolBase: 0x%x\n", hob->PlatformData.PlatGlobalMmiolBase);
	printk(BIOS_DEBUG, "\tPlatGlobalMmiolLimit: 0x%x\n", hob->PlatformData.PlatGlobalMmiolLimit);
	printk(BIOS_DEBUG, "\tPlatGlobalMmiohBase: 0x%llx\n", hob->PlatformData.PlatGlobalMmiohBase);
	printk(BIOS_DEBUG, "\tPlatGlobalMmiohLimit: 0x%llx\n", hob->PlatformData.PlatGlobalMmiohLimit);
	printk(BIOS_DEBUG, "\tMemTsegSize: 0x%x\n", hob->PlatformData.MemTsegSize);
	printk(BIOS_DEBUG, "\tMemIedSize: 0x%x\n", hob->PlatformData.MemIedSize);
	printk(BIOS_DEBUG, "\tPciExpressBase: 0x%llx\n", hob->PlatformData.PciExpressBase);
	printk(BIOS_DEBUG, "\tPciExpressSize: 0x%x\n", hob->PlatformData.PciExpressSize);
	printk(BIOS_DEBUG, "\tMemTolm: 0x%x\n", hob->PlatformData.MemTolm);
	printk(BIOS_DEBUG, "\tnumofIIO: 0x%x\n", hob->PlatformData.numofIIO);
	printk(BIOS_DEBUG, "\tMaxBusNumber: 0x%x\n", hob->PlatformData.MaxBusNumber);
	printk(BIOS_DEBUG, "\tIoGranularity: 0x%x\n", hob->PlatformData.IoGranularity);
	printk(BIOS_DEBUG, "\tMmiolGranularity: 0x%x\n", hob->PlatformData.MmiolGranularity);
	printk(BIOS_DEBUG, "\tMmiohGranularity: hi: 0x%x, lo:0x%x\n", hob->PlatformData.MmiohGranularity.hi,
					hob->PlatformData.MmiohGranularity.lo);

	for (int s=0; s < hob->PlatformData.numofIIO; ++s) {
		printk(BIOS_DEBUG, "\t============ Socket %d Info ================\n", s);
		printk(BIOS_DEBUG, "\tSocketID: 0x%x\n", hob->PlatformData.IIO_resource[s].SocketID);
		printk(BIOS_DEBUG, "\tBusBase: 0x%x\n", hob->PlatformData.IIO_resource[s].BusBase);
		printk(BIOS_DEBUG, "\tBusLimit: 0x%x\n", hob->PlatformData.IIO_resource[s].BusLimit);
		printk(BIOS_DEBUG, "\tPciResourceIoBase: 0x%x\n", hob->PlatformData.IIO_resource[s].PciResourceIoBase);
		printk(BIOS_DEBUG, "\tPciResourceIoLimit: 0x%x\n", hob->PlatformData.IIO_resource[s].PciResourceIoLimit);
		printk(BIOS_DEBUG, "\tIoApicBase: 0x%x\n", hob->PlatformData.IIO_resource[s].IoApicBase);
		printk(BIOS_DEBUG, "\tIoApicLimit: 0x%x\n", hob->PlatformData.IIO_resource[s].IoApicLimit);
		printk(BIOS_DEBUG, "\tPciResourceMem32Base: 0x%x\n", hob->PlatformData.IIO_resource[s].PciResourceMem32Base);
		printk(BIOS_DEBUG, "\tPciResourceMem32Limit: 0x%x\n", hob->PlatformData.IIO_resource[s].PciResourceMem32Limit);
		printk(BIOS_DEBUG, "\tPciResourceMem64Base: 0x%llx\n", hob->PlatformData.IIO_resource[s].PciResourceMem64Base);
		printk(BIOS_DEBUG, "\tPciResourceMem64Limit: 0x%llx\n", hob->PlatformData.IIO_resource[s].PciResourceMem64Limit);

		printk(BIOS_DEBUG, "\t============ Stack Info ================\n");
		for (int x=0; x < MAX_IIO_STACK; ++x) {
			const STACK_RES *ri = &hob->PlatformData.IIO_resource[s].StackRes[x];
			printk(BIOS_DEBUG, "\t\t========== Stack %d ===============\n", x);
			printk(BIOS_DEBUG, "\t\tBusBase: 0x%x\n", ri->BusBase);
			printk(BIOS_DEBUG, "\t\tBusLimit: 0x%x\n", ri->BusLimit);
			printk(BIOS_DEBUG, "\t\tPciResourceIoBase: 0x%x\n", ri->PciResourceIoBase);
			printk(BIOS_DEBUG, "\t\tPciResourceIoLimit: 0x%x\n", ri->PciResourceIoLimit);
			printk(BIOS_DEBUG, "\t\tIoApicBase: 0x%x\n", ri->IoApicBase);
			printk(BIOS_DEBUG, "\t\tIoApicLimit: 0x%x\n", ri->IoApicLimit);
			printk(BIOS_DEBUG, "\t\tPciResourceMem32Base: 0x%x\n", ri->PciResourceMem32Base);
			printk(BIOS_DEBUG, "\t\tPciResourceMem32Limit: 0x%x\n", ri->PciResourceMem32Limit);
			printk(BIOS_DEBUG, "\t\tPciResourceMem64Base: 0x%llx\n", ri->PciResourceMem64Base);
			printk(BIOS_DEBUG, "\t\tPciResourceMem64Limit: 0x%llx\n", ri->PciResourceMem64Limit);
			printk(BIOS_DEBUG, "\t\tVtdBarAddress: 0x%x\n", ri->VtdBarAddress);
		}
	}
}
