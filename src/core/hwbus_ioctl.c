// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * hwbus_ioctl.c - Descripción del módulo/archivo
 *
 * Copyright (C) 2026 Raúl Vílchez Ruiz <raulmicrosistemas@gmail.com>
 */
#include <hwbus-io.h>
#include <hwbus_param.h>

static bool is_valid_hwbus_cmd(unsigned int cmd)
{
  u8 offset = _IOC_NR(cmd);
  u8 size = _IOC_SIZE(cmd);
  /*RO, numero mágico, 64B limite, alineación natural*/
  return (_IOC_TYPE(cmd) == HWBUS_IOC_MAGIC) &&
         (_IOC_DIR(cmd) == _IOC_READ) &&
         (offset <= 0x3c) &&
         (size == 1 || size == 2 || size == 4) &&
         (offset % size == 0);
}

long hwbus_unlocked_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
  struct pci_dev *pdev = hwbus_get_pci_dev_from_param();
  int ret;

  if (cmd == HWBUS_IOC_GET_BDF)
  {
    struct hwbus_bdf_info info;

    if (!pdev)
      return -ENODEV;

    return 0;
  }

  u8 offset = _IOC_NR(cmd);
  u8 size = _IOC_SIZE(cmd);

  if (!is_valid_hwbus_cmd(cmd))
    return -ENOTTY;

  if (!access_ok((void __user *)arg, size))
    return -EFAULT;

  switch (size)
  {
  case 1:
  {
    u8 val8;
    ret = pci_read_config_byte(pdev, offset, &val8);
    if (ret)
      return ret;
    if (put_user(val8, (u8 __user *)arg))
      return -EFAULT;
    break;
  }
  case 2:
  {
    u16 val16;
    ret = pci_read_config_word(pdev, offset, &val16);
    if (ret)
      return ret;
    if (put_user(val16, (u16 __user *)arg))
      return -EFAULT;
    break;
  }
  case 4:
  {
    u32 val32;
    ret = pci_read_config_dword(pdev, offset, &val32);
    if (ret)
      return ret;
    if (put_user(val32, (u32 __user *)arg))
      return -EFAULT;
    break;
  }
  default:
    return -ENOTTY;
  }

  return 0;
}