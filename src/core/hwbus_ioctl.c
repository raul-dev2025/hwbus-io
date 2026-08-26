// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * hwbus_ioctl.c - Descripción del módulo/archivo
 *
 * Copyright (C) 2026 Raúl Vílchez Ruiz <raulmicrosistemas@gmail.com>
 */
#include <hwbus-io.h>

long hwbus_unlocked_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
  struct pci_dev *pdev = hwbus_get_pci_dev_from_param();
  u8 offset = _IOC_NR(cmd);
  u8 size = _IOC_SIZE(cmd);
  int ret;

  if (!is_valid_hwbus_cmd(cmd))
    return -ENOTTY;

  if (!access_ok((void __user *)arg, size))
    return -EFAULT;

  switch (size)
  {
  case 1:
  {
    break;
  }
  default:
    return -ENOTTY;
  }

  return 0;
}