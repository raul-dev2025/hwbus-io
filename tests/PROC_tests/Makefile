LTP_SRC ?= /home/builder/Repos/ltp

CFLAGS += -Wall -I../include -I$(LTP_SRC)/include -I$(LTP_SRC)/include/old
LDFLAGS += -L$(LTP_SRC)/lib
LDLIBS += -lltp

.PHONY: all clean

all: sysconf01 fork01

sysconf01: sysconf_test.c
	$(CC) $(CFLAGS) $(LDFLAGS) $< $(LDLIBS) -o $@

fork01: fork_test.c
	$(CC) $(CFLAGS) $(LDFLAGS) $< $(LDLIBS) -o $@

clean: 
	rm -f sysconf01 fork01 *.o