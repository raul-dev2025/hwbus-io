#ifndef HWBUS_SYSFS_PATHS_H
#define HWBUS_SYSFS_PATHS_H

/* Rutas base de sysfs para inspección POSIX */
#define SYSFS_PCI_DEV "/sys/bus/pci/devices"
#define SYSFS_CLASS_NVME "/sys/class/nvme"
#define SYSFS_CLASS_NET "/sys/class/net"

/* Atributos PCI en sysfs */
#define SYSFS_PCI_CONFIG "config"
#define SYSFS_PCI_MAX_LINK_SPEED "max_link_speed"
#define SYSFS_PCI_CUR_LINK_SPEED "current_link_speed"
#define SYSFS_PCI_MAX_LINK_WIDTH "max_link_width"
#define SYSFS_PCI_CUR_LINK_WIDTH "current_link_width"
#define SYSFS_PCI_AER_CORRECTABLE "aer_dev_correctable"
#define SYSFS_PCI_AER_FATAL "aer_dev_fatal"

/* Atributos de Red en sysfs */
#define SYSFS_NET_OPERSTATE "operstate"
#define SYSFS_NET_SPEED "speed"
#define SYSFS_NET_DUPLEX "duplex"
#define SYSFS_NET_RX_DROPPED "statistics/rx_dropped"
#define SYSFS_NET_TX_DROPPED "statistics/tx_dropped"

#endif /* HWBUS_SYSFS_PATHS_H */