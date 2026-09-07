// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * hwbus_io_suite00r.c - Orquestador para la suit de pruebas HwBus_IO
 *
 * Copyright (C) 2026 Raúl Vílchez Ruiz <raulmicrosistemas@gmail.com>
 */
#include <errno.h>     // Gestión de código de error devueltos por mmap e ioctl
#include <fcntl.h>     // Definición de flags de apertura de archivos como O_RDWR
#include <libgen.h>    // Extracción y manipulación de nombres de rutas de archivos
#include <stdint.h>    // Tipos de datos de ancho fijo para estructuras del driver
#include <stdio.h>     // Funciones estándar de entrada y salida para mensajes auxiliares
#include <stdlib.h>    // Utilidades generales del sistema y gestión de memoria
#include <string.h>    // Manipulación y formateo de cadenas de texto
#include <sys/ioctl.h> // Macros y funciones para invocación de comandos ioctl
#include <sys/mman.h>  // Definición de mmap, PROT_READ, MAP_SHARED y MAP_FAILED
#include <sys/wait.h>
#include <sys/types.h> // Definiciones de tipos primitivos del sistema como off_t
#include <unistd.h>    // Invocación de llamadas al sistema posix como close

#include "tst_test.h"           // Macroestructuras y API principal del framework de pruebas LTP
#include "tst_module.h"         //Herramientas de LTP para gestión y control del módulo kernel
#include <user/hwbus_io_uapi.h> //Cabecera uapi con cmds IOCTL específicos del driver

#ifndef MODULE_DIR
#define MODULE_DIR "/mnt/build-output/Repos/hwbus-io.git/src/core"
#define TESTS_DIR "/mnt/build-output/Repos/hwbus-io.git/tests"
#endif

#define DEV_PATH "/dev/hwbusc"

static const char *subtests[] = {
    "./hwbus_io01",
    "./hwbus_io02",
    "./hwbus_io03",
    "./hwbus_io04r",
    "./hwbus_io05"};
#define NUM_SUBTESTS sizeof(subtests) / sizeof(subtests[0])

static int ensure_module_loaded(void)
{
  struct stat st;

  if (stat(DEV_PATH, &st) == 0) // la carga del modulo esta implicita!
    return 0;

  tst_res(TINFO, "El nodo %s no está presente. Intentando recargar el módulo kernel...",
          DEV_PATH);
  tst_module_load("hwbus_io", NULL);

  if (stat(DEV_PATH, &st) != 0)
  {
    tst_res(TWARN, "Fallo al verificar el nodo %s tras intentar recargar el módulo",
            DEV_PATH);
    return -1;
  }
  tst_res(TINFO, "Módulo e interfaz %s restaurados correctamente",
          DEV_PATH);
  return 0;
}

static void setup(void)
{
  if (chdir(TESTS_DIR) != 0)
  {
    tst_brk(TBROK | TERRNO, "No se pudo cambiar al directorio %s", TESTS_DIR);
    return;
  }

  if (ensure_module_loaded() != 0)
  {
    tst_brk(TBROK, "Infraestructura no disponible: el nodo %s o el módulo no están listos",
            DEV_PATH);
    return;
  }

  // Valida permisos y existencia de los tests
  for (size_t i = 0; i < NUM_SUBTESTS; i++)
  {
    if (access(subtests[i], X_OK) != 0)
    {
      tst_brk(TBROK | TERRNO, "No se encontro el test %s de tests o fueron inaccesibles",
              subtests[i]);
      return;
    }
  }

  tst_res(TINFO, "Entorno u  sub-tests verificados correctamente");
}

static void cleanup(void)
{
  int local_fd;

  if (ensure_module_loaded() != 0)
  {
    tst_res(TWARN, "Cleanup: No se pudo verificar/recargar el módulo kernel");
    return;
  }

  local_fd = open(DEV_PATH, O_RDWR);
  if (local_fd < 0)
  {
    tst_res(TWARN | TERRNO, "Cleanup: No se pudo abrir %s para resetear el dispositivo",
            DEV_PATH);
    return;
  }

  if (ioctl(local_fd, HWBUS_IOCRESET) < 0)
  {
    tst_res(TWARN | TERRNO, "Cleanup: Falló el comando IOCTL HWBUS_IOCRESET");
  }
  else
  {
    tst_res(TINFO, "Cleanup: Dispositivo restaurado con éxito mediante HWBUS_IOCRESET");
  }

  close(local_fd);
}

static void run_all_tests(void);
static int run_subtest(const char *subtest_path)
{
  pid_t pid;
  int status;

  tst_res(TINFO, "Ejecutando sub-test: %s", subtest_path);

}


static struct tst_test test = {
    .setup = setup,
    .cleanup = cleanup,
    .test_all = run_all_tests,
};