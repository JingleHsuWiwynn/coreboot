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

#include <console/console.h>
#include <device/device.h>
#include <device/pci.h>
#include <intelblocks/cpulib.h>
#include <intelblocks/p2sb.h>
#include <intelblocks/lpc_lib.h>
#include <intelblocks/itss.h>
#include <reg_script.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <bootstate.h>
#include <assert.h>
#include <stdint.h>
#include <console/console.h>
#include <device/device.h>
#include <device/pci_ids.h>
#include <device/pci_ops.h>
#include <device/pci.h>
#include <device/pci_def.h>
#include <cpu/cpu.h>
#include <cpu/x86/msr.h>
#include <cpu/x86/mtrr.h>
#include <cpu/x86/cache.h>
#include <cpu/x86/lapic.h>
#include <cpu/x86/name.h>
#include <cpu/x86/mp.h>
#include <cpu/intel/turbo.h>
#include <arch/acpi.h>
#include <arch/io.h>
#include <memrange.h>
#include <soc/msr.h>
#include <soc/cpu.h>
#include <soc/iomap.h>
#include <soc/hob_mem.h>
#include <soc/hob_iiouds.h>
#include <soc/hob_memorymapdata.h>
#include <soc/soc_util.h>
#include <soc/skxsp_util.h>
#include <soc/pci_devs.h>
#include <soc/pcr_ids.h>
#include <soc/pcr.h>
#include <soc/p2sb.h>
#include <soc/acpi.h>
#include <soc/irq.h>
#include <commonlib/sort.h>


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

static void get_cpu_info(unsigned int *core_count, unsigned int *thread_count)
{
	register int ecx = 0;
	struct cpuid_result leaf_b;
	struct cpuid_result cpuid_regs;
	uint32_t max_cpu_index;
	uint64_t apic_base;
  msr_t msr;

  unsigned int num_virt_cores, num_phys_cores;

  cpu_read_topology(&num_phys_cores, &num_virt_cores);
  msr = rdmsr(MSR_CORE_THREAD_COUNT);
  num_virt_cores = (msr.lo >> 0) & 0xffff;
  num_phys_cores = (msr.lo >> 16) & 0xffff;
  printk(BIOS_DEBUG, "Detected %u core, %u thread CPU.\n",
         num_phys_cores, num_virt_cores);

	/* get max index of CPUID */
  cpuid_regs = cpuid(0);
	max_cpu_index = cpuid_regs.eax;
	printk(BIOS_DEBUG, "maximum input value for cpuid 0x%x\n", max_cpu_index);
	assert (max_cpu_index >= 0xb);

	/* get apic mode */
  msr = rdmsr(LAPIC_BASE_MSR); /* LAPIC_BASE_MSR 0x1B */
	apic_base = (((uint64_t)msr.hi & 0x00003fff) << 32) | (msr.lo & 0xfffff000);
	printk(BIOS_DEBUG, "LAPIC_BASE_MSR hi: 0x%x, lo: 0x%x, apic_base: 0x%llx, LAPIC_DEFAULT_BASE: 0x%x\n",
				 msr.hi, msr.lo, apic_base, LAPIC_DEFAULT_BASE);
	printk(BIOS_DEBUG, "LAPICID: 0x%lx\n", lapicid());

	/*
		CPUID.(EAX=0Bh, ECX=0h):EAX[4:0] = 1, shift 1 bit to get Core level of APIC ID
		from Thread level (ECX input =0). (ThreatBits = 1)
		CPUID.(EAX=0Bh, ECX=1h):EAX[4:0] = 6, shift 6 bits to get Socket level of APIC
		ID from Core level (ECX input =1) (CoreBits = 6 - 1 = 5)
	*/
	while (1) {
		leaf_b = cpuid_ext(0xb, ecx);
		printk(BIOS_DEBUG, "APICIdShift - EAX[4:0]: 0x%x, LogicalProcessors - EBX[15:0]: 0x%x, "
					 "LevelNumber - ECX[7:0]: 0x%x, LevelType - ECX[15:8]: 0x%x, x2APIC_ID - EDX[31:0]: 0x%x\n",
					 (leaf_b.eax & 0x1f), (leaf_b.ebx & 0xffff), (leaf_b.ecx & 0xff), ((leaf_b.ecx >> 8) & 0xff),
					 (leaf_b.edx & 0xffffffff));
		if (ecx == 0) {
			if ((leaf_b.ebx & 0xffff) != 0)
				printk(BIOS_DEBUG, "Initial APICID: 0x%x\n", leaf_b.edx);
		}

		/* Processor doesn't have hyperthreading so just determine the
		* number of cores by from level type (ecx[15:8] == * 2). */
		if ((leaf_b.ecx & 0xff00) == 0x0200)
			break;
		ecx++;
	}

	*core_count = num_phys_cores;
	*thread_count = num_virt_cores;
}

