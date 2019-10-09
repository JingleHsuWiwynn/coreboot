/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2007 - 2009 coresystems GmbH
 * Copyright (C) 2013 Google Inc.
 * Copyright (C) 2014 - 2017 Intel Corporation.
 * Copyright (C) 2018 Online SAS
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

#include <arch/acpi.h>
#include <arch/cpu.h>
#include <arch/acpigen.h>
#include <arch/ioapic.h>
#include <arch/smp/mpspec.h>
#include <bootstate.h>
#include <string.h>
#include <cf9_reset.h>
#include <cpu/intel/turbo.h>
#include <cpu/x86/msr.h>
#include <cpu/x86/smm.h>
#include <intelblocks/acpi.h>
#include <intelblocks/msr.h>
#include <intelblocks/pmclib.h>
#include <intelblocks/uart.h>
#include <device/pci.h>
#include <cbmem.h>
#include <soc/acpi.h>
#include <soc/cpu.h>
#include <soc/soc_util.h>
#include <soc/pm.h>
#include <soc/pmc.h>
#include <soc/systemagent.h>
#include <soc/memmap.h>
#include <soc/pci_devs.h>
#include <soc/hob_mem.h>
#include <soc/skxsp_util.h>
#include <soc/hob_iiouds.h>

#define MWAIT_RES(state, sub_state)                         \
	{                                                   \
		.addrl = (((state) << 4) | (sub_state)),    \
		.space_id = ACPI_ADDRESS_SPACE_FIXED,       \
		.bit_width = ACPI_FFIXEDHW_VENDOR_INTEL,    \
		.bit_offset = ACPI_FFIXEDHW_CLASS_MWAIT,    \
		.access_size = ACPI_FFIXEDHW_FLAG_HW_COORD, \
	}

#define CSTATE_RES(address_space, width, offset, address)		\
	{								\
	.space_id = address_space,					\
	.bit_width = width,						\
	.bit_offset = offset,						\
	.addrl = address,						\
	}

static acpi_cstate_t cstate_map[] = {
	{
		/* C1 */
		.ctype = 1,		/* ACPI C1 */
		.latency = 2,
		.power = 1000,
		.resource = MWAIT_RES(0, 0),
	},
	{
		.ctype = 2,		/* ACPI C2 */
		.latency = 10,
		.power = 10,
	  .resource = MWAIT_RES(0, 1),
#if 0
		.resource = CSTATE_RES(ACPI_ADDRESS_SPACE_IO, 8, 0,
				       ACPI_BASE_ADDRESS + 0x14),
#endif
	},
	{
		.ctype = 3,		/* ACPI C3 */
		.latency = 50,
		.power = 10,
	  .resource = MWAIT_RES(1, 0),
#if 0
		.resource = CSTATE_RES(ACPI_ADDRESS_SPACE_IO, 8, 0,
				       ACPI_BASE_ADDRESS + 0x15),
#endif
	}
};

static int acpi_sci_irq(void)
{
  int sci_irq = 9;
  uint32_t scis;

  scis = soc_read_sci_irq_select();
  scis &= SCI_IRQ_SEL;
  scis >>= SCI_IRQ_ADJUST;

  /* Determine how SCI is routed. */
  switch (scis) {
  case SCIS_IRQ9:
  case SCIS_IRQ10:
  case SCIS_IRQ11:
    sci_irq = scis - SCIS_IRQ9 + 9;
    break;
  case SCIS_IRQ20:
  case SCIS_IRQ21:
  case SCIS_IRQ22:
  case SCIS_IRQ23:
    sci_irq = scis - SCIS_IRQ20 + 20;
    break;
  default:
    printk(BIOS_DEBUG, "Invalid SCI route! Defaulting to IRQ9.\n");
    sci_irq = 9;
    break;
  }

  printk(BIOS_DEBUG, "SCI is IRQ%d\n", sci_irq);
  return sci_irq;
}

