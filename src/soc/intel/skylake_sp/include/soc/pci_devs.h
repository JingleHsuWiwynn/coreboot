/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2013 Google Inc.
 * Copyright (C) 2014-2017 Intel Corporation.
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

#ifndef _SKYLAKESP_PCI_DEVS_H_
#define _SKYLAKESP_PCI_DEVS_H_

/* All these devices live on bus 0 with the associated device and function */


#if 0
#define _SA_DEVFN(slot) PCI_DEVFN(SA_DEV_SLOT_##slot, 0)
#define _PCH_DEVFN(slot, func) PCI_DEVFN(PCH_DEV_SLOT_##slot, func)

#if ENV_RAMSTAGE
#include <device/device.h>
#include <device/pci_def.h>
#define _SA_DEV(slot) dev_find_slot(0, _SA_DEVFN(slot))
#define _PCH_DEV(slot, func) dev_find_slot(0, _PCH_DEVFN(slot, func))
#else
#include <arch/io.h>
#define _SA_DEV(slot) PCI_DEV(0, SA_DEV_SLOT_##slot, 0)
#define _PCH_DEV(slot, func) PCI_DEV(0, PCH_DEV_SLOT_##slot, func)
#endif
#endif
#include <device/pci_def.h>

#define _SA_DEVFN(slot)   PCI_DEVFN(SA_DEV_SLOT_ ## slot, 0)
#define _PCH_DEVFN(slot, func)  PCI_DEVFN(PCH_DEV_SLOT_ ## slot, func)

#if !defined(__SIMPLE_DEVICE__)
#include <device/device.h>
#define _SA_DEV(slot)   dev_find_slot(0, _SA_DEVFN(slot))
#define _PCH_DEV(slot, func)  dev_find_slot(0, _PCH_DEVFN(slot, func))
#else
#include <arch/io.h>
#define _SA_DEV(slot)   PCI_DEV(0, SA_DEV_SLOT_ ## slot, 0)
#define _PCH_DEV(slot, func)  PCI_DEV(0, PCH_DEV_SLOT_ ## slot, func)
#endif


/* Skylake SP devices, registers */
#define SKXSP_MMAP_VTD_CFG_REG_DEVID 		0x2024
#define SKXSP_VTD_DEV          				  5
#define SKXSP_VTD_FUNC                  0
#define SKXSP_VTD_MMCFG_BASE_CSR        0x90
#define SKXSP_VTD_MMCFG_LIMIT_CSR       0x98
#define SKXSP_VTD_TSEG_BASE_CSR         0xa8
#define SKXSP_VTD_TSEG_LIMIT_CSR        0xac
#define SKXSP_VTD_TOLM_CSR              0xd0
#define SKXSP_VTD_TOHM_CSR              0xd4 
#define SKXSP_VTD_MMIOL_CSR             0xdc
#define SKXSP_VTD_ME_BASE_CSR           0xf0
#define SKXSP_VTD_ME_LIMIT_CSR          0xf8
#define SKXSP_SAD_ALL_DEV               29
#define SKXSP_SAD_ALL_FUNC              0
#define SKXSP_SAD_ALL_PAM0123_CSR       0x40
#define SKXSP_SAD_ALL_PAM456_CSR        0x44

#define UBOX_DECS_BUS             0
#define UBOX_DECS_DEV             8
#define UBOX_DECS_FUNC            2
#define UBOX_DECS_CPUBUSNO_CSR    0xcc

#define CHA_UTIL_ALL_DEV          29
#define CHA_UTIL_ALL_FUNC         1
#define CHA_UTIL_ALL_MMCFG_CSR    0xc0

#define PCI_DEVICE_ID_INTEL_C620_FAST_SPI 0xa1a4


#define MAX_IIO_STACK             6

/* FIXME: Below devices need to be changed for SKX SP + LBG */

#if 0
/* SoC transaction router */
#define SA_DEV 0x0
#define SA_FUNC 0
#define SA_DEVID 0x1980
#define SA_DEVID_DNVAD 0x1995
#define SOC_DEV SA_DEV
#define SOC_FUNC SA_FUNC
#define SOC_DEVID SA_DEVID

/* RAS */
#define RAS_DEV 0x4
#define RAS_FUNC 0
#define RAS_DEVID 0x19a1

/* Root Complex Event Collector */
#define RCEC_DEV 0x5
#define RCEC_FUNC 0
#define RCEC_DEVID 0x19a2

/* Virtual Root Port 2 */
#define VRP2_DEV 0x6
#define VRP2_FUNC 0
#define VRP2_DEVID 0x19a3

