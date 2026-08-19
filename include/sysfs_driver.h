#ifndef HWBUS_SYSFS_DRIVER_H
#define HWBUS_SYSFS_DRIVER_H

#include <linux/device.h>
#include <linux/sysfs.h>

/* Funciones nativas para inicializar y remover los atributos del driver en sysfs */
int hwbus_sysfs_init(struct device *dev);
void hwbus_sysfs_cleanup(struct device *dev);

ssize_t hwbus_pci_config_read(struct file *filp, char __user *buf,
                              size_t count, loff_t *f_pos);

#endif /* HWBUS_SYSFS_DRIVER_H */