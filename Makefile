CC=gcc
CFLAGS=-Wall -Wextra -pedantic -ggdb
LIB_SOURCES = src/lib.c src/helper.c src/canvas.c src/objects/rectangle.c src/objects/square.c
all: terminal.ui libSoftView.wasm

terminal.ui: libSoftView.so UIs/terminal/main.c
	$(CC) $(CFLAGS) -o terminal.ui UIs/terminal/main.c -L. -lSoftView
	mv terminal.ui UIs/terminal/

libSoftView.so: $(LIB_SOURCES)
	$(CC) $(CFLAGS) -shared -o libSoftView.so -fPIC $^

libSoftView.wasm: $(LIB_SOURCES)
	emcc $^ -o libSoftView.html -sEXPORTED_FUNCTIONS=_SV_initialize_canvas,_SV_handle_command,_SV_update_required,_SV_get_canvas,_SV_get_width,_SV_get_height,_SV_delete_canvas -sEXPORTED_RUNTIME_METHODS=cwrap,wasmMemory -sMODULARIZE=1 -sEXPORT_ES6=1
	mv libSoftView.js UIs/wasm/
	mv libSoftView.wasm UIs/wasm/
	mv libSoftView.html UIs/wasm/

clean:
	rm -f libSoftView.so
	rm UIs/terminal/terminal.ui
	rm UIs/wasm/libSoftView.*
