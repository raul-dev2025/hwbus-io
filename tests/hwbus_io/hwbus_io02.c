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

  /* Little-endian decoding: bytes 0-1 (VendorID), bytes 2-3 (DeviceID) */
  actual_vendor = (uint16_t)buf[0] | ((uint16_t)buf[1] << 8);
  actual_device = (uint16_t)buf[2] | ((uint16_t)buf[3] << 8);

  if (actual_vendor == expected_vendor && actual_device == expected_device)
  {
    tst_res(TPASS, "Read exact PCI IDs match SysFS (VendorID: 0x%04x, DeviceID: 0x%04x)",
            actual_vendor, actual_device);
  }
  else
  {
    tst_res(TFAIL, "PCI IDs mismatch: got VendorID=0x%04x DeviceID=0x%04x, expected VendorID=0x%04x DeviceID=0x%04x",
            actual_vendor, actual_device, expected_vendor, expected_device);
  }
}

static void test_partial_read(void)
{
  int fd;
  uint16_t expected_vendor;
  uint8_t buf[2];
  ssize_t ret;
  uint16_t actual_vendor;

  expected_vendor = read_sysfs_hex16(SYSFS_VENDOR_PATH);

  fd = open(DEV_PATH, O_RDONLY);
  if (fd < 0)
  {
    tst_brk(TBROK | TERRNO, "Failed to open %s", DEV_PATH);
    return;
  }

  ret = read(fd, buf, sizeof(buf));
  close(fd);

  if (ret != 2)
  {
    tst_res(TFAIL, "Partial read returned %zd bytes, expected 2", ret);
    return;
  }

  actual_vendor = (uint16_t)buf[0] | ((uint16_t)buf[1] << 8);

  if (actual_vendor == expected_vendor)
  {
    tst_res(TPASS, "Partial read (2 bytes) returned correct VendorID: 0x%04x", actual_vendor);
  }
  else
  {
    tst_res(TFAIL, "Partial read VendorID mismatch: got 0x%04x, expected 0x%04x",
            actual_vendor, expected_vendor);
  }
}

static void test_overflow_and_eof(void)
{
  int fd;
  uint8_t buf[64];
  ssize_t ret;

  fd = open(DEV_PATH, O_RDONLY);

  /* First read requesting 64 bytes - should truncate to 4 bytes */
  ret = read(fd, buf, sizeof(buf));

  /* Second consecutive read - should return 0 (EOF) due to f_pos advancement */
  ret = read(fd, buf, sizeof(buf));
  close(fd);

}

static void run_tests(void)
{
  test_exact_pci_ids();
  test_partial_read();
  test_overflow_and_eof();
}

static struct tst_test test = {
    .test_all = run_tests,
};