void acpi_init_gnvs(global_nvs_t *gnvs)
{
	/* CPU core count */
	gnvs->pcnt = dev_count_cpu();
	printk(BIOS_DEBUG, "%s gnvs->pcnt: %d\n", __func__, gnvs->pcnt);

#if IS_ENABLED(CONFIG_CONSOLE_CBMEM)
	/* Update the mem console pointer. */
	gnvs->cbmc = (u32)cbmem_find(CBMEM_ID_CONSOLE);
#endif
}

uint32_t soc_read_sci_irq_select(void)
{
	struct device *dev = PCH_DEV_PMC;

	if (!dev)
		return 0;

	return pci_read_config32(dev, PMC_ACPI_CNT);
}

acpi_cstate_t *soc_get_cstate_map(size_t *entries)
{
	*entries = 0;
	return NULL;
	*entries = ARRAY_SIZE(cstate_map);
	return cstate_map;
}

unsigned long acpi_fill_mcfg(unsigned long current)
{
	current += acpi_create_mcfg_mmconfig((acpi_mcfg_mmconfig_t *)current,
                                       CONFIG_MMCONF_BASE_ADDRESS, 0, 0, 255);
	return current;
}

unsigned long acpi_madt_irq_overrides(unsigned long current)
{
  int sci = acpi_sci_irq();
  uint16_t flags = MP_IRQ_TRIGGER_LEVEL;

  /* INT_SRC_OVR */
  current += acpi_create_madt_irqoverride((void *)current, 0, 0, 2, 0);

  flags |= soc_madt_sci_irq_polarity(sci);

  /* SCI */
  current +=
      acpi_create_madt_irqoverride((void *)current, 0, sci, sci, flags);

  return current;
}

unsigned long acpi_fill_madt(unsigned long current)
{
  size_t hob_size;
  const uint8_t fsp_hob_iio_universal_data_guid[16] = FSP_HOB_IIO_UNIVERSAL_DATA_GUID;
  const IIO_UDS *hob;

  /* Local APICs */
  current = acpi_create_madt_lapics(current);

  /* IOAPIC */
   /*
    IOAPIC
    PCH I/O APIC is on LPC
    The IIO I/O APIC is fixed on PCI <bus bridge>:05.4
    fec00000-fec003ff : IOAPIC 0 [Stack 0]
      00:05.4 PIC: Intel Corporation Device 2026 (rev 04) (prog-if 20 [IO(X)-APIC])
    fec01000-fec013ff : IOAPIC 1 [Stack 0]
      00:1f.0 ISA bridge: Intel Corporation Lewisburg LPC Controller (rev 09)
    fec08000-fec083ff : IOAPIC 2 [Stack 1]
      16:05.4 PIC: Intel Corporation Device 2036 (rev 04) (prog-if 20 [IO(X)-APIC])
    fec10000-fec103ff : IOAPIC 3 [Stack 2]
      64:05.4 PIC: Intel Corporation Device 2036 (rev 04) (prog-if 20 [IO(X)-APIC])
    fec18000-fec183ff : IOAPIC 4 [Stack 3]
      b2:05.4 PIC: Intel Corporation Device 2036 (rev 04) (prog-if 20 [IO(X)-APIC])
   */

  current += acpi_create_madt_ioapic((acpi_madt_ioapic_t *) current,
                                     8, 0xfec00000, 0);
  current += acpi_create_madt_ioapic((acpi_madt_ioapic_t *) current,
                                     9, 0xfec01000, 0x18);
  current += acpi_create_madt_ioapic((acpi_madt_ioapic_t *) current,
                                     0xa, 0xfec08000, 0x20);
  current += acpi_create_madt_ioapic((acpi_madt_ioapic_t *) current,
                                     0xb, 0xfec10000, 0x28);
  current += acpi_create_madt_ioapic((acpi_madt_ioapic_t *) current,
                                     0xc, 0xfec18000, 0x30);

	if (0) {
		hob = fsp_find_extension_hob_by_guid(
														fsp_hob_iio_universal_data_guid,
														&hob_size);
		assert(hob != NULL && hob_size != 0);

		// find out total number of stacks
		int i = 0;
		for (int socket=0; socket < hob->PlatformData.numofIIO; ++socket) {
			for (int stack=0; stack < MAX_IIO_STACK; ++stack) {
				const STACK_RES *ri = &hob->PlatformData.IIO_resource[socket].StackRes[stack];
				if (ri->BusBase != ri->BusLimit) { // TODO: do we have situation with only bux 0 and one stack?
					printk(BIOS_DEBUG, "Adding MADT IOAPIC for socket: %d, stack: %d, id: 0x%x, base: 0x%x, gsi_base: 0x%x\n", 
								 socket, stack,  (i+8), ri->IoApicBase, (8*i)+0x18);
					/* acpi_create_madt_ioapic implementation in src/arch/x86/acpi.c */
					current += acpi_create_madt_ioapic((acpi_madt_ioapic_t *) current, (i+8), 
																						 ri->IoApicBase, (i == 0) ? 0 : ((8*i)+0x18));
					++i;
				}
			}
		}
	}

  return acpi_madt_irq_overrides(current);
}

