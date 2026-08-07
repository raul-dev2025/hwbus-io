LTP_SRC ?= /home/builder/Repos/ltp

CFLAGS += -Wall -I../include -I$(LTP_SRC)/include -I$(LTP_SRC)/include/old
LDFLAGS += -L$(LTP_SRC)/lib
LDLIBS += -lltp

# Objetivos a generar
TARGETS := hello

.PHONY: all clean

all: $(TARGETS)

hello: hello.c
	$(CC) $(CFLAGS) $< $(LDFLAGS) $(LDLIBS) -o $@




clean:
	rm -f $(TARGETS) *.o