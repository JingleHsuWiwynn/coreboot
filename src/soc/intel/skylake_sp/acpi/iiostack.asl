/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2007 - 2009 coresystems GmbH
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

#include "../include/soc/iomap.h"

Scope(\)
{
  // IO-Trap at 0x800. This is the ACPI->SMI communication interface.

  OperationRegion(IO_T, SystemIO, 0x800, 0x10)
  Field(IO_T, ByteAcc, NoLock, Preserve)
  {
    Offset(0x8),
    TRP0, 8   // IO-Trap at 0x808
  }

  // Private Chipset Register(PCR). Memory Mapped through ILB
  OperationRegion(PCRR, SystemMemory, P2SB_BAR, 0x01000000)
  Field(PCRR, DWordAcc, Lock, Preserve)
  {
    Offset (0xD03100),  // Interrupt Routing Registers
    PRTA, 8,
    PRTB, 8,
    PRTC, 8,
    PRTD, 8,
    PRTE, 8,
    PRTF, 8,
    PRTG, 8,
    PRTH, 8,
  }
}

Device (PC00)
{
	Name (_HID, EisaId ("PNP0A08") /* PCI Express Bus */)  // _HID: Hardware ID
	Name (_CID, EisaId ("PNP0A03") /* PCI Bus */)  // _CID: Compatible ID
	Name (_ADR, 0x00)  // _ADR: Address
	Method (^BN00, 0, NotSerialized)
	{
			Return (0x00)
	}

	Method (_BBN, 0, NotSerialized)  // _BBN: BIOS Bus Number
	{
			Return (BN00 ())
	}

	Name (_UID, 0x00)  // _UID: Unique ID

	Name (SUPP, 0x00)
	Name (CTRL, 0x00)
	Name (_PXM, 0x00)  // _PXM: Device Proximity

	Device (APIC)
	{
			Name (_HID, EisaId ("PNP0003") /* IO-APIC Interrupt Controller */)  // _HID: Hardware ID
			Name (_CRS, ResourceTemplate ()  // _CRS: Current Resource Settings
			{
					Memory32Fixed (ReadOnly,
							0xFEC00000,         // Address Base
							0x00100000,         // Address Length
							)
			})
	}


	Name (BUF0, ResourceTemplate ()
	{
			WordBusNumber (ResourceProducer, MinFixed, MaxFixed, PosDecode,
					0x0000,             // Granularity
					0x0000,             // Range Minimum
					0x00FF,             // Range Maximum
					0x0000,             // Translation Offset
					0x0100,             // Length
					,, )
			DWordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
					0x00000000,         // Granularity
					0x00000000,         // Range Minimum
					0x00000CF7,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00000CF8,         // Length
					,, , TypeStatic, DenseTranslation)
			IO (Decode16,
					0x0CF8,             // Range Minimum
					0x0CF8,             // Range Maximum
					0x01,               // Alignment
					0x08,               // Length
					)
			DWordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
					0x00000000,         // Granularity
					0x00000D00,         // Range Minimum
					0x0000FFFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x0000F300,         // Length
					,, , TypeStatic, DenseTranslation)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x000A0000,         // Range Minimum
					0x000BFFFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00020000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x000C0000,         // Range Minimum
					0x000C3FFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00004000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x000C4000,         // Range Minimum
					0x000C7FFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00004000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x000C8000,         // Range Minimum
					0x000CBFFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00004000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x000CC000,         // Range Minimum
					0x000CFFFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00004000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x000D0000,         // Range Minimum
					0x000D3FFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00004000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x000D4000,         // Range Minimum
					0x000D7FFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00004000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x000D8000,         // Range Minimum
					0x000DBFFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00004000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x000DC000,         // Range Minimum
					0x000DFFFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00004000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x000E0000,         // Range Minimum
					0x000E3FFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00004000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x000E4000,         // Range Minimum
					0x000E7FFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00004000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x000E8000,         // Range Minimum
					0x000EBFFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00004000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x000EC000,         // Range Minimum
					0x000EFFFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00004000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x000F0000,         // Range Minimum
					0x000FFFFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00010000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x00000000,         // Range Minimum
					0xFEAFFFFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0xFEB00000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			QWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x0000000000000000, // Granularity
					0x0000000000010000, // Range Minimum
					0x000000000001FFFF, // Range Maximum
					0x0000000000000000, // Translation Offset
					0x0000000000010000, // Length
					,, , AddressRangeMemory, TypeStatic)
	})

	Name (P0RS, ResourceTemplate ()
	{
			WordBusNumber (ResourceProducer, MinFixed, MaxFixed, PosDecode,
					0x0000,             // Granularity
					0x0000,             // Range Minimum
					0x0015,             // Range Maximum
					0x0000,             // Translation Offset
					0x0016,             // Length
					,, )
			IO (Decode16,
					0x0CF8,             // Range Minimum
					0x0CF8,             // Range Maximum
					0x01,               // Alignment
					0x08,               // Length
					)
			WordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
					0x0000,             // Granularity
					0x0000,             // Range Minimum
					0x03AF,             // Range Maximum
					0x0000,             // Translation Offset
					0x03B0,             // Length
					,, , TypeStatic, DenseTranslation)
			WordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
					0x0000,             // Granularity
					0x03E0,             // Range Minimum
					0x0CF7,             // Range Maximum
					0x0000,             // Translation Offset
					0x0918,             // Length
					,, , TypeStatic, DenseTranslation)
			WordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
					0x0000,             // Granularity
					0x03B0,             // Range Minimum
					0x03BB,             // Range Maximum
					0x0000,             // Translation Offset
					0x000C,             // Length
					,, , TypeStatic, DenseTranslation)
			WordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
					0x0000,             // Granularity
					0x03C0,             // Range Minimum
					0x03DF,             // Range Maximum
					0x0000,             // Translation Offset
					0x0020,             // Length
					,, , TypeStatic, DenseTranslation)
			WordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
					0x0000,             // Granularity
					0x1000,             // Range Minimum
					0x3FFF,             // Range Maximum
					0x0000,             // Translation Offset
					0x3000,             // Length
					,, , TypeStatic, DenseTranslation)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x000A0000,         // Range Minimum
					0x000BFFFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00020000,         // Length
					,, , AddressRangeMemory, TypeStatic)

			/* TPM Area (0xfed40000-0xfed44fff) */
  	  DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000, 0xfed40000, 0xfed44fff, 0x00000000,
					0x00005000)

			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, Cacheable, ReadWrite,
					0x00000000,         // Granularity
					0x00000000,         // Range Minimum
					0x00000000,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00000000,         // Length
					,, _Y00, AddressRangeMemory, TypeStatic)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
					0x00000000,         // Granularity
					0xFE010000,         // Range Minimum
					0xFE010FFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x00001000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
					0x00000000,         // Granularity
					0x90000000,         // Range Minimum
					0xAAFFFFFF,         // Range Maximum
					0x00000000,         // Translation Offset
					0x1B000000,         // Length
					,, , AddressRangeMemory, TypeStatic)
			QWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
					0x0000000000000000, // Granularity
					0x0000380000000000, // Range Minimum
					0x000038003FFFFFFF, // Range Maximum
					0x0000000000000000, // Translation Offset
					0x0000000040000000, // Length
					,, , AddressRangeMemory, TypeStatic)
	})
	OperationRegion (TMEM, PCI_Config, 0x00, 0x0100)
	Field (TMEM, ByteAcc, NoLock, Preserve)
	{
			Offset (0x40), 
					,   4, 
			BSEG,   4, 
			PAMS,   48, 
			Offset (0x52), 
			DIM0,   4, 
			DIM1,   4, 
			Offset (0x54), 
			DIM2,   4
	}

	Name (MTBL, Package (0x10)
	{
			0x00, 
			0x20, 
			0x20, 
			0x30, 
			0x40, 
			0x40, 
			0x60, 
			0x80, 
			0x80, 
			0x80, 
			0x80, 
			0xC0, 
			0x0100, 
			0x0100, 
			0x0100, 
			0x0200
	})
	Name (ERNG, Package (0x0D)
	{
			0x000C0000, 
			0x000C4000, 
			0x000C8000, 
			0x000CC000, 
			0x000D0000, 
			0x000D4000, 
			0x000D8000, 
			0x000DC000, 
			0x000E0000, 
			0x000E4000, 
			0x000E8000, 
			0x000EC000, 
			0x000F0000
	})
	Name (PAMB, Buffer (0x07){})

	Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
	{
			Return (P0RS) /* \_SB_.PC00.P0RS */
	}

	Name (AR00, Package (0x28)
	{
			Package (0x04)
			{
					0x000FFFFF, 
					0x00, 
					0x00, 
					0x10
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x00, 
					0x00, 
					0x10
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x01, 
					0x00, 
					0x11
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x02, 
					0x00, 
					0x12
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x03, 
					0x00, 
					0x13
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x00, 
					0x00, 
					0x10
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x00, 
					0x00, 
					0x10
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x01, 
					0x00, 
					0x11
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x02, 
					0x00, 
					0x12
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x03, 
					0x00, 
					0x13
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x00, 
					0x00, 
					0x10
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x01, 
					0x00, 
					0x11
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x02, 
					0x00, 
					0x12
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x03, 
					0x00, 
					0x13
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x00, 
					0x00, 
					0x10
			}, 

			Package (0x04)
			{
					0x0018FFFF, 
					0x00, 
					0x00, 
					0x10
			}, 

			Package (0x04)
			{
					0x001BFFFF, 
					0x00, 
					0x00, 
					0x10
			}, 

			Package (0x04)
			{
					0x001BFFFF, 
					0x01, 
					0x00, 
					0x11
			}, 

			Package (0x04)
			{
					0x001BFFFF, 
					0x02, 
					0x00, 
					0x12
			}, 

			Package (0x04)
			{
					0x001BFFFF, 
					0x03, 
					0x00, 
					0x13
			}, 

			Package (0x04)
			{
					0x001CFFFF, 
					0x00, 
					0x00, 
					0x10
			}, 

			Package (0x04)
			{
					0x001CFFFF, 
					0x01, 
					0x00, 
					0x11
			}, 

			Package (0x04)
			{
					0x001CFFFF, 
					0x02, 
					0x00, 
					0x12
			}, 

			Package (0x04)
			{
					0x001CFFFF, 
					0x03, 
					0x00, 
					0x13
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x00, 
					0x00, 
					0x10
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x01, 
					0x00, 
					0x11
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x02, 
					0x00, 
					0x12
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x03, 
					0x00, 
					0x13
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x02, 
					0x00, 
					0x16
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x03, 
					0x00, 
					0x17
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x00, 
					0x00, 
					0x10
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					0x00, 
					0x1F
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x00, 
					0x00, 
					0x1A
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x01, 
					0x00, 
					0x1B
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x02, 
					0x00, 
					0x1A
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x03, 
					0x00, 
					0x1B
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x00, 
					0x00, 
					0x18
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x01, 
					0x00, 
					0x1C
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x02, 
					0x00, 
					0x1D
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x03, 
					0x00, 
					0x1E
			}
	})
	#include <soc/intel/skylake_sp/acpi/Pch.asl>
}