__attribute__ ((weak)) void motherboard_fill_fadt(acpi_fadt_t *fadt)
{
}

void generate_t_state_entries(int core, int cores_per_package)
{
  acpi_tstate_t *soc_tss_table;
  int entries;

  soc_tss_table = soc_get_tss_table(&entries);
  if (entries == 0)
    return;

  /* Indicate SW_ALL coordination for T-states */
  acpigen_write_TSD_package(core, cores_per_package, SW_ALL);

  /* Indicate FixedHW so OS will use MSR */
  acpigen_write_empty_PTC();

  /* Set NVS controlled T-state limit */
  acpigen_write_TPC("\\TLVL");

  /* Write TSS table for MSR access */
  acpigen_write_TSS_package(entries, soc_tss_table);
}

static void generate_c_state_entries(void)
{
  acpi_cstate_t *c_state_map;
  size_t entries;

  c_state_map = soc_get_cstate_map(&entries);

  /* Generate C-state tables */
  acpigen_write_CST_package(c_state_map, entries);
}

static int calculate_power(int tdp, int p1_ratio, int ratio)
{
	u32 m;
	u32 power;

	/*
	 * M = ((1.1 - ((p1_ratio - ratio) * 0.00625)) / 1.1) ^ 2
	 *
	 * Power = (ratio / p1_ratio) * m * tdp
	 */

	m = (110000 - ((p1_ratio - ratio) * 625)) / 11;
	m = (m * m) / 1000;

	power = ((ratio * 100000 / p1_ratio) / 100);
	power *= (m / 100) * (tdp / 1000);
	power /= 1000;

	return (int)power;
}

void generate_p_state_entries(int core, int cores_per_package)
{
	int ratio_min, ratio_max, ratio_turbo, ratio_step;
	int coord_type, power_max, num_entries;
	int ratio, power, clock, clock_max;
	bool turbo;

	printk(BIOS_DEBUG, "generate_p_state_entries\n");
	coord_type = cpu_get_coord_type();
	ratio_min = cpu_get_min_ratio();
	ratio_max = cpu_get_max_ratio();
	clock_max = (ratio_max * cpu_get_bus_clock()) / KHz;
	turbo = (get_turbo_state() == TURBO_ENABLED);

	/* Calculate CPU TDP in mW */
	power_max = cpu_get_power_max();

	/* Write _PCT indicating use of FFixedHW */
	acpigen_write_empty_PCT();

	/* Write _PPC with no limit on supported P-state */
	acpigen_write_PPC_NVS();
	/* Write PSD indicating configured coordination type */
	acpigen_write_PSD_package(core, 1, coord_type);

	/* Add P-state entries in _PSS table */
	acpigen_write_name("_PSS");

	/* Determine ratio points */
	ratio_step = PSS_RATIO_STEP;
	do {
		num_entries = ((ratio_max - ratio_min) / ratio_step) + 1;
		if (((ratio_max - ratio_min) % ratio_step) > 0)
			num_entries += 1;
		if (turbo)
			num_entries += 1;
		if (num_entries > PSS_MAX_ENTRIES)
			ratio_step += 1;
	} while (num_entries > PSS_MAX_ENTRIES);

	/* _PSS package count depends on Turbo */
	acpigen_write_package(num_entries);

	/* P[T] is Turbo state if enabled */
	if (turbo) {
		ratio_turbo = cpu_get_max_turbo_ratio();

		/* Add entry for Turbo ratio */
		acpigen_write_PSS_package(clock_max + 1,	/* MHz */
					  power_max,		/* mW */
					  PSS_LATENCY_TRANSITION,/* lat1 */
					  PSS_LATENCY_BUSMASTER,/* lat2 */
					  ratio_turbo << 8,	/* control */
					  ratio_turbo << 8);	/* status */
		num_entries -= 1;
	}

	/* First regular entry is max non-turbo ratio */
	acpigen_write_PSS_package(clock_max,		/* MHz */
				  power_max,		/* mW */
				  PSS_LATENCY_TRANSITION,/* lat1 */
				  PSS_LATENCY_BUSMASTER,/* lat2 */
				  ratio_max << 8,	/* control */
				  ratio_max << 8);	/* status */
	num_entries -= 1;

	/* Generate the remaining entries */
	for (ratio = ratio_min + ((num_entries - 1) * ratio_step);
	     ratio >= ratio_min; ratio -= ratio_step) {

		/* Calculate power at this ratio */
		power = calculate_power(power_max, ratio_max, ratio);
		clock = (ratio * cpu_get_bus_clock()) / KHz;

		acpigen_write_PSS_package(clock,		/* MHz */
					  power,		/* mW */
					  PSS_LATENCY_TRANSITION,/* lat1 */
					  PSS_LATENCY_BUSMASTER,/* lat2 */
					  ratio << 8,		/* control */
					  ratio << 8);		/* status */
	}
	/* Fix package length */
	acpigen_pop_len();
}

