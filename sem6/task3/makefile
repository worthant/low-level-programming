CC=gcc
CFLAGS=-std=c17 -pedantic -Wall -Werror

all: main

main: main.o vector.o
	$(CC) $(CFLAGS) -o main main.o vector.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

vector.o: vector.c
	$(CC) $(CFLAGS) -c vector.c

clean:
	rm -f *.o main
