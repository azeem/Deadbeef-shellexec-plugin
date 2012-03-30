OUT=shellexec.so
UIOUT=shellexecui.so

CC?=gcc
CFLAGS+=-g3 -O0 -Wall -fPIC -D_GNU_SOURCE ${INCLUDE}
LDFLAGS+=-shared 

SOURCES=shellexec.c
UISOURCES=interface.c shellexecui.c support.c

OBJECTS=$(SOURCES:.c=.o)
UIOBJECTS=$(UISOURCES:.c=.o)

$(UIOBJECTS):GTK_CFLAGS=`pkg-config --cflags gtk+-2.0`
GTK_LDFLAGS=`pkg-config --libs gtk+-2.0`

all: $(OUT) $(UIOUT) install

$(OUT): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(UIOUT): $(UIOBJECTS)
	$(CC) $(LDFLAGS) $(GTK_LDFLAGS) $(UIOBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $(GTK_CFLAGS) $< -c -o $@

install: $(OUT) $(UIOUT)
	cp $(OUT) ~/.local/lib/deadbeef/
	cp $(UIOUT) ~/.local/lib/deadbeef/

run: install
	deadbeef

clean:
	rm $(OBJECTS) $(OUT) $(UIOBJECTS) $(UIOUT)