void generate_cpu_entries(struct device *device)
{
  size_t hob_size;
  const uint8_t fsp_hob_iio_universal_data_guid[16] = FSP_HOB_IIO_UNIVERSAL_DATA_GUID;
  const IIO_UDS *hob;

	int core_id, cpu_id, pcontrol_blk = ACPI_BASE_ADDRESS;
	int plen = 6;
	int totalcores = dev_count_cpu();
	int cores_per_package = get_cores_per_package();
	int numcpus = totalcores / cores_per_package;

	/* these fields are incorrect - need debugging */
  hob = fsp_find_extension_hob_by_guid(
                          fsp_hob_iio_universal_data_guid,
                          &hob_size);
  assert(hob != NULL && hob_size != 0);
	printk(BIOS_DEBUG, "numCpus: %d, socketPresentBitMap: 0x%x\n", hob->SystemStatus.numCpus, 
				 hob->SystemStatus.socketPresentBitMap);
	for (int i=0; i < MAX_SOCKET; ++i) {
		printk(BIOS_DEBUG, "Socket %d FusedCores: 0x%x, ActiveCores: 0x%x\n", i, 
					 hob->SystemStatus.FusedCores[i], hob->SystemStatus.ActiveCores[i]);
	}

	printk(BIOS_DEBUG, "Found %d CPU(s) with %d core(s) each, totalcores: %d.\n",
	       numcpus, cores_per_package, totalcores);

	for (cpu_id = 0; cpu_id < numcpus; cpu_id++) {
		for (core_id = 0; core_id < cores_per_package; core_id++) {
			if (core_id > 0) {
				pcontrol_blk = 0;
				plen = 0;
			}

			/* Generate processor \_PR.CPUx */
			printk(BIOS_DEBUG, "^^^ acpigen_write_processor cpu_id: 0x%x, core_id: 0x%x\n", cpu_id, core_id);
			acpigen_write_processor((cpu_id) * cores_per_package +
						core_id, pcontrol_blk, plen);

			/* Generate C-state tables */
			if (0) generate_c_state_entries();

			/* Soc specific power states generation */
			//soc_power_states_generation(core_id, cores_per_package);

			acpigen_pop_len();
		}
	}
	/* PPKG is usually used for thermal management
	   of the first and only package. */
	acpigen_write_processor_package("PPKG", 0, cores_per_package);

	/* Add a method to notify processor nodes */
	acpigen_write_processor_cnot(cores_per_package);
}

