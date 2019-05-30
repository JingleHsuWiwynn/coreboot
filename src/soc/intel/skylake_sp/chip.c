/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2015 - 2017 Intel Corp.
 * Copyright (C) 2017 Online SAS.
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

#include <arch/acpi.h>
#include <bootstate.h>
#include <cbfs.h>
#include <console/console.h>
#include <device/device.h>
#include <device/pci.h>
#include <fsp/api.h>
#include <fsp/util.h>
#include <intelblocks/fast_spi.h>
#include <soc/iomap.h>
#include <soc/intel/common/vbt.h>
#include <soc/pci_devs.h>
#include <soc/ramstage.h>
#include <spi-generic.h>
#include <soc/hob_mem.h>

#define DRV_IS_PCI_VENDOR_ID_INTEL 0x8086
#define VENDOR_ID_MSASK 0x0000FFFF
#define DEVICE_ID_MASK 0xFFFF00000
#define DEVICE_ID_BITSHIFT 16
#define PCI_ENABLE 0x80000000
#define FORM_PCI_ADDR(bus,dev,fun,off) (((PCI_ENABLE)) | \
		((bus & 0xFF) << 16)| \
		((dev & 0x1F) << 11)| \
		((fun & 0x07) << 8) | \
		((off & 0xFF) << 0))
#define SKYLAKE_SERVER_SOCKETID_UBOX_DID 0x2014
//the below LNID and GID applies to Skylake Server
#define UNC_SOCKETID_UBOX_LNID_OFFSET 0xC0
#define UNC_SOCKETID_UBOX_GID_OFFSET 0xD4

static void pci_domain_set_resources(struct device *dev)
{
	printk(BIOS_DEBUG, "^^^ ENTER %s:%d:%s (dev: %s)\n", __FILE__, __LINE__, __func__, dev_path(dev));
#if 0
	assign_resources(dev->link_list);
#endif
	printk(BIOS_DEBUG, "^^^ EXIT %s:%d:%s (dev: %s)\n", __FILE__, __LINE__, __func__, dev_path(dev));
}

static struct device_operations pci_domain_ops = {
	.read_resources = &pci_domain_read_resources,
	.set_resources = &pci_domain_set_resources,
	.scan_bus = &pci_domain_scan_bus,
};

static struct device_operations cpu_bus_ops = {
	.read_resources = DEVICE_NOOP,
	.set_resources = DEVICE_NOOP,
	.enable_resources = DEVICE_NOOP,
	.init = skylake_sp_init_cpus,
	.scan_bus = NULL,
#if IS_ENABLED(CONFIG_HAVE_ACPI_TABLES)
	.acpi_fill_ssdt_generator = generate_cpu_entries,
#endif
};

static void soc_enable_dev(struct device *dev)
{
	printk(BIOS_DEBUG, "^^^ ENTER %s:%d:%s (dev: %s)\n", __FILE__, __LINE__, __func__, dev_path(dev));
	/* Set the operations if it is a special bus type */
	if (dev->path.type == DEVICE_PATH_DOMAIN)
		dev->ops = &pci_domain_ops;
	else if (dev->path.type == DEVICE_PATH_CPU_CLUSTER)
		dev->ops = &cpu_bus_ops;
	printk(BIOS_DEBUG, "^^^ EXIT %s:%d:%s (dev: %s)\n", __FILE__, __LINE__, __func__, dev_path(dev));
}

static void soc_init(void *data)
{
	printk(BIOS_DEBUG, "^^^ ENTER %s:%d:%s\n", __FILE__, __LINE__, __func__);
	printk(BIOS_DEBUG, "coreboot: calling fsp_silicon_init\n");
	fsp_silicon_init(false);
	printk(BIOS_DEBUG, "coreboot: calling soc_save_dimm_info \n");
	soc_save_dimm_info();
	printk(BIOS_DEBUG, "^^^ EXIT %s:%d:%s\n", __FILE__, __LINE__, __func__);
}

