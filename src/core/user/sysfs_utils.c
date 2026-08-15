// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * sysfs_utils.c - Descripción del módulo/archivo
 *
 * Copyright (C) 2026 Raúl Vílchez Ruiz <raulmicrosistemas@gmail.com>
 */

#include "sysfs_utils.h"
#include "hwbus_error.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int sysfs_build_path(char *dest, size_t max_len, const char *subsys, const char *dev_id, const char *attr)
{
  if (!dest || !subsys || !dev_id || !attr)
  {
    return -EINVAL;
  }
  int len = snprintf(dest, max_len, "/sys/bus/%s/devices/%s/%s", subsys, dev_id, attr);
  if (len < 0 || (size_t)len >= max_len)
  {
    return -HWBUS_ERR_PATH_TOO_LONG;
  }

  return HWBUS_SUCCESS;
}

int sysfs_read_uint(const char *path, unsigned int *val)
{
  if (!path || !val)
  {
    return -EINVAL;
  }
  FILE *f = fopen(path, "r");
  if (!f)
  {
    return -errno;
  }

  if (fscanf(f, "%i", val) != 1)
  {
    fclose(f);
    return -EIO;
  }

  fclose(f);
  return HWBUS_SUCCESS;
}

int sysfs_read_string(const char *path, char *buf, size_t size)
{
  if (!path || !buf || size == 0)
  {
    return -EINVAL;
  }

  FILE *f = fopen(path, "r");
  if (!f)
  {
    return -errno;
  }

  if (!fgets(buf, (int)size, f))
  {
    fclose(f);
    return -EIO;
  }

  fclose(f);

  /*Elimina salto de line si lo hay*/
  size_t len = strlen(buf);
  if (len > 0 && buf[len - 1] == '\n')
  {
    buf[len - 1] = '\0';
  }

  return HWBUS_SUCCESS;
}

int sysfs_read_binary(const char *path, off_t offset, void *buf, size_t count)
{
  if (!path || !buf || count == 0)
  {
    return -EINVAL;
  }

  int fd = open(path, O_RDONLY);
  if (fd < 0)
  {
    return -errno;
  }
  ssize_t bytes_read = pread(fd, buf, count, offset);
  close(fd);

  if (bytes_read < 0)
  {
    return -errno;
  }

  if ((size_t)bytes_read != count)
  {
    return -EIO;
  }
  return HWBUS_SUCCESS;
}