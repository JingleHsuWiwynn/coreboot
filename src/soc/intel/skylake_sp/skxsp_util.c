/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2014 - 2019 Intel Corporation.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <stdint.h>
#include <console/console.h>
#include <arch/io.h>
#include <device/pci_ops.h>
#include <device/pci.h>
#include <device/pci_def.h>
#include <device/device.h>
#include <soc/skxsp_util.h>
#include <soc/pci_devs.h>

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

/*
 * Get TOLM CSR B0:D5:F0:Offset_d0h
 */
uintptr_t get_tolm(u32 bus)
{
  u32 w = pci_read_csr32(bus, SKXSP_VTD_DEV, SKXSP_VTD_FUNC, SKXSP_VTD_TOLM_CSR);
  uintptr_t addr =  w & 0xfc000000;
  printk(BIOS_DEBUG, "SKXSP_VTD_TOLM_CSR 0x%x, addr: 0x%lx\n", w, addr);
  return addr;
}

void get_tseg_base_lim(u32 bus, u32 *base, u32 *limit)
{
  u32 w1 = pci_read_csr32(bus, SKXSP_VTD_DEV, SKXSP_VTD_FUNC, SKXSP_VTD_TSEG_BASE_CSR);
  u32 wh = pci_read_csr32(bus, SKXSP_VTD_DEV, SKXSP_VTD_FUNC, SKXSP_VTD_TSEG_LIMIT_CSR);
  *base = w1 & 0xfff00000;
  *limit = wh & 0xfff00000;
}

/*
 * Get MMCFG CSR B1:D29:F1:Offset_C0h
 */
uintptr_t get_cha_mmcfg_base(u32 bus)
{
  u32 wl = pci_read_csr32(bus, CHA_UTIL_ALL_DEV, CHA_UTIL_ALL_FUNC, CHA_UTIL_ALL_MMCFG_CSR);
  u32 wh = pci_read_csr32(bus, CHA_UTIL_ALL_DEV, CHA_UTIL_ALL_FUNC, CHA_UTIL_ALL_MMCFG_CSR + 4);
  uintptr_t addr = ((((wh & 0x3fff) << 6) | ((wl >> 26) & 0x3f)) << 26);
  printk(BIOS_DEBUG, "CHA_UTIL_ALL_MMCFG_CSR wl: 0x%x, wh: 0x%x, addr: 0x%lx\n", wl, wh, addr);
  return addr;
}

/*
 * Get Socket 0 CPUBUSNO(0), CPUBUSNO(1) PCI bus numbers UBOX (B0:D8:F2:Offset_CCh)
 * TODO: D0h
 */
void get_cpubusnos(u32 *bus0, u32 *bus1, u32 *bus2, u32 *bus3)
{
  u32 bus =  pci_read_csr32(UBOX_DECS_BUS, UBOX_DECS_DEV, UBOX_DECS_FUNC, UBOX_DECS_CPUBUSNO_CSR);
  if (bus0)
    *bus0 = (bus & 0xff);
  if (bus1)
    *bus1 = (bus >> 8) & 0xff;
  if (bus2)
    *bus2 = (bus >> 16) & 0xff;
  if (bus3)
    *bus3 = (bus >> 24) & 0xff;
}

u32 pci_read_csr32(u32 bus, u32 dev, u32 func, u32 reg)
{
  //outl(0x80000000 | bus << 16 | dev << 11 | func << 8 | (reg & 0xfc), 0xcf8);
  outl(CONFIG_MMCONF_BASE_ADDRESS | bus << 16 | dev << 11 | func << 8 | (reg & 0xfc), 0xcf8);
  return inl(0xcfc);
}

void pci_write_csr32(u32 bus, u32 dev, u32 func, u32 reg, u32 val)
{
  outl(0x80000000 | bus << 16 | dev << 11 | func << 8 | (reg & 0xfc), 0xcf8);
	outl(val, 0xcfc);
}

u32 pci_read_mmio_reg(int bus, u32 dev, u32 func, int offset)
{
	/*
		uintptr_t loc = DEFAULT_PCIEXBAR + (bus*32*8*0x1000) + (dev*8*0x1000) + (func * 0x1000);
		printk(BIOS_DEBUG, "map for [bus: %d, device: %d, func: %d] => loc: %p\n", bus, dev, func, (void *)loc);
		u32 val = *((u32 *)(loc + offset));
		printk(BIOS_DEBUG, "\tvalue for offset 0x%x is 0x%x\n", offset, val);
	*/
	return pci_mmio_read_config32(PCI_DEV(bus, dev, func), offset);
}

void debug_pci_scan_buses(void)
{
	/*
   * 256 buses × 32 devices × 8 functions × 4 KiB = 256 MiB
   * Each socket takes 32 buses = 256/<8 sockets> = 32
   */

  for (int bus = 0; bus < 256; ++bus) {
    for (int dev=0; dev < 32; ++dev) {
      for (int fun=0; fun < 8; ++fun) {
        uintptr_t loc = DEFAULT_PCIEXBAR + (bus*32*8*0x1000) + (dev*8*0x1000) + (fun * 0x1000);
        if ((u32) *((u32 *)loc) != 0xffffffff)
          printk(BIOS_DEBUG, "[bus: %d, device: %d, func: %d], addr: 0x%lx, val: 0x%x\n", 
								 bus, dev, fun, loc, (u32) *((u32 *)loc));
      }
    }
  }
}

