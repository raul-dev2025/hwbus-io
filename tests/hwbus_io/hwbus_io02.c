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
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "tst_test.h"
#include <user/hwbus_io_uapi.h>

#define DEV_PATH "dev/hwbusc"
#define SYSFS_PCI_PATH "/sys/bus/pci/devices/0000:02:00.0/"

static int fd = -1;

void read_config_ref(uint16_t offset, void *out_val, size_t size)
{
  int sysfs_fd;
  ssize_t bytes_read;
  const char *sysfs_path = SYSFS_PCI_PATH;

  /* Validar parametros de entrada */
  if (size != 1 && size != 2 && size != 4)
  {
    tst_brk(TBROK, "Tamaño de lectura no válido (%zu bytes). Debe ser 1, 2 o 4.", size);
  }

  if ((offset + size) > 4096)
  {
    tst_brk(TBROK, "El offset 0x%x + tamaño %zu excede el límite de 4096 bytes.", offset, size);
  }

  /* Limpieza de buffer de salida */
  memset(out_val, 0, size);

  /* Apertura del archivo en sysfs */
  sysfs_fd = SAFE_OPEN(sysfs_path, O_RDONLY);

  /* Posicionamiento del puntero en el offset */
  if (lseek(sysfs_fd, offset, SEEK_SET) == (off_t)-1)
  {
    SAFE_CLOSE(sysfs_fd);
    tst_brk(TBROK | TERRNO, "Error en lseek sobre %s en offset 0x%x", sysfs_path, offset);
  }

  /* Lectura y verificacion */
  bytes_read = read(sysfs_fd, out_val, size);
  if (bytes_read != (ssize_t)size)
  {
    SAFE_CLOSE(sysfs_fd);
    tst_brk(TBROK | TERRNO, "Lectura incompleta en SysFS. Esperados %zu bytes, leídos %zd",
            size, bytes_read);
  }

  /* Cierre del descriptor */
  SAFE_CLOSE(sysfs_fd);
}

static void test_ioctl_dedicated(void);

static void test_data_width(unsigned long cmd, uint16_t offset, size_t size, const char *reg_name)
{
  uint32_t val_ioctl = 0;
  uint32_t val_ref = 0;
  uint32_t mask;
  int ret;
}

static void test_ioctl_invalid(void);

static void setup(void)
{
  fd = SAFE_OPEN(DEV_PATH, O_RDWR);
}

static void cleanup(void)
{
  if (fd >= 0)
    SAFE_CLOSE(fd);
}

static void run_tests(void) {}
static struct tst_test test = {
    .setup = setup,
    .cleanup = cleanup,
    .test_all = run_tests,
};