void get_core_thread_bits(uint32_t *core_bits, uint32_t *thread_bits)
{
	register int ecx;
	struct cpuid_result cpuid_regs;

	/* get max index of CPUID */
  cpuid_regs = cpuid(0);
	assert (cpuid_regs.eax >= 0xb); /* cpuid_regs.eax is max input value for cpuid */

	*thread_bits = *core_bits = 0;
	ecx = 0;
	while (1) {
		cpuid_regs = cpuid_ext(0xb, ecx);
		if (ecx == 0) {
			*thread_bits = (cpuid_regs.eax & 0x1f);
		}
		else {
			*core_bits = (cpuid_regs.eax & 0x1f) - *thread_bits;
			break;
		}
		ecx++;
	}
}

void get_cpu_info_from_apicid(uint32_t apicid, uint32_t core_bits, uint32_t thread_bits,
 														  uint8_t *package, uint8_t *core, uint8_t *thread)
{
	if (package != NULL)
		*package = (apicid >> (thread_bits + core_bits));
	if (core != NULL)
		*core = (uint32_t)((apicid >> thread_bits) & ~((~0) << core_bits));
	if (thread != NULL)
		*thread = (uint32_t)(apicid & ~((~0) << thread_bits));
}

int get_cpu_count(void)
{
  size_t hob_size;
  const uint8_t fsp_hob_iio_universal_data_guid[16] = FSP_HOB_IIO_UNIVERSAL_DATA_GUID;
  const IIO_UDS *hob;

	/* these fields are incorrect - need debugging */
  hob = fsp_find_extension_hob_by_guid(fsp_hob_iio_universal_data_guid, &hob_size);
  assert(hob != NULL && hob_size != 0);
	return hob->SystemStatus.numCpus;
}

int get_threads_per_package(void)
{
	unsigned int core_count, thread_count;
	get_cpu_info(&core_count, &thread_count);
	return thread_count;
}

int get_platform_thread_count(void)
{
	return get_cpu_count() * get_threads_per_package();
}

void dump_pch_int_regs(const char *header)
{
	/*
   * Refer to C620 P2SB for PID_ITSS Table 36-10.Private Configuration Space Register Target Port IDs
   * Processor Interface, 8254 Timer, HPET, APIC 0xC4
   * PID_ITSS is 0xC4
   */
	printk(BIOS_DEBUG, "%s\n", header);
	printk(BIOS_DEBUG, "\tP2SB Target Port ID 0x%x\n", PID_ITSS);

	printk(BIOS_DEBUG, "\tPIRQ[A-H] Routing Control Data\n");
  for (int i=0; i < MAX_PXRC_CONFIG; ++i) {
		uint16_t reg = (PCR_ITSS_PIRQA_ROUT + (i * sizeof(uint8_t)));
		void *addr = (void *) PCH_PCR_ADDRESS(PID_ITSS, reg);
    uint8_t val = read8(addr);
    printk(BIOS_DEBUG, "\t\tpirq_reg: x%x, addr: 0x%p, val: 0x%x\n", reg, addr, val);
  }

	printk(BIOS_DEBUG, "\tPIR[0-4] PCI Interrupt Route Data\n");
	for (int i=0; i < 5; ++i) {
		uint16_t reg = (PCR_ITSS_PIR00 + (i * sizeof(uint16_t)));
		void *addr = (void *) PCH_PCR_ADDRESS(PID_ITSS, reg);
		uint16_t val = read16(addr);
		printk(BIOS_DEBUG, "\t\tpir_reg: x%x, addr: 0x%p, val: 0x%x", reg, addr, val);
		for (int p=0; p < 4; ++p) {
			char intn = 'A' + p;
			uint8_t pir = (val >> (p*4)) & 0x3;
			char pin = 'A' + pir;
			printk(BIOS_DEBUG, ", INT%c => PIRQ%c", intn, pin);
		}
		printk(BIOS_DEBUG, "\n");
	}

	printk(BIOS_DEBUG, "\tIPC[0-3] Interrupt Polarity Control Data\n");
	for (int i=0; i < 4; ++i) {
		uint16_t reg = (PCH_PCR_ITSS_IPC0 + (i * sizeof(uint32_t)));
		void *addr = (void *) PCH_PCR_ADDRESS(PID_ITSS, reg);
		uint32_t val = read32(addr);
    printk(BIOS_DEBUG, "\t\tipc_reg: x%x, addr: 0x%p, val: 0x%x\n", reg, addr, val);
	}
}

