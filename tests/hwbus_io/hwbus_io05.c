// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * hwbus_io05.c - Concurrencia y Mapeo de Memoria
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

#define DEV_PATH "/dev/hwbusc"
#define STRESS_ITERATIONS 1000

static void verify_mmap_rejection(int fd)
{
  size_t page_size = (size_t)sysconf(_SC_PAGESIZE);

  TST_EXP_FAIL2(mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0),
                ENODEV,
                "mmap() sobre /dev/hwbusc denegado correctamente");
}

static void child_process_work(void)
{
  int local_fd;
  struct hwbus_bdf_info bdf;
  uint16_t vendor_id = 0;
  uint16_t device_id = 0;

  local_fd = SAFE_OPEN(DEV_PATH, O_RDONLY);
  verify_mmap_rejection(local_fd);

  for (int i = 0; i < STRESS_ITERATIONS; i++)
  {
    TST_EXP_PASS(ioctl(local_fd, HWBUS_IOC_GET_BDF, &bdf),
                 "ioctl(HWBUS_IOC_GET_BDF) ejecutado correctamente en iteracion %d", i);
    TST_EXP_PASS(ioctl(local_fd, HWBUS_IOC_READ_VENDOR, &vendor_id),
                 "ioctl(HWBUS_IOC_READ_VENDOR) ejecutado correctamente");
    TST_EXP_PASS(ioctl(local_fd, HWBUS_IOC_READ_DEVICE, &device_id),
                 "ioctl(HWBUS_IOC_READ_DEVICE) ejecutado correctamente");
  }
  SAFE_CLOSE(local_fd);
  exit(0);
}

static void setup(void)
{
  if (access(DEV_PATH, F_OK) != 0)
    tst_brk(TBROK, "El dispositivo %s no estaba preparado", DEV_PATH);
  if (access(DEV_PATH, R_OK) != 0)
    tst_brk(TBROK, "Permisos insuficientes sobre el dispositivo %s", DEV_PATH);
}

static void cleanup(void)
{
  if (fd >= 0)
    SAFE_CLOSE(fd);
}

static void run_test(void)
{
}

static struct tst_test test = {
    .setup = setup,
    .cleanup = cleanup,
    .test_all = run_test,
    //.forks = 3,
};