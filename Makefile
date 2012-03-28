OUT=shellexec.so
CC?=gcc
CFLAGS+=-g -O0 -Wall -fPIC -D_GNU_SOURCE ${INCLUDE} `pkg-config --cflags gtk+-2.0`
LDFLAGS+=-shared `pkg-config --libs gtk+-2.0`

SOURCES=shellexec.c

OBJECTS=$(SOURCES:.c=.o)

all: $(SOURCES) $(OUT)

$(OUT): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -c -o $@

install: $(OUT)
	cp $(OUT) ~/.local/lib/deadbeef/

run: install
	deadbeef

clean:
	rm $(OBJECTS) $(OUT)
