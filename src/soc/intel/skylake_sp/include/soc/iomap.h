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

#ifndef _SKYLAKESP_IOMAP_H_
#define _SKYLAKESP_IOMAP_H_

/*
 * Memory-mapped I/O registers.
 */
/* P2SB PCR cfg BAR */
#define PCH_PRESERVED_BASE_ADDRESS      0xfd000000
#define PCH_PRESERVED_BASE_SIZE 			  0x01800000

#define UART_BASE_SIZE		0x1000
#define UART_BASE_0_ADDRESS	0xfe030000
/* Both UART BAR 0 and 1 are 4KB in size */
#define UART_BASE_0_ADDR(x)	(UART_BASE_0_ADDRESS + (2 * \
					UART_BASE_SIZE * (x)))
#define UART_BASE(x)		UART_BASE_0_ADDR(x)

#define EARLY_I2C_BASE_ADDRESS	0xfe040000
#define EARLY_I2C_BASE(x)	(EARLY_I2C_BASE_ADDRESS + (0x1000 * (x)))

#define MCH_BASE_ADDRESS	0xfed10000
#define MCH_BASE_SIZE		0x8000

#define DMI_BASE_ADDRESS	0xfed18000
#define DMI_BASE_SIZE		0x1000

#define EP_BASE_ADDRESS		0xfed19000
#define EP_BASE_SIZE		0x1000

#define EDRAM_BASE_ADDRESS	0xfed80000
#define EDRAM_BASE_SIZE		0x4000

#define GDXC_BASE_ADDRESS	0xfed84000
#define GDXC_BASE_SIZE		0x1000

#define GFXVT_BASE_ADDRESS	0xfed90000
#define GFXVT_BASE_SIZE		0x1000

#define VTVC0_BASE_ADDRESS	0xfed91000
#define VTVC0_BASE_SIZE		0x1000

#define PCH_PWRM_BASE_ADDRESS	0xfe000000
#define PCH_PWRM_BASE_SIZE	0x10000

#define SPI_BASE_ADDRESS	0xfe010000
#define EARLY_GSPI_BASE_ADDRESS 0xfe011000

#define GPIO_BASE_SIZE		0x10000

#define HECI1_BASE_ADDRESS	0xfed1a000

#define THERMAL_BASE_ADDRESS	0xfe600000

#define TPM_BASE_ADDRESS 0xfed40000
#define TPM_BASE_SIZE    (0xfed44fff - 0xfed40000 + 1) 

/* CPU Trace reserved memory size */
#define GDXC_MOT_MEMORY_SIZE	(96*MiB)
#define GDXC_IOT_MEMORY_SIZE	(32*MiB)
#define PSMI_BUFFER_AREA_SIZE	(64*MiB)

/* PTT registers */
#define PTT_TXT_BASE_ADDRESS	0xfed30800
#define PTT_PRESENT		0x00070000

/*
 * I/O port address space
 */
#define SMBUS_BASE_ADDRESS	0x0efa0
#define SMBUS_BASE_SIZE		0x20

#define ACPI_BASE_ADDRESS	0x500
//#define ACPI_BASE_ADDRESS	0x1800
#define ACPI_BASE_SIZE		0x100

#define TCO_BASE_ADDRESS	0x400
#define TCO_BASE_SIZE		0x20

#define P2SB_BAR		CONFIG_PCR_BASE_ADDRESS
#define P2SB_SIZE		0x1800000

#define RESERVED1_BASE_ADDRESS   0xfe800000
#define RESERVED1_BASE_SIZE      0x00400000

/* Transactions in this range will abort */
#define ABORT_BASE_ADDRESS       0xfeb00000
#define ABORT_BASE_SIZE          0x00080000

/* PSEG */
#define PSEG_BASE_ADDRESS        0xfeb80000
#define PSEG_BASE_SIZE           0x00080000

/* IOxAPIC */
#define IOXAPIC_BASE_ADDRESS     0xfec00000
#define IOAPIC_SIZE              0x00100000

#define IOXAPIC1_BASE_ADDRESS    0xfec00000
#define IOXAPIC1_BASE_SIZE       0x00100000
#define IOXAPIC2_BASE_ADDRESS    0xfec01000
#define IOXAPIC2_BASE_SIZE       0x00100000

/* PCH (HPET/LT/TPM/Others) */
#define PCH_BASE_ADDRESS         0xfed00000
#define PCH_BASE_SIZE            0x00100000

/* Local XAPIC */
#define LXAPIC_BASE_ADDRESS      0xfee00000
#define LXAPIC_BASE_SIZE         0x00100000

/* High Performance Event Timer */
#define HPET_BASE_ADDRESS        0xfed00000
#define HPET_BASE_SIZE           0x400

/* TODO - Reserved */
#define RESERVED2_BASE_ADDRESS    0xfef00000
#define RESERVED2_BASE_SIZE       0x00100000

/* Firmware */
#define FIRMWARE_BASE_ADDRESS    0xff000000
#define FIRMWARE_BASE_SIZE       0x01000000

/* Northbridge BARs */
#define DEFAULT_PCIEXBAR CONFIG_MMCONF_BASE_ADDRESS /* 4 KB per PCIe device */
#define DEFAULT_MCHBAR 0xfed10000		    /* 16 KB */

/* 
   Error Record Serialization Table (ERST) support is initialized
   APEI firmware first mode is enabled by APEI bit and WHEA _OSC
   6a7a9000-6c8a8fff : Reserved
   6b88e018-6b88e018 : APEI ERST
   6b88e01c-6b88e021 : APEI ERST
   6b88e028-6b88e039 : APEI ERST
   6b88e040-6b88e04c : APEI ERST
 */

#define APEI_ERST_BASE_ADDRESS    0x6a7a9000
#define APEI_ERST_BASE_SIZE       (0x6c8a8fff - APEI_ERST_BASE_ADDRESS + 1)

#endif /* _SKYLAKESP_IOMAP_H_ */