static void soc_final(void *data) 
{
	printk(BIOS_DEBUG, "^^^ ENTER %s:%d:%s\n", __FILE__, __LINE__, __func__);
	u32 b1 = pci_mmio_read_config32(PCI_DEV(0, 8, 2), 0xcc);
	u32 b2 = pci_mmio_read_config32(PCI_DEV(0, 8, 2), 0xd0);
	//u32 bus0 = (b1 & 0xff);
	u32 bus1 = ((b1 >> 8) & 0xff);
	printk(BIOS_DEBUG, "[0xcc: 0x%x, 0xd0: 0x%x] bus0: 0x%x, bus1: 0x%x, bus2: 0x%x, bus3: 0x%x, bus4: 0x%x, bus5: 0x%x\n",
				 b1, b2, (b1 & 0xff), (b1 >> 8) & 0xff, (b1 >> 16) & 0xff, (b1 >> 24) & 0xff,
				 (b2 && 0xff), (b2 >> 8) & 0xff);

	u32 r = pci_mmio_read_config32(PCI_DEV(0, 8, 2), 0xd4);
	printk(BIOS_DEBUG, "busno valid: 0x%x\n", ((r & 0x80000000) >> 31));

#if 0
	/* MMCFG Target List */
	r = pci_mmio_read_config32(PCI_DEV(bus1, 29, 1), 0xec);
	for (int i=0; i<8; ++i) {
		u32 target = (r >> (i * 4)) & 0xf;
		u32 id = target & 0x8;
		if (id == 1)
			printk(BIOS_DEBUG, "MMCFG target for Package%d is local IIO Stack (0x%x)\n", i, target);
		else
			printk(BIOS_DEBUG, "MMCFG target for Package%d is Remote Socket with NodeID (0x%x)\n", i, target & 0x7);
	}

	/* MMCFG_LOCAL_RULE */
	r = pci_mmio_read_config32(PCI_DEV(bus1, 29, 1), 0xe4);
	for (int i=0; i<6; ++i) {
    printk(BIOS_DEBUG, "MMCFG LOCAL RULE for  Target physical stack ID for logical IIO Stack%d: 0x%x,", 
					 i, (r >> (i * 4)) & 0xf);
		if ((r >> (24 + i) & 0x1) == 0)
			printk(BIOS_DEBUG, "Send Root BUS with Device ID < 16 to the UBOX\n");
		else
			printk(BIOS_DEBUG, "Send Root BUS with all Device IDs to the UBOX\n");
	}
#endif

	/* MMCFG_LOCAL_RULE_ADDRESS_0 */
	r = pci_mmio_read_config32(PCI_DEV(bus1, 29, 1), 0xc8);
	for (int i=0; i<4; ++i) {
		u32 stack_id = 0;
		if (i > 1)
			stack_id = i-1;
		printk(BIOS_DEBUG, "IIO Stack %d Bus Limit 0x%x\n", stack_id, (r >> (i * 8)) & 0xff);
	}			

	/* MMCFG_LOCAL_RULE_ADDRESS_1 */
	r = pci_mmio_read_config32(PCI_DEV(bus1, 29, 1), 0xcc);
	for (int i=0; i<4; ++i) 
		printk(BIOS_DEBUG, "IIO Stack %d Bus Limit 0x%x\n", i+3, (r >> (i * 8)) & 0xff);

#if 0
	/* MMCFG_RULE */
	r = pci_mmio_read_config32(PCI_DEV(bus0, 8, 2), 0xdc);
	printk(BIOS_DEBUG, "[0x%x] MMCFG Enabled? %d, ", r, r & 0x1);
	u32 maxbusno = ((r >> 1) & 0x3);
	switch (maxbusno) {
		case 0:
			printk(BIOS_DEBUG, "Max Bus Number 255 (>= 256MB)\n");
			break;
		case 1:
			printk(BIOS_DEBUG, "Max Bus Number 127 (>= 128MB)\n");
			break;
		case 2:
			printk(BIOS_DEBUG, "Max Bus Number 63 (>= 64MB)\n");
			break;
		default:
			printk(BIOS_DEBUG, "Invalid Max Bus Number 0x%x\n", maxbusno);
	}

	/* MMCFG base address */
	r = pci_mmio_read_config32(PCI_DEV(bus1, 29, 1), 0xc0);
	printk(BIOS_DEBUG, "[0x%x] MMCFG_Rule Enabled? %d Valid Targets 0x%x, ",
				 r, r & 0x1, (r >> 6) & 0xff);
	maxbusno = (r >> 1) & 0x7;
	switch (maxbusno) {
	  case 0:
      printk(BIOS_DEBUG, "Max Bus Number 2048 (2GB MMCFG Range)\n");
      break;
    case 1:
      printk(BIOS_DEBUG, "Max Bus Number 1048 (1GB MMCFG range)\n");
      break;
    case 2:
      printk(BIOS_DEBUG, "Max Bus Number 512 (512MB MMCFG range)\n");
      break;
    case 4:
      printk(BIOS_DEBUG, "Max Bus Number 256 (256MB MMCFG range)\n");
      break;
    case 5:
      printk(BIOS_DEBUG, "Max Bus Number 127 (128MB MMCFG range)\n");
      break;
    case 6:
      printk(BIOS_DEBUG, "Max Bus Number 63 (64MB MMCFG range)\n");
      break;
    default:
			printk(BIOS_DEBUG, "Invalid Max Bus Number 0x%x\n", maxbusno);
			break;
	}

	u32 r2 = pci_mmio_read_config32(PCI_DEV(bus1, 29, 1), 0xc4);
	u64 addr = r2;
	addr = (addr << 32) | (r & 0xfc000000);
	printk(BIOS_DEBUG, "[r: 0x%x, r2: 0x%x] MMCFG_Rule Base Address: 0x%llx\n", r, r2, addr);
	
	/* MMIO_RULE_CFG_ */
	for (int i=0; i < 16; ++i) {
		r =  pci_mmio_read_config32(PCI_DEV(bus1, 29, 1), (0x40+(i*4)));
		r2 =  pci_mmio_read_config32(PCI_DEV(bus1, 29, 1), (0x40+(i*4)+4));
		u32 rule_enable = (r & 0x1);
		u32 base_addr = (r >> 1) & 0xfffff;
		u32 limit_addr = ((r2 & 0x3fff) << 6) | ((r >> 26) & 0x3f);
		if (rule_enable)
			printk(BIOS_DEBUG, "MMIO_RULE_CFG_%d [0x%x%x] rule_enable: %d, base_addr: 0x%x, limit_addr: 0x%x\n",
						 i, r2, r, rule_enable, base_addr, limit_addr);
	}

	/* MMIO_Target_LIST_CFG_0 */
  r = pci_mmio_read_config32(PCI_DEV(bus1, 29, 1), 0xe8);
  for (int i=0; i<8; ++i) {
    u32 target = (r >> (i * 4)) & 0xf;
		u32 id = target & 0x8;
		if (id == 1)
      printk(BIOS_DEBUG, "MMIO target for Package%d is local IIO Stack (0x%x)\n", i, target);
		else
      printk(BIOS_DEBUG, "MMIO target for Package%d is Remote Socket with NodeID (0x%x)\n", i, target & 0x7);
  }

	/* MMIO_Target_Interleave_LIST_CFG_ */
	for (int t=0; t < 4; ++t) {
	  r = pci_mmio_read_config32(PCI_DEV(bus1, 29, 1), 0x204 + (t * 4));
		for (int i=0; i<8; ++i) {
			u32 target = (r >> (i * 4)) & 0xf;
			u32 id = target & 0x8;
			if (id == 1)
				printk(BIOS_DEBUG, "MMIO CFG %d Interleave target for Package%d is local IIO Stack (0x%x)\n", t, i, target);
			else
				printk(BIOS_DEBUG, "MMIO CFG %d Interleave target for Package%d is Remote Socket with NodeID (0x%x)\n", t, i, target & 0x7);
		}
	}

	/* MMIOH_INTERLEAVE_RULE */
	r =  pci_mmio_read_config32(PCI_DEV(bus1, 29, 1), 0x100);
	r2 =  pci_mmio_read_config32(PCI_DEV(bus1, 29, 1), 0x104);
	u32 rule_enable = (r & 0x1);
	u32 base_addr = (r >> 1) & 0xfffff;
	u32 limit_addr = ((r2 & 0x3fff) << 6) | ((r >> 26) & 0x3f);
	printk(BIOS_DEBUG, "MMIOH_INTERLEAVE_RULE [0x%x%x] rule_enable: %d, base_addr: 0x%x, limit_addr: 0x%x, ",
				 r2, r, rule_enable, base_addr, limit_addr);
	/* 48:46 Interleave mode i.e. 16:14 */
	u32 interleave_mode = (r2 >> 14) & 0x7;
	switch (interleave_mode) {
		case 0:
			printk(BIOS_DEBUG, "Interleave_Mode is 1G\n"); break;
		case 1:
			printk(BIOS_DEBUG, "Interleave_Mode is 4G\n"); break;
		case 2:
			printk(BIOS_DEBUG, "Interleave_Mode is 16G\n"); break;
		case 3:
			printk(BIOS_DEBUG, "Interleave_Mode is 64G\n"); break;
		case 4:
			printk(BIOS_DEBUG, "Interleave_Mode is 256G\n"); break;
		case 5:
			printk(BIOS_DEBUG, "Interleave_Mode is 1024G\n"); break;
		default:
			printk(BIOS_DEBUG, "Invalid Interleave_Mode 0x%x\n", interleave_mode); break;
	}

	/* MMIOH_NONINTERLEAVE_RULE */
	r =  pci_mmio_read_config32(PCI_DEV(bus1, 29, 1), 0x108);
	r2 =  pci_mmio_read_config32(PCI_DEV(bus1, 29, 1), 0x10c);
	rule_enable = (r & 0x1);
	base_addr = (r >> 1) & 0xfffff;
	limit_addr = ((r2 & 0x3fff) << 6) | ((r >> 26) & 0x3f);
	printk(BIOS_DEBUG, "MMIOH_NONINTERLEAVE_RULE [0x%x%x] rule_enable: %d, base_addr: 0x%x, limit_addr: 0x%x, ",
				 r2, r, rule_enable, base_addr, limit_addr);
	/* 48:46 Interleave mode i.e. 16:14 */
	u32 target = (r2 >> 14) & 0xf;
	u32 id = target & 0x8;
	if (id == 1)
		printk(BIOS_DEBUG, "Target is local IIO Stack 0x%x\n", (target & 0x7));
	else
		printk(BIOS_DEBUG, "Target is remote socket with NodeID 0x%x\n", (target & 0x7));

	for (int bus_no = 0; bus_no < 256; bus_no++) {
		for (int device_no = 0; device_no < 32; device_no++) {
			for (int function_no = 0; function_no < 8; function_no++) {
				/* find bus, device, and function number for socket ID UBOX device */
				u16 vendor_id = pci_mmio_read_config16(PCI_DEV(bus_no, device_no, function_no), 0);
				u16 device_id = pci_mmio_read_config16(PCI_DEV(bus_no, device_no, function_no), 2);
				if (vendor_id != 0xffff && device_id != 0xffff && vendor_id != 0 && device_id != 0) {
					printk(BIOS_DEBUG, "bus_no: 0x%x, device_no: 0x%x, function_no: 0x%x, vendor_id: 0x%x, device_id: 0x%x",
								 bus_no, device_no, function_no, vendor_id, device_id);
					for (int b=0; b < 6; ++b) {
						u32 bar = pci_mmio_read_config32(PCI_DEV(bus_no, device_no, function_no), (0x10 + (b * 4)));
						printk(BIOS_DEBUG, ", bar%d: 0x%x", b, bar);
					}
					printk(BIOS_DEBUG, "\n");
				}
				if (vendor_id != DRV_IS_PCI_VENDOR_ID_INTEL) {
					continue;
				}
				if (device_id == SKYLAKE_SERVER_SOCKETID_UBOX_DID) {
					/* first get node id for the local socket */
					r = pci_mmio_read_config32(PCI_DEV(bus_no, device_no, function_no), UNC_SOCKETID_UBOX_LNID_OFFSET);
					u32 nodeid = r & 0x00000007;
					/*
					 * Every 3b of the Node ID mapping register maps to a specific node
					 * Read the Node ID Mapping Register and find the node that matches
					 * the gid read from the Node ID configuration register (above).
					 * e.g. Bits 2:0 map to node 0, bits 5:3 maps to package 1, etc.
					 */
					u32 mapping = pci_mmio_read_config32(PCI_DEV(bus_no, device_no, function_no), UNC_SOCKETID_UBOX_GID_OFFSET);
					u32 gid = 0;
					for (int i = 0; i < 8; i++){
						if (nodeid == ((mapping >> (3 * i)) & 0x7)) {
							gid = i;
							break;
						}
					}
					printk(BIOS_DEBUG, "Found UBOX bus_no: 0x%x, device_no: 0x%x, function_no: 0x%x, gid: 0x%x\n", bus_no, device_no,
								 function_no, gid);
					/*
					 * scan all devices 256, get bus for Ubox
					 *		nodeid from (B: <above bus>, D:8, F:0, 0:0xc0)
					 *    cpubusnos from (B: <above bus>, D:8, F:2, O:0xcc, 0xd0)
					 *    get this nodeid stack limits [0-5] (B:<CPUBUSNO1 above>, D:29, F:1, 0:0xc8, 0xcc)
					 * 
					 */
					b1 = pci_mmio_read_config32(PCI_DEV(bus_no, 8, 2), 0xcc);
					b2 = pci_mmio_read_config32(PCI_DEV(bus_no, 8, 2), 0xd0);
					bus1 = ((b1 >> 8) & 0xff);

					/* MMCFG_LOCAL_RULE_ADDRESS_0 */
					r = pci_mmio_read_config32(PCI_DEV(bus1, 29, 1), 0xc8);
					for (int i=0; i<4; ++i) {
						if (i == 0) continue;
						u32 stack_id = i-1;
						u32 start_busno = ((b1 >> (stack_id * 8)) & 0xff);
						printk(BIOS_DEBUG, "IIO Stack %d Bus [0x%x : 0x%x]\n", stack_id, start_busno, (r >> (i * 8)) & 0xff);
					}

					/* MMCFG_LOCAL_RULE_ADDRESS_1 */
					r = pci_mmio_read_config32(PCI_DEV(bus1, 29, 1), 0xcc);
					for (int i=0; i<4; ++i) {
						u32 stack_id = i+3;
						u32 start_busno;
						if (i == 0) 
							start_busno = ((b1 >> (stack_id * 8)) & 0xff);	
						else
							start_busno = ((b2 >> ((i-1) * 8)) & 0xff);
						printk(BIOS_DEBUG, "IIO Stack %d Bus [0x%x : 0x%x]\n", stack_id, start_busno, (r >> (i * 8)) & 0xff);
					}
				}
			}
		}
	}
#endif

	printk(BIOS_DEBUG, "^^^ EXIT %s:%d:%s\n", __FILE__, __LINE__, __func__);
}

