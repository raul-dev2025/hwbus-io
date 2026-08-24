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

static uint16_t read_sysfs_hex16(const char *path)
{
  FILE *fp;
  uint16_t val = 0;

  fp = fopen(path, "r");
  if (!fp)
  {
    tst_brk(TBROK | TERRNO, "Failed to open %s", path);
    return 0;
  }

  if (fscanf(fp, "0x%" SCNx16, &val) != 1)
  {
    fclose(fp);
    tst_brk(TBROK, "Failed to parse hex value from %s", path);
    return 0;
  }

  fclose(fp);
  return val;
}

static void test_exact_pci_ids(void)
{
  int fd;
  uint16_t expected_vendor, expected_device;
  uint8_t buf[4];
  ssize_t ret;
  uint16_t actual_vendor, actual_device;

  expected_vendor = read_sysfs_hex16(SYSFS_VENDOR_PATH);
  expected_device = read_sysfs_hex16(SYSFS_DEVICE_PATH);

  fd = open(DEV_PATH, O_RDONLY);
  if (fd < 0)
  {
    tst_brk(TBROK | TERRNO, "Failed to open %s", DEV_PATH);
    return;
  }

  ret = read(fd, buf, sizeof(buf));
  close(fd);

  if (ret != 4)
  {
    tst_res(TFAIL, "Exact read returned %ssize %zd, expected 4", DEV_PATH, ret);
    return;
  }

}


static struct tst_test test = {
    .test_all = run_tests,
};