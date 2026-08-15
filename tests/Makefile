# SPDX-License-Identifier: GPL-2.0-or-later
# Copyright (C) 2026 Raúl Vílchez Ruiz <raulmicrosistemas@gmail.com>
#
# Makefile - Build instructions for hwbus-io
#



.PHONY: test clean

# Subdirectorio activo configurado en el propio Makefile
SUBDIR ?= IO_tests
TARGET ?= mmap01

test:
	$(MAKE) -C $(SUBDIR) $(TARGET)

clean:
	$(MAKE) -C IO_tests clean