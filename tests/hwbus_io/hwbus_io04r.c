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
#include <libgen.h>

#include "tst_test.h"
#include "tst_module.h"
#include <user/hwbus_io_uapi.h>

#ifndef PCI_SLOT
#define PCI_SLOT(devfn) (((devfn) >> 3) & 0x1f)
#endif
#ifndef PCI_FUNC
#define PCI_FUNC(devfn) ((devfn) & 0x07)
#endif

#define DEV_PATH "/dev/hwbusc"
#define BDF_PARAM "/sys/module/hwbus_io/parameters/bdf"

#ifndef MODULE_DIR
#define MODULE_DIR "/mnt/build-output/Repos/hwbus-io.git/src/core"
#endif

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

/// @brief Compara los valores en SysFS y /dev/hwbusc, constatando el bdf.
/// @param expected_bdf
static void verify_bdf_consistency(const char *expected_bdf)
{
  char sysfs_bdf[32], dev_bdf[32];

  get_device_bdf(dev_bdf, sizeof(dev_bdf));
  read_sysfs_param(sysfs_bdf, sizeof(sysfs_bdf));

  if (strcmp(dev_bdf, sysfs_bdf) != 0)
  {
    tst_res(TFAIL, "Inconsistencia detectada: /dev/hwbusc (%s) != SysFS (%s)",
            dev_bdf, sysfs_bdf);
    return;
  }

  if (strcmp(dev_bdf, expected_bdf) != 0)
  {
    tst_res(TFAIL, "BDF no coincide con el esperado: obtenido (%s) != esperado (%s)",
            dev_bdf, expected_bdf);
    return;
  }

  tst_res(TPASS, "BDF %s en /dev/ y BDF %s en SysFS coinciden.",
          dev_bdf, sysfs_bdf);
}

/// @brief Orquestar el ciclo de recarga, utilizando las herramientas LTP.
/// @param bdf_str
static void reload_hwbus_module(const char *bdf_str)
{
  char param[64];
  char *const params[] = {param, NULL};
  // char mod_dir[] = MODULE_DIR;
  char cwd[1024];

  snprintf(param, sizeof(param), "bdf=%s", bdf_str);

  SAFE_CLOSE(fd);

  // Situa el WD en el directorio .ko
  // setenv("LTP_MODULE_PATH", dirname(mod_dir), 1);
  // chdir(dirname(mod_dir));
  // SAFE_SETENV("LTP_MODULE_PATH", MODULE_DIR, 1);
  // chdir(MODULE_DIR);
  // cambia al directorio y vuelve a consultar getcwd

  tst_module_unload("hwbus_io");
  if (getcwd(cwd, sizeof(cwd)))
    tst_res(TINFO, "Directorio actual (WD): %s", cwd);
  chdir(MODULE_DIR);
  if (getcwd(cwd, sizeof(cwd)))
    tst_res(TINFO, "Directorio actual (WD): %s", cwd);
  tst_module_load("hwbus_io.ko", params);
  tst_res(TINFO, "Probando recarga con BDF: %s", bdf_str);
  fd = SAFE_OPEN(DEV_PATH, O_RDWR);
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
  // const char *test_bdfs[] = {"0000:03:00.0", "0000:00:02.2", "0000:0a:01.0"};
  const char *test_bdfs[] = {"0000:03:00.0"};
  for (int i = 0; i < 1; i++)
  {
    reload_hwbus_module(test_bdfs[i]);
    verify_bdf_consistency(test_bdfs[i]);
  }
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