# SPDX-License-Identifier: GPL-2.0-or-later
# Copyright (C) 2026 Raúl Vílchez Ruiz <raulmicrosistemas@gmail.com>
#
# Makefile - Makefile dedicado a la pruebas própias del controlador.
#
LTP_SRC ?= /home/builder/Repos/ltp

CFLAGS += -Wall -I../include -I$(LTP_SRC)/include -I$(LTP_SRC)/include/old
LDFLAGS += -L$(LTP_SRC)/lib
LDLIBS += -lltp

# Detecta todas las fuentes y  permite invocar objetos individuales
SRCS := $(wildcard hwbus_io*.c)
TARGETS := $(SRCS:.c=)

.PHONY: all clean

# Compila todo con 'make' o 'make all'
all: $(TARGETS)

# regla implicita para compilar individualmente
%: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) $< $(LDLIBS) -o $@



clean:
	rm -f $(TARGETS)