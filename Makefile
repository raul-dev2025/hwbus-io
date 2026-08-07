.PHONY: hello clean

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

hello:	
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/tests modules

io-test:
	$(MAKE) -C IO_tests

bus-test:
	$(MAKE) -C BUS_tests

proc-test:
	$(MAKE) -C PROC_tests

pci-dw:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)/pci_dw modules





clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	make -C IO_tests clean
	make -C BUS_tests clean
	make -C PROC_tests clean
	make -C hello clean
	$(MAKE) -C BUS_tests clean
	