void get_iiostack_info(struct iiostack_resource *info)
{
	size_t hob_size;
	u8 stack_no;
	const uint8_t fsp_hob_iio_universal_data_guid[16] = FSP_HOB_IIO_UNIVERSAL_DATA_GUID;
  const IIO_UDS *hob;

	memset(info, 0, sizeof(struct iiostack_resource));

	hob = fsp_find_extension_hob_by_guid(
                          fsp_hob_iio_universal_data_guid,
                          &hob_size);
  assert(hob != NULL && hob_size != 0);

	// find out total number of stacks
	info->no_of_stacks = 0;
	info->sres = NULL;
	for (int s=0; s < hob->PlatformData.numofIIO; ++s) {
		for (int x=0; x < MAX_IIO_STACK; ++x) {
			const STACK_RES *ri = &hob->PlatformData.IIO_resource[s].StackRes[x];
			if (ri->BusBase < ri->BusLimit) // TODO: do we have situation with only bux 0 and one stack?
				++info->no_of_stacks;
		}
	}
	assert(info->no_of_stacks > 0);

	// allocate and copy stack info from FSP HOB
	info->sres = malloc(info->no_of_stacks * sizeof(STACK_RES));
	if (info->sres == 0)
		die("build_stack_info(): out of memory.\n");
	memset(info->sres, 0, info->no_of_stacks * sizeof(STACK_RES));

	stack_no = 0;
  for (int s=0; s < hob->PlatformData.numofIIO; ++s) {
    for (int x=0; x < MAX_IIO_STACK; ++x) {
      const STACK_RES *ri = &hob->PlatformData.IIO_resource[s].StackRes[x];
			if (ri->BusBase < ri->BusLimit) // TODO: do we have situation with only bux 0 and one stack?
				memcpy(&info->sres[stack_no++], ri, sizeof(STACK_RES));
    }
  }
}

#if ENV_RAMSTAGE

void xeonsp_init_cpu_config(void)
{
	struct device *dev;
	int apic_ids[CONFIG_MAX_CPUS] = {0}, apic_ids_by_thread[CONFIG_MAX_CPUS] = {0}, num_apics = 0;
	uint32_t core_bits, thread_bits;
	unsigned int core_count, thread_count;
	unsigned int num_cpus;

	/* sort APIC ids in asending order to identify apicid ranges for
     each numa domain
   */
  for (dev = all_devices; dev; dev = dev->next) {
    if ((dev->path.type != DEVICE_PATH_APIC) ||
      (dev->bus->dev->path.type != DEVICE_PATH_CPU_CLUSTER)) {
      continue;
    }
    if (!dev->enabled)
      continue;
    if (num_apics >= ARRAY_SIZE(apic_ids))
      break;
    apic_ids[num_apics++] = dev->path.apic.apic_id;
  }
  if (num_apics > 1)
    bubblesort(apic_ids, num_apics, NUM_ASCENDING);

  num_cpus = get_cpu_count();
  get_cpu_info(&core_count, &thread_count);
	assert (num_apics == (num_cpus * thread_count));

	/* sort them by thread i.e., all cores with thread 0 and then thread 1 */
	int index = 0;
	for (int id=0; id < num_apics; ++id) {
		int apic_id = apic_ids[id];
		if (apic_id & 0x1) { /* 2nd thread */
			apic_ids_by_thread[index + (num_apics/2) - 1] = apic_id;
		}
		else { /* 1st thread */
			apic_ids_by_thread[index++] = apic_id;
		}
	}

	/* update apic_id, node_id in sorted order */
	num_apics = 0;
  get_core_thread_bits(&core_bits, &thread_bits);
  for (dev = all_devices; dev; dev = dev->next) {
		uint8_t package;

    if ((dev->path.type != DEVICE_PATH_APIC) ||
      (dev->bus->dev->path.type != DEVICE_PATH_CPU_CLUSTER)) {
      continue;
    }
    if (!dev->enabled)
      continue;
    if (num_apics >= ARRAY_SIZE(apic_ids))
      break;
		dev->path.apic.apic_id = apic_ids_by_thread[num_apics];
		get_cpu_info_from_apicid(dev->path.apic.apic_id, core_bits, thread_bits, &package, NULL, NULL);
		dev->path.apic.node_id = package;
		printk(BIOS_DEBUG, "CPU %d apic_id: 0x%x, node_id: 0x%x\n", num_apics, dev->path.apic.apic_id, dev->path.apic.node_id);

		++num_apics;
  }
}