Device (PC01)
{
		Name (_HID, EisaId ("PNP0A08") /* PCI Express Bus */)  // _HID: Hardware ID
		Name (_CID, EisaId ("PNP0A03") /* PCI Bus */)  // _CID: Compatible ID
		Name (_ADR, 0x00)  // _ADR: Address
		Method (^BN10, 0, NotSerialized)
		{
				Return (0x10)
		}

		Method (_BBN, 0, NotSerialized)  // _BBN: BIOS Bus Number
		{
				Return (BN10 ())
		}

		Name (_UID, 0x01)  // _UID: Unique ID

		Name (SUPP, 0x00)
		Name (CTRL, 0x00)
		Name (_PXM, 0x00)  // _PXM: Device Proximity

		Name (PR01, ResourceTemplate ()
		{
				WordBusNumber (ResourceProducer, MinFixed, MaxFixed, PosDecode,
						0x0000,             // Granularity
						0x0016,             // Range Minimum
						0x0063,             // Range Maximum
						0x0000,             // Translation Offset
						0x004E,             // Length
						,, )
				WordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
						0x0000,             // Granularity
						0x4000,             // Range Minimum
						0x7FFF,             // Range Maximum
						0x0000,             // Translation Offset
						0x4000,             // Length
						,, , TypeStatic, DenseTranslation)
				DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
						0x00000000,         // Granularity
						0xAB000000,         // Range Minimum
						0xC5FFFFFF,         // Range Maximum
						0x00000000,         // Translation Offset
						0x1B000000,         // Length
						,, , AddressRangeMemory, TypeStatic)
				QWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
						0x0000000000000000, // Granularity
						0x0000380040000000, // Range Minimum
						0x000038007FFFFFFF, // Range Maximum
						0x0000000000000000, // Translation Offset
						0x0000000040000000, // Length
						,, , AddressRangeMemory, TypeStatic)
		})
		Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
		{
				Return (PR01) /* \_SB_.PC01.PR01 */
		}
}


