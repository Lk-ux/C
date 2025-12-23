CC = gcc
CFLAGS = -g -Wall -c

all: main

main: main.o list.o
	$(CC) main.o list.o -o main

main.o: main.c list.h
	$(CC) $(CFLAGS) main.c

list.o: list.c list.h
	$(CC) $(CFLAGS) list.c

clean:
	rm -f *.o main

