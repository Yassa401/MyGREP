
#ifndef UTILITAIRE_H
#define UTILITAIRE_H

void usage(int argc,char **argv) ;

void traitement_option(int argc ,char **argv, int * indice_arg, char * liste_options) ;

int existe_option(char * liste_options, char option) ;

#endif
