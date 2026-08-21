// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * hwbus_io01.c - Verificación de Presencia y Registro
 *
 * Copyright (C) 2026 Raúl Vílchez Ruiz <raulmicrosistemas@gmail.com>
 *
 * Verifies:
 * 1. Existence and character device properties of /dev/hwbusc.
 * 2. Major number registration (240) in /proc/devices.
 * 3. SysFS class hierarchy under /sys/class/hwbusc/hwbusc/.
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include "tst_test.h"

#define DEV_PATH "/dev/hwbusc"
#define PROC_DEV_PATH "/proc/devices"
#define SYSFS_CLASS "/sys/class/hwbusc/hwbusc/dev"
#define EXPECTED_MAJOR 240


static struct tst_test test = {
    .test_all = run_tests,
};