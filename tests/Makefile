.PHONY: test clean

# Subdirectorio activo configurado en el propio Makefile
SUBDIR ?= IO_tests
TARGET ?= mmap01

test:
	$(MAKE) -C $(SUBDIR) $(TARGET)

clean:
	$(MAKE) -C IO_tests clean