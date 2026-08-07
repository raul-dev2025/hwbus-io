LTP_SRC ?= /home/builder/Repos/ltp

CFLAGS += -Wall -I../include -I$(LTP_SRC)/include -I$(LTP_SRC)/include/old
LDFLAGS += -L$(LTP_SRC)/lib
LDLIBS += -lltp

.PHONY: all clean

all: hello

hello: hello.c
	$(CC) $(CFLAGS) $(LDFLAGS) $< $(LDLIBS) -o $@


clean:
	rm -f hello *.o