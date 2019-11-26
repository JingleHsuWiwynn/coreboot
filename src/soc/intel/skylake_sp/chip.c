/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2015 - 2017 Intel Corp.
 * Copyright (C) 2017 Online SAS.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <arch/acpi.h>
#include <bootstate.h>
#include <cbfs.h>
#include <assert.h>
#include <console/console.h>
#include <device/device.h>
#include <device/pci.h>
#include <fsp/api.h>
#include <fsp/util.h>
#include <intelblocks/rtc.h>
#include <intelblocks/fast_spi.h>
#include <soc/acpi.h>
#include <soc/iomap.h>
#include <soc/intel/common/vbt.h>
#include <soc/pci_devs.h>
#include <soc/ramstage.h>
#include <spi-generic.h>
#include <soc/hob_mem.h>
#include <soc/skxsp_util.h>
#include <soc/hob_iiouds.h>
#include <lib.h>

#include <cpu/x86/mp.h>
#include <cpu/x86/lapic.h>


struct pci_resource {
	struct device        *dev;
	struct resource      *res;
	struct pci_resource  *next;
};

struct stack_dev_resource {
	u8                        align;
	struct pci_resource       *children;
	struct stack_dev_resource *next;
};

static void skxsp_pci_domain_set_resources(struct device *dev)
{
	DEV_FUNC_ENTER(dev);
	struct bus *link = dev->link_list;
  while (link != NULL) {
    printk(BIOS_DEBUG, "%s:%s bus: 0x%x, path: %s\n", __FILE__, __func__, link->secondary, bus_path(link));
		assign_resources(link);
    link = link->next;
  }

	DEV_FUNC_EXIT(dev);
}

static void skxsp_pci_domain_scan_bus(struct device *dev)
{
	DEV_FUNC_ENTER(dev);
  struct bus *link = dev->link_list;
  while (link != NULL) {
    printk(BIOS_DEBUG, "%s:%s bus: 0x%x, path: %s\n", __FILE__, __func__, link->secondary, bus_path(link));
    pci_scan_bus(link, PCI_DEVFN(0, 0), 0xff);
    link = link->next;
  }
	DEV_FUNC_EXIT(dev);
}

static void skxsp_pci_dev_iterator(struct bus *bus,
		void (*dev_iterator)(struct device *, void *),
		void (*res_iterator)(struct device *, struct resource *, void *),
		void *data)
{
	struct device *curdev;
	struct resource *res;

	/* Walk through all devices and find which resources they need. */
  for (curdev = bus->children; curdev; curdev = curdev->sibling) {
    struct bus *link;

    if (!curdev->enabled)
      continue;

    if (!curdev->ops || !curdev->ops->read_resources) {
      if (curdev->path.type != DEVICE_PATH_APIC)
        printk(BIOS_ERR, "%s missing read_resources\n",
               dev_path(curdev));
      continue;
    }

		if (dev_iterator)
			dev_iterator(curdev, data);

		if (res_iterator) {
			for (res = curdev->resource_list; res; res = res->next)
				res_iterator(curdev, res, data);
		}

    /* Read in the resources behind the current device's links. */
    for (link = curdev->link_list; link; link = link->next)
			skxsp_pci_dev_iterator(link, dev_iterator, res_iterator, data);
  }
}

static void skxsp_pci_dev_read_resources(struct device *dev, void *data)
{
	post_log_path(dev);
	dev->ops->read_resources(dev);
}

static bool need_assignment(struct resource *res)
{
	if (res->size != 0 && ((res->flags & IORESOURCE_IO) || (res->flags & IORESOURCE_MEM)) &&
			!(res->flags & (IORESOURCE_STORED | IORESOURCE_RESERVE | IORESOURCE_FIXED | IORESOURCE_ASSIGNED)))
		return true;
	else
		return false;
}

