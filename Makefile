CC=gcc
CFLAGS=-Wall -Wextra -pedantic -ggdb
LIB_SOURCES = src/lib.c src/helper.c src/canvas.c src/objects/rectangle.c src/objects/square.c
all: terminal.ui

terminal.ui: libSoftView.so UIs/terminal/main.c
	$(CC) $(CFLAGS) -o terminal.ui UIs/terminal/main.c -L. -lSoftView

libSoftView.so: $(LIB_SOURCES)
	$(CC) $(CFLAGS) -shared -o libSoftView.so -fPIC $^

clean:
	rm -f libSoftView.so && rm -f *.ui
