#ifndef HWBUS_SYSFS_DRIVER_H
#define HWBUS_SYSFS_DRIVER_H

#include <linux/sysfs.h>
#include <linux/device.h>

/* Funciones nativas para inicializar y remover los atributos del driver en sysfs */
int hwbus_sysfs_init(struct device *dev);
void hwbus_sysfs_cleanup(struct device *dev);

#endif /* HWBUS_SYSFS_DRIVER_H */