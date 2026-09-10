// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * hwbus_io06.c - Reset IOCTL command
 *
 * Copyright (C) 2026 Raúl Vílchez Ruiz <raulmicrosistemas@gmail.com>
 */
#include <errno.h>     // Gestión de error devultos por mmap e ioctl
#include <fcntl.h>     // Definición de flags de apertura de archivos como O_RDWR
#include <stdint.h>    // Tipos de datos de ancho fijo para estructuras del driver
#include <stdio.h>     // Funciones estándar de entrada y salida para mensajes auxiliares
#include <stdlib.h>    // Utilidades generales del sistema y gestión de memoria
#include <string.h>    // Manipulación y formateo de cadenas de texto
#include <sys/ioctl.h> // Macros y funciones para invocación de comando ioctl
#include <sys/types.h> // Definiciones de tipos primitivos de sistema como off_t
#include <unistd.h>    // Invocación de llamadas al sistema posix como close()

#include "tst_test.h"           // Macroestructuras y API principal del framework de pruebas
#include <user/hwbus_io_uapi.h> // Cabecera uapi con cmds ioctl específicos del driver

#define DEV_PATH "/dev/hwbusc"

static int fd = -1;

static void setup(void)
{
  fd = SAFE_OPEN(DEV_PATH, O_RDWR);
}

static void cleanup(void)
{
  if (fd >= 0)
    SAFE_CLOSE(fd);
}

static void run_test(kvoid);
static struct tst_test test = {
    .setup = setup,
    .cleanup = cleanup,
    .test_all = run_test,
};