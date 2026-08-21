// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * hwbus_io01.c - Verificación de Presencia y Registro
 *
 * Copyright (C) 2026 Raúl Vílchez Ruiz <raulmicrosistemas@gmail.com>
 *
 * Verifies:
 * 1. Existence and character device properties of /dev/hwbusc.
 * 2. Major number registration (240) in /proc/devices.
 * 3. SysFS class hierarchy under /sys/class/hwbusc/hwbusc/.
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include "tst_test.h"

#define DEV_PATH "/dev/hwbusc"
#define PROC_DEV_PATH "/proc/devices"
#define SYSFS_CLASS "/sys/class/hwbusc/hwbusc/dev"
#define EXPECTED_MAJOR 240

static void test_node_presence(void)
{
  struct stat st;

  if (stat(DEV_PATH, &st) != 0)
  {
    tst_res(TFAIL | TERRNO, "Device node %s does not exist", DEV_PATH);
    return;
  }

  if (!S_ISCHR(st.st_mode))
  {
    tst_res(TFAIL, "%s is not a character device", DEV_PATH);
    return;
  }
  tst_res(TPASS, "Device node %s exists and is a character device", DEV_PATH);
}

static void test_proc_devices(void)
{
  FILE *fp;
  char line[256];
  int found = 0;
  int major;
  char name[64];

  fp = fopen(PROC_DEV_PATH, "r");
  if (!fp)
  {
    tst_brk(TBROK | TERRNO, "Failed to open %s", PROC_DEV_PATH);
    return;
  }
  while (fgets(line, sizeof(line), fp))
  {
    if (sscanf(line, "%d %63s", &major, name) == 2)
    {
      if (major == EXPECTED_MAJOR && strcmp(name, "hwbusc") == 0)
      {
        found = 1;
        break;
      }
    }
  }
  fclose(fp);
  if (found)
  {
    tst_res(TPASS, "Major %d (hwbusc) registered in %s", EXPECTED_MAJOR, PROC_DEV_PATH);
  }
  else
  {
    tst_res(TFAIL | TERRNO, "Major %d (hwbusc) NOT found in %s", EXPECTED_MAJOR, PROC_DEV_PATH);
  }
}

static void test_sysfs_class(void)
{
  if (access(SYSFS_CLASS, F_OK) == 0)
  {
    tst_res(TPASS, "SysFS class node %s is present", SYSFS_CLASS);
  }
  else
  {
    tst_res(TFAIL | TERRNO, "SysFS class node %s missing", SYSFS_CLASS);
  }
}

static void run_tests(void)
{
  test_node_presence();
  test_proc_devices();
  test_sysfs_class();
}

static struct tst_test test = {
    .test_all = run_tests,
};