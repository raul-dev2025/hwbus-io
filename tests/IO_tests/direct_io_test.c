// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * direct_io_test.c - Test de E/S Directa (O_DIRECT) omitiendo la Page Cache del Kernel.
 *
 * Copyright (C) 2026 Raúl Vílchez Ruiz <raulmicrosistemas@gmail.com>
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "tst_test.h"

#define ALIGNMENT 4096
#define BUFFER_SIZE 4096
#define TEST_FILE "test_direct_io.tmp"

static char *wbuf;
static char *rbuf;
static int fd = -1;

static void setup(void)
{
  /* 1. Reserva de memoria alineada obligatoria para O_DIRECT */
  if (posix_memalign((void **)&wbuf, ALIGNMENT, BUFFER_SIZE) != 0)
  {
    tst_brk(TBROK | TERRNO, "Error reservando buffer de escritura alineado");
  }

  if (posix_memalign((void **)&rbuf, ALIGNMENT, BUFFER_SIZE) != 0)
  {
    free(wbuf);
    tst_brk(TBROK | TERRNO, "Error reservando buffer de lectura alineado");
  }

  /* Inicializar buffers con patron de prueba */
  memset(wbuf, 'X', BUFFER_SIZE);
  memset(rbuf, 0, BUFFER_SIZE);

  /* 2. Apertura con control de compatibilidad para O_DIRECT */
  fd = open(TEST_FILE, O_RDWR | O_CREAT | O_TRUNC | O_DIRECT, 0644);
  if (fd < 0)
  {
    if (errno == EINVAL || errno == EOPNOTSUPP)
    {
      tst_brk(TCONF | TERRNO, "El sistema de archivos no soporta O_DIRECT");
    }
    else
    {
      tst_brk(TBROK | TERRNO, "open() con O_DIRECT fallo inesperadamente");
    }
  }
}

static void cleanup(void)
{
  if (fd >= 0)
    close(fd);

  if (wbuf)
    free(wbuf);

  if (rbuf)
    free(rbuf);
}

static void run(void)
{
  ssize_t ret;

  tst_res(TINFO, "Probando escritura directa (O_DIRECT) de %d bytes...", BUFFER_SIZE);

  /* 1. Escritura directa en disco */
  ret = write(fd, wbuf, BUFFER_SIZE);
  if (ret != BUFFER_SIZE)
  {
    tst_res(TFAIL | TERRNO, "write() O_DIRECT fallo (ret = %zd)", ret);
    return;
  }

  /* 2. Rebobinar cursor */
  if (lseek(fd, 0, SEEK_SET) == (off_t)-1)
  {
    tst_brk(TBROK | TERRNO, "lseek() fallo al posicionar el offset");
    return;
  }

  tst_res(TINFO, "Probando lectura directa (O_DIRECT)...");

  /* 3. Lectura directa desde disco */
  ret = read(fd, rbuf, BUFFER_SIZE);
  if (ret != BUFFER_SIZE)
  {
    tst_res(TFAIL | TERRNO, "read() O_DIRECT fallo (ret = %zd)", ret);
    return;
  }

  /* 4. Verificación de integridad de los datos */
  if (memcmp(wbuf, rbuf, BUFFER_SIZE) == 0)
  {
    tst_res(TPASS, "Escritura y lectura O_DIRECT exitosas con datos coherentes");
  }
  else
  {
    tst_res(TFAIL, "Los datos leidos mediante O_DIRECT no coinciden con los escritos");
  }
}

static struct tst_test test = {
    .needs_tmpdir = 1,
    .setup = setup,
    .cleanup = cleanup,
    .test_all = run,
};