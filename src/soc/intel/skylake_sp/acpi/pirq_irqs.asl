/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2007-2009 coresystems GmbH
 * Copyright (C) 2014 Google Inc.
 * Copyright (C) 2015 Intel Corporation.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

/*
 * PIRQ routing control is in PCR ITSS region.
 *
 * Due to what appears to be an ACPI interpreter bug we do not use
 * the PCRB() method here as it may not be defined yet because the method
 * definiton depends on the order of the include files in pch.asl.
 *
 * https://bugs.acpica.org/show_bug.cgi?id=1201
 */

/* 
   Refer to Intel® C620 Series Chipset Platform Controller Hub section 20.11
   CONFIG_PCR_BASE_ADDRESS 0xfd000000 0x3100
   (0xfd000000 | ((uint8_t)(0xC4) << 16) | (uint16_t)(0x3100) = 0xFDC43100
*/

OperationRegion (ITSS, SystemMemory,
		 Add (PCR_ITSS_PIRQA_ROUT,
		      Add (CONFIG_PCR_BASE_ADDRESS,
		           ShiftLeft (PID_ITSS, PCR_PORTID_SHIFT))), 8)
Field (ITSS, ByteAcc, NoLock, Preserve)
{
	PIRA, 8,	/* PIRQA Routing Control */
	PIRB, 8,	/* PIRQB Routing Control */
	PIRC, 8,	/* PIRQC Routing Control */
	PIRD, 8,	/* PIRQD Routing Control */
	PIRE, 8,	/* PIRQE Routing Control */
	PIRF, 8,	/* PIRQF Routing Control */
	PIRG, 8,	/* PIRQG Routing Control */
	PIRH, 8,	/* PIRQH Routing Control */
}

Name (IREN, 0x80)	/* Interrupt Routing Enable */
Name (IREM, 0x0f)	/* Interrupt Routing Mask */

Name (PRSA, ResourceTemplate ()
{
		IRQ (Level, ActiveLow, Shared, )
				{3,4,5,6,7,10,11,12,14,15}
})
Alias (PRSA, PRSB)
Name (PRSC, ResourceTemplate ()
{
		IRQ (Level, ActiveLow, Shared, )
				{3,4,5,6,10,11,12,14,15}
})
Alias (PRSC, PRSD)
Alias (PRSA, PRSE)
Alias (PRSA, PRSF)
Alias (PRSA, PRSG)
Alias (PRSA, PRSH)

Device (LNKA)
{
	Name (_HID, EISAID ("PNP0C0F"))
	Name (_UID, 1)

	Method (_PRS, 0, NotSerialized)  // _PRS: Possible Resource Settings
  {
		Return (PRSA) /* \_SB_.PRSA */
	}

	Method (_CRS, 0, Serialized)
	{
		Name (RTLA, ResourceTemplate ()
		{
			IRQ (Level, ActiveLow, Shared) {}
		})
		CreateWordField (RTLA, 1, IRQ0)
		Store (Zero, IRQ0)

		/* Set the bit from PIRQ Routing Register */
		ShiftLeft (1, And (^^PIRA, ^^IREM), IRQ0)

		Return (RTLA)
	}

	Method (_SRS, 1, Serialized)
	{
		CreateWordField (Arg0, 1, IRQ0)
		FindSetRightBit (IRQ0, Local0)
		Decrement (Local0)
		Store (Local0, ^^PIRA)
	}

	Method (_STA, 0, Serialized)
	{
		If (And (^^PIRA, ^^IREN)) {
			Return (0x9)
		} Else {
			Return (0xb)
		}
	}

	Method (_DIS, 0, Serialized)
	{
		Or (^^PIRA, ^^IREN, ^^PIRA)
	}
}