static void skxsp_dump_pci_resources(struct device *dev, struct resource *res, void *data)
{
	if (need_assignment(res))
		printk(BIOS_DEBUG, "%s%s resource base %llx size %llx "
					"align %d gran %d limit %llx flags %lx type %s%s%s%s%s%s index %lx\n",
					"\t", dev_path(dev), res->base, res->size,
					res->align, res->gran, res->limit, res->flags, resource_type(res),
					(res->flags & IORESOURCE_STORED) ? " stored" : "",
					(res->flags & IORESOURCE_RESERVE) ? " reserved" : "",
					(res->flags & IORESOURCE_FIXED) ? " fixed" : "",
					(res->flags & IORESOURCE_ASSIGNED) ? " assigned" : "",
					(res->flags & IORESOURCE_PREFETCH) ? " prefetchable " : " non-prefetchable",
					res->index);
}

static void skxsp_dump_assigned_pci_resources(struct device *dev, struct resource *res, void *data)
{
  if (res->size != 0 && ((res->flags & IORESOURCE_IO) || (res->flags & IORESOURCE_MEM)) &&
		  !(res->flags & (IORESOURCE_RESERVE | IORESOURCE_FIXED)))
    printk(BIOS_DEBUG, "%s%s resource base %llx size %llx "
          "align %d gran %d limit %llx flags %lx type %s%s%s%s%s%s index %lx\n",
          "\t", dev_path(dev), res->base, res->size,
          res->align, res->gran, res->limit, res->flags, resource_type(res),
          (res->flags & IORESOURCE_STORED) ? " stored" : "",
          (res->flags & IORESOURCE_RESERVE) ? " reserved" : "",
          (res->flags & IORESOURCE_FIXED) ? " fixed" : "",
          (res->flags & IORESOURCE_ASSIGNED) ? " assigned" : "",
          (res->flags & IORESOURCE_PREFETCH) ? " prefetchable " : " non-prefetchable",
          res->index);
}

static void skxsp_pci_dev_dummy_func(struct device *dev)
{
}

static void skxsp_reset_pci_op(struct device *dev, void *data)
{
	if (dev->ops)
		dev->ops->read_resources = skxsp_pci_dev_dummy_func;
}

static STACK_RES *find_stack_for_bus(struct iiostack_resource *info, u8 bus)
{
	for (int i=0; i < info->no_of_stacks; ++i) {
		if (bus >= info->sres[i].BusBase && bus <= info->sres[i].BusLimit)
			return &info->sres[i];
	}
	return NULL;
}

static void add_res_to_stack(struct stack_dev_resource **root, struct device *dev, struct resource *res)
{
	struct stack_dev_resource *cur = *root;
	while (cur) {
		if (cur->align == res->align || cur->next == NULL) /* equal or last record */
			break;
		else if (cur->align > res->align) {
			if (cur->next->align < res->align) /* need to insert new record here */
				break;
			else
				cur = cur->next;
		}
		else {
			break;
		}
	}

	struct stack_dev_resource *nr;
	if (!cur || cur->align != res->align) { /* need to add new record */
		nr = malloc(sizeof(struct stack_dev_resource));
		if (nr == 0)
			die("assign_resource_to_stack(): out of memory.\n");
		memset(nr, 0, sizeof(struct stack_dev_resource));
		nr->align = res->align;
		if (!cur) {
			*root = nr; /* head node */
		}
		else if (cur->align > nr->align) {
			if (cur->next == NULL) {
				cur->next = nr;
			}
			else {
				nr->next = cur->next;
				cur->next = nr;
			}
		}
		else { /* insert in the begining */
			nr->next = cur;
			*root = nr;
		}
	}
	else {
		nr = cur;
	}

	assert (nr != NULL && nr->align == res->align);

	struct pci_resource *npr = malloc(sizeof(struct pci_resource));
	if (npr == 0)
		die("assign_resource_to_stack(): out of memory.\n");
	npr->res = res;
	npr->dev = dev;
	npr->next = NULL;

	if (nr->children == NULL) {
		nr->children = npr;
	}
	else {
		struct pci_resource *pr = nr->children;
		while (pr->next != NULL)
			pr = pr->next;
		pr->next = npr;
	}
}

/**
 * Round a number up to an alignment.
 *
 * @param val The starting value.
 * @param pow Alignment as a power of two.
 * @return Rounded up number.
 */
static resource_t round(resource_t val, unsigned long pow)
{
  resource_t mask;
  mask = (1ULL << pow) - 1ULL;
  val += mask;
  val &= ~mask;
  return val;
}