static void soc_silicon_init_params(FSPS_UPD *silupd)
{
	printk(BIOS_DEBUG, "^^^ ENTER %s:%d:%s\n", __FILE__, __LINE__, __func__);
	printk(BIOS_DEBUG, "^^^ EXIT %s:%d:%s\n", __FILE__, __LINE__, __func__);
}

void platform_fsp_silicon_init_params_cb(FSPS_UPD *silupd)
{
	const struct microcode *microcode_file;
	size_t microcode_len;

	printk(BIOS_DEBUG, "^^^ ENTER %s:%d:%s\n", __FILE__, __LINE__, __func__);
	microcode_file = cbfs_boot_map_with_leak("cpu_microcode_blob.bin",
		CBFS_TYPE_MICROCODE, &microcode_len);

	if ((microcode_file != NULL) && (microcode_len != 0)) {
		/* Update CPU Microcode patch base address/size */
		silupd->FspsConfig.PcdCpuMicrocodePatchBase =
		       (uint32_t)microcode_file;
		silupd->FspsConfig.PcdCpuMicrocodePatchSize =
		       (uint32_t)microcode_len;
	}

	printk(BIOS_DEBUG, "platform_fsp_silicon_init_params_cb calling soc_silicon_init_params\n");
	soc_silicon_init_params(silupd);
	printk(BIOS_DEBUG, "platform_fsp_silicon_init_params_cb calling mainboard_silicon_init_params\n");
	mainboard_silicon_init_params(silupd);
	printk(BIOS_DEBUG, "^^^ EXIT %s:%d:%s\n", __FILE__, __LINE__, __func__);
}

