/*
 * pci_bar_test.c
 * 
 * Test de inspeccion de regiones BAR (Base Address Registers) y MMIO/PIO.
 * Parte de la Fase 2 del proyecto foundry.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>
#include "tst_test.h"

#define SYSFS_PCI_DEV "/sys/bus/pci/devices"

/* Banderas del kernel para tipo de recursos PCI */
#define IORESOURCE_IO      0x00000100
#define IORESOURCE_MEM     0x00000200
#define IORESOURCE_PREFETCH 0x00002000
#define IORESOURCE_MEM_64  0x00000100  /* Dentro del sub-campo de MEM */

static void inspect_device_bars(const char *bdf)
{
	char path[1024];
	FILE *f;
	uint64_t start, end, flags;
	int bar_idx = 0;
	int valid_bars = 0;

	snprintf(path, sizeof(path), "%s/%s/resource", SYSFS_PCI_DEV, bdf);
	f = fopen(path, "r");
	if (!f) {
		tst_res(TWARN, "BDF: %s -> No se pudo abrir el archivo de recursos", bdf);
		return;
	}

	/* Parse de las lineas de 'resource': start end flags */
	while (fscanf(f, "%" SCNx64 " %" SCNx64 " %" SCNx64, &start, &end, &flags) == 3) {
		if (start != 0 || end != 0) {
			uint64_t size = end - start + 1;
			const char *type_str = "Desconocido";

			if (flags & IORESOURCE_IO) {
				type_str = "Port I/O";
			} else if (flags & IORESOURCE_MEM) {
				if (flags & IORESOURCE_PREFETCH)
					type_str = "MMIO (Prefetchable)";
				else
					type_str = "MMIO (Non-Prefetchable)";
			}

			tst_res(TINFO, "BDF: %s | BAR%d: [0x%" PRIx64 " - 0x%" PRIx64 "] | Tamano: %" PRIu64 " KB | Tipo: %s",
				bdf, bar_idx, start, end, size / 1024, type_str);
			valid_bars++;
		}
		bar_idx++;
		/* Nos centramos en las 6 regiones BAR estándar (0-5) */
		if (bar_idx >= 6)
			break;
	}

	fclose(f);

	if (valid_bars == 0) {
		tst_res(TINFO, "BDF: %s -> No tiene BARs asignadas/activas", bdf);
	}
}

static void run(void)
{
	DIR *dir;
	struct dirent *entry;
	int count = 0;

	dir = opendir(SYSFS_PCI_DEV);
	if (!dir) {
		tst_brk(TBROK | TERRNO, "No se pudo abrir el directorio %s", SYSFS_PCI_DEV);
	}

	tst_res(TINFO, "Analizando regiones BAR/MMIO en %s...", SYSFS_PCI_DEV);

	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_name[0] == '.')
			continue;

		inspect_device_bars(entry->d_name);
		count++;

		if (count >= 5)
			break;
	}

	closedir(dir);

	if (count > 0) {
		tst_res(TPASS, "Se inspeccionaron correctamente las regiones BAR de %d dispositivos", count);
	} else {
		tst_res(TFAIL, "No se encontraron dispositivos PCI para analizar BARs");
	}
}

static struct tst_test test = {
	.test_all = run,
};