static void reserve_dev_resources(STACK_RES *stack, unsigned long res_type, struct stack_dev_resource *res_root,
																  struct resource *bridge)
{
	u8	align;
	u64 orig_base, base;

	if (res_type & IORESOURCE_IO)
		orig_base = stack->PciResourceIoBase;
	else if ((res_type & IORESOURCE_MEM) && ((res_type & IORESOURCE_PCI64) ||
		(!res_root && bridge && (bridge->flags & IORESOURCE_PREFETCH))))
		orig_base = stack->PciResourceMem64Base;
	else
		orig_base = stack->PciResourceMem32Base;
	printk(BIOS_DEBUG, "orig_base: 0x%llx\n", orig_base);

	align = 0;
	base = orig_base;
	bool first = 1;
  while (res_root) { /* loop through all devices grouped by alignment requirements */
    struct pci_resource *pr = res_root->children;
    while (pr) {
			if (first) {
				if (bridge) { /* takes highest alignment */
					if (bridge->align < pr->res->align)
						bridge->align = pr->res->align;
					orig_base = round(orig_base, bridge->align);
				}
				else {
					orig_base = round(orig_base, pr->res->align);
				}
				base = orig_base;

				if (bridge)
					bridge->base = base;
				pr->res->base = base;
				first = 0;
			}
			else {
				pr->res->base = round(base, pr->res->align);
				printk(BIOS_DEBUG, "\t\t dev %s base 0x%llx align %d res_base 0x%llx\n",
						  dev_path(pr->dev), base, pr->res->align, pr->res->base);
			}
			pr->res->limit = pr->res->base + pr->res->size - 1;
			base = pr->res->limit + 1;
      pr->res->flags |= (IORESOURCE_ASSIGNED);
      printk(BIOS_DEBUG, "\t[align %d] %s resource base 0x%llx size 0x%llx limit 0x%llx align %d type %s\n",
            pr->res->align, dev_path(pr->dev), pr->res->base, pr->res->size, pr->res->limit,
						pr->res->align, resource_type(pr->res));
      pr = pr->next;
    }
    res_root = res_root->next;
  }

	printk(BIOS_DEBUG, "\t%s: Assigned Range [0x%llx - 0x%llx]\n", __func__, orig_base, base);

	if (bridge) {
		if (first) { /* this bridge doesn't have any resouces, will set it to default window */
				orig_base = round(orig_base, bridge->align);
				bridge->base = orig_base;
				base = orig_base + (1ULL << bridge->gran);
		}

		bridge->size = round(base, bridge->align) - bridge->base;

		bridge->limit = bridge->base + bridge->size - 1;
		bridge->flags |= (IORESOURCE_ASSIGNED);
		base = bridge->limit + 1;
	}

	/* update new limits */
	if (res_type & IORESOURCE_IO)
    stack->PciResourceIoBase = base;
	else if ((res_type & IORESOURCE_MEM) && ((res_type & IORESOURCE_PCI64) ||
		(!res_root && bridge && (bridge->flags & IORESOURCE_PREFETCH))))
    stack->PciResourceMem64Base = base;
  else
    stack->PciResourceMem32Base = base;
}

static void reclaim_resource_mem(struct stack_dev_resource *res_root)
{
  while (res_root) { /* loop through all devices grouped by alignment requirements */
    /* free pci_resource */
    struct pci_resource *pr = res_root->children;
    while (pr) {
      struct pci_resource *dpr = pr;
      pr = pr->next;
      free(dpr);
    }

    /* free stack_dev_resource */
    struct stack_dev_resource *ddr = res_root;
    res_root = res_root->next;
    free(ddr);
  }
}

