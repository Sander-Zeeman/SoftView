CC = clang
CFLAGS = -Wall -Wextra -Wswitch-enum

all: SoftView.term SoftView.wasm

SoftView.o: SoftView.c
	$(CC) $(CFLAGS) -c SoftView.c 

SoftView.term: SoftView.o
	$(CC) $(CFLAGS) -o SoftView.term main.c SoftView.o

SoftView.wasm: SoftView.c
	$(CC) $(CFLAGS) -DWASM -Os --target=wasm32 --no-standard-libraries -Wl,--no-entry -Wl,--allow-undefined -o SoftView.wasm SoftView.c

clean:
	rm -f SoftView.o
	rm -f SoftView.term
	rm -f SoftView.wasm
