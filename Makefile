CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pedantic -ggdb

all: SoftView

SoftView: main.o
	$(CC) main.o -o SoftView

main.o: main.c
	$(CC) $(CFLAGS) main.c -c -o main.o

clean:
	rm main.o
	rm SoftView