static void assign_stack_resources(struct iiostack_resource *stack_list, struct device *dev, struct resource *bridge)
{
	struct bus *bus;

	/* Read in the resources behind the current device's links. */
	for (bus = dev->link_list; bus; bus = bus->next) {
		struct device *curdev;
		STACK_RES *stack;

		/* get IIO stack for this bus */
		stack = find_stack_for_bus(stack_list, bus->secondary);
		assert(stack != 0);

		printk(BIOS_DEBUG, "%s: assign_stack_resources processing bus %d for dev %s\n", __func__, bus->secondary, dev_path(dev));

		/* Assign resources to bridge */
		for (curdev = bus->children; curdev; curdev = curdev->sibling) {
			struct resource *res;
			if (!curdev->enabled)
				continue;

			for (res = curdev->resource_list; res; res = res->next) {
				if ((res->flags & IORESOURCE_BRIDGE) &&
						(!bridge ||
						 ((bridge->flags & (IORESOURCE_IO | IORESOURCE_MEM | IORESOURCE_PREFETCH | IORESOURCE_PCI64)) ==
              (res->flags & (IORESOURCE_IO | IORESOURCE_MEM | IORESOURCE_PREFETCH | IORESOURCE_PCI64))))) {
					assign_stack_resources(stack_list, curdev, res);
					printk(BIOS_DEBUG, "%s: dev %s res %s bridge window base 0x%llx limit 0x%llx (parent res: %s)\n",
								 __func__, dev_path(curdev), resource_type(res), res->base, res->limit, (bridge ? resource_type(res) : ""));
					if (bridge) {
						if (!(bridge->flags & IORESOURCE_ASSIGNED)) { /* for 1st time update, overloading IORESOURCE_ASSIGNED */
							bridge->base = res->base;
							bridge->limit = res->limit;
							bridge->flags |= (IORESOURCE_ASSIGNED);
						}
						else {
							/* update bridge range from child bridge range */
							if (res->base < bridge->base)
								bridge->base = res->base;
							if (res->limit > bridge->limit)
								bridge->limit = res->limit;
						}
						bridge->size = (bridge->limit - bridge->base + 1);
						printk(BIOS_DEBUG, "%s: Parent bridge %s base 0x%llx size 0x%llx limit 0x%llx\n",
									 __func__, resource_type(res), bridge->base, bridge->size, bridge->limit);
					}
				}
			}
		}

		/* Pick non-bridged resources for resouce allocation for each resource type */
		unsigned long flags[5] = {IORESOURCE_IO, IORESOURCE_MEM, (IORESOURCE_PCI64|IORESOURCE_MEM),
					(IORESOURCE_MEM|IORESOURCE_PREFETCH), (IORESOURCE_PCI64|IORESOURCE_MEM|IORESOURCE_PREFETCH)};
		u8 no_res_types = 5;
		if (bridge) {
			flags[0] = bridge->flags & (IORESOURCE_IO | IORESOURCE_MEM | IORESOURCE_PREFETCH);
			if ((bridge->flags & IORESOURCE_MEM) && (bridge->flags & IORESOURCE_PREFETCH))
				flags[0] |= IORESOURCE_PCI64;
			no_res_types = 1;
		}

		/* Process each resource type */
		for (int rt=0; rt < no_res_types; ++rt) {
			struct stack_dev_resource *res_root = NULL;

			for (curdev = bus->children; curdev; curdev = curdev->sibling) {
				struct resource *res;
				if (!curdev->enabled)
					continue;

				for (res = curdev->resource_list; res; res = res->next) {
					printk(BIOS_DEBUG, "\tdev %s res %s rt %d flags 0x%lx rt_flags 0x%lx\n", dev_path(curdev), resource_type(res),
								 rt, res->flags & (IORESOURCE_IO | IORESOURCE_MEM | IORESOURCE_PCI64 | IORESOURCE_PREFETCH),
								 flags[rt]);

					if((res->flags & IORESOURCE_BRIDGE) ||
						 (res->flags & (IORESOURCE_STORED | IORESOURCE_RESERVE | IORESOURCE_FIXED | IORESOURCE_ASSIGNED)) ||
						 ((res->flags & (IORESOURCE_IO | IORESOURCE_MEM | IORESOURCE_PCI64 | IORESOURCE_PREFETCH)) != flags[rt]) ||
						 res->size == 0)
						continue;
					else
						add_res_to_stack(&res_root, curdev, res);
				}
			}

			/* Allocate resources and update bridge range */
			if (res_root || (bridge && !(bridge->flags & IORESOURCE_ASSIGNED))) {
				reserve_dev_resources(stack, flags[rt], res_root, bridge);
				reclaim_resource_mem(res_root);
			}
		}
	}
}

