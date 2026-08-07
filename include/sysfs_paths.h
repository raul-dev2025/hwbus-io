/*
 * Constantes puras, cadenas de texto con rutas de sysfs y offsets de hardware (compartida por tests y la app).
 */

#ifndef SYSFS_PATHS_H
#define SYSFS_PATHS_H

/* RUTA BASE DE SYSFS */
#define SYSFS_PCI_DEV "/sys/bus/pci/devices"
#define SYSFS_CLASS_NVME "/sys/class/nvme"
#define SYSFS_CLASS_NET "/sys/class/net"

/* 1. PARÁMETROS Y ERRORES DE ENLACE PCIE */
#define SYSFS_PCI_CONFIG "config"
#define SYSFS_PCI_MAX_LINK_SPEED "max_link_speed"       /* Velocidad máxima soportada (ej. 16.0 GT/s) */
#define SYSFS_PCI_CUR_LINK_SPEED "current_link_speed"   /* Velocidad actual negociada */
#define SYSFS_PCI_MAX_LINK_WIDTH "max_link_width"       /* Ancho de líneas máximo (ej. 4) */
#define SYSFS_PCI_CUR_LINK_WIDTH "current_link_width"   /* Ancho de líneas actual */
#define SYSFS_PCI_AER_CORRECTABLE "aer_dev_correctable" /* Errores corregibles (AER) */
#define SYSFS_PCI_AER_FATAL "aer_dev_fatal"             /* Errores fatales (AER) */

/* 2. REGISTROS DEL ESPACIO DE CONFIGURACIÓN PCI (OFFSETS) */
#define PCI_VENDOR_ID 0x00       /* 2 bytes */
#define PCI_DEVICE_ID 0x02       /* 2 bytes */
#define PCI_COMMAND 0x04         /* 2 bytes */
#define PCI_STATUS 0x06          /* 2 bytes */
#define PCI_CLASS_REVISION 0x08  /* 4 bytes (Revision ID + Class Code) */
#define PCI_HEADER_TYPE 0x0E     /* 1 byte */
#define PCI_CAPABILITY_LIST 0x34 /* 1 byte (Offset a la primera Capability) */

/* 3. CAPABILITIES EXTENDIDAS (OFFSETS EN REGISTRO DE CONFIGURACIÓN) */
#define PCI_CAP_ID_PM 0x01   /* Power Management */
#define PCI_CAP_ID_EXP 0x10  /* PCI Express Capability Structure */
#define PCI_CAP_ID_MSIX 0x11 /* MSI-X Interrupts */

/* 4. MONITOREO DE RED (ETH/NIC SYSFS ATTRIBUTES) */
#define SYSFS_NET_OPERSTATE "operstate"              /* Estado del enlace: up/down */
#define SYSFS_NET_SPEED "speed"                      /* Velocidad en Mbps */
#define SYSFS_NET_DUPLEX "duplex"                    /* Modo full/half */
#define SYSFS_NET_RX_DROPPED "statistics/rx_dropped" /* Paquetes descartados en RX */
#define SYSFS_NET_TX_DROPPED "statistics/tx_dropped" /* Paquetes descartados en TX */

#endif /* SYSFS_PATHS_H */