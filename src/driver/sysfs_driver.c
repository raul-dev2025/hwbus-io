// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * sysfs_driver.c - single device pci attribute reading
 *
 * Copyright (C) 2026 Raúl Vílchez Ruiz <raulmicrosistemas@gmail.com>
 */
/*
  - Atributos de estado del dispositivo (/sys/class/hwbusc/hwbusc/): Exposición de información de diagnóstico en modo texto (ASCII) para inspección rápida mediante cat, sin requerir llamadas IOCTL (por ejemplo, estado de vinculación PCI, estadísticas de lecturas o errores).
*/

/*
  - Callbacks de atributos (sysfs_ops): Implementación de funciones show y store mediante las macros de kernel DEVICE_ATTR_RO o DEVICE_ATTR_RW.
*/

/*
  - Control dinámico vía SysFS: Posibilidad de modificar comportamientos en tiempo de ejecución (como alternar el nivel de depuración o forzar un re-escaneo del bus
*/
