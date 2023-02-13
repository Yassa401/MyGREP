CC=gcc
CFLAGS= -W -Wall -std=c90 -pedantic -c -O2
LFLAGS=

all : mygrep

mygrep : main.o 
	$(CC) $^ -o $@
main.o : main.c
	$(CC) $(CFLAGS) $<

clean :
	rm -f *.o mygrep
