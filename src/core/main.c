// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * main.c - Descripción del módulo/archivo
 *
 * Copyright (C) 2026 Raúl Vílchez Ruiz <raulmicrosistemas@gmail.com>
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <hwbus-io.h>
#include "hwbus_param.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Raul Vilchez");
MODULE_DESCRIPTION("Simple char device");
MODULE_VERSION("0.0.1");

// Identificacion del dispositivo de caracteres
static int hwbus_major = HWBUS_MAJOR;
static int hwbus_devs_count = HWBUS_DEVS;
static dev_t dev_num;

// Modelo de dispositivo y estructuras de estado
static struct class *hwbus_class = NULL;
static struct device *hwbus_device = NULL;
static struct hwbus_dev hwbus_device_data;

ssize_t hwbus_pci_config_read(struct file *filp, char __user *buf,
                              size_t count, loff_t *f_pos);

static int hwbus_open(struct inode *inode, struct file *filp)
{
  struct hwbus_dev *dev;
  dev = container_of(inode->i_cdev, struct hwbus_dev, cdev);
  filp->private_data = dev;
  return 0;
}

static int hwbus_release(struct inode *inode, struct file *filp)
{
  return 0;
}

struct file_operations hwbus_fops = {
    .owner = THIS_MODULE,
    .open = hwbus_open,
    .release = hwbus_release,
    .read = hwbus_pci_config_read,
};

static int __init hwbus_init(void)
{
  int result;

  if (hwbus_major)
  {
    dev_num = MKDEV(hwbus_major, 0);
    result = register_chrdev_region(dev_num, hwbus_devs_count, "hwbusc");
  }
  else
  {
    result = alloc_chrdev_region(&dev_num, 0, hwbus_devs_count, "hwbusc");
    hwbus_major = MAJOR(dev_num);
  }

  if (result < 0)
  {
    pr_err("hwbus_io: No se pudo obtener el numero major %d\n", hwbus_major);
    return result;
  }

}

static void __exit hwbus_exit(void)
{
  device_destroy(hwbus_class, dev_num);
  class_destroy(hwbus_class);
  cdev_del(&hwbus_device_data.cdev);
  unregister_chrdev_region(dev_num, hwbus_devs_count);
  pr_info("hwbus_io: Módulo descargado correctamente\n");
}

module_init(hwbus_init);
module_exit(hwbus_exit);