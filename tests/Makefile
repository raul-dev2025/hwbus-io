# tests/Makefile
KDIR ?= /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

# Si se pasa un módulo específico (ej. MODULE=hello.ko), se compila solo ese.
# Si no se especifica ninguno, por defecto es hello.ko.
MODULE ?= hello.ko
obj-m := $(MODULE:.ko=.o)

.PHONY: all clean

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules







clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean