// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * sysfs_driver.c - single device pci attribute reading
 *
 * Copyright (C) 2026 Raúl Vílchez Ruiz <raulmicrosistemas@gmail.com>
 */
#include <linux/pci.h>

static ssize_t hwbus_pci_config_read(struct file *filp, char __user *buf,
                                     size_t count, loff_t *f_pos)
{
  struct pci_dev *pdev = get_target_pci_dev();
  u16 val;

  return 0;
}