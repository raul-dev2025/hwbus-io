// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * main.c - Descripción del módulo/archivo
 *
 * Copyright (C) 2026 Raúl Vílchez Ruiz <raulmicrosistemas@gmail.com>
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <hwbus-io.h>
#include "hwbus_param.h"