/* PCIe Root Ports */
#define PCIE_DEV 0x09
#define MAX_PCIE_PORT 0x8
#define PCIE_PORT1_DEV 0x09
#define PCIE_PORT1_FUNC 0
#define PCIE_PORT1_DEVID 0x19a4
#define PCIE_PORT2_DEV 0x0a
#define PCIE_PORT2_FUNC 0
#define PCIE_PORT2_DEVID 0x19a5
#define PCIE_PORT3_DEV 0x0b
#define PCIE_PORT3_FUNC 0
#define PCIE_PORT3_DEVID 0x19a6
#define PCIE_PORT4_DEV 0x0c
#define PCIE_PORT4_FUNC 0
#define PCIE_PORT4_DEVID 0x19a7
#define PCIE_PORT5_DEV 0x0e
#define PCIE_PORT5_FUNC 0
#define PCIE_PORT5_DEVID 0x19a8
#define PCIE_PORT6_DEV 0x0f
#define PCIE_PORT6_FUNC 0
#define PCIE_PORT6_DEVID 0x19a9
#define PCIE_PORT7_DEV 0x10
#define PCIE_PORT7_FUNC 0
#define PCIE_PORT7_DEVID 0x19aa
#define PCIE_PORT8_DEV 0x11
#define PCIE_PORT8_FUNC 0
#define PCIE_PORT8_DEVID 0x19ab

/* SMBUS 2 */
#define SMBUS2_DEV 0x12
#define SMBUS2_FUNC 0
#define SMBUS2_DEVID 0x19ac

/* SATA */
#define SATA_DEV 0x13
#define SATA_FUNC 0
#define AHCI_DEVID 0xa1d2
#define SATA2_DEV 0x14
#define SATA2_FUNC 0
#define AHCI2_DEVID 0xa182

/* xHCI */
#define XHCI_DEV 0x15
#define XHCI_FUNC 0
#define XHCI_DEVID 0x19d0

/* Virtual Root Port 0 */
#define VRP0_DEV 0x16
#define VRP0_FUNC 0
#define VRP0_DEVID 0x19d1

/* Virtual Root Port 1 */
#define VRP1_DEV 0x17
#define VRP1_FUNC 0
#define VRP1_DEVID 0x19d2

/* CSME */
#define ME_HECI_DEV 0x18
#define ME_HECI1_DEV ME_HECI_DEV
#define ME_HECI1_FUNC 0
#define ME_HECI1_DEVID 0x19d3
#define ME_HECI2_DEV ME_HECI_DEV
#define ME_HECI2_FUNC 1
#define ME_HECI2_DEVID 0x19d4
#define ME_IEDR_DEV ME_HECI_DEV
#define ME_IEDR_FUNC 2
#define ME_IEDR_DEVID 0x19ea
#define ME_MEKT_DEV ME_HECI_DEV
#define ME_MEKT_FUNC 3
#define ME_MEKT_DEVID 0x19d5
#define ME_HECI3_DEV ME_HECI_DEV
#define ME_HECI3_FUNC 4
#define ME_HECI3_DEVID 0x19d6

/* HSUART */
#define HSUART_DEV 0x1a
#define HSUART_DEVID 0x19d8
#define HSUART1_DEV HSUART_DEV
#define HSUART1_FUNC 0
#define HSUART1_DEVID HSUART_DEVID
#define HSUART2_DEV HSUART_DEV
#define HSUART2_FUNC 1
#define HSUART2_DEVID HSUART_DEVID
#define HSUART3_DEV HSUART_DEV
#define HSUART3_FUNC 2
#define HSUART3_DEVID HSUART_DEVID

/* IE */
#define IE_HECI_DEV 0x1b
#define IE_HECI1_DEV IE_HECI_DEV
#define IE_HECI1_FUNC 0
#define IE_HECI1_DEVID 0x19e5
#define IE_HECI2_DEV IE_HECI_DEV
#define IE_HECI2_FUNC 1
#define IE_HECI2_DEVID 0x19e6
#define IE_IEDR_DEV IE_HECI_DEV
#define IE_IEDR_FUNC 2
#define IE_IEDR_DEVID 0x19e7
#define IE_MEKT_DEV IE_HECI_DEV
#define IE_MEKT_FUNC 3
#define IE_MEKT_DEVID 0x19e8
#define IE_HECI3_DEV IE_HECI_DEV
#define IE_HECI3_FUNC 4
#define IE_HECI3_DEVID 0x19e9

/* MMC Port */
#define MMC_DEV 0x1c
#define MMC_FUNC 0
#define MMC_DEVID 0x19db

