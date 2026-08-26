// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * hwbus_file_ops.c - Operaciones POSIX sobre /dev/hwbusc (llseek, read, etc.)
 *
 * Copyright (C) 2026 Raúl Vílchez Ruiz <raulmicrosistemas@gmail.com>
 */
#include <hwbus-io.h>

loff_t hwbus_llseek(struct file *filp, loff_t off, int whence)
{
  return fixed_size_llseek(filp, off, whence, HWBUS_CFG_SIZE);
}

/* Futuras funciones adicionales como hwbus_trim(), etc. */
