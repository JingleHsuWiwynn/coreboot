#!/bin/bash -exu
make
vpd -f build/coreboot.rom -O -s 'Boot0000={"type": "localboot"}' -i RW_VPD
vpd -f build/coreboot.rom -l -i RW_VPD
