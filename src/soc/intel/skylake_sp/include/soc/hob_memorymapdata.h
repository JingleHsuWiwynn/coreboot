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


  @file MemoryMapData.h

  GUID used for Memory Map Data entries in the HOB list.

**/

#ifndef _MEMORY_MAP_GUID_H_
#define _MEMORY_MAP_GUID_H_

#define FSP_SYSTEM_MEMORYMAP_HOB_GUID { \
		0x15, 0x00, 0x87, 0xf8, 0x94, 0x69, 0x98, 0x4b, 0x95,0xa2,0xbd,0x56,0xda,0x91,0xc0,0x7f \
	}

#define MEMTYPE_1LM_MASK       (1 << 0)
#define MEMTYPE_2LM_MASK       (1 << 1)
#define MEMTYPE_VOLATILE_MASK  (MEMTYPE_1LM_MASK | MEMTYPE_2LM_MASK)

#define MAX_IMC_PER_SOCKET                2
#define MAX_SRAT_MEM_ENTRIES_PER_IMC      8
#define MAX_ACPI_MEMORY_AFFINITY_COUNT    MAX_SOCKET*MAX_IMC_PER_SOCKET*MAX_SRAT_MEM_ENTRIES_PER_IMC

/* ACPI SRAT Memory Flags */
#define SRAT_ACPI_MEMORY_ENABLED               (1 << 0)
#define SRAT_ACPI_MEMORY_HOT_REMOVE_SUPPORTED  (1 << 1)
#define SRAT_ACPI_MEMORY_NONVOLATILE           (1 << 2)

#define MAX_UNIQUE_NGN_DIMM_INTERLEAVE 2
#define NGN_MAX_MANUFACTURER_STRLEN    2
#define NGN_MAX_SERIALNUMBER_STRLEN    4
#define NGN_MAX_PARTNUMBER_STRLEN      20
#define MAX_RANK_DIMM                  4
#define NGN_LOG_TYPE_NUM               2
#define NGN_LOG_LEVEL_NUM              2
#define MAX_SPARE_RANK                 2
#define MAX_RIR                        4
#define MAX_RIR_WAYS                   8

#define MEM_TYPE_RESERVED (1 << 8)
#define MEM_ADDR_64MB_SHIFT_BITS 26

//
//  System Memory Map HOB information
//

#pragma pack(1)
struct RankDevice {
  UINT8   enabled;                // 0 = disabled,  1 = enabled
  UINT8   logicalRank;            // Logical Rank number (0 - 7)
  UINT16  rankSize;               // Units of 64 MB
};

struct PersisentDpaMap
{
    UINT32 perRegionDPAOffset;
    UINT32 SPALimit;
};

struct DimmDevice {
  UINT8  Present;
  BOOLEAN Enabled;
  UINT8  aepDimmPresent;     // 1 - This is a AEP Dimm
  UINT8  X4Present;
  UINT8  NumRanks;
  UINT8  keyByte;
  UINT8  actKeyByte2;        // Actual module type reported by SPD
  UINT8  actSPDModuleOrg;    // Actual number of DRAM ranks and device width
  UINT8  actSPDSDRAMBanks;   // Actual number of banks and DRAM density
  UINT8  SPDMemBusWidth;     // Width of the Primary bus and extension
  UINT8  dimmTs;             // Thermal sensor data.
  BOOLEAN newDimm;           // 0 - DIMM is not new to the system for this boot 1 - DIMM is new to the system for this boot (AEP DIMM only)
  UINT16 VolCap;             // Volatile capacity (AEP DIMM only)
  UINT16 nonVolCap;          // Non-volatile capacity (AEP DIMM only)
  UINT16 DimmSize;
  UINT32 NVmemSize;
  UINT16 SPDMMfgId;          // Module Mfg Id from SPD
  UINT16 SPDSDRAMBanks;
  UINT16 VendorID;
  UINT16 DeviceID;
  UINT16 RevisionID;
  UINT32 perRegionDPA;       // DPA of PMEM that Nfit needs
  struct PersisentDpaMap perDPAMap[MAX_UNIQUE_NGN_DIMM_INTERLEAVE]; // DPA map
  UINT8  manufacturer[NGN_MAX_MANUFACTURER_STRLEN];  // Manufacturer
  UINT8  serialNumber[NGN_MAX_SERIALNUMBER_STRLEN];  // Serial Number
  UINT8  PartNumber[NGN_MAX_PARTNUMBER_STRLEN];    // Part Number
  UINT8  FirmwareVersion[4];
  struct RankDevice  rankList[MAX_RANK_DIMM];
  UINT16 InterfaceFormatCode;
  UINT16 subSysVendorID;
  UINT16 subSysDeviceID;
  UINT16 subSysRevisionID;
  UINT16 FisVersion;         // Firmware Interface Specification version
  UINT8  DimmSku;            // Dimm SKU info 
  UINT8  manufacturingLocation;  // Manufacturing location for the NVDIMM
  UINT16 manufacturingDate;      // Date the NVDIMM was manufactured
  INT32  commonTck;
  UINT8   EnergyType;     // 0: 12V aux power; 1: dedicated backup energy source; 2: no backup energy source
  UINT8   nvCtrlSmbAddr;  // NVDIMM SMBUS ADDRESS
  UINT16  funcdesc;       // NVDIMM FUNCTION DESCRIPTOR
  UINT32  nvDimmStatus;   // NVDIMMSTATUS
  UINT16  NgnLogSeqNum[NGN_LOG_TYPE_NUM][NGN_LOG_LEVEL_NUM];
  UINT16  NgnMaxLogEntries[NGN_LOG_TYPE_NUM][NGN_LOG_LEVEL_NUM];
};

