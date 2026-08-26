# SPDX-License-Identifier: GPL-2.0-or-later
# Copyright (C) 2026 Raúl Vílchez Ruiz <raulmicrosistemas@gmail.com>
#
# Makefile - Build instructions for hwbus-io
#
DRIVER_DIR ?= ../driver

obj-m += hwbus_io.o
hwbus_io-y := main.o hwbus_param.o hwbus_ioctl.o hwbus_file_ops.o $(DRIVER_DIR)/sysfs_driver.o

# obj-m += mi_modulo.o
# mi_modulo-y := hello.c otro.c otro_mas.c

# Cabeceras del proyecto
ccflags-y := -I$(src)/../../include