void soc_fill_fadt(acpi_fadt_t *fadt)
{
	u16 pmbase = ACPI_BASE_ADDRESS;

	/* System Management */
	if (!IS_ENABLED(CONFIG_HAVE_SMI_HANDLER)) {
		fadt->smi_cmd = 0x00;
		fadt->acpi_enable = 0x00;
		fadt->acpi_disable = 0x00;
	}

	/* Power Control */
	fadt->pm2_cnt_blk = pmbase + PM2_CNT;
	fadt->pm_tmr_blk = pmbase + PM1_TMR;
	fadt->gpe1_blk = 0;

	/* Control Registers - Length */
	fadt->pm2_cnt_len = 1;
	fadt->pm_tmr_len = 4;
	  /* There are 4 GPE0 STS/EN pairs each 32 bits wide. */
  fadt->gpe0_blk_len = 2 * GPE0_REG_MAX * sizeof(uint32_t);
	//fadt->gpe0_blk_len = 8;
	fadt->gpe1_blk_len = 0;
	fadt->gpe1_base = 0;
	fadt->cst_cnt = 0;
	fadt->p_lvl2_lat = ACPI_FADT_C2_NOT_SUPPORTED;
	fadt->p_lvl3_lat = ACPI_FADT_C3_NOT_SUPPORTED;
	fadt->flush_size = 0;   /* set to 0 if WBINVD is 1 in flags */
	fadt->flush_stride = 0; /* set to 0 if WBINVD is 1 in flags */
	fadt->duty_offset = 1;
	fadt->duty_width = 0;

	/* RTC Registers */
	fadt->day_alrm = 0x0D;
	fadt->mon_alrm = 0x00;
	fadt->century = 0x00;
	fadt->iapc_boot_arch = ACPI_FADT_LEGACY_DEVICES | ACPI_FADT_8042;

	fadt->flags = ACPI_FADT_WBINVD | ACPI_FADT_C1_SUPPORTED |
		      ACPI_FADT_C2_MP_SUPPORTED | ACPI_FADT_SLEEP_BUTTON |
		      ACPI_FADT_RESET_REGISTER | ACPI_FADT_SLEEP_TYPE |
		      ACPI_FADT_S4_RTC_WAKE | ACPI_FADT_PLATFORM_CLOCK;

	/* Reset Register */
	fadt->reset_reg.space_id = ACPI_ADDRESS_SPACE_IO;
	fadt->reset_reg.bit_width = 8;
	fadt->reset_reg.bit_offset = 0;
	fadt->reset_reg.access_size = ACPI_ACCESS_SIZE_BYTE_ACCESS;
	fadt->reset_reg.addrl = 0xCF9;
	fadt->reset_reg.addrh = 0x00;
	fadt->reset_value = 6;

	/* PM1 Status & PM1 Enable */
	fadt->x_pm1a_evt_blk.space_id = ACPI_ADDRESS_SPACE_IO;
	fadt->x_pm1a_evt_blk.bit_width = 32;
	fadt->x_pm1a_evt_blk.bit_offset = 0;
	fadt->x_pm1a_evt_blk.access_size = ACPI_ACCESS_SIZE_DWORD_ACCESS;
	fadt->x_pm1a_evt_blk.addrl = fadt->pm1a_evt_blk;
	fadt->x_pm1a_evt_blk.addrh = 0x00;

	fadt->x_pm1b_evt_blk.space_id = ACPI_ADDRESS_SPACE_IO;
	fadt->x_pm1b_evt_blk.bit_width = 0;
	fadt->x_pm1b_evt_blk.bit_offset = 0;
	fadt->x_pm1b_evt_blk.access_size = 0;
	fadt->x_pm1b_evt_blk.addrl = fadt->pm1b_evt_blk;
	fadt->x_pm1b_evt_blk.addrh = 0x00;

	/* PM1 Control Registers */
	fadt->x_pm1a_cnt_blk.space_id = ACPI_ADDRESS_SPACE_IO;
	fadt->x_pm1a_cnt_blk.bit_width = 16;
	fadt->x_pm1a_cnt_blk.bit_offset = 0;
	fadt->x_pm1a_cnt_blk.access_size = ACPI_ACCESS_SIZE_WORD_ACCESS;
	fadt->x_pm1a_cnt_blk.addrl = fadt->pm1a_cnt_blk;
	fadt->x_pm1a_cnt_blk.addrh = 0x00;

	fadt->x_pm1b_cnt_blk.space_id = ACPI_ADDRESS_SPACE_IO;
	fadt->x_pm1b_cnt_blk.bit_width = 0;
	fadt->x_pm1b_cnt_blk.bit_offset = 0;
	fadt->x_pm1b_cnt_blk.access_size = 0;
	fadt->x_pm1b_cnt_blk.addrl = fadt->pm1b_cnt_blk;
	fadt->x_pm1b_cnt_blk.addrh = 0x00;

	/* PM2 Control Registers */
	fadt->x_pm2_cnt_blk.space_id = ACPI_ADDRESS_SPACE_IO;
	fadt->x_pm2_cnt_blk.bit_width = 8;
	fadt->x_pm2_cnt_blk.bit_offset = 0;
	fadt->x_pm2_cnt_blk.access_size = ACPI_ACCESS_SIZE_BYTE_ACCESS;
	fadt->x_pm2_cnt_blk.addrl = fadt->pm2_cnt_blk;
	fadt->x_pm2_cnt_blk.addrh = 0x00;

	/* PM1 Timer Register */
	fadt->x_pm_tmr_blk.space_id = ACPI_ADDRESS_SPACE_IO;
	fadt->x_pm_tmr_blk.bit_width = 32;
	fadt->x_pm_tmr_blk.bit_offset = 0;
	fadt->x_pm_tmr_blk.access_size = ACPI_ACCESS_SIZE_DWORD_ACCESS;
	fadt->x_pm_tmr_blk.addrl = fadt->pm_tmr_blk;
	fadt->x_pm_tmr_blk.addrh = 0x00;

	/*  General-Purpose Event Registers */
	fadt->x_gpe0_blk.space_id = ACPI_ADDRESS_SPACE_IO;
	fadt->x_gpe0_blk.bit_width = 64; /* EventStatus + EventEnable */
	fadt->x_gpe0_blk.bit_offset = 0;
	fadt->x_gpe0_blk.access_size = ACPI_ACCESS_SIZE_DWORD_ACCESS;
	fadt->x_gpe0_blk.addrl = fadt->gpe0_blk;
	fadt->x_gpe0_blk.addrh = 0x00;

	fadt->x_gpe1_blk.space_id = ACPI_ADDRESS_SPACE_IO;
	fadt->x_gpe1_blk.bit_width = 0;
	fadt->x_gpe1_blk.bit_offset = 0;
	fadt->x_gpe1_blk.access_size = 0;
	fadt->x_gpe1_blk.addrl = fadt->gpe1_blk;
	fadt->x_gpe1_blk.addrh = 0x00;

	motherboard_fill_fadt(fadt);
}