Device (LNKB)
{
	Name (_HID, EISAID ("PNP0C0F"))
	Name (_UID, 2)

	Method (_PRS, 0, NotSerialized)  // _PRS: Possible Resource Settings
  {
		Return (PRSB) /* \_SB_.PRSB */
	}

	Method (_CRS, 0, Serialized)
	{
		Name (RTLA, ResourceTemplate ()
		{
			IRQ (Level, ActiveLow, Shared) {}
		})
		CreateWordField (RTLA, 1, IRQ0)
		Store (Zero, IRQ0)

		/* Set the bit from PIRQ Routing Register */
		ShiftLeft (1, And (^^PIRB, ^^IREM), IRQ0)

		Return (RTLA)
	}

	Method (_SRS, 1, Serialized)
	{
		CreateWordField (Arg0, 1, IRQ0)
		FindSetRightBit (IRQ0, Local0)
		Decrement (Local0)
		Store (Local0, ^^PIRB)
	}

	Method (_STA, 0, Serialized)
	{
		If (And (^^PIRB, ^^IREN)) {
			Return (0x9)
		} Else {
			Return (0xb)
		}
	}

	Method (_DIS, 0, Serialized)
	{
		Or (^^PIRB, ^^IREN, ^^PIRB)
	}
}

Device (LNKC)
{
	Name (_HID, EISAID ("PNP0C0F"))
	Name (_UID, 3)

	Method (_PRS, 0, NotSerialized)  // _PRS: Possible Resource Settings
  {
		Return (PRSC) /* \_SB_.PRSC */
	}

	Method (_CRS, 0, Serialized)
	{
		Name (RTLA, ResourceTemplate ()
		{
			IRQ (Level, ActiveLow, Shared) {}
		})
		CreateWordField (RTLA, 1, IRQ0)
		Store (Zero, IRQ0)

		/* Set the bit from PIRQ Routing Register */
		ShiftLeft (1, And (^^PIRC, ^^IREM), IRQ0)

		Return (RTLA)
	}

	Method (_SRS, 1, Serialized)
	{
		CreateWordField (Arg0, 1, IRQ0)
		FindSetRightBit (IRQ0, Local0)
		Decrement (Local0)
		Store (Local0, ^^PIRC)
	}

	Method (_STA, 0, Serialized)
	{
		If (And (^^PIRC, ^^IREN)) {
			Return (0x9)
		} Else {
			Return (0xb)
		}
	}

	Method (_DIS, 0, Serialized)
	{
		Or (^^PIRC, ^^IREN, ^^PIRC)
	}
}

Device (LNKD)
{
	Name (_HID, EISAID ("PNP0C0F"))
	Name (_UID, 4)

	Method (_PRS, 0, NotSerialized)  // _PRS: Possible Resource Settings
  {
		Return (PRSD) /* \_SB_.PRSD */
	}

	Method (_CRS, 0, Serialized)
	{
		Name (RTLA, ResourceTemplate ()
		{
			IRQ (Level, ActiveLow, Shared) {}
		})
		CreateWordField (RTLA, 1, IRQ0)
		Store (Zero, IRQ0)

		/* Set the bit from PIRQ Routing Register */
		ShiftLeft (1, And (^^PIRD, ^^IREM), IRQ0)

		Return (RTLA)
	}

	Method (_SRS, 1, Serialized)
	{
		CreateWordField (Arg0, 1, IRQ0)
		FindSetRightBit (IRQ0, Local0)
		Decrement (Local0)
		Store (Local0, ^^PIRD)
	}

	Method (_STA, 0, Serialized)
	{
		If (And (^^PIRD, ^^IREN)) {
			Return (0x9)
		} Else {
			Return (0xb)
		}
	}

	Method (_DIS, 0, Serialized)
	{
		Or (^^PIRD, ^^IREN, ^^PIRD)
	}
}

Device (LNKE)
{
	Name (_HID, EISAID ("PNP0C0F"))
	Name (_UID, 5)

	Method (_PRS, 0, NotSerialized)  // _PRS: Possible Resource Settings
  {
		Return (PRSE) /* \_SB_.PRSE */
	}

	Method (_CRS, 0, Serialized)
	{
		Name (RTLA, ResourceTemplate ()
		{
			IRQ (Level, ActiveLow, Shared) {}
		})
		CreateWordField (RTLA, 1, IRQ0)
		Store (Zero, IRQ0)

		/* Set the bit from PIRQ Routing Register */
		ShiftLeft (1, And (^^PIRE, ^^IREM), IRQ0)

		Return (RTLA)
	}

	Method (_SRS, 1, Serialized)
	{
		CreateWordField (Arg0, 1, IRQ0)
		FindSetRightBit (IRQ0, Local0)
		Decrement (Local0)
		Store (Local0, ^^PIRE)
	}

	Method (_STA, 0, Serialized)
	{
		If (And (^^PIRE, ^^IREN)) {
			Return (0x9)
		} Else {
			Return (0xb)
		}
	}

	Method (_DIS, 0, Serialized)
	{
		Or (^^PIRE, ^^IREN, ^^PIRE)
	}
}

