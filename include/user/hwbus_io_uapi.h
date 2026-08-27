#ifndef HWBUS_IO_UAPI_H
#define HWBUS_IO_UAPI_H

#include <sys/ioctl.h>
#include <stdint.h>

/* Definiciones de Offset PCI (si no se incluyen desde <linux/pci_regs.h>) */
#ifndef PCI_VENDOR_ID
#define PCI_VENDOR_ID 0x00
#define PCI_DEVICE_ID 0x02
#define PCI_COMMAND 0x04
#define PCI_STATUS 0x06
#define PCI_REVISION_ID 0x08
#define PCI_CLASS_PROG 0x09
#define PCI_CLASS_DEVICE 0x0a
#define PCI_CACHE_LINE_SIZE 0x0c
#define PCI_LATENCY_TIMER 0x0d
#define PCI_HEADER_TYPE 0x0e
#define PCI_BIST 0x0f
#define PCI_BASE_ADDRESS_0 0x10
#define PCI_BASE_ADDRESS_1 0x14
#define PCI_BASE_ADDRESS_2 0x18
#define PCI_BASE_ADDRESS_3 0x1c
#define PCI_BASE_ADDRESS_4 0x20
#define PCI_BASE_ADDRESS_5 0x24
#define PCI_SUBSYSTEM_VENDOR_ID 0x2c
#define PCI_SUBSYSTEM_ID 0x2e
#define PCI_ROM_ADDRESS 0x30
#define PCI_CAPABILITY_LIST 0x34
#define PCI_INTERRUPT_LINE 0x3c
#define PCI_INTERRUPT_PIN 0x3d
#endif


#endif // HWBUS_IO_UAPI_H