Device (PC02)
{
		Name (_HID, EisaId ("PNP0A08") /* PCI Express Bus */)  // _HID: Hardware ID
		Name (_CID, EisaId ("PNP0A03") /* PCI Bus */)  // _CID: Compatible ID
		Name (_ADR, 0x00)  // _ADR: Address
		Method (^BN20, 0, NotSerialized)
		{
				Return (0x20)
		}

		Method (_BBN, 0, NotSerialized)  // _BBN: BIOS Bus Number
		{
				Return (BN20 ())
		}

		Name (_UID, 0x02)  // _UID: Unique ID
		Name (SUPP, 0x00)
		Name (CTRL, 0x00)
		Name (_PXM, 0x00)  // _PXM: Device Proximity

		Name (PR02, ResourceTemplate ()
		{
				WordBusNumber (ResourceProducer, MinFixed, MaxFixed, PosDecode,
						0x0000,             // Granularity
						0x0064,             // Range Minimum
						0x00B1,             // Range Maximum
						0x0000,             // Translation Offset
						0x004E,             // Length
						,, )
				WordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
						0x0000,             // Granularity
						0x8000,             // Range Minimum
						0xBFFF,             // Range Maximum
						0x0000,             // Translation Offset
						0x4000,             // Length
						,, , TypeStatic, DenseTranslation)
				DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
						0x00000000,         // Granularity
						0xC6000000,         // Range Minimum
						0xE0FFFFFF,         // Range Maximum
						0x00000000,         // Translation Offset
						0x1B000000,         // Length
						,, , AddressRangeMemory, TypeStatic)
				QWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
						0x0000000000000000, // Granularity
						0x0000380080000000, // Range Minimum
						0x00003800BFFFFFFF, // Range Maximum
						0x0000000000000000, // Translation Offset
						0x0000000040000000, // Length
						,, , AddressRangeMemory, TypeStatic)
		})
		Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
		{
				Return (PR02) /* \_SB_.PC02.PR02 */
		}
}

