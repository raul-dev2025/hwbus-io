// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * sysfs_driver.c - single device pci attribute reading
 *
 * Copyright (C) 2026 Raúl Vílchez Ruiz <raulmicrosistemas@gmail.com>
 */
#include <hwbus_param.h>
#include <linux/pci.h>

ssize_t hwbus_pci_config_read(struct file *filp, char __user *buf,
                              size_t count, loff_t *f_pos)
{
  struct pci_dev *pdev = hwbus_get_pci_dev_from_param();
  u16 val;

  if (!pdev)
    return -ENODEV;

  if (*f_pos == 0 && count >= 2)
  {
    pci_read_config_word(pdev, PCI_VENDOR_ID, &val);
    if (copy_to_user(buf, &val, 2))
      return -EFAULT;
    *f_pos += 2;
    return 2;
  }
  else if (*f_pos == 2 && count >= 2)
  {
    pci_read_config_word(pdev, PCI_DEVICE_ID, &val);
    if (copy_to_user(buf, &val, 2))
      return -EFAULT;
    *f_pos += 2;
    return 2;
  }

  return 0;
}