
#ifndef UTILITAIRE_H
#define UTILITAIRE_H

void usage(int argc,char **argv, char * liste_options) ;

void print_help() ;

char * traitement_option(int argc ,char **argv, char ***motifs, int * nb_motif,  int * indice_arg) ;

int existe_option(char * liste_options, char option) ;

#endif