Device (PC03)
{
		Name (_HID, EisaId ("PNP0A08") /* PCI Express Bus */)  // _HID: Hardware ID
		Name (_CID, EisaId ("PNP0A03") /* PCI Bus */)  // _CID: Compatible ID
		Name (_ADR, 0x00)  // _ADR: Address
		Method (^BN28, 0, NotSerialized)
		{
				Return (0x28)
		}

		Method (_BBN, 0, NotSerialized)  // _BBN: BIOS Bus Number
		{
				Return (BN28 ())
		}

		Name (_UID, 0x03)  // _UID: Unique ID
		Name (SUPP, 0x00)
		Name (CTRL, 0x00)

		Name (PR03, ResourceTemplate ()
		{
				WordBusNumber (ResourceProducer, MinFixed, MaxFixed, PosDecode,
						0x0000,             // Granularity
						0x00B2,             // Range Minimum
						0x00FF,             // Range Maximum
						0x0000,             // Translation Offset
						0x004E,             // Length
						,, )
				WordIO (ResourceProducer, MinFixed, MaxFixed, PosDecode, EntireRange,
						0x0000,             // Granularity
						0xC000,             // Range Minimum
						0xFFFF,             // Range Maximum
						0x0000,             // Translation Offset
						0x4000,             // Length
						,, , TypeStatic, DenseTranslation)
				DWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
						0x00000000,         // Granularity
						0xE1000000,         // Range Minimum
						0xFBFFFFFF,         // Range Maximum
						0x00000000,         // Translation Offset
						0x1B000000,         // Length
						,, , AddressRangeMemory, TypeStatic)
				QWordMemory (ResourceProducer, PosDecode, MinFixed, MaxFixed, NonCacheable, ReadWrite,
						0x0000000000000000, // Granularity
						0x00003800C0000000, // Range Minimum
						0x00003800FFFFFFFF, // Range Maximum
						0x0000000000000000, // Translation Offset
						0x0000000040000000, // Length
						,, , AddressRangeMemory, TypeStatic)
		})
		Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
		{
				Return (PR03) /* \_SB_.PC03.PR03 */
		}
}
