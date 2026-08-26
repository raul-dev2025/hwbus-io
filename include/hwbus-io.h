#ifndef HWBUS_IO_H
#define HWBUS_IO_H

#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/types.h>

#define HWBUS_MODULE_NAME "hwbus_io"
#define HWBUS_MODULE_VERSION "0.1.0"
#define HWBUS_MAJOR 0
#define HWBUS_DEVS 1

/**
 * struct hwbus_dev - Estructura principal de contexto del driver hwbus-io
 * @dev_id: Identificador único interno
 * @is_active: Estado de inicialización del dispositivo
 * @cdev: dispositivo de carácteres asociado
 * @pdev: dispositivo PCI asociado(BDF)
 */
struct hwbus_dev
{
  u32 dev_id;
  bool is_active;
  struct cdev cdev;
  struct pci_dev *pdev;
};

/*
  IOCTL command encoding - Mapeo declarativo de comandos o
                           despacho semántico por tabla de tipos
*/
#define HWBUS_IOC_MAGIC 'L'

/* Registros de Identificación y Control (16 bits) */
#define HWBUS_IOC_READ_VENDOR _IOR(HWBUS_IOC_MAGIC, PCI_VENDOR_ID, u16)
#define HWBUS_IOC_READ_DEVICE _IOR(HWBUS_IOC_MAGIC, PCI_DEVICE_ID, u16)
#define HWBUS_IOC_READ_COMMAND _IOR(HWBUS_IOC_MAGIC, PCI_COMMAND, u16)
#define HWBUS_IOC_READ_STATUS _IOR(HWBUS_IOC_MAGIC, PCI_STATUS, u16)

/* Registros de Información de Silicio y Clase (8 y 16 bits) */
#define HWBUS_IOC_READ_REVISION _IOR(HWBUS_IOC_MAGIC, PCI_REVISION_ID, u8)
#define HWBUS_IOC_READ_CLASS_PROG _IOR(HWBUS_IOC_MAGIC, PCI_CLASS_PROG, u8)
#define HWBUS_IOC_READ_CLASS _IOR(HWBUS_IOC_MAGIC, PCI_CLASS_DEVICE, u16)

/* Registros Temporales y Cabecera (8 bits) */
#define HWBUS_IOC_READ_CACHE _IOR(HWBUS_IOC_MAGIC, PCI_CACHE_LINE_SIZE, u8)
#define HWBUS_IOC_READ_LATENCY _IOR(HWBUS_IOC_MAGIC, PCI_LATENCY_TIMER, u8)
#define HWBUS_IOC_READ_HTYPE _IOR(HWBUS_IOC_MAGIC, PCI_HEADER_TYPE, u8)
#define HWBUS_IOC_READ_BIST _IOR(HWBUS_IOC_MAGIC, PCI_BIST, u8)

/* Direcciones Base (BARs - 32 bits) */
#define HWBUS_IOC_READ_BAR0 _IOR(HWBUS_IOC_MAGIC, PCI_BASE_ADDRESS_0, u32)
#define HWBUS_IOC_READ_BAR1 _IOR(HWBUS_IOC_MAGIC, PCI_BASE_ADDRESS_1, u32)
#define HWBUS_IOC_READ_BAR2 _IOR(HWBUS_IOC_MAGIC, PCI_BASE_ADDRESS_2, u32)
#define HWBUS_IOC_READ_BAR3 _IOR(HWBUS_IOC_MAGIC, PCI_BASE_ADDRESS_3, u32)
#define HWBUS_IOC_READ_BAR4 _IOR(HWBUS_IOC_MAGIC, PCI_BASE_ADDRESS_4, u32)
#define HWBUS_IOC_READ_BAR5 _IOR(HWBUS_IOC_MAGIC, PCI_BASE_ADDRESS_5, u32)

/* Subsistema y ROM */
#define HWBUS_IOC_READ_SVENDOR _IOR(HWBUS_IOC_MAGIC, PCI_SUBSYSTEM_VENDOR_ID, u16)
#define HWBUS_IOC_READ_SUBSYSTEM _IOR(HWBUS_IOC_MAGIC, PCI_SUBSYSTEM_ID, u16)
#define HWBUS_IOC_READ_ROM _IOR(HWBUS_IOC_MAGIC, PCI_ROM_ADDRESS, u32)

/* Capacidades e Interrupciones */
#define HWBUS_IOC_READ_PTR _IOR(HWBUS_IOC_MAGIC, PCI_CAPABILITY_LIST, u8)
#define HWBUS_IOC_READ_IRQ_LINE _IOR(HWBUS_IOC_MAGIC, PCI_INTERRUPT_LINE, u8)
#define HWBUS_IOC_READ_IRQ_PIN _IOR(HWBUS_IOC_MAGIC, PCI_INTERRUPT_PIN, u8)

loff_t hwbus_llseek(struct file *filp, loff_t off, int whence);
long hwbus_unlocked_ioctl(struct file *filp, unsigned int cmd, unsigned long arg);

#endif // HWBUS_IO_H