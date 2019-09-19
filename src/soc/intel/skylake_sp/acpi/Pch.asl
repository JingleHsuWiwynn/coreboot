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

// SATA 0:13.0
#include "sata.asl"

// SATA 0:14.0
#include "sata2.asl"

// PMC 0:1f.0
#include "lpc.asl"

// PMC 0:1f.2
#include "pmc.asl"

// XHCI 00:14.0
#include "xhci.asl"

// SMBus 00:1F.4
#include "smbus.asl"

#include "pcie.asl"

Device (PRRE)
{
		Name (_HID, EisaId ("PNP0C02") /* PNP Motherboard Resources */)  // _HID: Hardware ID
		Name (_UID, "PCHRESV")  // _UID: Unique ID
		Name (_STA, 0x03)  // _STA: Status
		Method (_CRS, 0, Serialized)  // _CRS: Current Resource Settings
		{
				Name (BUF0, ResourceTemplate ()
				{
						Memory32Fixed (ReadWrite,
								0xFD000000,         // Address Base
								0x00AC0000,         // Address Length
								)
						Memory32Fixed (ReadWrite,
								0xFDAD0000,         // Address Base
								0x00010000,         // Address Length
								)
						Memory32Fixed (ReadWrite,
								0xFDB00000,         // Address Base
								0x00500000,         // Address Length
								)
						Memory32Fixed (ReadWrite,
								0xFE000000,         // Address Base
								0x00010000,         // Address Length
								)
						Memory32Fixed (ReadWrite,
								0xFE011000,         // Address Base
								0x0000F000,         // Address Length
								)
						Memory32Fixed (ReadWrite,
								0xFE036000,         // Address Base
								0x00006000,         // Address Length
								)
						Memory32Fixed (ReadWrite,
								0xFE03D000,         // Address Base
								0x003C3000,         // Address Length
								)
						Memory32Fixed (ReadWrite,
								0xFE410000,         // Address Base
								0x003F0000,         // Address Length
								)
				})
				Return (BUF0) /* \_SB_.PC00.PRRE._CRS.BUF0 */
		}
}

Device (TERM)
{
	Name (_ADR, 0x00140002)  // _ADR: Address
	Name (_HID, "INT343D")  // _HID: Hardware ID
	Name (_UID, 0x01)  // _UID: Unique ID
	Name (RBUF, ResourceTemplate ()
	{
			Memory32Fixed (ReadWrite,
					0xFE03C000,         // Address Base
					0x00001000,         // Address Length
					)
			Interrupt (ResourceConsumer, Level, ActiveLow, Shared, ,, _Y1D)
			{
					0x00000012,
			}
	})
	//CreateDWordField (RBUF, \_SB.PC00.TERM._Y1D._INT, IRQN)  // _INT: Interrupts
	Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
	{
			//IRQN = TIRQ /* \TIRQ */
			Return (RBUF) /* \_SB_.PC00.TERM.RBUF */
	}

	Method (_STA, 0, NotSerialized)  // _STA: Status
	{
			Return (0x0F)
	}
}

