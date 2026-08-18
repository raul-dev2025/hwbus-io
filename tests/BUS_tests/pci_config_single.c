/*
 * pci_config_test.c
 * 
 * Test de validacion del Espacio de Configuracion PCI mediante sysfs.
 * Parte de la Fase 2 del proyecto foundry.
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include "tst_test.h"

#define SYSFS_PCI_DEV "/sys/bus/pci/devices"

static void run(void)
{
	DIR *dir;
	struct dirent *entry;
	char path[1024];
	int fd, count = 0;
   const char *target_bdf = "0000:01:00.0";
	unsigned short vendor_id = 0, device_id = 0;

	dir = opendir(SYSFS_PCI_DEV);
	if (!dir) {
		tst_brk(TBROK | TERRNO, "No se pudo abrir el directorio %s", SYSFS_PCI_DEV);
	}

	tst_res(TINFO, "Escaneando dispositivos en %s...", SYSFS_PCI_DEV);

	while ((entry = readdir(dir)) != NULL) {
		/* Ignorar entradas '.' y '..' */
		if (entry->d_name[0] == '.')
			continue;

		/*consulta un dispositivo*/
		if(strstr(entry->d_name, target_bdf) == NULL) {
      continue;
    }

		/* Construir ruta al archivo 'config' del dispositivo BDF */
		snprintf(path, sizeof(path), "%s/%s/config", SYSFS_PCI_DEV, entry->d_name);

		fd = open(path, O_RDONLY);
		if (fd < 0) {
			tst_res(TWARN, "No se pudo abrir config para BDF %s", entry->d_name);
			continue;
		}

		/* Leer los primeros 4 bytes (Vendor ID [2B] y Device ID [2B]) */
		if (read(fd, &vendor_id, 2) == 2 && read(fd, &device_id, 2) == 2) {
			tst_res(TINFO, "BDF: %s -> VendorID: 0x%04x | DeviceID: 0x%04x",
				entry->d_name, vendor_id, device_id);
			count++;
		} else {
			tst_res(TWARN, "Error leyendo cabecera de config para %s", entry->d_name);
		}

		close(fd);
    break;
	}

	closedir(dir);

	if (count > 0) {
		tst_res(TPASS, "Se leyo correctamente el Espacio de Configuracion PCI de %d dispositivos", count);
	} else {
		tst_res(TFAIL, "No se pudo leer el Espacio de Configuracion de ningun dispositivo PCI");
	}
}

static struct tst_test test = {
	.test_all = run,
	//.needs_root = 1,
};