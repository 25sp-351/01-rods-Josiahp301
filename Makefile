all: rodcut

CC = gcc
CFLAGS = -Wall

rodcut: rodcut.o piece_values.o
	gcc -o rodcut $(CFLAGS) rodcut.o piece_values.o

rodcut.o: rodcut.c piece_values.h

clean:
	rm -f rodcut *.o
