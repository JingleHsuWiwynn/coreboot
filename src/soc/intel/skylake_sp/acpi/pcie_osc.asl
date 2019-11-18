            Method (_OSC, 4, NotSerialized)  // _OSC: Operating System Capabilities
            {
                CreateDWordField (Arg3, 0x00, CDW1)
                If (Arg0 == ToUUID ("33db4d5b-1ff7-401c-9657-7441c03dd766") /* PCI Host Bridge Device */)
                {
                    CreateDWordField (Arg3, 0x04, CDW2)
                    If (Arg2 > 0x02)
                    {
                        CreateDWordField (Arg3, 0x08, CDW3)
                    }

                    SUPP = CDW2 /* \_SB_.PC00._OSC.CDW2 */
                    CTRL = CDW3 /* \_SB_.PC00._OSC.CDW3 */
                    If (AHPE || ((SUPP & 0x16) != 0x16))
                    {
                        CTRL &= 0x1E
                        Sleep (0x03E8)
                    }

                    CTRL &= 0x1D
                    CTRL &= 0x17
                    If (Arg1 != One)
                    {
                        CDW1 |= 0x08
                    }

                    If (CDW3 != CTRL)
                    {
                        CDW1 |= 0x10
                    }

                    CDW3 = CTRL /* \_SB_.PC00.CTRL */
                    Return (Arg3)
                }
                Else
                {
                    CDW1 |= 0x04
                    IO80 = 0xEE
                    Return (Arg3)
                }
            }
