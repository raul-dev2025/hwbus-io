# SPDX-License-Identifier: GPL-2.0-or-later
# Copyright (C) 2026 Raúl Vílchez Ruiz <raulmicrosistemas@gmail.com>
#
# Makefile - Build instructions for hwbus-io
#
SUBDIRS := hwbus_io IO_tests BUS_tests PROC_tests

# Subdirectorio activo configurado en el propio Makefile
SUBDIR ?= hwbus_io
TARGET ?= hwbus_io04r

.PHONY: all test clean $(SUBDIRS)

# Compila el test configurado
test:
	$(MAKE) -C $(SUBDIR) $(TARGET)

# Compila toda la bateria de tests
all:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir all; \
	done

clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done