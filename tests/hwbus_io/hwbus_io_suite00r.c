// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * hwbus_io_suite00r.c - Orquestador para la suit de pruebas HwBus_IO
 *
 * Copyright (C) 2026 Raúl Vílchez Ruiz <raulmicrosistemas@gmail.com>
 */
#include <errno.h>     // Gestión de código de error devueltos por mmap e ioctl
#include <fcntl.h>     // Definición de flags de apertura de archivos como O_RDWR
#include <stdint.h>    // Tipos de datos de ancho fijo para estructuras del driver
#include <stdio.h>     // Funciones estándar de entrada y salida para mensajes auxiliares
#include <stdlib.h>    // Utilidades generales del sistema y gestión de memoria
#include <string.h>    // Manipulación y formateo de cadenas de texto
#include <sys/ioctl.h> // Macros y funciones para invocación de comandos ioctl
#include <sys/mman.h>  // Definición de mmap, PROT_READ, MAP_SHARED y MAP_FAILED
#include <sys/types.h> // Definiciones de tipos primitivos del sistema como off_t
#include <unistd.h>    // Invocación de llamadas al sistema posix como close
#include <libgen.h>    // Extracción y manipulación de nombres de rutas de archivos

#include "tst_test.h"           // Macroestructuras y API principal del framework de pruebas LTP
#include "tst_module.h"         //Herramientas de LTP para gestión y control del módulo kernel
#include <user/hwbus_io_uapi.h> //Cabecera uapi con cmds IOCTL específicos del driver

#ifndef MODULE_DIR
#define MODULE_DIR "/mnt/build-output/Repos/hwbus-io.git/src/core"
#define TESTS_DIR "/mnt/build-output/Repos/hwbus-io.git/tests"
#endif

#define DEV_PATH "/dev/hwbusc"
