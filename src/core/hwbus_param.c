// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * hwbus_param.c - Parámetros disponibles
 *
 * Copyright (C) 2026 Raúl Vílchez Ruiz <raulmicrosistemas@gmail.com>
 */

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/pci.h>
#include "hwbus_param.h"

// Valor por defecto: "0000:02:00.0"
char *hwbus_bdf_param = "0000:02:00.0";
module_param_named(bdf, hwbus_bdf_param, charp, 0444);
MODULE_PARM_DESC(bdf, "Target PCI Device BDF (e.g. 0000:02:00.0)");

