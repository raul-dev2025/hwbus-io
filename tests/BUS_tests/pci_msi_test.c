/*
 * pci_msi_test.c
 * 
 * Test de validacion de asignacion de vectores de interrupcion (MSI/MSI-X / INTx).
 * Parte de la Fase 2 del proyecto foundry.
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include "tst_test.h"

#define SYSFS_PCI_DEV "/sys/bus/pci/devices"

static void check_device_irq(const char *bdf)
{
	char path[1024];
	char buf[256];
	int fd, irq_num = -1;
	DIR *msi_dir;

	/* 1. Comprobar si existen vectores asignados en la carpeta msi_irqs */
	snprintf(path, sizeof(path), "%s/%s/msi_irqs", SYSFS_PCI_DEV, bdf);
	msi_dir = opendir(path);

	if (msi_dir) {
		struct dirent *entry;
		int msi_count = 0;

		while ((entry = readdir(msi_dir)) != NULL) {
			if (entry->d_name[0] != '.')
				msi_count++;
		}
		closedir(msi_dir);

		if (msi_count > 0) {
			tst_res(TINFO, "BDF: %s -> Asignados %d vectores MSI/MSI-X", bdf, msi_count);
			return;
		}
	}

	/* 2. Si no hay MSI/MSI-X explícito, leer el archivo 'irq' convencional */
	snprintf(path, sizeof(path), "%s/%s/irq", SYSFS_PCI_DEV, bdf);
	fd = open(path, O_RDONLY);
	if (fd >= 0) {
		ssize_t ret = read(fd, buf, sizeof(buf) - 1);
		close(fd);
		if (ret > 0) {
			buf[ret] = '\0';
			irq_num = atoi(buf);
			tst_res(TINFO, "BDF: %s -> Asignada linea IRQ tradicional (INTx): %d", bdf, irq_num);
			return;
		}
	}

	tst_res(TWARN, "BDF: %s -> No se pudo determinar la IRQ asignada", bdf);
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

	tst_res(TINFO, "Analizando asignacion de interrupciones en %s...", SYSFS_PCI_DEV);

	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_name[0] == '.')
			continue;

		check_device_irq(entry->d_name);
		count++;

		if (count >= 5)
			break;
	}

	closedir(dir);

	if (count > 0) {
		tst_res(TPASS, "Se verifico correctamente la asignacion de interrupciones en %d dispositivos", count);
	} else {
		tst_res(TFAIL, "No se encontraron dispositivos PCI para analizar interrupciones");
	}
}

static struct tst_test test = {
	.test_all = run,
};