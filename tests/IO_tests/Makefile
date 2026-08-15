# SPDX-License-Identifier: GPL-2.0-or-later
# Copyright (C) 2026 Raúl Vílchez Ruiz <raulmicrosistemas@gmail.com>
#
# Makefile - Build instructions for hwbus-io
#
LTP_SRC ?= /home/builder/Repos/ltp

CFLAGS  += -Wall -I../include -I$(LTP_SRC)/include -I$(LTP_SRC)/include/old
LDFLAGS += -L$(LTP_SRC)/lib
LDLIBS  += -lltp

.PHONY: clean mmap01 direct_io01

# Switch on/off when needed, but then turn off specific tests
# all: mmap01 direct_io01

# Reglas explícitas individuales (sin target 'all')
mmap01: mmap01.c
	$(CC) $(CFLAGS) $(LDFLAGS) $< $(LDLIBS) -o $@

direct_io01: direct_io_test.c
	$(CC) $(CFLAGS) $(LDFLAGS) $< $(LDLIBS) -o $@

clean:
	rm -f mmap01 direct_io01 *.o