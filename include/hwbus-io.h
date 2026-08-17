#ifndef HWBUS_IO_H
#define HWBUS_IO_H

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/types.h>

#define HWBUS_MODULE_NAME "hwbus_io"
#define HWBUS_MODULE_VERSION "0.1.0"
#define HWBUS_MAJOR 0
#define HWBUS_DEVS 1

/**
 * struct hwbus_dev - Estructura principal de contexto del driver hwbus-io
 * @dev_id: Identificador único interno
 * @is_active: Estado de inicialización del dispositivo
 */
struct hwbus_dev
{
  u32 dev_id;
  bool is_active;
};

int __init hwbus_init(void);
void __exit hwbus_exit(void);

#endif // HWBUS_IO_H
