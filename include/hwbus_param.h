#ifndef HWBUS_PARAM_H
#define HWBUS_PARAM_H

#include <linux/pci.h>

/*Parametros expuestos*/
extern char *hwbus_bdf_param;

/* Helper para obtener el pci_dev actual a partir del parámetro BDF */
struct pci_dev *hwbus_get_pci_dev_from_param(void);

#endif // HWBUS_PARAM_H