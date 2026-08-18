LTP_SRC ?= /home/builder/Repos/ltp

CFLAGS += -Wall -I../include -I$(LTP_SRC)/include -I$(LTP_SRC)/include/old
LDFLAGS += -L$(LTP_SRC)/lib
LDLIBS += -lltp

.PHONY: all clean

all: pci_config01 pci_msi01 pci_bar01

pci_config01: pci_config_test.c
	$(CC) $(CFLAGS) $(LDFLAGS) $< $(LDLIBS) -o $@

pci_config02: pci_config_single.c
	$(CC) $(CFLAGS) $(LDFLAGS) $< $(LDLIBS) -o $@

pci_msi01: pci_msi_test.c
	$(CC) $(CFLAGS) $(LDFLAGS) $< $(LDLIBS) -o $@

pci_bar01: pci_bar_test.c
	$(CC) $(CFLAGS) $(LDFLAGS) $< $(LDLIBS) -o $@

pci_config03: pci_single_conf.c
	$(CC) $(CFLAGS) $(LDFLAGS) $< $(LDLIBS) -o $@

clean:
	rm -f pci_config01 pci_config02 pci_config03 pci_msi01 pci_bar01 *.o