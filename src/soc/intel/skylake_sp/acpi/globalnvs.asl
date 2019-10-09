/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2013 Google Inc.
 * Copyright (C) 2014 - 2017 Intel Corporation.
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

/* Global Variables */

Name(\PICM, 0)		// IOAPIC/8259

/* Global ACPI memory region. This region is used for passing information
 * between coreboot (aka "the system bios"), ACPI, and the SMI handler.
 * Since we don't know where this will end up in memory at ACPI compile time,
 * we have to fix it up in coreboot's ACPI creation phase.
 */


External(NVSA)
OperationRegion (GNVS, SystemMemory, NVSA, 0x2000)
Field (GNVS, ByteAcc, NoLock, Preserve)
{
	/* Miscellaneous */
	Offset (0x00),
	OSYS,	16,	// 0x00 - Operating System
	SMIF,	 8,	// 0x02 - SMI function
	PRM0,	 8,	// 0x03 - SMI function parameter
	PRM1,	 8,	// 0x04 - SMI function parameter
	SCIF,	 8,	// 0x05 - SCI function
	PRM2,	 8,	// 0x06 - SCI function parameter
	PRM3,	 8,	// 0x07 - SCI function parameter
	LCKF,	 8,	// 0x08 - Global Lock function for EC
	PRM4,	 8,	// 0x09 - Lock function parameter
	PRM5,	 8,	// 0x0a - Lock function parameter
	P80D,	32,	// 0x0b - Debug port (IO 0x80) value
	LIDS,	 8,	// 0x0f - LID state (open = 1)
	PWRS,	 8,	// 0x10 - Power State (AC = 1)
	PCNT,	 8,	// 0x11 - Processor count
	TPMP,	 8,	// 0x12 - TPM Present and Enabled
	TLVL,	 8,	// 0x13 - Throttle Level
	PPCM,	 8,	// 0x14 - Maximum P-state usable by OS
  PM1I, 64, // 0x15 - PM1 wake status bit
  GPEI, 64, // 0x1D - GPE wake status bit


	/* Device Config */
	Offset (0x30),
	S5U0,	 8,	// 0x30 - Enable USB0 in S5
	S5U1,	 8,	// 0x31 - Enable USB1 in S5
	S3U0,	 8,	// 0x32 - Enable USB0 in S3
	S3U1,	 8,	// 0x33 - Enable USB1 in S3
	TACT,	 8,	// 0x34 - Thermal Active trip point
	TPSV,	 8,	// 0x35 - Thermal Passive trip point
	TCRT,	 8,	// 0x36 - Thermal Critical trip point
	DPTE,	 8,	// 0x37 - Enable DPTF

	/* Base addresses */
	Offset (0x50),
	CMEM,	 32,	// 0x50 - CBMEM TOC
	TOLM,	 32,	// 0x54 - Top of Low Memory
	CBMC,	 32,	// 0x58 - coreboot mem console pointer
	MMOB,	 32,	// 0x5C - MMIO Base Low Base
	MMOL,	 32,	// 0x60 - MMIO Base Low Limit
	MMHB,	 64,	// 0x64 - MMIO Base High Base
	MMHL,	 64,	// 0x6C - MMIO Base High Limit
	TSGB,	 32,	// 0x74 - TSEG Base
	TSSZ,	 32,	// 0x78 - TSEG Size
}

/* Set flag to enable USB charging in S3 */
Method (S3UE)
{
	Store (One, \S3U0)
	Store (One, \S3U1)
}

/* Set flag to disable USB charging in S3 */
Method (S3UD)
{
	Store (Zero, \S3U0)
	Store (Zero, \S3U1)
}

/* Set flag to enable USB charging in S5 */
Method (S5UE)
{
	Store (One, \S5U0)
	Store (One, \S5U1)
}

/* Set flag to disable USB charging in S5 */
Method (S5UD)
{
	Store (Zero, \S5U0)
	Store (Zero, \S5U1)
}
