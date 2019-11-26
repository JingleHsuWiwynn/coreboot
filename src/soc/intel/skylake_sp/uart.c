/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2015 Google Inc.
 * Copyright (C) 2015-2018 Intel Corporation
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

#include <console/console.h>
#include <intelblocks/uart.h>
#include <soc/pci_devs.h>

DEVTREE_CONST struct device *soc_uart_console_to_device(int uart_console)
{
	/*
	 * if index is valid, this function will return corresponding structure
	 * for uart console else will return NULL.
	 */
	switch (uart_console) {
	case 0:
		return (struct device *)PCH_DEV_UART0;
	case 1:
		return (struct device *)PCH_DEV_UART1;
	case 2:
		return (struct device *)PCH_DEV_UART2;
	default:
		printk(BIOS_ERR, "Invalid UART console index\n");
		return NULL;
	}
}
