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

	// Leave USB ports on for to allow Wake from USB

	Method(_S3D,0)	// Highest D State in S3 State
	{
		Return (2)
	}

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

		}
}