Device (LNKF)
{
	Name (_HID, EISAID ("PNP0C0F"))
	Name (_UID, 6)

	Method (_PRS, 0, NotSerialized)  // _PRS: Possible Resource Settings
  {
		Return (PRSF) /* \_SB_.PRSF */
	}

	Method (_CRS, 0, Serialized)
	{
		Name (RTLA, ResourceTemplate ()
		{
			IRQ (Level, ActiveLow, Shared) {}
		})
		CreateWordField (RTLA, 1, IRQ0)
		Store (Zero, IRQ0)

		/* Set the bit from PIRQ Routing Register */
		ShiftLeft (1, And (^^PIRF, ^^IREM), IRQ0)

		Return (RTLA)
	}

	Method (_SRS, 1, Serialized)
	{
		CreateWordField (Arg0, 1, IRQ0)
		FindSetRightBit (IRQ0, Local0)
		Decrement (Local0)
		Store (Local0, ^^PIRF)
	}

	Method (_STA, 0, Serialized)
	{
		If (And (^^PIRF, ^^IREN)) {
			Return (0x9)
		} Else {
			Return (0xb)
		}
	}

	Method (_DIS, 0, Serialized)
	{
		Or (^^PIRF, ^^IREN, ^^PIRF)
	}
}

Device (LNKG)
{
	Name (_HID, EISAID ("PNP0C0F"))
	Name (_UID, 7)

	Method (_PRS, 0, NotSerialized)  // _PRS: Possible Resource Settings
  {
		Return (PRSG) /* \_SB_.PRSG */
	}

	Method (_CRS, 0, Serialized)
	{
		Name (RTLA, ResourceTemplate ()
		{
			IRQ (Level, ActiveLow, Shared) {}
		})
		CreateWordField (RTLA, 1, IRQ0)
		Store (Zero, IRQ0)

		/* Set the bit from PIRQ Routing Register */
		ShiftLeft (1, And (^^PIRG, ^^IREM), IRQ0)

		Return (RTLA)
	}

	Method (_SRS, 1, Serialized)
	{
		CreateWordField (Arg0, 1, IRQ0)
		FindSetRightBit (IRQ0, Local0)
		Decrement (Local0)
		Store (Local0, ^^PIRG)
	}

	Method (_STA, 0, Serialized)
	{
		If (And (^^PIRG, ^^IREN)) {
			Return (0x9)
		} Else {
			Return (0xb)
		}
	}

	Method (_DIS, 0, Serialized)
	{
		Or (^^PIRG, ^^IREN, ^^PIRG)
	}
}

Device (LNKH)
{
	Name (_HID, EISAID ("PNP0C0F"))
	Name (_UID, 8)

	Method (_PRS, 0, NotSerialized)  // _PRS: Possible Resource Settings
  {
		Return (PRSH) /* \_SB_.PRSH */
	}

	Method (_CRS, 0, Serialized)
	{
		Name (RTLA, ResourceTemplate ()
		{
			IRQ (Level, ActiveLow, Shared) {}
		})
		CreateWordField (RTLA, 1, IRQ0)
		Store (Zero, IRQ0)

		/* Set the bit from PIRQ Routing Register */
		ShiftLeft (1, And (^^PIRH, ^^IREM), IRQ0)

		Return (RTLA)
	}

	Method (_SRS, 1, Serialized)
	{
		CreateWordField (Arg0, 1, IRQ0)
		FindSetRightBit (IRQ0, Local0)
		Decrement (Local0)
		Store (Local0, ^^PIRH)
	}

	Method (_STA, 0, Serialized)
	{
		If (And (^^PIRH, ^^IREN)) {
			Return (0x9)
		} Else {
			Return (0xb)
		}
	}

	Method (_DIS, 0, Serialized)
	{
		Or (^^PIRH, ^^IREN, ^^PIRH)
	}
}
