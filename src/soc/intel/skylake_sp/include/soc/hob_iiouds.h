//
// This file contains an 'Intel Peripheral Driver' and is
// licensed for Intel CPUs and chipsets under the terms of your
// license agreement with Intel or your vendor.  This file may
// be modified by the user, subject to additional terms of the
// license agreement
//
/**

Copyright (c) 1999 -  2018 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.


  @file IioUniveralData.h

  Data format for Universal Data Structure

**/

#ifndef _HOB_IIOUDS_H_
#define _HOB_IIOUDS_H_

#include <fsp/util.h>
#define MAX_IIO_STACK                 6
#define MAX_KTI_PORTS                 3
#define MAX_SOCKET                    2
#define NUMBER_PORTS_PER_SOCKET       21
#define MaxIIO                        MAX_SOCKET
#define CONFIG_TDP_MAX_LEVEL          5
#define MAX_IMC                       2
#define MC_MAX_NODE                   (MAX_SOCKET * MAX_IMC)

#define FSP_HOB_IIO_UNIVERSAL_DATA_GUID { \
  0xa1, 0x96, 0xf3, 0x7f, 0x7d, 0xee, 0x1e, 0x43, \
  0xba, 0x53, 0x8f, 0xCa, 0x12, 0x7c, 0x44, 0xc0  \
}

//--------------------------------------------------------------------------------------//
// Structure definitions for Universal Data Store (UDS)
//--------------------------------------------------------------------------------------//
#define UINT64  unsigned long long

typedef struct u64_struct {
  UINT32  lo;
  UINT32  hi;
} UINT64_STRUCT;

typedef struct {
    UINT8       Device;
    UINT8       Function;
} IIO_PORT_INFO;

#pragma pack(1)

typedef struct {
  UINT8                     Valid;         // TRUE, if the link is valid (i.e reached normal operation)
  UINT8                     PeerSocId;     // Socket ID
  UINT8                     PeerSocType;   // Socket Type (0 - CPU; 1 - IIO)
  UINT8                     PeerPort;      // Port of the peer socket
}QPI_PEER_DATA;

typedef struct {
  UINT8                     Valid;
  UINT8                     SocketFirstBus;
  UINT8                     SocketLastBus;
  UINT8                     segmentSocket;
  UINT8                     PcieSegment;
  UINT64_STRUCT             SegMmcfgBase;
  UINT8                     stackPresentBitmap;
  UINT8                     StackBus[MAX_IIO_STACK];
  UINT8                     M2PciePresentBitmap;
  UINT8                     TotM3Kti;   
  UINT8                     TotCha;
  UINT32                    ChaList;
  UINT32                    SocId;
  QPI_PEER_DATA             PeerInfo[MAX_KTI_PORTS];    // QPI LEP info
} QPI_CPU_DATA;

typedef struct {
  UINT8                     Valid;
  UINT8                     SocId;
  QPI_PEER_DATA             PeerInfo[MAX_SOCKET];    // QPI LEP info
} QPI_IIO_DATA;

typedef struct {
    IIO_PORT_INFO           PortInfo[NUMBER_PORTS_PER_SOCKET];
} IIO_DMI_PCIE_INFO;

typedef struct _STACK_RES {
  UINT8                   Personality;
  UINT8                   BusBase;
  UINT8                   BusLimit;
  UINT16                  PciResourceIoBase;
  UINT16                  PciResourceIoLimit;
  UINT32                  IoApicBase;
  UINT32                  IoApicLimit;
  UINT32                  PciResourceMem32Base;
  UINT32                  PciResourceMem32Limit;
  UINT64                  PciResourceMem64Base;
  UINT64                  PciResourceMem64Limit;
  UINT32                  VtdBarAddress;
} STACK_RES;

typedef struct {
    UINT8                   Valid;
    UINT8                   SocketID;            // Socket ID of the IIO (0..3)
    UINT8                   BusBase;
    UINT8                   BusLimit;
    UINT16                  PciResourceIoBase;
    UINT16                  PciResourceIoLimit;
    UINT32                  IoApicBase;
    UINT32                  IoApicLimit;
    UINT32                  PciResourceMem32Base;
    UINT32                  PciResourceMem32Limit;
    UINT64                  PciResourceMem64Base;
    UINT64                  PciResourceMem64Limit;
    STACK_RES               StackRes[MAX_IIO_STACK];
    UINT32                  RcBaseAddress;
    IIO_DMI_PCIE_INFO       PcieInfo;
    UINT8                   DmaDeviceCount;
} IIO_RESOURCE_INSTANCE;

