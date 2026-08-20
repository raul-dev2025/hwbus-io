// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * pci_single_conf.c - Consula de atributos en el bus PCI en un dispositivo específico
 *
 * Copyright (C) 2026 Raúl Vílchez Ruiz <raulmicrosistemas@gmail.com>
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "sysfs_paths.h"
#include "tst_test.h"

static const char *target_bdf = "0000:02:00.0";

static void run(void)
{
  char path[1024];
  int fd;
  unsigned short vendor_id = 0, device_id = 0;

  snprintf(path, sizeof(path), "%s/%s/%s", SYSFS_PCI_DEV, target_bdf, SYSFS_PCI_CONFIG);

  fd = open(path, O_RDONLY);
  if (fd < 0)
  {
    tst_brk(TBROK | TERRNO, "No se pudo abrir config para el BDF %s", target_bdf);
  }
  if (read(fd, &vendor_id, 2) == 2 && read(fd, &device_id, 2) == 2)
  {
    tst_res(TPASS, "BDF %s -> VendorID: 0x%04x | DeviceID: 0x%04x",
            target_bdf, vendor_id, device_id);
  }
  else
  {
    tst_res(TFAIL | TERRNO, "Error leyendo cabecera de config para %s", target_bdf);
  }

  close(fd);
}

static struct tst_test test = {
    .test_all = run,
};
