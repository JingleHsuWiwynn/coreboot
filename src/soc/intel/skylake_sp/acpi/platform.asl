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

/* Enable ACPI _SWS methods */
#include <soc/intel/common/acpi/acpi_wake_source.asl>

/* The APM port can be used for generating software SMIs */

OperationRegion (APMP, SystemIO, 0xb2, 2)
Field (APMP, ByteAcc, NoLock, Preserve)
{
	APMC, 8,	// APM command
	APMS, 8		// APM status
}

/* Port 80 POST */

OperationRegion (POST, SystemIO, 0x80, 1)
Field (POST, ByteAcc, Lock, Preserve)
{
	DBG0, 8
}

/* IO-Trap at 0x800.
 * This is the ACPI->SMI communication interface.
 */
OperationRegion (IO_T, SystemIO, 0x800, 0x10)
Field (IO_T, ByteAcc, NoLock, Preserve)
{
	Offset (0x8),
	TRP0, 8		/* IO-Trap at 0x808 */
}

    OperationRegion (PSYS, SystemMemory, 0x6D081000, 0x0400)
    Field (PSYS, ByteAcc, NoLock, Preserve)
    {
        PLAT,   32, 
        APC0,   1, 
        AP00,   1, 
        AP01,   1, 
        AP02,   1, 
        AP03,   1, 
        AP04,   1, 
        AP05,   1, 
        AP06,   1, 
        AP07,   1, 
        AP08,   1, 
        AP09,   1, 
        AP10,   1, 
        AP11,   1, 
        AP12,   1, 
        AP13,   1, 
        AP14,   1, 
        AP15,   1, 
        AP16,   1, 
        AP17,   1, 
        AP18,   1, 
        AP19,   1, 
        AP20,   1, 
        AP21,   1, 
        AP22,   1, 
        AP23,   1, 
        RESA,   7, 
        SKOV,   1, 
        RES0,   7, 
        TPME,   1, 
        CSEN,   1, 
        C3EN,   1, 
        C6EN,   1, 
        C7EN,   1, 
        MWOS,   1, 
        PSEN,   1, 
        EMCA,   1, 
        HWAL,   2, 
        KPRS,   1, 
        MPRS,   1, 
        TSEN,   1, 
        FGTS,   1, 
        OSCX,   1, 
        RESX,   1, 
        CPHP,   8, 
        IIOP,   8, 
        IIOH,   64, 
        PRBM,   32, 
        P0ID,   32, 
        P1ID,   32, 
        P2ID,   32, 
        P3ID,   32, 
        P4ID,   32, 
        P5ID,   32, 
        P6ID,   32, 
        P7ID,   32, 
        P0BM,   64, 
        P1BM,   64, 
        P2BM,   64, 
        P3BM,   64, 
        P4BM,   64, 
        P5BM,   64, 
        P6BM,   64, 
        P7BM,   64, 
        MEBM,   16, 
        MEBC,   16, 
        CFMM,   32, 
        TSSZ,   32, 
        M0BS,   64, 
        M1BS,   64, 
        M2BS,   64, 
        M3BS,   64, 
        M4BS,   64, 
        M5BS,   64, 
        M6BS,   64, 
        M7BS,   64, 
        M0RN,   64, 
        M1RN,   64, 
        M2RN,   64, 
        M3RN,   64, 
        M4RN,   64, 
        M5RN,   64, 
        M6RN,   64, 
        M7RN,   64, 
        SMI0,   32, 
        SMI1,   32, 
        SMI2,   32, 
        SMI3,   32, 
        SCI0,   32, 
        SCI1,   32, 
        SCI2,   32, 
        SCI3,   32, 
        MADD,   64, 
        CUU0,   128, 
        CUU1,   128, 
        CUU2,   128, 
        CUU3,   128, 
        CUU4,   128, 
        CUU5,   128, 
        CUU6,   128, 
        CUU7,   128, 
        CPSP,   8, 
        ME00,   128, 
        ME01,   128, 
        ME10,   128, 
        ME11,   128, 
        ME20,   128, 
        ME21,   128, 
        ME30,   128, 
        ME31,   128, 
        ME40,   128, 
        ME41,   128, 
        ME50,   128, 
        ME51,   128, 
        ME60,   128, 
        ME61,   128, 
        ME70,   128, 
        ME71,   128, 
        MESP,   16, 
        LDIR,   64, 
        PRID,   32, 
        AHPE,   8, 
        DHRD,   192, 
        ATSR,   192, 
        RHSA,   192, 
        WSIC,   8, 
        WSIS,   16, 
        WSIB,   8, 
        WSID,   8, 
        WSIF,   8, 
        WSTS,   8, 
        WHEA,   8, 
        BGMA,   64, 
        BGMS,   8, 
        BGIO,   16, 
        BGIL,   8, 
        CNBS,   8, 
        XHMD,   8, 
        SBV1,   8, 
        SBV2,   8, 
        HWEN,   2, 
        ACEN,   1, 
        HWPI,   1, 
        RES1,   4, 
        BB00,   8, 
        BB01,   8, 
        BB02,   8, 
        BB03,   8, 
        BB04,   8, 
        BB05,   8, 
        BB06,   8, 
        BB07,   8, 
        BB08,   8, 
        BB09,   8, 
        BB10,   8, 
        BB11,   8, 
        BB12,   8, 
        BB13,   8, 
        BB14,   8, 
        BB15,   8, 
        BB16,   8, 
        BB17,   8, 
        BB18,   8, 
        BB19,   8, 
        BB20,   8, 
        BB21,   8, 
        BB22,   8, 
        BB23,   8, 
        BB24,   8, 
        BB25,   8, 
        BB26,   8, 
        BB27,   8, 
        BB28,   8, 
        BB29,   8, 
        BB30,   8, 
        BB31,   8, 
        BB32,   8, 
        BB33,   8, 
        BB34,   8, 
        BB35,   8, 
        BB36,   8, 
        BB37,   8, 
        BB38,   8, 
        BB39,   8, 
        BB40,   8, 
        BB41,   8, 
        BB42,   8, 
        BB43,   8, 
        BB44,   8, 
        BB45,   8, 
        BB46,   8, 
        BB47,   8, 
        SGEN,   8, 
        SG00,   8, 
        SG01,   8, 
        SG02,   8, 
        SG03,   8, 
        SG04,   8, 
        SG05,   8, 
        SG06,   8, 
        SG07,   8, 
        CLOD,   8, 
        XTUB,   32, 
        XTUS,   32, 
        XMBA,   32, 
        DDRF,   8, 
        RT3S,   8, 
        RTP0,   8, 
        RTP3,   8, 
        FBB0,   8, 
        FBB1,   8, 
        FBB2,   8, 
        FBB3,   8, 
        FBB4,   8, 
        FBB5,   8, 
        FBB6,   8, 
        FBB7,   8, 
        FBL0,   8, 
        FBL1,   8, 
        FBL2,   8, 
        FBL3,   8, 
        FBL4,   8, 
        FBL5,   8, 
        FBL6,   8, 
        FBL7,   8, 
        P0FB,   8, 
        P1FB,   8, 
        P2FB,   8, 
        P3FB,   8, 
        P4FB,   8, 
        P5FB,   8, 
        P6FB,   8, 
        P7FB,   8, 
        FMB0,   32, 
        FMB1,   32, 
        FMB2,   32, 
        FMB3,   32, 
        FMB4,   32, 
        FMB5,   32, 
        FMB6,   32, 
        FMB7,   32, 
        FML0,   32, 
        FML1,   32, 
        FML2,   32, 
        FML3,   32, 
        FML4,   32, 
        FML5,   32, 
        FML6,   32, 
        FML7,   32, 
        FKPB,   32, 
        FKB0,   8, 
        FKB1,   8, 
        FKB2,   8, 
        FKB3,   8, 
        FKB4,   8, 
        FKB5,   8, 
        FKB6,   8, 
        FKB7,   8
    }

/* SMI I/O Trap */
Method (TRAP, 1, Serialized)
{
	Store (Arg0, SMIF)	// SMI Function
	Store (0, TRP0)		// Generate trap
	Return (SMIF)		// Return value of SMI handler
}

/*
 * The _PIC method is called by the OS to choose between interrupt
 * routing via the i8259 interrupt controller or the APIC.
 *
 * _PIC is called with a parameter of 0 for i8259 configuration and
 * with a parameter of 1 for Local Apic/IOAPIC configuration.
 */

Method (_PIC, 1)
{
	/* Remember the OS' IRQ routing choice. */
	Store (Arg0, PICM)
}

/*
 * The _PTS method (Prepare To Sleep) is called before the OS is
 * entering a sleep state. The sleep state number is passed in Arg0
 */

Method (_PTS, 1)
{
}

/* The _WAK method is called on system wakeup */

Method (_WAK, 1)
{
	Return (Package (){ 0, 0 })
}