struct ChannelDevice {
  UINT8 Enabled;                            // 0 = channel disabled, 1 = channel enabled
  UINT8 Features;                           // Bit mask of features to enable or disable
  UINT8 MaxDimm;                            // Number of DIMM
  UINT8 NumRanks;                           // Number of ranks on this channel
  UINT8 chFailed;
  UINT8 ngnChFailed;
  UINT8 SpareLogicalRank[MAX_SPARE_RANK];    // Logical rank, selected as Spare
  UINT8 SparePhysicalRank[MAX_SPARE_RANK];   // Physical rank, selected as spare
  UINT16 SpareRankSize[MAX_SPARE_RANK];      // spare rank size
  UINT8 EnabledLogicalRanks; // Bitmap of Logical ranks that are enabled
  UINT16 rirLimit[MAX_RIR];  // Rank Interleave Register Limits
  UINT8  rirWay[MAX_RIR];    // Rank Interleave Register Ways
  UINT8  rirValid[MAX_RIR];  // RIR valid bit
  UINT32 rirOffset[MAX_RIR][MAX_RIR_WAYS];
  UINT8  rirIntList[MAX_RIR][MAX_RIR_WAYS];
  struct DimmDevice  DimmInfo[MAX_DIMM];
};

typedef struct TADTable {
  UINT8   Enable;         // Rule enable
  UINT8   SADId;          // SAD Index
  UINT8   mode;           // Interleave Mode
  UINT8   socketWays;     // Socket Interleave ways for TAD
  UINT8   channelWays;    // Channel Interleave ways for TAD
  UINT8   NmTadIndex;     // Index of near memory TAD
  UINT8   FmTadIndex;     // Index of far memory TAD
  UINT32  Limit;          // Limit of the current TAD entry
  UINT32  ChannelAddressLow;  // Base channel address (in channel address space)
  UINT32  ChannelAddressHigh; // Base channel address (in channel address space)
} TAD_TABLE;

struct memcontroller {
  UINT8     TADintList[MAX_TAD_RULES][MAX_TAD_WAYS];  // TAD interleave list for node
  UINT8     TADChnIndex[MAX_TAD_RULES][MAX_TAD_WAYS]; // Corresponding TAD channel indexes
  UINT32    TADOffset[MAX_TAD_RULES][MAX_TAD_WAYS];   // Corresponding TAD offsets
  TAD_TABLE TAD[MAX_TAD_RULES];                       // TAD table
  UINT32    MemSize;
  BOOLEAN   IsMapped;                                // Is this node mapped to system address space
  UINT64    WpqFlushHintAddress;
};