void acpi_fill_fadt(acpi_fadt_t *fadt)
{
	const uint16_t pmbase = ACPI_BASE_ADDRESS;

	/* Use ACPI 3.0 revision */
	fadt->header.revision = get_acpi_table_revision(FADT);

	fadt->sci_int = acpi_sci_irq();
	fadt->smi_cmd = APM_CNT;
	fadt->acpi_enable = APM_CNT_ACPI_ENABLE;
	fadt->acpi_disable = APM_CNT_ACPI_DISABLE;
	fadt->s4bios_req = 0x0;
	fadt->pstate_cnt = 0;

	fadt->pm1a_evt_blk = pmbase + PM1_STS;
	fadt->pm1b_evt_blk = 0x0;
	fadt->pm1a_cnt_blk = pmbase + PM1_CNT;
	fadt->pm1b_cnt_blk = 0x0;
	fadt->pm2_cnt_blk = pmbase + PM2_CNT;
	fadt->pm_tmr_blk = pmbase + PM1_TMR;
	fadt->gpe0_blk = pmbase + GPE0_STS(0);
	fadt->gpe1_blk = 0;

	fadt->pm1_evt_len = 4;
	fadt->pm1_cnt_len = 2;
	fadt->pm2_cnt_len = 1;
	fadt->pm_tmr_len = 4;
	/* There are 4 GPE0 STS/EN pairs each 32 bits wide. */
	fadt->gpe0_blk_len = 2 * GPE0_REG_MAX * sizeof(uint32_t);
	fadt->gpe1_blk_len = 0;
	fadt->gpe1_base = 0;
	fadt->cst_cnt = 0;
	fadt->p_lvl2_lat = 1;
	fadt->p_lvl3_lat = 87;
	fadt->flush_size = 1024;
	fadt->flush_stride = 16;
	fadt->duty_offset = 1;
	fadt->duty_width = 0;
	fadt->day_alrm = 0xd;
	fadt->mon_alrm = 0x00;
	fadt->century = 0x00;
	fadt->iapc_boot_arch = ACPI_FADT_LEGACY_FREE;
	if (!IS_ENABLED(CONFIG_NO_FADT_8042))
		fadt->iapc_boot_arch |= ACPI_FADT_8042;

	fadt->flags = ACPI_FADT_WBINVD | ACPI_FADT_C1_SUPPORTED |
			ACPI_FADT_C2_MP_SUPPORTED | ACPI_FADT_SLEEP_BUTTON |
			ACPI_FADT_RESET_REGISTER | ACPI_FADT_SEALED_CASE |
			ACPI_FADT_S4_RTC_WAKE | ACPI_FADT_PLATFORM_CLOCK;

	/*
	if (config && config->s0ix_enable)
		fadt->flags |= ACPI_FADT_LOW_PWR_IDLE_S0;
	*/

	fadt->reset_reg.space_id = 1;
	fadt->reset_reg.bit_width = 8;
	fadt->reset_reg.bit_offset = 0;
	fadt->reset_reg.resv = 0;
	fadt->reset_reg.addrl = 0xcf9;
	fadt->reset_reg.addrh = 0;
	fadt->reset_value = 6;

	fadt->x_pm1a_evt_blk.space_id = 1;
	fadt->x_pm1a_evt_blk.bit_width = fadt->pm1_evt_len * 8;
	fadt->x_pm1a_evt_blk.bit_offset = 0;
	fadt->x_pm1a_evt_blk.resv = 0;
	fadt->x_pm1a_evt_blk.addrl = pmbase + PM1_STS;
	fadt->x_pm1a_evt_blk.addrh = 0x0;

	fadt->x_pm1b_evt_blk.space_id = 1;
	fadt->x_pm1b_evt_blk.bit_width = 0;
	fadt->x_pm1b_evt_blk.bit_offset = 0;
	fadt->x_pm1b_evt_blk.resv = 0;
	fadt->x_pm1b_evt_blk.addrl = 0x0;
	fadt->x_pm1b_evt_blk.addrh = 0x0;

	fadt->x_pm1a_cnt_blk.space_id = 1;
	fadt->x_pm1a_cnt_blk.bit_width = fadt->pm1_cnt_len * 8;
	fadt->x_pm1a_cnt_blk.bit_offset = 0;
	fadt->x_pm1a_cnt_blk.resv = 0;
	fadt->x_pm1a_cnt_blk.addrl = pmbase + PM1_CNT;
	fadt->x_pm1a_cnt_blk.addrh = 0x0;

	fadt->x_pm1b_cnt_blk.space_id = 1;
	fadt->x_pm1b_cnt_blk.bit_width = 0;
	fadt->x_pm1b_cnt_blk.bit_offset = 0;
	fadt->x_pm1b_cnt_blk.resv = 0;
	fadt->x_pm1b_cnt_blk.addrl = 0x0;
	fadt->x_pm1b_cnt_blk.addrh = 0x0;

	fadt->x_pm2_cnt_blk.space_id = 1;
	fadt->x_pm2_cnt_blk.bit_width = fadt->pm2_cnt_len * 8;
	fadt->x_pm2_cnt_blk.bit_offset = 0;
	fadt->x_pm2_cnt_blk.resv = 0;
	fadt->x_pm2_cnt_blk.addrl = pmbase + PM2_CNT;
	fadt->x_pm2_cnt_blk.addrh = 0x0;

	fadt->x_pm_tmr_blk.space_id = 1;
	fadt->x_pm_tmr_blk.bit_width = fadt->pm_tmr_len * 8;
	fadt->x_pm_tmr_blk.bit_offset = 0;
	fadt->x_pm_tmr_blk.resv = 0;
	fadt->x_pm_tmr_blk.addrl = pmbase + PM1_TMR;
	fadt->x_pm_tmr_blk.addrh = 0x0;

	fadt->x_gpe0_blk.space_id = 0;
	fadt->x_gpe0_blk.bit_width = 0;
	fadt->x_gpe0_blk.bit_offset = 0;
	fadt->x_gpe0_blk.resv = 0;
	fadt->x_gpe0_blk.addrl = 0;
	fadt->x_gpe0_blk.addrh = 0;

	fadt->x_gpe1_blk.space_id = 1;
	fadt->x_gpe1_blk.bit_width = 0;
	fadt->x_gpe1_blk.bit_offset = 0;
	fadt->x_gpe1_blk.resv = 0;
	fadt->x_gpe1_blk.addrl = 0x0;
	fadt->x_gpe1_blk.addrh = 0x0;

	soc_fill_fadt(fadt);
}

