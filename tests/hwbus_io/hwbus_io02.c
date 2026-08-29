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
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "tst_test.h"
#include <user/hwbus_io_uapi.h>

#define DEV_PATH "/dev/hwbusc"
#define SYSFS_PCI_PATH "/sys/bus/pci/devices/0000:02:00.0/config"

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

static void test_data_width(unsigned long cmd, const char *reg_name)
{
  uint32_t val_ioctl = 0;
  uint32_t val_ref = 0;
  uint32_t mask;
  int ret;

  /* Extrae metadatos */
  uint16_t offset = _IOC_NR(cmd);
  size_t size = _IOC_SIZE(cmd);

  /* LLamada IOCTL del controlador */
  ret = ioctl(fd, cmd, &val_ioctl);
  if (ret < 0)
  {
    tst_res(TFAIL | TERRNO, "Fallo en ioctl() para registro %s (cmd: 0x%lx)", reg_name, cmd);
    return;
  }

  /* Lectura en sysfs */
  read_config_ref(offset, &val_ref, size);

  /* Definicion de mascara segun tamaño */
  switch (size)
  {
  case 1:
    mask = 0x000000FF;
    break;
  case 2:
    mask = 0X0000FFFF;
    break;
  case 4:
    mask = 0XFFFFFFFF;
    break;
  default:
    tst_brk(TBROK, "Tamaño no soportado (%zu) en test_ioctl_by_width para %s", size, reg_name);
    return;
  }

  /* Enmascaramiento para limpiar bits no utilizados */
  val_ioctl &= mask;
  val_ref &= mask;

  /* Comparacion y reporte a LTP */
  if (val_ioctl == val_ref)
  {
    tst_res(TPASS, "Registro %s (offset 0x%02x, %zu bytes): ioctl [0x%0*x] == sysfs [0x%0*x]", reg_name, offset, size, (int)(size * 2), val_ioctl, (int)(size * 2), val_ref);
  }
  else
  {
    tst_res(TFAIL, "Discrepancia en %s (offset 0x%02x): ioctl=0x%0*x != sysfs=0x%0*x", reg_name, offset, (int)(size * 2), val_ioctl, (int)(size * 2), val_ref);
  }
}

static void test_ioctl_dedicated(void)
{
  /* Registros fijos */
  test_data_width(HWBUS_IOC_READ_VENDOR, "PCI_VENDOR_ID");
  test_data_width(HWBUS_IOC_READ_DEVICE, "PCI_DEVICE_ID");

  /* Registros representativos */
  test_data_width(HWBUS_IOC_READ_COMMAND, "PCI_COMMAND");
  test_data_width(HWBUS_IOC_READ_REVISION, "PCI_REVISION_ID");
  test_data_width(HWBUS_IOC_READ_BAR0, "PCI_BASE_ADDRESS_0");
}

static void test_ioctl_invalid()
{
  uint32_t val;
  int ret;

  /* 1. IOCTL con comando no reconocido */
  /* Número magico o comando que el driver no reconoce */
  unsigned long cmd_invalid = _IOR('X', 0xFF, uint32_t);

  ret = ioctl(fd, cmd_invalid, &val);

  if (ret == -1 && errno == ENOTTY)
    tst_res(TPASS, "ioctl() rechazo comando no reconocido con ENOTTY correctamente");
  else
    tst_res(TFAIL, "ioctl() fallo al validar comando invalido (ret=%d, errno=%d, esperado ENOTTY)", ret, errno);

  /* 2. IOCTL valida pero pasando un puntero NULL */
  ret = ioctl(fd, HWBUS_IOC_READ_STATUS, NULL);

  if (ret == -1 && errno == EFAULT)
    tst_res(TPASS, "ioctl() rechazo puntero NULL con EFAULT correctamente");
  else
    tst_res(TFAIL, "ioctl() fallo al validar puntero NULL (ret=%d, errno=%d, esperado EFAULT)", ret, errno);
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

static void run_tests(void)
{
  test_ioctl_dedicated();
  test_ioctl_invalid();
}
static struct tst_test test = {
    .setup = setup,
    .cleanup = cleanup,
    .test_all = run_tests,
};