static void skxsp_constrain_pci_resources(struct device *dev, struct resource *res, void *data)
{
	STACK_RES *stack = (STACK_RES *) data;
	if (!(res->flags & IORESOURCE_FIXED))
		return;

	u64 base, limit;
	if (res->flags & IORESOURCE_IO) {
    base = stack->PciResourceIoBase;
		limit = stack->PciResourceIoLimit;
	}
  else if ((res->flags & IORESOURCE_MEM) && (res->flags & IORESOURCE_PCI64)) {
    base = stack->PciResourceMem64Base;
		limit = stack->PciResourceMem64Limit;
	}
  else {
    base = stack->PciResourceMem32Base;
		limit = stack->PciResourceMem32Limit;
	}

	if (((res->base + res->size -1) < base) || (res->base > limit)) /* outside window */
		return;

	if (res->limit > limit) /* resource end is out of limit */
		limit = res->base - 1;
	else
		base = res->base + res->size;

	if (res->flags & IORESOURCE_IO) {
    stack->PciResourceIoBase = base;
    stack->PciResourceIoLimit = limit;
  }
  else if ((res->flags & IORESOURCE_MEM) && (res->flags & IORESOURCE_PCI64)) {
    stack->PciResourceMem64Base = base;
    stack->PciResourceMem64Limit = limit;
  }
  else {
    stack->PciResourceMem32Base = base;
    stack->PciResourceMem32Limit = limit;
  }
}

static void skxsp_pci_domain_read_resources(struct device *dev)
{
	struct bus *link;

	DEV_FUNC_ENTER(dev);

	pci_domain_read_resources(dev);

	/*
	 * Walk through all devices in this domain and read resources.
	 * Since there is no callback when read resource operation is
	 * complete for all devices, domain read resource function initiates
	 * read resources for all devices and swaps read resource operation
	 * with dummy function to avoid warning.
	 */
	for (link = dev->link_list; link; link = link->next)
		skxsp_pci_dev_iterator(link, skxsp_pci_dev_read_resources, NULL, NULL);

	for (link = dev->link_list; link; link = link->next)
		skxsp_pci_dev_iterator(link, skxsp_reset_pci_op, NULL, NULL);

	printk(BIOS_DEBUG, "============ BEGIN DUMP NON ZERO PCI RESOURCES ============\n");
	for (link = dev->link_list; link; link = link->next)
		skxsp_pci_dev_iterator(link, NULL, skxsp_dump_pci_resources, NULL);
	printk(BIOS_DEBUG, "============ END DUMP NON ZERO PCI RESOURCES ============\n");


	/*
	 * 1. group devices, resources for each stack
	 * 2. order resources in descending order of requested resource allocation sizes
   */
	struct iiostack_resource stack_info;
	get_iiostack_info(&stack_info);
	printk(BIOS_DEBUG, "No of IIO Stacks %d\n", stack_info.no_of_stacks);
	for (int s=0; s < stack_info.no_of_stacks; ++s)
    printk(BIOS_DEBUG, "\t[Stack %d] [Bus 0x%x - 0x%x]\n", s, stack_info.sres[s].BusBase, stack_info.sres[s].BusLimit);

	/* constrain stack window */
	for (link = dev->link_list; link; link = link->next) {
		STACK_RES *stack = find_stack_for_bus(&stack_info, link->secondary);
    assert(stack != 0);
		printk(BIOS_DEBUG, "Before Constrain Resources bus 0x%x bus_base 0x%x bus_limit 0x%x IoBase 0x%x IoLimit 0x%x "
					 "Mem32Base 0x%x Mem32Limit 0x%x Mem64Base 0x%llx Mem64Limit 0x%llx\n",
					 link->secondary, stack->BusBase, stack->BusLimit, stack->PciResourceIoBase, stack->PciResourceIoLimit,
					 stack->PciResourceMem32Base, stack->PciResourceMem32Limit, stack->PciResourceMem64Base,
					 stack->PciResourceMem64Limit);
    skxsp_pci_dev_iterator(link, NULL, skxsp_constrain_pci_resources, stack);
		printk(BIOS_DEBUG, "After Constrain Resources bus 0x%x bus_base 0x%x bus_limit 0x%x IoBase 0x%x IoLimit 0x%x "
					 "Mem32Base 0x%x Mem32Limit 0x%x Mem64Base 0x%llx Mem64Limit 0x%llx\n",
					 link->secondary, stack->BusBase, stack->BusLimit, stack->PciResourceIoBase, stack->PciResourceIoLimit,
					 stack->PciResourceMem32Base, stack->PciResourceMem32Limit, stack->PciResourceMem64Base,
					 stack->PciResourceMem64Limit);
	}

	/* assign resources */
	assign_stack_resources(&stack_info, dev, NULL);

	/* reclaim memory */
	free(stack_info.sres);

	printk(BIOS_DEBUG, "============ BEGIN DUMP ASSIGNED NON ZERO PCI RESOURCES ============\n");
	for (link = dev->link_list; link; link = link->next)
		skxsp_pci_dev_iterator(link, NULL, skxsp_dump_assigned_pci_resources, NULL);
	printk(BIOS_DEBUG, "============ END DUMP ASSIGNED NON ZERO PCI RESOURCES ============\n");

	DEV_FUNC_EXIT(dev);
}

