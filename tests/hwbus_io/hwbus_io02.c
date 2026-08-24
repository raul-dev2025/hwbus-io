// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * hwbus_io02.c - Validación de Lecturas y Contenido PCI
 *
 * Copyright (C) 2026 Raúl Vílchez Ruiz <raulmicrosistemas@gmail.com>
 *
 * Verifies:
 * 1. Exact read of VendorID and DeviceID (4 bytes, little-endian) matching SysFS.
 * 2. Partial read (2 bytes) returning only VendorID.
 * 3. Buffer overflow request (64 bytes) truncated to 4 bytes, and subsequent
 *    EOF (0 bytes read) due to f_pos displacement.
 */
#include <fcntl.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "tst_test.h"

#define DEV_PATH "/dev/hwbusc"
#define SYSFS_VENDOR_PATH "/sys/bus/pci/devices/0000:02:00.0/vendor"
#define SYSFS_DEVICE_PATH "/sys/bus/pci/devices/0000:02:00.0/device"

static struct tst_test test = {
    .test_all = run_tests,
};