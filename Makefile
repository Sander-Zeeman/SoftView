CC = clang
CFLAGS = -Wall -Wextra -Wswitch-enum

all: SoftView.term SoftView.wasm

SoftView.o: lib/SoftView.c
	$(CC) $(CFLAGS) -c lib/SoftView.c 

SoftView.term: SoftView.o
	$(CC) $(CFLAGS) -o SoftView.term src/main.c SoftView.o

SoftView.wasm: lib/SoftView.c
	$(CC) $(CFLAGS) -DWASM -Os --target=wasm32 --no-standard-libraries -Wl,--no-entry -Wl,--allow-undefined -o SoftView.wasm lib/SoftView.c

clean:
	rm -f SoftView.o
	rm -f SoftView.term
	rm -f SoftView.wasm
