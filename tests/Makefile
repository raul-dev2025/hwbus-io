# SPDX-License-Identifier: GPL-2.0-or-later
# Copyright (C) 2026 Raúl Vílchez Ruiz <raulmicrosistemas@gmail.com>
#
# Makefile - Build instructions for hwbus-io
#

.PHONY: all test clean

# Subdirectorio activo configurado en el propio Makefile
SUBDIR ?= hwbus_io
TARGET ?= hwbus_io01

# Compila el test configurado
test:
	$(MAKE) -C $(SUBDIR) $(TARGET)

# Compila toda la bateria de tests
all:
	$(MAKE) -C $(SUBDIR) all

clean:
	$(MAKE) -C $(SUBDIR) clean