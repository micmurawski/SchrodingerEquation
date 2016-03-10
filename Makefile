CC=gcc
CFLAGS=-O2 -Wall -pedantic -std=c99
LFLAGS=-lm

OBJS = schrodinger.o main.o

all: program

program: $(OBJS)
		$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)

clean:
		rm -f *.o main

.PHONY: all clean
