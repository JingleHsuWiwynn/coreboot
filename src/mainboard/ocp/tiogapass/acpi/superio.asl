//Scope(\_SB.P00.LPCB)
//{
    Name (SP1O, 0x2E)
                Device (SIO1)
                {
                    Name (_HID, EisaId ("PNP0C02") /* PNP Motherboard Resources */)  // _HID: Hardware ID
                    Name (_UID, 0x00)  // _UID: Unique ID
                    Name (CRS, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x0000,             // Range Minimum
                            0x0000,             // Range Maximum
                            0x00,               // Alignment
                            0x00,               // Length
                            _Y01)
                        IO (Decode16,
                            0x0000,             // Range Minimum
                            0x0000,             // Range Maximum
                            0x00,               // Alignment
                            0x00,               // Length
                            _Y02)
                        IO (Decode16,
                            0x0000,             // Range Minimum
                            0x0000,             // Range Maximum
                            0x00,               // Alignment
                            0x00,               // Length
                            _Y03)
                        IO (Decode16,
                            0x0000,             // Range Minimum
                            0x0000,             // Range Maximum
                            0x00,               // Alignment
                            0x00,               // Length
                            _Y04)
                        IO (Decode16,
                            0x0000,             // Range Minimum
                            0x0000,             // Range Maximum
                            0x00,               // Alignment
                            0x00,               // Length
                            _Y05)
                        IO (Decode16,
                            0x0000,             // Range Minimum
                            0x0000,             // Range Maximum
                            0x00,               // Alignment
                            0x00,               // Length
                            _Y06)
                    })
                    Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
                    {
                        If ((SP1O < 0x03F0) && (SP1O > 0xF0))
                        {
                            CreateWordField (CRS, \_SB.P00.LPCB.SIO1._Y01._MIN, GPI0)  // _MIN: Minimum Base Address
                            CreateWordField (CRS, \_SB.P00.LPCB.SIO1._Y01._MAX, GPI1)  // _MAX: Maximum Base Address
                            CreateByteField (CRS, \_SB.P00.LPCB.SIO1._Y01._LEN, GPIL)  // _LEN: Length
                            GPI0 = SP1O /* \SP1O */
                            GPI1 = SP1O /* \SP1O */
                            GPIL = 0x02
                        }

                        If (IO1B)
                        {
                            CreateWordField (CRS, \_SB.P00.LPCB.SIO1._Y02._MIN, GP10)  // _MIN: Minimum Base Address
                            CreateWordField (CRS, \_SB.P00.LPCB.SIO1._Y02._MAX, GP11)  // _MAX: Maximum Base Address
                            CreateByteField (CRS, \_SB.P00.LPCB.SIO1._Y02._LEN, GPL1)  // _LEN: Length
                            GP10 = IO1B /* \IO1B */
                            GP11 = IO1B /* \IO1B */
                            GPL1 = IO1L /* \IO1L */
                        }

                        If (IO2B)
                        {
                            CreateWordField (CRS, \_SB.P00.LPCB.SIO1._Y03._MIN, GP20)  // _MIN: Minimum Base Address
                            CreateWordField (CRS, \_SB.P00.LPCB.SIO1._Y03._MAX, GP21)  // _MAX: Maximum Base Address
                            CreateByteField (CRS, \_SB.P00.LPCB.SIO1._Y03._LEN, GPL2)  // _LEN: Length
                            GP20 = IO2B /* \IO2B */
                            GP21 = IO2B /* \IO2B */
                            GPL2 = IO2L /* \IO2L */
                        }

                        If (IO3B)
                        {
                            CreateWordField (CRS, \_SB.P00.LPCB.SIO1._Y04._MIN, GP30)  // _MIN: Minimum Base Address
                            CreateWordField (CRS, \_SB.P00.LPCB.SIO1._Y04._MAX, GP31)  // _MAX: Maximum Base Address
                            CreateByteField (CRS, \_SB.P00.LPCB.SIO1._Y04._LEN, GPL3)  // _LEN: Length
                            GP30 = IO3B /* \IO3B */
                            GP31 = IO3B /* \IO3B */
                            GPL3 = IO3L /* \IO3L */
                        }

                        If (IO4B)
                        {
                            CreateWordField (CRS, \_SB.P00.LPCB.SIO1._Y05._MIN, GP40)  // _MIN: Minimum Base Address
                            CreateWordField (CRS, \_SB.P00.LPCB.SIO1._Y05._MAX, GP41)  // _MAX: Maximum Base Address
                            CreateByteField (CRS, \_SB.P00.LPCB.SIO1._Y05._LEN, GPL4)  // _LEN: Length
                            GP40 = IO4B /* \IO4B */
                            GP41 = IO4B /* \IO4B */
                            GPL4 = IO4L /* \IO4L */
                        }

                        If (IO5B)
                        {
                            CreateWordField (CRS, \_SB.P00.LPCB.SIO1._Y06._MIN, GP50)  // _MIN: Minimum Base Address
                            CreateWordField (CRS, \_SB.P00.LPCB.SIO1._Y06._MAX, GP51)  // _MAX: Maximum Base Address
                            CreateByteField (CRS, \_SB.P00.LPCB.SIO1._Y06._LEN, GPL5)  // _LEN: Length
                            GP50 = IO5B /* \IO5B */
                            GP51 = IO5B /* \IO5B */
                            GPL5 = IO5L /* \IO5L */
                        }

                        Return (CRS) /* \_SB_.P00.LPCB.SIO1.CRS_ */
                    }

                    Name (DCAT, Package (0x15)
                    {
                        0x02, 
                        0x03, 
                        0xFF, 
                        0xFF, 
                        0xFF, 
                        0xFF, 
                        0xFF, 
                        0xFF, 
                        0xFF, 
                        0xFF, 
                        0x05, 
                        0xFF, 
                        0xFF, 
                        0xFF, 
                        0x05, 
                        0xFF, 
                        0xFF, 
                        0x0B, 
                        0x0C, 
                        0xFF, 
                        0xFF
                    })
                    Mutex (MUT0, 0x00)
                    Method (ENFG, 1, NotSerialized)
                    {
                        Acquire (MUT0, 0x0FFF)
                        INDX = ENTK /* \ENTK */
                        INDX = ENTK /* \ENTK */
                        LDN = Arg0
                    }

                    Method (EXFG, 0, NotSerialized)
                    {
                        INDX = EXTK /* \EXTK */
                        Release (MUT0)
                    }

                    Method (UHID, 1, NotSerialized)
                    {
                        Return (0x0105D041)
                    }

                    OperationRegion (IOID, SystemIO, SP1O, 0x02)
                    Field (IOID, ByteAcc, NoLock, Preserve)
                    {
                        INDX,   8, 
                        DATA,   8
                    }

                    IndexField (INDX, DATA, ByteAcc, NoLock, Preserve)
                    {
                        Offset (0x07), 
                        LDN,    8, 
                        Offset (0x21), 
                        SCF1,   8, 
                        SCF2,   8, 
                        SCF3,   8, 
                        SCF4,   8, 
                        SCF5,   8, 
                        SCF6,   8, 
                        Offset (0x29), 
                        CKCF,   8, 
                        Offset (0x2D), 
                        CR2D,   8, 
                        Offset (0x30), 
                        ACTR,   8, 
                        Offset (0x60), 
                        IOAH,   8, 
                        IOAL,   8, 
                        IOH2,   8, 
                        IOL2,   8, 
                        Offset (0x70), 
                        INTR,   4, 
                        INTT,   4, 
                        Offset (0x74), 
                        DMCH,   8, 
                        Offset (0xE0), 
                        RGE0,   8, 
                        RGE1,   8, 
                        RGE2,   8, 
                        RGE3,   8, 
                        RGE4,   8, 
                        RGE5,   8, 
                        RGE6,   8, 
                        RGE7,   8, 
                        RGE8,   8, 
                        RGE9,   8, 
                        Offset (0xF0), 
                        OPT0,   8, 
                        OPT1,   8, 
                        OPT2,   8, 
                        OPT3,   8, 
                        OPT4,   8, 
                        OPT5,   8, 
                        OPT6,   8, 
                        OPT7,   8, 
                        OPT8,   8, 
                        OPT9,   8
                    }

                    Method (CGLD, 1, NotSerialized)
                    {
                        Return (DerefOf (DCAT [Arg0]))
                    }

                    Method (DSTA, 1, NotSerialized)
                    {
                        ENFG (CGLD (Arg0))
                        Local0 = ACTR /* \_SB_.P00.LPCB.SIO1.ACTR */
                        EXFG ()
                        If (Local0 == 0xFF)
                        {
                            Return (0x00)
                        }

                        Local0 &= 0x01
                        If (Arg0 < 0x10)
                        {
                            IOST |= (Local0 << Arg0)
                        }

                        If (Local0)
                        {
                            Return (0x0F)
                        }
                        ElseIf (Arg0 < 0x10)
                        {
                            If ((0x01 << Arg0) & IOST)
                            {
                                Return (0x0D)
                            }
                            Else
                            {
                                Return (0x00)
                            }
                        }
                        Else
                        {
                            Return (0x00)
                        }
                    }

                    Method (ESTA, 1, NotSerialized)
                    {
                        ENFG (CGLD (Arg0))
                        Local0 = ACTR /* \_SB_.P00.LPCB.SIO1.ACTR */
                        EXFG ()
                        If (Local0 == 0xFF)
                        {
                            Return (0x00)
                        }

                        Local0 &= 0x01
                        If (Arg0 > 0x0F)
                        {
                            IOES |= (Local0 << (Arg0 & 0x0F))
                        }

                        If (Local0)
                        {
                            Return (0x0F)
                        }
                        ElseIf (Arg0 > 0x0F)
                        {
                            If ((0x01 << (Arg0 & 0x0F)) & IOES)
                            {
                                Return (0x0D)
                            }
                            Else
                            {
                                Return (0x00)
                            }
                        }
                        Else
                        {
                            Return (0x00)
                        }
                    }

                    Method (DCNT, 2, NotSerialized)
                    {
                        ENFG (CGLD (Arg0))
                        If ((DMCH < 0x04) && ((Local1 = (DMCH & 0x03)) != 0x00))
                        {
                            RDMA (Arg0, Arg1, Local1++)
                        }

                        ACTR = Arg1
                        Local1 = (IOAH << 0x08)
                        Local1 |= IOAL
                        RRIO (Arg0, Arg1, Local1, 0x08)
                        EXFG ()
                    }

                    Name (CRS1, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x0000,             // Range Minimum
                            0x0000,             // Range Maximum
                            0x01,               // Alignment
                            0x00,               // Length
                            _Y09)
                        IRQNoFlags (_Y07)
                            {}
                        DMA (Compatibility, NotBusMaster, Transfer8, _Y08)
                            {}
                    })
                    CreateWordField (CRS1, \_SB.P00.LPCB.SIO1._Y07._INT, IRQM)  // _INT: Interrupts
                    CreateByteField (CRS1, \_SB.P00.LPCB.SIO1._Y08._DMA, DMAM)  // _DMA: Direct Memory Access
                    CreateWordField (CRS1, \_SB.P00.LPCB.SIO1._Y09._MIN, IO11)  // _MIN: Minimum Base Address
                    CreateWordField (CRS1, \_SB.P00.LPCB.SIO1._Y09._MAX, IO12)  // _MAX: Maximum Base Address
                    CreateByteField (CRS1, \_SB.P00.LPCB.SIO1._Y09._LEN, LEN1)  // _LEN: Length
                    Name (CRS2, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x0000,             // Range Minimum
                            0x0000,             // Range Maximum
                            0x01,               // Alignment
                            0x00,               // Length
                            _Y0C)
                        IO (Decode16,
                            0x0000,             // Range Minimum
                            0x0000,             // Range Maximum
                            0x01,               // Alignment
                            0x00,               // Length
                            _Y0D)
                        IRQNoFlags (_Y0A)
                            {}
                        DMA (Compatibility, NotBusMaster, Transfer8, _Y0B)
                            {}
                    })
                    CreateWordField (CRS2, \_SB.P00.LPCB.SIO1._Y0A._INT, IRQE)  // _INT: Interrupts
                    CreateByteField (CRS2, \_SB.P00.LPCB.SIO1._Y0B._DMA, DMAE)  // _DMA: Direct Memory Access
                    CreateWordField (CRS2, \_SB.P00.LPCB.SIO1._Y0C._MIN, IO21)  // _MIN: Minimum Base Address
                    CreateWordField (CRS2, \_SB.P00.LPCB.SIO1._Y0C._MAX, IO22)  // _MAX: Maximum Base Address
                    CreateByteField (CRS2, \_SB.P00.LPCB.SIO1._Y0C._LEN, LEN2)  // _LEN: Length
                    CreateWordField (CRS2, \_SB.P00.LPCB.SIO1._Y0D._MIN, IO31)  // _MIN: Minimum Base Address
                    CreateWordField (CRS2, \_SB.P00.LPCB.SIO1._Y0D._MAX, IO32)  // _MAX: Maximum Base Address
                    CreateByteField (CRS2, \_SB.P00.LPCB.SIO1._Y0D._LEN, LEN3)  // _LEN: Length
                    Name (CRS3, ResourceTemplate ()
                    {
                        IO (Decode16,
                            0x0000,             // Range Minimum
                            0x0000,             // Range Maximum
                            0x01,               // Alignment
                            0x00,               // Length
                            _Y10)
                        IRQ (Level, ActiveLow, Shared, _Y0E)
                            {}
                        DMA (Compatibility, NotBusMaster, Transfer8, _Y0F)
                            {}
                    })
                    CreateWordField (CRS3, \_SB.P00.LPCB.SIO1._Y0E._INT, IRQT)  // _INT: Interrupts
                    CreateByteField (CRS3, \_SB.P00.LPCB.SIO1._Y0E._HE, IRQS)  // _HE_: High-Edge
                    CreateByteField (CRS3, \_SB.P00.LPCB.SIO1._Y0F._DMA, DMAT)  // _DMA: Direct Memory Access
                    CreateWordField (CRS3, \_SB.P00.LPCB.SIO1._Y10._MIN, IO41)  // _MIN: Minimum Base Address
                    CreateWordField (CRS3, \_SB.P00.LPCB.SIO1._Y10._MAX, IO42)  // _MAX: Maximum Base Address
                    CreateByteField (CRS3, \_SB.P00.LPCB.SIO1._Y10._LEN, LEN4)  // _LEN: Length
                    Method (DCRS, 2, NotSerialized)
                    {
                        ENFG (CGLD (Arg0))
                        IO11 = (IOAH << 0x08)
                        IO11 |= IOAL /* \_SB_.P00.LPCB.SIO1.IO11 */
                        IO12 = IO11 /* \_SB_.P00.LPCB.SIO1.IO11 */
                        LEN1 = 0x08
                        If (INTR)
                        {
                            IRQM = (0x01 << INTR) /* \_SB_.P00.LPCB.SIO1.INTR */
                        }
                        Else
                        {
                            IRQM = 0x00
                        }

                        If ((DMCH > 0x03) || (Arg1 == 0x00))
                        {
                            DMAM = 0x00
                        }
                        Else
                        {
                            Local1 = (DMCH & 0x03)
                            DMAM = (0x01 << Local1)
                        }

                        EXFG ()
                        Return (CRS1) /* \_SB_.P00.LPCB.SIO1.CRS1 */
                    }

                    Method (DCR2, 2, NotSerialized)
                    {
                        ENFG (CGLD (Arg0))
                        IO21 = (IOAH << 0x08)
                        IO21 |= IOAL /* \_SB_.P00.LPCB.SIO1.IO21 */
                        IO22 = IO21 /* \_SB_.P00.LPCB.SIO1.IO21 */
                        LEN2 = 0x08
                        IO31 = (IOH2 << 0x08)
                        IO31 |= IOL2 /* \_SB_.P00.LPCB.SIO1.IO31 */
                        IO32 = IO31 /* \_SB_.P00.LPCB.SIO1.IO31 */
                        LEN3 = 0x08
                        If (INTR)
                        {
                            IRQE = (0x01 << INTR) /* \_SB_.P00.LPCB.SIO1.INTR */
                        }
                        Else
                        {
                            IRQE = 0x00
                        }

                        If ((DMCH > 0x03) || (Arg1 == 0x00))
                        {
                            DMAE = 0x00
                        }
                        Else
                        {
                            Local1 = (DMCH & 0x03)
                            DMAE = (0x01 << Local1)
                        }

                        EXFG ()
                        Return (CRS2) /* \_SB_.P00.LPCB.SIO1.CRS2 */
                    }

                    Method (DCR3, 2, NotSerialized)
                    {
                        ENFG (CGLD (Arg0))
                        IO41 = (IOAH << 0x08)
                        IO41 |= IOAL /* \_SB_.P00.LPCB.SIO1.IO41 */
                        IO42 = IO41 /* \_SB_.P00.LPCB.SIO1.IO41 */
                        LEN4 = 0x08
                        If (INTR)
                        {
                            IRQT = (0x01 << INTR) /* \_SB_.P00.LPCB.SIO1.INTR */
                        }
                        Else
                        {
                            IRQT = 0x00
                        }

                        If ((DMCH > 0x03) || (Arg1 == 0x00))
                        {
                            DMAT = 0x00
                        }
                        Else
                        {
                            Local1 = (DMCH & 0x03)
                            DMAT = (0x01 << Local1)
                        }

                        EXFG ()
                        Return (CRS3) /* \_SB_.P00.LPCB.SIO1.CRS3 */
                    }

                    Method (DSRS, 2, NotSerialized)
                    {
                        CreateWordField (Arg0, 0x09, IRQM)
                        CreateByteField (Arg0, 0x0C, DMAM)
                        CreateWordField (Arg0, 0x02, IO11)
                        ENFG (CGLD (Arg1))
                        IOAL = (IO11 & 0xFF)
                        IOAH = (IO11 >> 0x08)
                        If (IRQM)
                        {
                            FindSetRightBit (IRQM, Local0)
                            INTR = (Local0 - 0x01)
                        }
                        Else
                        {
                            INTR = 0x00
                        }

                        If (DMAM)
                        {
                            FindSetRightBit (DMAM, Local0)
                            DMCH = (Local0 - 0x01)
                        }
                        Else
                        {
                            DMCH = 0x04
                        }

                        EXFG ()
                        DCNT (Arg1, 0x01)
                    }

                    Method (DSR2, 2, NotSerialized)
                    {
                        CreateWordField (Arg0, 0x11, IRQE)
                        CreateByteField (Arg0, 0x14, DMAE)
                        CreateWordField (Arg0, 0x02, IO21)
                        CreateWordField (Arg0, 0x0A, IO31)
                        ENFG (CGLD (Arg1))
                        IOAL = (IO21 & 0xFF)
                        IOAH = (IO21 >> 0x08)
                        IOL2 = (IO31 & 0xFF)
                        IOH2 = (IO31 >> 0x08)
                        If (IRQE)
                        {
                            FindSetRightBit (IRQE, Local0)
                            INTR = (Local0 - 0x01)
                        }
                        Else
                        {
                            INTR = 0x00
                        }

                        If (DMAE)
                        {
                            FindSetRightBit (DMAE, Local0)
                            DMCH = (Local0 - 0x01)
                        }
                        Else
                        {
                            DMCH = 0x04
                        }

                        EXFG ()
                        DCNT (Arg1, 0x01)
                    }

                    Method (DSR3, 2, NotSerialized)
                    {
                        CreateWordField (Arg0, 0x02, IO41)
                        CreateWordField (Arg0, 0x09, IRQT)
                        CreateByteField (Arg0, 0x0B, IRQS)
                        CreateByteField (Arg0, 0x0D, DMAT)
                        ENFG (CGLD (Arg1))
                        IOAL = (IO41 & 0xFF)
                        IOAH = (IO41 >> 0x08)
                        If (IRQT)
                        {
                            FindSetRightBit (IRQT, Local0)
                            INTR = (Local0 - 0x01)
                        }
                        Else
                        {
                            INTR = 0x00
                        }

                        If (DMAT)
                        {
                            FindSetRightBit (DMAT, Local0)
                            DMCH = (Local0 - 0x01)
                        }
                        Else
                        {
                            DMCH = 0x04
                        }

                        EXFG ()
                        DCNT (Arg1, 0x01)
                    }

                    Name (PMFG, 0x00)
                    Method (SIOS, 1, NotSerialized)
                    {
                        Debug = "SIOS"
                    }

                    Method (SIOW, 1, NotSerialized)
                    {
                        Debug = "SIOW"
                    }

                    Method (SIOH, 0, NotSerialized)
                    {
                    }

                    Method (_PRW, 0, NotSerialized)  // _PRW: Power Resources for Wake
                    {
                        Return (GPRW (0x1D, 0x03))
                    }
                }

                Device (UAR1)
                {
                    Name (_HID, EisaId ("PNP0501") /* 16550A-compatible COM Serial Port */)  // _HID: Hardware ID
                    Name (_UID, 0x00)  // _UID: Unique ID
                    Name (LDN, 0x02)
                    Method (_STA, 0, NotSerialized)  // _STA: Status
                    {
                        Return (^^SIO1.DSTA (0x00))
                    }

                    Method (_DIS, 0, NotSerialized)  // _DIS: Disable Device
                    {
                        ^^SIO1.DCNT (0x00, 0x00)
                    }

                    Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
                    {
                        Return (^^SIO1.DCRS (0x00, 0x00))
                    }

                    Method (_SRS, 1, NotSerialized)  // _SRS: Set Resource Settings
                    {
                        ^^SIO1.DSRS (Arg0, 0x00)
                    }

                    Name (_PRS, ResourceTemplate ()  // _PRS: Possible Resource Settings
                    {
                        StartDependentFn (0x00, 0x00)
                        {
                            IO (Decode16,
                                0x03F8,             // Range Minimum
                                0x03F8,             // Range Maximum
                                0x01,               // Alignment
                                0x08,               // Length
                                )
                            IRQNoFlags ()
                                {4}
                            DMA (Compatibility, NotBusMaster, Transfer8, )
                                {}
                        }
                        StartDependentFnNoPri ()
                        {
                            IO (Decode16,
                                0x03F8,             // Range Minimum
                                0x03F8,             // Range Maximum
                                0x01,               // Alignment
                                0x08,               // Length
                                )
                            IRQNoFlags ()
                                {3,4,5,7,9,10,11,12}
                            DMA (Compatibility, NotBusMaster, Transfer8, )
                                {}
                        }
                        StartDependentFnNoPri ()
                        {
                            IO (Decode16,
                                0x02F8,             // Range Minimum
                                0x02F8,             // Range Maximum
                                0x01,               // Alignment
                                0x08,               // Length
                                )
                            IRQNoFlags ()
                                {3,4,5,7,9,10,11,12}
                            DMA (Compatibility, NotBusMaster, Transfer8, )
                                {}
                        }
                        StartDependentFnNoPri ()
                        {
                            IO (Decode16,
                                0x03E8,             // Range Minimum
                                0x03E8,             // Range Maximum
                                0x01,               // Alignment
                                0x08,               // Length
                                )
                            IRQNoFlags ()
                                {3,4,5,7,9,10,11,12}
                            DMA (Compatibility, NotBusMaster, Transfer8, )
                                {}
                        }
                        StartDependentFnNoPri ()
                        {
                            IO (Decode16,
                                0x02E8,             // Range Minimum
                                0x02E8,             // Range Maximum
                                0x01,               // Alignment
                                0x08,               // Length
                                )
                            IRQNoFlags ()
                                {3,4,5,7,9,10,11,12}
                            DMA (Compatibility, NotBusMaster, Transfer8, )
                                {}
                        }
                        EndDependentFn ()
                    })
                }

                Device (UAR2)
                {
                    Name (_HID, EisaId ("PNP0501") /* 16550A-compatible COM Serial Port */)  // _HID: Hardware ID
                    Name (_UID, 0x01)  // _UID: Unique ID
                    Name (LDN, 0x03)
                    Method (_STA, 0, NotSerialized)  // _STA: Status
                    {
                        Return (^^SIO1.DSTA (0x01))
                    }

                    Method (_DIS, 0, NotSerialized)  // _DIS: Disable Device
                    {
                        ^^SIO1.DCNT (0x01, 0x00)
                    }

                    Method (_CRS, 0, NotSerialized)  // _CRS: Current Resource Settings
                    {
                        Return (^^SIO1.DCRS (0x01, 0x00))
                    }

                    Method (_SRS, 1, NotSerialized)  // _SRS: Set Resource Settings
                    {
                        ^^SIO1.DSRS (Arg0, 0x01)
                    }

                    Name (_PRS, ResourceTemplate ()  // _PRS: Possible Resource Settings
                    {
                        StartDependentFn (0x00, 0x00)
                        {
                            IO (Decode16,
                                0x02F8,             // Range Minimum
                                0x02F8,             // Range Maximum
                                0x01,               // Alignment
                                0x08,               // Length
                                )
                            IRQNoFlags ()
                                {3}
                            DMA (Compatibility, NotBusMaster, Transfer8, )
                                {}
                        }
                        StartDependentFnNoPri ()
                        {
                            IO (Decode16,
                                0x03F8,             // Range Minimum
                                0x03F8,             // Range Maximum
                                0x01,               // Alignment
                                0x08,               // Length
                                )
                            IRQNoFlags ()
                                {3,4,5,7,9,10,11,12}
                            DMA (Compatibility, NotBusMaster, Transfer8, )
                                {}
                        }
                        StartDependentFnNoPri ()
                        {
                            IO (Decode16,
                                0x02F8,             // Range Minimum
                                0x02F8,             // Range Maximum
                                0x01,               // Alignment
                                0x08,               // Length
                                )
                            IRQNoFlags ()
                                {3,4,5,7,9,10,11,12}
                            DMA (Compatibility, NotBusMaster, Transfer8, )
                                {}
                        }
                        StartDependentFnNoPri ()
                        {
                            IO (Decode16,
                                0x03E8,             // Range Minimum
                                0x03E8,             // Range Maximum
                                0x01,               // Alignment
                                0x08,               // Length
                                )
                            IRQNoFlags ()
                                {3,4,5,7,9,10,11,12}
                            DMA (Compatibility, NotBusMaster, Transfer8, )
                                {}
                        }
                        StartDependentFnNoPri ()
                        {
                            IO (Decode16,
                                0x02E8,             // Range Minimum
                                0x02E8,             // Range Maximum
                                0x01,               // Alignment
                                0x08,               // Length
                                )
                            IRQNoFlags ()
                                {3,4,5,7,9,10,11,12}
                            DMA (Compatibility, NotBusMaster, Transfer8, )
                                {}
                        }
                        EndDependentFn ()
                    })
                }
//}