/* Platform Controller Unit */
/* Device Ids for Intel C621 Chipset (QS/PRQ) */
#define PCU_DEV         0x1f
#define LPC_DEV         PCU_DEV
#define LPC_FUNC        0
#define LPC_DEVID       0xa1c1  // TiogaPass chipset device id
#define P2SB_DEV        PCU_DEV
#define P2SB_FUNC       1
#define P2SB_DEVID      0xa1a0
#define PMC_DEV         PCU_DEV
#define PMC_FUNC        2
#define PMC_DEVID       0xa1a1
#define SMBUS_DEV       PCU_DEV
#define SMBUS_FUNC      4
#define SMBUS_DEVID     0xa1a3
#define SPI_DEV         PCU_DEV
#define SPI_FUNC        5
#define SPI_DEVID       0xa1a4
#define NPK_DEV         PCU_DEV
#define NPK_FUNC        7
#define NPK_DEVID       0xa1a6 // Intel Trace Hub

/* TODO - New added */
#define SA_DEV_SLOT_ROOT 0x00
#define SA_DEVFN_ROOT _SA_DEVFN(ROOT)
#define SA_DEV_ROOT _SA_DEV(ROOT)

#define PCH_DEV_SLOT_LPC 0x1f
#define PCH_DEVFN_LPC _PCH_DEVFN(LPC, 0)
#define PCH_DEVFN_SPI _PCH_DEVFN(LPC, 5)
#define PCH_DEV_LPC _PCH_DEV(LPC, 0)
#define PCH_DEV_SPI _PCH_DEV(LPC, 5)
#endif
/* System Agent Devices */

#define SA_DEV_SLOT_ROOT	0x00
#define  SA_DEVFN_ROOT		_SA_DEVFN(ROOT)
#define  SA_DEV_ROOT		_SA_DEV(ROOT)

#define SA_DEV_SLOT_IGD		0x02
#define  SA_DEVFN_IGD		_SA_DEVFN(IGD)
#define  SA_DEV_IGD		_SA_DEV(IGD)

/* PCH Devices */

#define PCH_DEV_SLOT_ISH	0x13
#define  PCH_DEVFN_ISH		_PCH_DEVFN(ISH, 0)
#define  PCH_DEV_ISH		_PCH_DEV(ISH, 0)

#define PCH_DEV_SLOT_XHCI	0x14
#define  PCH_DEVFN_XHCI		_PCH_DEVFN(XHCI, 0)
#define  PCH_DEVFN_USBOTG	_PCH_DEVFN(XHCI, 1)
#define  PCH_DEVFN_THERMAL	_PCH_DEVFN(XHCI, 2)
#define  PCH_DEVFN_CIO		_PCH_DEVFN(XHCI, 3)
#define  PCH_DEV_XHCI		_PCH_DEV(XHCI, 0)
#define  PCH_DEV_USBOTG		_PCH_DEV(XHCI, 1)
#define  PCH_DEV_THERMAL	_PCH_DEV(XHCI, 2)
#define  PCH_DEV_CIO		_PCH_DEV(XHCI, 3)

#define PCH_DEV_SLOT_SIO1	0x15
#define  PCH_DEVFN_I2C0		_PCH_DEVFN(SIO1, 0)
#define  PCH_DEVFN_I2C1		_PCH_DEVFN(SIO1, 1)
#define  PCH_DEVFN_I2C2		_PCH_DEVFN(SIO1, 2)
#define  PCH_DEVFN_I2C3		_PCH_DEVFN(SIO1, 3)
#define  PCH_DEV_I2C0		_PCH_DEV(SIO1, 0)
#define  PCH_DEV_I2C1		_PCH_DEV(SIO1, 1)
#define  PCH_DEV_I2C2		_PCH_DEV(SIO1, 2)
#define  PCH_DEV_I2C3		_PCH_DEV(SIO1, 3)

#define PCH_DEV_SLOT_CSE	0x16
#define  PCH_DEVFN_CSE		_PCH_DEVFN(CSE, 0)
#define  PCH_DEVFN_CSE_2	_PCH_DEVFN(CSE, 1)
#define  PCH_DEVFN_CSE_IDER	_PCH_DEVFN(CSE, 2)
#define  PCH_DEVFN_CSE_KT	_PCH_DEVFN(CSE, 3)
#define  PCH_DEVFN_CSE_3	_PCH_DEVFN(CSE, 4)
#define  PCH_DEV_CSE		_PCH_DEV(CSE, 0)
#define  PCH_DEV_CSE_2		_PCH_DEV(CSE, 1)
#define  PCH_DEV_CSE_IDER	_PCH_DEV(CSE, 2)
#define  PCH_DEV_CSE_KT		_PCH_DEV(CSE, 3)
#define  PCH_DEV_CSE_3		_PCH_DEV(CSE, 4)

