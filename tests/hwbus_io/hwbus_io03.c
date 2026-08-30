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
}

static struct tst_test test = {
};