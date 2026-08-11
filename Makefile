.PHONY: module test clean

PWD  := $(shell pwd)
KDIR ?= /lib/modules/$(shell uname -r)/build

# Subdirectorio de módulo activo (configurado en el propio Makefile)
MODULE_DIR ?= src/core

# Compilación explícita del módulo
module:
	$(MAKE) -C $(KDIR) M=$(PWD)/$(MODULE_DIR) modules

# Compilación explícita de pruebas delegando en la jerarquía tests/
test:
	$(MAKE) -C tests test

# Limpieza global sin fallar si un directorio no existe o está limpio
clean:
	$(MAKE) -C $(KDIR) M=$(PWD)/src/core clean 2>/dev/null || true
	$(MAKE) -C $(KDIR) M=$(PWD)/src/driver clean 2>/dev/null || true
	$(MAKE) -C tests clean 2>/dev/null || true