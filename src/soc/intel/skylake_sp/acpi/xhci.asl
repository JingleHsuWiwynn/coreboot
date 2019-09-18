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

// 00:14.0 USB controller: Intel Corporation Lewisburg USB 3.0 xHCI Controller (rev 09) (prog-if 30 [XHCI])

Device (XHC1)
{
	Name (_ADR, 0x00140000)  // _ADR: Address

	Name (_PRW, Package(){ 0x0D, 3 }) // Power Resources for Wake

/*
	OperationRegion (XHCP, SystemMemory, (GPCB () + 0x000A0000), 0x0100)
	Field (XHCP, AnyAcc, Lock, Preserve)
	{
			Offset (0x04), 
			PDBM,   16, 
			Offset (0x10), 
			MEMB,   64
	}
*/

/*
	Method (_PRW, 0, NotSerialized)  // _PRW: Power Resources for Wake
	{
			Return (GPRW (0x6D, 0x04))
	}
*/


	// Leave USB ports on for to allow Wake from USB

	Method(_S3D,0)	// Highest D State in S3 State
	{
		Return (2)
	}

/*
	Device (HUB7)
	{
		Name (_ADR, 0x00000000)

		// How many are there?
		Device (PRT1) { Name (_ADR, 1) } // USB Port 0
		Device (PRT2) { Name (_ADR, 2) } // USB Port 1
		Device (PRT3) { Name (_ADR, 3) } // USB Port 2
		Device (PRT4) { Name (_ADR, 4) } // USB Port 3
		Device (PRT5) { Name (_ADR, 5) } // USB Port 4
		Device (PRT6) { Name (_ADR, 6) } // USB Port 5
	}
*/

		Device (RHUB)
		{
				Name (_ADR, Zero)  // _ADR: Address

				Device (HS01)
				{
						Name (_ADR, 0x01)  // _ADR: Address
				}

				Device (HS02)
				{
						Name (_ADR, 0x02)  // _ADR: Address
				}

				Device (HS03)
				{
						Name (_ADR, 0x03)  // _ADR: Address
				}

				Device (HS04)
				{
						Name (_ADR, 0x04)  // _ADR: Address
				}

				Device (HS05)
				{
						Name (_ADR, 0x05)  // _ADR: Address
				}

				Device (HS06)
				{
						Name (_ADR, 0x06)  // _ADR: Address
				}

				Device (HS07)
				{
						Name (_ADR, 0x07)  // _ADR: Address
				}

				Device (HS08)
				{
						Name (_ADR, 0x08)  // _ADR: Address
				}

				Device (HS09)
				{
						Name (_ADR, 0x09)  // _ADR: Address
				}

				Device (HS10)
				{
						Name (_ADR, 0x0A)  // _ADR: Address
				}


/*
				Device (USR1)
				{
						Method (_ADR, 0, NotSerialized)  // _ADR: Address
						{
								Return ((USRA () + 0x00))
						}
				}

				Device (USR2)
				{
						Method (_ADR, 0, NotSerialized)  // _ADR: Address
						{
								Return ((USRA () + 0x01))
						}
				}

				Device (SS01)
				{
						Method (_ADR, 0, NotSerialized)  // _ADR: Address
						{
								Return ((SSPA () + 0x00))
						}
				}

				Device (SS02)
				{
						Method (_ADR, 0, NotSerialized)  // _ADR: Address
						{
								Return ((SSPA () + 0x01))
						}
				}

				Device (SS03)
				{
						Method (_ADR, 0, NotSerialized)  // _ADR: Address
						{
								Return ((SSPA () + 0x02))
						}
				}

				Device (SS04)
				{
						Method (_ADR, 0, NotSerialized)  // _ADR: Address
						{
								Return ((SSPA () + 0x03))
						}
				}

				Device (SS05)
				{
						Method (_ADR, 0, NotSerialized)  // _ADR: Address
						{
								Return ((SSPA () + 0x04))
						}
				}

				Device (SS06)
				{
						Method (_ADR, 0, NotSerialized)  // _ADR: Address
						{
								Return ((SSPA () + 0x05))
						}
				}
*/
		}
}