struct SADTable {
  UINT8   Enable;         // Rule enable
  UINT16  type;           // Bit map of memory region types, See defines 'MEM_TYPE_???' above for bit definitions of the ranges
  UINT8   granularity;    // Interleave granularities for current SAD entry.  Possible interleave granularity options depend on the SAD entry type.  Note that SAD entry type BLK Window and CSR/Mailbox/Ctrl region do not support any granularity options
  UINT32  Limit;          // Limit of the current SAD entry
  UINT8   ways;           // Interleave ways for SAD
  UINT8   channelInterBitmap[MAX_IMC];   //Bit map to denote which DDR4/NM channels are interleaved per IMC eg: 111b - Ch 2,1 & 0 are interleaved; 011b denotes Ch1 & 0 are interleaved
  UINT8   FMchannelInterBitmap[MAX_IMC];   //Bit map to denote which FM channels are interleaved per IMC eg: 111b - Ch 2,1 & 0 are interleaved; 011b denotes Ch1 & 0 are interleaved
  UINT8   imcInterBitmap;       //Bit map to denote which IMCs are interleaved from this socket.
  BOOLEAN local;          //0 - Remote 1- Local
  UINT8   IotEnabled;     // To indicate if IOT is enabled
  UINT8   mirrored;       //To Indicate the SAD is mirrored while enabling partial mirroring
  UINT8   Attr;
  UINT8   tgtGranularity;  // Target granularity
};

struct socket {
  UINT8    SocketEnabled;
  UINT8    IioStackBitmap;
  UINT8    imcEnabled[MAX_IMC];
  UINT8    SADintList[SAD_RULES][MC_MAX_NODE];     // SAD interleave list
  UINT8    SktSkuValid;                            // Whether Socket SKU value is valid from PCU
  UINT32   SktSkuLimit;                            // SKU limit value from PCU
  UINT32   SktTotMemMapSPA;                        // Total memory mapped to SPA
  UINT32   SktMemSize2LM;                          // Total memory excluded from Limit
  struct   SADTable SAD[SAD_RULES];                // SAD table
  struct   memcontroller imc[MAX_IMC];
  struct   ChannelDevice  ChannelInfo[MAX_CH];
};

struct SystemMemoryMapElement {
  UINT8    NodeId;         // Node ID of the HA Owning the memory
  UINT8    SocketId;       // Socket Id of socket that has his memory - ONLY IN NUMA
  UINT8    ImcInterBitmap; // IMC interleave bitmap for this DRAM rule - ONLY IN NUMA
  UINT32   BaseAddress;    // Base Address of the element in 64MB chunks
  UINT32   ElementSize;    // Size of this memory element in 64MB chunks
  UINT16   Type;           // Type of this memory element; Bit0: 1LM  Bit1: 2LM  Bit2: PMEM  Bit3: PMEM-cache  Bit4: BLK Window  Bit5: CSR/Mailbox/Ctrl region
};

struct SystemMemoryMapHob {
  UINT32   lowMemBase;     // Mem base in 64MB units for below 4GB mem.
  UINT32   lowMemSize;     // Mem size in 64MB units for below 4GB mem.
  UINT32   highMemBase;    // Mem base in 64MB units for above 4GB mem.
  UINT32   highMemSize;    // Mem size in 64MB units for above 4GB mem.
  UINT32   asilLoMemBase;  // Mem base in 64MB units for below 4GB mem.
  UINT32   asilHiMemBase;  // Mem base in 64MB units for above 4GB mem.
  UINT32   asilLoMemSize;  // Mem size in 64MB units for below 4GB mem.
  UINT32   asilHiMemSize;  // Mem size in 64MB units for above 4GB mem.

  UINT32   memSize;      // Total physical memory size
  UINT16   memFreq;      // Mem Frequency
  UINT8    memMode;      // 0 - Independent, 1 - Lockstep
  UINT8    volMemMode;   // 0 - 1LM, 1 - 2LM
  UINT8    DimmType;
  UINT16   DramType;
  UINT8    DdrVoltage;
  UINT8    AepDimmPresent; // If at least one Aep Dimm Present (used by Nfit), then this should get set
  UINT8    SADNum;
  UINT8    XMPProfilesSup;
  UINT8    cpuType;
  UINT8    cpuStepping;
  UINT8    SystemRasType;
  UINT8    RasModesEnabled; // RAS modes that are enabled
  UINT8    ExRasModesEnabled; // Extended RAS modes that are enabled
  UINT8    RasModesSupported; //RAS modes that are supported by current memory population.
  UINT8    sncEnabled;      // 0 - SNC disabled for this configuration, 1 - SNC enabled for this configuration
  UINT8    NumOfCluster;
#ifdef SV_HOOKS
  UINT8    ExtendedADDDCEn;
#endif
  UINT8    NumChPerMC;
  UINT8    numberEntries;   // Number of Memory Map Elements
  UINT8    maxIMC;
  UINT8    maxCh;
  struct   SystemMemoryMapElement Element[MAX_SOCKET * SAD_RULES];
	UINT8    reserved1[982];
  struct   socket Socket[MAX_SOCKET];
	UINT8    reserved2[707];
};

#pragma pack()

#endif