#if CONFIG(HAVE_ACPI_TABLES)
static const char *soc_acpi_name(const struct device *dev)
{
  return "";
}
#endif

static struct device_operations pci_domain_ops = {
	.read_resources = &skxsp_pci_domain_read_resources,
	.set_resources = &skxsp_pci_domain_set_resources,
	.scan_bus = &skxsp_pci_domain_scan_bus,
#if CONFIG(HAVE_ACPI_TABLES)
  .write_acpi_tables  = &northbridge_write_acpi_tables,
	//.acpi_fill_ssdt_generator = northbridge_acpi_write_vars,
  .acpi_name    = &soc_acpi_name,
#endif
};

static struct device_operations cpu_bus_ops = {
	.read_resources = DEVICE_NOOP,
	.set_resources = DEVICE_NOOP,
	.enable_resources = DEVICE_NOOP,
	.init = skylake_sp_init_cpus,
	.scan_bus = NULL,
#if CONFIG(HAVE_ACPI_TABLES)
	.acpi_fill_ssdt_generator = generate_cpu_entries, /* defined in src/soc/intel/common/block/acpi/acpi.c */
#endif
};

/* Attach IIO stack bus numbers with dummy device to PCI DOMAIN 0000 device */
static void attach_iio_stacks(struct device *dev)
{
	struct bus *iiostack_bus;
	struct device dummy;
	struct iiostack_resource stack_info;

	DEV_FUNC_ENTER(dev);

	get_iiostack_info(&stack_info);
	for (int s=0; s < stack_info.no_of_stacks; ++s) {
		printk(BIOS_DEBUG, "Attaching stack 0x%x to device %s\n", stack_info.sres[s].BusBase, dev_path(dev));
		if (stack_info.sres[s].BusBase == 0) /* only non zero bus no. needs to be enumerated */
			continue;

		iiostack_bus = malloc(sizeof(struct bus));
		if (iiostack_bus == 0)
			die("attach_iio_stacks(): out of memory.\n");
		memset(iiostack_bus, 0, sizeof(struct bus));
		memcpy(iiostack_bus, dev->bus, sizeof(struct bus));
		iiostack_bus->secondary = stack_info.sres[s].BusBase;
		iiostack_bus->subordinate = stack_info.sres[s].BusBase;
		iiostack_bus->dev = NULL;
		iiostack_bus->children = NULL;
		iiostack_bus->next = NULL;
		iiostack_bus->link_num = 1;

		dummy.bus = iiostack_bus;
		dummy.path.type = DEVICE_PATH_PCI;
		dummy.path.pci.devfn = 0;
		u32 id = pci_read_config32(&dummy, PCI_VENDOR_ID);
		if (id == 0xffffffff)
			printk(BIOS_WARNING, "IIO Stack device %s not visible\n", dev_path(&dummy));

		if (dev->link_list == NULL) {
			dev->link_list = iiostack_bus;
		}
		else {
			struct bus *nlink = dev->link_list;
			while (nlink->next != NULL)
				nlink = nlink->next;
			nlink->next = iiostack_bus;
		}
	}

	DEV_FUNC_EXIT(dev);
}

