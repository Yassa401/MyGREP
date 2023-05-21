CC=gcc
CFLAGS= -W -Wall -std=c90 -pedantic -O2

all : mygrep

mygrep : main.o recherche.o recherche_sans_affiche.o utilitaire.o 
	$(CC) $^ -o $@
main.o : main.c recherche.h utilitaire.h
	$(CC) -c $(CFLAGS) $<
recherche.o : recherche.c recherche.h utilitaire.h
	$(CC) -c $(CFLAGS) $<
recherche_sans_affiche.o : recherche_sans_affiche.c recherche_sans_affiche.h recherche.h
	$(CC) -c $(CFLAGS) $<
utilitaire.o : utilitaire.c utilitaire.h recherche_sans_affiche.h
	$(CC) -c $(CFLAGS) $<

%.o : macro.h

clean :
	rm -f *.o mygrep
