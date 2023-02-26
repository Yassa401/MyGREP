CC=gcc
CFLAGS= -W -Wall -std=c90 -pedantic -O2
LFLAGS=

all : mygrep

mygrep : main.o recherche.o utilitaire.o 
	$(CC) $^ -o $@
main.o : main.c recherche.h utilitaire.h
	$(CC) -c $(CFLAGS) $<
recherche.o : recherche.c recherche.h
	$(CC) -c $(CFLAGS) $<
utilitaire.o : utilitaire.c utilitaire.h
	$(CC) -c $(CFLAGS) $<

%.o : macro.h

clean :
	rm -f *.o mygrep