unsigned int get_srat_memory_entries(acpi_srat_mem_t *srat_mem)
{
	const struct SystemMemoryMapHob *memory_map;
  size_t hob_size;
  const uint8_t mem_hob_guid[16] = FSP_SYSTEM_MEMORYMAP_HOB_GUID;
	unsigned int mmap_index;

  /* these fields are incorrect - need debugging */
  memory_map = fsp_find_extension_hob_by_guid(mem_hob_guid, &hob_size);
  assert(memory_map != NULL && hob_size != 0);
	printk(BIOS_DEBUG, "FSP_SYSTEM_MEMORYMAP_HOB_GUID hob_size: %ld\n", hob_size);

	mmap_index = 0;
	for (int e = 0; e < memory_map->numberEntries; ++e) {
		const struct SystemMemoryMapElement *mem_element = &memory_map->Element[e];
		uint64_t addr = (uint64_t) ((uint64_t)mem_element->BaseAddress << MEM_ADDR_64MB_SHIFT_BITS);
		uint64_t size = (uint64_t) ((uint64_t)mem_element->ElementSize << MEM_ADDR_64MB_SHIFT_BITS);

		printk(BIOS_DEBUG, "memory_map %d addr: 0x%llx, BaseAddress: 0x%x, size: 0x%llx, ElementSize: 0x%x, reserved: %d\n",
					 e, addr, mem_element->BaseAddress, size, mem_element->ElementSize, (mem_element->Type & MEM_TYPE_RESERVED));

		assert(mmap_index < MAX_ACPI_MEMORY_AFFINITY_COUNT);

		/* skip reserved memory region */
		if (mem_element->Type & MEM_TYPE_RESERVED)
			continue;

		/* skip if this address is already added */
		bool skip = false;
		for (int idx = 0; idx < mmap_index; ++idx) {
			uint64_t base_addr = ((uint64_t)srat_mem[idx].base_address_high << 32) + srat_mem[idx].base_address_low;
			if (addr == base_addr) {
				skip = true;
				break;
			}
		}
		if (skip)
			continue;

		srat_mem[mmap_index].type = 1; /* Memory affinity structure */
		srat_mem[mmap_index].length = sizeof(acpi_srat_mem_t);
		srat_mem[mmap_index].base_address_low = (uint32_t) (addr & 0xffffffff);
		srat_mem[mmap_index].base_address_high = (uint32_t) (addr >> 32);
		srat_mem[mmap_index].length_low = (uint32_t) (size & 0xffffffff);
		srat_mem[mmap_index].length_high = (uint32_t) (size >> 32);
		srat_mem[mmap_index].proximity_domain = mem_element->SocketId;
		srat_mem[mmap_index].flags = SRAT_ACPI_MEMORY_ENABLED;
		if ((mem_element->Type & MEMTYPE_VOLATILE_MASK) == 0)
			srat_mem[mmap_index].flags |= SRAT_ACPI_MEMORY_NONVOLATILE;
		++mmap_index;
	}

	return mmap_index;
}

#endif