static acpi_tstate_t skylake_sp_tss_table[] = {
	{ 100, 1000, 0, 0x00, 0 },
	{ 88, 875, 0, 0x1e, 0 },
	{ 75, 750, 0, 0x1c, 0 },
	{ 63, 625, 0, 0x1a, 0 },
	{ 50, 500, 0, 0x18, 0 },
	{ 38, 375, 0, 0x16, 0 },
	{ 25, 250, 0, 0x14, 0 },
	{ 13, 125, 0, 0x12, 0 },
};

acpi_tstate_t *soc_get_tss_table(int *entries)
{
	*entries = ARRAY_SIZE(skylake_sp_tss_table);
	return skylake_sp_tss_table;
}

void soc_power_states_generation(int core_id, int cores_per_package)
{
	//generate_p_state_entries(core_id, cores_per_package);
	//generate_t_state_entries(core_id, cores_per_package);
}

int soc_madt_sci_irq_polarity(int sci)
{
	if (sci >= 20)
		return MP_IRQ_POLARITY_LOW;
	else
		return MP_IRQ_POLARITY_HIGH;
}

unsigned long southbridge_write_acpi_tables(struct device *device,
					     unsigned long current,
					     struct acpi_rsdp *rsdp)
{
	acpi_header_t *ssdt2;

