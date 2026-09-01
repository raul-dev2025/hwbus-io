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

/// @brief Consulta ioctl() sobre fd para obtener la dirección BDF activa.
/// @param bdf_out
/// @param size
static void get_device_bdf(char *bdf_out, size_t size)
{
  if (fd < 0)
    tst_brk(TBROK, "File descriptor /dev/hwbusc is invalid");

  memset(bdf_out, 0, size);

  if (ioctl(fd, HWBUS_IOC_GET_BDF, bdf_out) < 0)
  {
    tst_brk(TBROK | TERRNO, "ioctl(HWBUS_IOC_GET_BDF) failed");
  }

  bdf_out[size - 1] = '\0';
  bdf_out[strcspn(bdf_out, "\r\n")] = '\0';
}

/// @brief Lectura atómica en SysFS usando la macro de LTP SAFE_FILE_READ_ATOMIC.
/// @param sysfs_out
/// @param size
static void read_sysfs_param(char *sysfs_out, size_t size)
{
  memset(sysfs_out, 0, size);
  SAFE_FILE_SCANF(BDF_PARAM, "%31s", sysfs_out);
  sysfs_out[size - 1] = '\0';
  sysfs_out[strcspn(sysfs_out, "\r\n")] = '\0';
}


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

static const char *const kconfig[] = {
    "CONFIG_PCI=y",
    "CONFIG_MODULES=y",
    NULL};

static struct tst_test test = {
    .needs_root = 1,
    .needs_kconfigs = kconfig,
    .setup = setup,
    .cleanup = cleanup,
    .test_all = run_test,
};