// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * hwbus_io03.c - Auditoría y Rechazo de Operaciones POSIX Tradicionales (lseek, read, write)
 *
 * Copyright (C) 2026 Raúl Vílchez Ruiz <raulmicrosistemas@gmail.com>
 */
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "tst_test.h"
#include <user/hwbus_io_uapi.h>

#define DEV_PATH "/dev/hwbusc"

static int fd = -1;

static void test_reject_lseek(void)
{
  off_t ret;

  ret = lseek(fd, 0, SEEK_SET);

  if (ret == (off_t)-1 && (errno == ESPIPE || errno == EINVAL))
  {
    tst_res(TPASS, "lseek() rechazado correctamente con errno=%d (%s)",
            errno, strerror(errno));
  }
  else
  {
    tst_res(TFAIL | TERRNO,
            "lseek() no fue rechazado como se esperaba (ret=%ld)",
            (long)ret);
  }
}

static void test_reject_read(void)
{
}

static void test_reject_write(void)
{
}

static void setup(void)
{
  fd = SAFE_OPEN(DEV_PATH, O_RDWR);
}

static void cleanup(void)
{
  if (fd >= 0)
    SAFE_CLOSE(fd);
}

static void run_tests(void)
{
  test_reject_lseek();
  test_reject_read();
  test_reject_write();
}

static struct tst_test test = {
    .setup = setup,
    .cleanup = cleanup,
    .test_all = run_tests,
};