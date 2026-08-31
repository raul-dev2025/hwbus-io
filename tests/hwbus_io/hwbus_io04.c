// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * hwbus_io04.c - Verificación de Parámetros de Módulo
 *
 * Copyright (C) 2026 Raúl Vílchez Ruiz <raulmicrosistemas@gmail.com>
 */
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>

#include "tst_test.h"
#include "tst_module.h"
#include <user/hwbus_io_uapi.h>

#define DEV_PATH "/dev/hwbusc"
#define BDF_PARAM "/sys/module/hwbus_io/parameters/bdf"
#define MODULE_PATH "/mnt/build-output/Repos/hwbus-io.git/src"

static int fd = -1;


static void setup(void)
{
  fd = SAFE_OPEN(DEV_PATH, O_RDWR);
}

static void cleanup(void)
{
  if (fd >= 0)
    SAFE_CLOSE(fd);
}

static void run_test(void)
{
}

static struct tst_test test = {
    .needs_root = 1,
    .needs_kconfigs = 1,
    .setup = setup,
    .cleanup = cleanup,
    .test_all = run_test,
};