typedef struct {
    UINT16                  PlatGlobalIoBase;       // Global IO Base
    UINT16                  PlatGlobalIoLimit;      // Global IO Limit
    UINT32                  PlatGlobalMmiolBase;    // Global Mmiol base
    UINT32                  PlatGlobalMmiolLimit;   // Global Mmiol limit
    UINT64                  PlatGlobalMmiohBase;    // Global Mmioh Base [43:0]
    UINT64                  PlatGlobalMmiohLimit;   // Global Mmioh Limit [43:0]
    QPI_CPU_DATA            CpuQpiInfo[MAX_SOCKET]; // QPI related info per CPU
    QPI_IIO_DATA            IioQpiInfo[MAX_SOCKET]; // QPI related info per IIO
    UINT32                  MemTsegSize;
    UINT32                  MemIedSize;
    UINT64                  PciExpressBase;
    UINT32                  PciExpressSize;
    UINT32                  MemTolm;
    IIO_RESOURCE_INSTANCE   IIO_resource[MAX_SOCKET];
    UINT8                   numofIIO;
    UINT8                   MaxBusNumber;
    UINT32                  packageBspApicID[MAX_SOCKET]; // This data array is valid only for SBSP, not for non-SBSP CPUs. <AS> for CpuSv
    UINT8                   EVMode;
    UINT8                   Pci64BitResourceAllocation;
    UINT8                   SkuPersonality[MAX_SOCKET];
    UINT8                   VMDStackEnable[MaxIIO][MAX_IIO_STACK];
    UINT16                  IoGranularity;
    UINT32                  MmiolGranularity;
    UINT64_STRUCT           MmiohGranularity;
    UINT8                   RemoteRequestThreshold;
    UINT64                  softskuSocketPresentBitMap;    // bitmap of Softsku sockets with CPUs present detected
    BOOLEAN                 Simics;                        // TRUE - Simics Environtment; FALSE - H\w
} PLATFORM_DATA;

typedef struct {
		UINT32                  FILLER_BUG;
    UINT8                   CurrentCsiLinkSpeed;// Current programmed CSI Link speed (Slow/Full speed mode)
    UINT8                   CurrentCsiLinkFrequency; // Current requested CSI Link frequency (in GT)
    UINT32                  OutKtiPerLinkL1En[MAX_SOCKET];    // output kti link enabled status for PM 
    UINT8                   IsocEnable;
    UINT32                  meRequestedSize; // Size of the memory range requested by ME FW, in MB
    UINT8                   DmiVc1;
    UINT8                   DmiVcm;
    UINT32                  CpuPCPSInfo;
    UINT8                   MinimumCpuStepping;
    UINT8                   LtsxEnable;
    UINT8                   MctpEn;
    UINT8                   cpuType;
    UINT8                   cpuSubType;
    UINT8                   SystemRasType;
    UINT8                   numCpus;                // 1,..4. Total number of CPU packages installed and detected (1..4)by QPI RC
    UINT32                  FusedCores[MAX_SOCKET]; ///< Fused Core Mask in the package
    UINT32                  ActiveCores[MAX_SOCKET];// Current actived core Mask in the package
    UINT8                   MaxCoreToBusRatio[MAX_SOCKET]; // Package Max Non-turbo Ratio (per socket).
    UINT8                   MinCoreToBusRatio[MAX_SOCKET]; // Package Maximum Efficiency Ratio (per socket).
    UINT8                   CurrentCoreToBusRatio;      // Current system Core to Bus Ratio
    UINT32                  IntelSpeedSelectCapable;    // ISS Capable (system level) Bit[7:0] and current Config TDP Level Bit[15:8]
    UINT32                  IssConfigTdpLevelInfo;      // get B2P CONFIG_TDP_GET_LEVELS_INFO
    UINT32                  IssConfigTdpTdpInfo[CONFIG_TDP_MAX_LEVEL];     // get B2P CONFIG_TDP_GET_TDP_INFO
    UINT32                  IssConfigTdpPowerInfo[CONFIG_TDP_MAX_LEVEL];   // get B2P CONFIG_TDP_GET_POWER_INFO
    UINT8                   IssConfigTdpCoreCount[CONFIG_TDP_MAX_LEVEL];   // get B2P CONFIG_TDP_GET_CORE_COUNT
    UINT32                  socketPresentBitMap;    // bitmap of sockets with CPUs present detected by QPI RC
    UINT32                  FpgaPresentBitMap;      // bitmap of NID w/ fpga  present detected by QPI RC
    UINT16                  tolmLimit;
    UINT32                  tohmLimit;
    UINT32                  mmCfgBase;
    UINT32                  RcVersion;
    UINT8                   DdrXoverMode;           // DDR 2.2 Mode
    // For RAS
    UINT8                   bootMode;
    UINT8                   OutClusterOnDieEn; // Whether RC enabled COD support
    UINT8                   OutSncEn;
    UINT8                   OutNumOfCluster;
    UINT8                   imcEnabled[MAX_SOCKET][MAX_IMC];
    UINT8                   numChPerMC;
    UINT8                   maxCh;
    UINT8                   maxIMC;
    UINT16                  LlcSizeReg;
    UINT8                   chEnabled[MAX_SOCKET][MAX_CH];
    UINT8                   mcId[MAX_SOCKET][MAX_CH];
    UINT8                   memNode[MC_MAX_NODE];
    UINT8                   IoDcMode;
    UINT8                   CpuAccSupport;
    UINT8                   SmbusErrorRecovery;
    UINT8                   AepDimmPresent;
} SYSTEM_STATUS;

typedef struct {
    PLATFORM_DATA           PlatformData;
    SYSTEM_STATUS           SystemStatus;
    UINT32                  OemValue;
} IIO_UDS;
#pragma pack()

void soc_display_iio_universal_data_hob(void);

#endif