struct chip_operations soc_intel_skylake_sp_ops = {
	CHIP_NAME("Intel Skylake-SP SOC")
	.enable_dev = soc_enable_dev,
	.init = soc_init,
	.final = soc_final
};

static void soc_set_subsystem(struct device *dev, uint32_t vendor,
			      uint32_t device)
{
	printk(BIOS_DEBUG, "^^^ ENTER %s:%d:%s (dev: %s)\n", __FILE__, __LINE__, __func__, dev_path(dev));
	if (!vendor || !device) {
		pci_write_config32(dev, PCI_SUBSYSTEM_VENDOR_ID,
				   pci_read_config32(dev, PCI_VENDOR_ID));
	} else {
		pci_write_config32(dev, PCI_SUBSYSTEM_VENDOR_ID,
				   ((device & 0xffff) << 16) |
					   (vendor & 0xffff));
	}
	printk(BIOS_DEBUG, "^^^ EXIT %s:%d:%s (dev: %s)\n", __FILE__, __LINE__, __func__, dev_path(dev));
}

struct pci_operations soc_pci_ops = {
	.set_subsystem = soc_set_subsystem,
};

/*
 * spi_flash init() needs to run unconditionally on every boot (including
 * resume) to allow write protect to be disabled for eventlog and nvram
 * updates. This needs to be done as early as possible in ramstage. Thus, add a
 * callback for entry into BS_PRE_DEVICE.
 */
static void spi_flash_init_cb(void *unused)
{
	printk(BIOS_DEBUG, "^^^ ENTER %s:%d:%s\n", __FILE__, __LINE__, __func__);
	fast_spi_init();
	printk(BIOS_DEBUG, "^^^ EXIT %s:%d:%s\n", __FILE__, __LINE__, __func__);
}

BOOT_STATE_INIT_ENTRY(BS_PRE_DEVICE, BS_ON_ENTRY, spi_flash_init_cb, NULL);