/* bus needs to be of size 6 (MAX_IIO_STACK) */
void get_stack_busnos(u32 *bus)
{
  u32 reg1, reg2;

  reg1 = pci_mmio_read_config32(PCI_DEV(UBOX_DECS_BUS, UBOX_DECS_DEV, UBOX_DECS_FUNC), 0xcc);
  reg2 = pci_mmio_read_config32(PCI_DEV(UBOX_DECS_BUS, UBOX_DECS_DEV, UBOX_DECS_FUNC), 0xd0);

  for (int i=0; i < 4; ++i)
    bus[i] = ((reg1 >> (i * 8)) & 0xff);
  for (int i=0; i < 2; ++i)
    bus[4+i] = ((reg2 >> (i * 8)) & 0xff);
}

void dump_iio_stack_basic(void)
{
	u32 bus[MAX_IIO_STACK];
	
	get_stack_busnos(bus);
	for (int i=0; i < MAX_IIO_STACK; ++i) 
		printk(BIOS_DEBUG, "IIO STACK %i bus 0x%x\n", i, bus[i]);

	u32 r = pci_mmio_read_config32(PCI_DEV(UBOX_DECS_BUS, UBOX_DECS_DEV, UBOX_DECS_FUNC), 0xd4);
	printk(BIOS_DEBUG, "busno valid: 0x%x\n", ((r & 0x80000000) >> 31));

	/* MMCFG_LOCAL_RULE_ADDRESS_0 */
	r = pci_mmio_read_config32(PCI_DEV(bus[1], CHA_UTIL_ALL_DEV, CHA_UTIL_ALL_FUNC), 0xc8);
	for (int i=0; i<4; ++i) {
		u32 stack_id = 0;
		if (i > 1)
			stack_id = i-1;
		printk(BIOS_DEBUG, "IIO Stack %d Bus Limit 0x%x\n", stack_id, (r >> (i * 8)) & 0xff);
	}			

	/* MMCFG_LOCAL_RULE_ADDRESS_1 */
	r = pci_mmio_read_config32(PCI_DEV(bus[1], CHA_UTIL_ALL_DEV, CHA_UTIL_ALL_FUNC), 0xcc);
	for (int i=0; i<4; ++i) 
		printk(BIOS_DEBUG, "IIO Stack %d Bus Limit 0x%x\n", i+3, (r >> (i * 8)) & 0xff);
}

void dump_iio_stack_detailed(void)
{
	u32 b1 = pci_mmio_read_config32(PCI_DEV(0, 8, 2), 0xcc);
	u32 b2 = pci_mmio_read_config32(PCI_DEV(0, 8, 2), 0xd0);
	u32 bus0 = (b1 & 0xff);
	u32 bus1 = ((b1 >> 8) & 0xff);
	printk(BIOS_DEBUG, "[0xcc: 0x%x, 0xd0: 0x%x] bus0: 0x%x, bus1: 0x%x, bus2: 0x%x, bus3: 0x%x, bus4: 0x%x, bus5: 0x%x\n",
				 b1, b2, (b1 & 0xff), (b1 >> 8) & 0xff, (b1 >> 16) & 0xff, (b1 >> 24) & 0xff,
				 (b2 && 0xff), (b2 >> 8) & 0xff);

	u32 r = pci_mmio_read_config32(PCI_DEV(0, 8, 2), 0xd4);
	printk(BIOS_DEBUG, "busno valid: 0x%x\n", ((r & 0x80000000) >> 31));

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
}

void unlock_pam_regions(void)
{
	u32 bus1 = 0;
	u32 pam0123_unlock_dram = 0x33333330;
	u32 pam456_unlock_dram = 0x00333333;

  get_cpubusnos(NULL, &bus1, NULL, NULL);
	pci_write_csr32(bus1, SKXSP_SAD_ALL_DEV, SKXSP_SAD_ALL_FUNC, SKXSP_SAD_ALL_PAM0123_CSR, pam0123_unlock_dram);
	pci_write_csr32(bus1, SKXSP_SAD_ALL_DEV, SKXSP_SAD_ALL_FUNC, SKXSP_SAD_ALL_PAM456_CSR, pam456_unlock_dram);

	u32 reg1 = pci_read_csr32(bus1, SKXSP_SAD_ALL_DEV, SKXSP_SAD_ALL_FUNC, SKXSP_SAD_ALL_PAM0123_CSR);
	u32 reg2 = pci_read_csr32(bus1, SKXSP_SAD_ALL_DEV, SKXSP_SAD_ALL_FUNC, SKXSP_SAD_ALL_PAM456_CSR);
	printk(BIOS_DEBUG, "%s:%s pam0123_csr: 0x%x, pam456_csr: 0x%x\n", __FILE__, __func__, reg1, reg2);
}
