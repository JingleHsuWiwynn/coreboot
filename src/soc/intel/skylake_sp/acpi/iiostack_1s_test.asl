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

#include <intelblocks/itss.h>
#include <intelblocks/pcr.h>
#include <soc/iomap.h>
#include <soc/irq.h>
#include <soc/itss.h>
#include <soc/gpe.h>
#include <soc/pcr_ids.h>

#if 0
Scope(\)
{
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
#endif

Scope (_SB)
{
	#include "pirq_irqs.asl"
}

Device (PC00)
{
	Name (_HID, EisaId ("PNP0A08") /* PCI Express Bus */)  // _HID: Hardware ID
	Name (_CID, EisaId ("PNP0A03") /* PCI Bus */)  // _CID: Compatible ID
	Name (_ADR, 0x00)  // _ADR: Address

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

	Name (PR00, Package (0x28)
	{
			Package (0x04)
			{
					0x000FFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0010FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0011FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0014FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0016FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0017FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0018FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x001BFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x001BFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x001BFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x001BFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x001CFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x001CFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x001CFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x001CFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x001DFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x001EFFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x001FFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0xFFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0004FFFF, 
					0x03, 
					LNKD, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x00, 
					LNKA, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x01, 
					LNKB, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x02, 
					LNKC, 
					0x00
			}, 

			Package (0x04)
			{
					0x0008FFFF, 
					0x03, 
					LNKD, 
					0x00
			}
	})

	Method (_PRT, 0, NotSerialized)  // _PRT: PCI Routing Table
	{
			If (PICM)
			{
					Return (AR00) /* \_SB_.AR00 */
			}

			Return (PR00) /* \_SB_.PR00 */
	}
}