	current = acpi_write_hpet(device, current, rsdp);
	current = (ALIGN(current, 16));

	ssdt2 = (acpi_header_t *)current;
	memset(ssdt2, 0, sizeof(acpi_header_t));
	acpi_create_serialio_ssdt(ssdt2);
	if (ssdt2->length) {
		current += ssdt2->length;
		acpi_add_table(rsdp, ssdt2);
		printk(BIOS_DEBUG, "ACPI:     * SSDT2 @ %p Length %x\n", ssdt2,
		       ssdt2->length);
		current = (ALIGN(current, 16));
	} else {
		ssdt2 = NULL;
		printk(BIOS_DEBUG, "ACPI:     * SSDT2 not generated.\n");
	}

	printk(BIOS_DEBUG, "current = %lx\n", current);

	return current;
}

void southbridge_inject_dsdt(struct device *device)
{
	global_nvs_t *gnvs;

	gnvs = cbmem_find(CBMEM_ID_ACPI_GNVS);
	if (!gnvs) {
		gnvs = cbmem_add(CBMEM_ID_ACPI_GNVS, sizeof(*gnvs));
		if (gnvs)
			memset(gnvs, 0, sizeof(*gnvs));
	}

	if (gnvs) {
		acpi_create_gnvs(gnvs);
#if CONFIG_HAVE_SMI_HANDLER
		/* And tell SMI about it */
		smm_setup_structures(gnvs, NULL, NULL);
#endif

		/* Add it to DSDT.  */
		acpigen_write_scope("\\");
		acpigen_write_name_dword("NVSA", (u32)gnvs);
		acpigen_pop_len();
	}
}

__weak void acpi_create_serialio_ssdt(acpi_header_t *ssdt) {}
