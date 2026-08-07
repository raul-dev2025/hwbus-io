.PHONY: all tests clean

# Directorios de trabajo
PWD := $(shell pwd)
KDIR ?= /lib/modules/$(shell uname -r)/build

# Regla principal (compilación de módulos/fuentes del proyecto)
all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

# Delegación de pruebas al Makefile del subdirectorio tests/
tests:
	$(MAKE) -C tests

# Limpieza general
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	$(MAKE) -C tests clean