#define PCH_DEV_SLOT_SATA	0x17
#define  PCH_DEVFN_SATA		_PCH_DEVFN(SATA, 0)
#define  PCH_DEV_SATA		_PCH_DEV(SATA, 0)

#define PCH_DEV_SLOT_SIO2	0x19
#define  PCH_DEVFN_UART2	_PCH_DEVFN(SIO2, 0)
#define  PCH_DEVFN_I2C5		_PCH_DEVFN(SIO2, 1)
#define  PCH_DEVFN_I2C4		_PCH_DEVFN(SIO2, 2)
#define  PCH_DEV_UART2		_PCH_DEV(SIO2, 0)
#define  PCH_DEV_I2C5		_PCH_DEV(SIO2, 1)
#define  PCH_DEV_I2C4		_PCH_DEV(SIO2, 2)

#define PCH_DEV_SLOT_PCIE_2	0x1b
#define  PCH_DEVFN_PCIE17	_PCH_DEVFN(PCIE_2, 0)
#define  PCH_DEVFN_PCIE18	_PCH_DEVFN(PCIE_2, 1)
#define  PCH_DEVFN_PCIE19	_PCH_DEVFN(PCIE_2, 2)
#define  PCH_DEVFN_PCIE20	_PCH_DEVFN(PCIE_2, 3)
#define  PCH_DEVFN_PCIE21	_PCH_DEVFN(PCIE_2, 4)
#define  PCH_DEVFN_PCIE22	_PCH_DEVFN(PCIE_2, 5)
#define  PCH_DEVFN_PCIE23	_PCH_DEVFN(PCIE_2, 6)
#define  PCH_DEVFN_PCIE24	_PCH_DEVFN(PCIE_2, 7)
#define  PCH_DEV_PCIE17		_PCH_DEV(PCIE_2, 0)
#define  PCH_DEV_PCIE18		_PCH_DEV(PCIE_2, 1)
#define  PCH_DEV_PCIE19		_PCH_DEV(PCIE_2, 2)
#define  PCH_DEV_PCIE20		_PCH_DEV(PCIE_2, 3)
#define  PCH_DEV_PCIE21		_PCH_DEV(PCIE_2, 4)
#define  PCH_DEV_PCIE22		_PCH_DEV(PCIE_2, 5)
#define  PCH_DEV_PCIE23		_PCH_DEV(PCIE_2, 6)
#define  PCH_DEV_PCIE24		_PCH_DEV(PCIE_2, 7)

#define PCH_DEV_SLOT_PCIE	0x1c
#define  PCH_DEVFN_PCIE1	_PCH_DEVFN(PCIE, 0)
#define  PCH_DEVFN_PCIE2	_PCH_DEVFN(PCIE, 1)
#define  PCH_DEVFN_PCIE3	_PCH_DEVFN(PCIE, 2)
#define  PCH_DEVFN_PCIE4	_PCH_DEVFN(PCIE, 3)
#define  PCH_DEVFN_PCIE5	_PCH_DEVFN(PCIE, 4)
#define  PCH_DEVFN_PCIE6	_PCH_DEVFN(PCIE, 5)
#define  PCH_DEVFN_PCIE7	_PCH_DEVFN(PCIE, 6)
#define  PCH_DEVFN_PCIE8	_PCH_DEVFN(PCIE, 7)
#define  PCH_DEV_PCIE1		_PCH_DEV(PCIE, 0)
#define  PCH_DEV_PCIE2		_PCH_DEV(PCIE, 1)
#define  PCH_DEV_PCIE3		_PCH_DEV(PCIE, 2)
#define  PCH_DEV_PCIE4		_PCH_DEV(PCIE, 3)
#define  PCH_DEV_PCIE5		_PCH_DEV(PCIE, 4)
#define  PCH_DEV_PCIE6		_PCH_DEV(PCIE, 5)
#define  PCH_DEV_PCIE7		_PCH_DEV(PCIE, 6)
#define  PCH_DEV_PCIE8		_PCH_DEV(PCIE, 7)