static void soc_enable_dev(struct device *dev)
{
	DEV_FUNC_ENTER(dev);
	/* Set the operations if it is a special bus type */
	if (dev->path.type == DEVICE_PATH_DOMAIN) {
		dev->ops = &pci_domain_ops;
		attach_iio_stacks(dev);
	}
	else if (dev->path.type == DEVICE_PATH_CPU_CLUSTER) {
		dev->ops = &cpu_bus_ops;
	}
	DEV_FUNC_EXIT(dev);
}

static const struct mp_ops mp_ops = {
  .pre_mp_init = NULL,
  .get_cpu_count = get_platform_thread_count,
  .get_smm_info = NULL,
  .pre_mp_smm_init = NULL,
  .relocation_handler = NULL,
  .post_mp_init = NULL,
};

static void soc_init(void *data)
{
	FUNC_ENTER();

	printk(BIOS_DEBUG, "coreboot: calling fsp_silicon_init\n");
	fsp_silicon_init(false);

	if (0) {
		struct device *curdev;
		for (curdev = dev_root.link_list->children; curdev; curdev = curdev->sibling) {
			if (curdev->path.type == DEVICE_PATH_CPU_CLUSTER) {
				printk(BIOS_DEBUG, "Found CPU Cluster\n");
				if (mp_init_with_smm(curdev->link_list, &mp_ops) < 0)
					printk(BIOS_ERR, "MP initialization failure.\n");
			}
		}
		die("halt...");
	}

	printk(BIOS_DEBUG, "coreboot: calling soc_save_dimm_info \n");
	soc_save_dimm_info();

	soc_display_iio_universal_data_hob();

	FUNC_EXIT();
}

static void soc_final(void *data)
{
	FUNC_ENTER();
	FUNC_EXIT();
}

static void soc_silicon_init_params(FSPS_UPD *silupd)
{
}

void platform_fsp_silicon_init_params_cb(FSPS_UPD *silupd)
{
	const struct microcode *microcode_file;
	size_t microcode_len;

	microcode_file = cbfs_boot_map_with_leak("cpu_microcode_blob.bin",
		CBFS_TYPE_MICROCODE, &microcode_len);

	if ((microcode_file != NULL) && (microcode_len != 0)) {
		/* Update CPU Microcode patch base address/size */
		silupd->FspsConfig.PcdCpuMicrocodePatchBase =
		       (uint32_t)microcode_file;
		silupd->FspsConfig.PcdCpuMicrocodePatchSize =
		       (uint32_t)microcode_len;
	}

	soc_silicon_init_params(silupd);
	mainboard_silicon_init_params(silupd);
}

struct chip_operations soc_intel_skylake_sp_ops = {
	CHIP_NAME("Intel Skylake-SP SOC")
	.enable_dev = soc_enable_dev,
	.init = soc_init,
	.final = soc_final
};

static void soc_set_subsystem(struct device *dev, uint32_t vendor,
			      uint32_t device)
{
	if (!vendor || !device) {
		pci_write_config32(dev, PCI_SUBSYSTEM_VENDOR_ID,
				   pci_read_config32(dev, PCI_VENDOR_ID));
	} else {
		pci_write_config32(dev, PCI_SUBSYSTEM_VENDOR_ID,
				   ((device & 0xffff) << 16) |
					   (vendor & 0xffff));
	}
}

struct pci_operations soc_pci_ops = {
	.set_subsystem = soc_set_subsystem,
};

/*
 * spi_flash init() needs to run unconditionally on every boot (including
 * resume) to allow write protect to be disabled for eventlog and nvram
 * updates. This needs to be done as early as possible in ramstage. Thus, add a
 * callback for entry into BS_PRE_DEVICE.
 */
static void spi_flash_init_cb(void *unused)
{
       //fast_spi_init();
}

BOOT_STATE_INIT_ENTRY(BS_PRE_DEVICE, BS_ON_ENTRY, spi_flash_init_cb, NULL);
