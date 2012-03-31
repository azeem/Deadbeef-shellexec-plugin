OUT=shellexec.so
UIOUT=shellexecui.so

CC?=gcc
CFLAGS+=-Wall -fPIC -D_GNU_SOURCE ${INCLUDE}
LDFLAGS+=-shared 
debug: CFLAGS +=-g3 -O0 -DDEBUG
SOURCES=shellexec.c
UISOURCES=interface.c shellexecui.c support.c

OBJECTS=$(SOURCES:.c=.o)
UIOBJECTS=$(UISOURCES:.c=.o)

$(UIOBJECTS):GTK_CFLAGS=`pkg-config --cflags gtk+-2.0`
GTK_LDFLAGS=`pkg-config --libs gtk+-2.0`

all: $(OUT) $(UIOUT)

debug: $(OUT) $(UIOUT)

$(OUT): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(UIOUT): $(UIOBJECTS)
	$(CC) $(LDFLAGS) $(GTK_LDFLAGS) $(UIOBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $(GTK_CFLAGS) $< -c -o $@

install: $(OUT) $(UIOUT)
	mkdir -p $(HOME)/.local/lib/deadbeef/
	cp $(OUT) $(HOME)/.local/lib/deadbeef/
	cp $(UIOUT) $(HOME)/.local/lib/deadbeef/

uninstall:
	rm $(HOME)/.local/lib/deadbeef/$(OUT)
	rm $(HOME)/.local/lib/deadbeef/$(UIOUT)

run: install
	deadbeef

clean:
	rm $(OBJECTS) $(OUT) $(UIOBJECTS) $(UIOUT)