#define PCH_DEV_SLOT_PCIE_1	0x1d
#define  PCH_DEVFN_PCIE9	_PCH_DEVFN(PCIE_1, 0)
#define  PCH_DEVFN_PCIE10	_PCH_DEVFN(PCIE_1, 1)
#define  PCH_DEVFN_PCIE11	_PCH_DEVFN(PCIE_1, 2)
#define  PCH_DEVFN_PCIE12	_PCH_DEVFN(PCIE_1, 3)
#define  PCH_DEVFN_PCIE13	_PCH_DEVFN(PCIE_1, 4)
#define  PCH_DEVFN_PCIE14	_PCH_DEVFN(PCIE_1, 5)
#define  PCH_DEVFN_PCIE15	_PCH_DEVFN(PCIE_1, 6)
#define  PCH_DEVFN_PCIE16	_PCH_DEVFN(PCIE_1, 7)
#define  PCH_DEV_PCIE9		_PCH_DEV(PCIE_1, 0)
#define  PCH_DEV_PCIE10		_PCH_DEV(PCIE_1, 1)
#define  PCH_DEV_PCIE11		_PCH_DEV(PCIE_1, 2)
#define  PCH_DEV_PCIE12		_PCH_DEV(PCIE_1, 3)
#define  PCH_DEV_PCIE13		_PCH_DEV(PCIE_1, 4)
#define  PCH_DEV_PCIE14		_PCH_DEV(PCIE_1, 5)
#define  PCH_DEV_PCIE15		_PCH_DEV(PCIE_1, 6)
#define  PCH_DEV_PCIE16		_PCH_DEV(PCIE_1, 7)

#define PCH_DEV_SLOT_STORAGE	0x1e
#define  PCH_DEVFN_UART0	_PCH_DEVFN(STORAGE, 0)
#define  PCH_DEVFN_UART1	_PCH_DEVFN(STORAGE, 1)
#define  PCH_DEVFN_GSPI0	_PCH_DEVFN(STORAGE, 2)
#define  PCH_DEVFN_GSPI1	_PCH_DEVFN(STORAGE, 3)
#define  PCH_DEVFN_EMMC		_PCH_DEVFN(STORAGE, 4)
#define  PCH_DEVFN_SDIO		_PCH_DEVFN(STORAGE, 5)
#define  PCH_DEVFN_SDCARD	_PCH_DEVFN(STORAGE, 6)
#define  PCH_DEV_UART0		_PCH_DEV(STORAGE, 0)
#define  PCH_DEV_UART1		_PCH_DEV(STORAGE, 1)
#define  PCH_DEV_GSPI0		_PCH_DEV(STORAGE, 2)
#define  PCH_DEV_GSPI1		_PCH_DEV(STORAGE, 3)
#define  PCH_DEV_EMMC		_PCH_DEV(STORAGE, 4)
#define  PCH_DEV_SDIO		_PCH_DEV(STORAGE, 5)
#define  PCH_DEV_SDCARD		_PCH_DEV(STORAGE, 6)

#define PCH_DEV_SLOT_LPC	0x1f
#define  PCH_DEVFN_LPC		_PCH_DEVFN(LPC, 0)
#define  PCH_DEVFN_P2SB         _PCH_DEVFN(LPC, 1)
#define  PCH_DEVFN_PMC		_PCH_DEVFN(LPC, 2)
#define  PCH_DEVFN_HDA		_PCH_DEVFN(LPC, 3)
#define  PCH_DEVFN_SMBUS	_PCH_DEVFN(LPC, 4)
#define  PCH_DEVFN_SPI		_PCH_DEVFN(LPC, 5)
#define  PCH_DEVFN_GBE		_PCH_DEVFN(LPC, 6)
#define  PCH_DEVFN_TRACEHUB	_PCH_DEVFN(LPC, 7)
#define  PCH_DEV_LPC		_PCH_DEV(LPC, 0)
#define  PCH_DEV_P2SB		_PCH_DEV(LPC, 1)
#define  PCH_DEV_PMC		_PCH_DEV(LPC, 2)
#define  PCH_DEV_HDA		_PCH_DEV(LPC, 3)
#define  PCH_DEV_SMBUS		_PCH_DEV(LPC, 4)
#define  PCH_DEV_SPI		_PCH_DEV(LPC, 5)
#define  PCH_DEV_GBE		_PCH_DEV(LPC, 6)
#define  PCH_DEV_TRACEHUB	_PCH_DEV(LPC, 7)

// TODO ** cleanup uses denverton_ns sata.c
/* SATA */
#define SATA_DEV 		0x11
#define SATA_FUNC 		5
#define AHCI_DEVID 		0xa1d2
#define SATA2_DEV 		0x17
#define SATA2_FUNC 		0
#define AHCI2_DEVID 		0xa182


#endif /* _SKYLAKESP_PCI_DEVS_H_ */
