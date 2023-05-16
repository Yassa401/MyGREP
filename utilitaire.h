
#ifndef UTILITAIRE_H
#define UTILITAIRE_H

typedef struct {
    int existe_option_A , existe_option_B ; /* si l'option A ou B existe on met la valeur à 1*/
    int n_A , n_B ; /* on stocke le nombre de lignes qui va avec les options dans les variables n_A et n_B */
} option_A_B ;

void usage(int argc,char **argv, char * liste_options) ;

void print_help() ;

char * traitement_option(int argc ,char **argv, char ***motifs, int * nb_motif,  int * indice_arg, option_A_B * option_a_b) ;

int existe_option(char * liste_options, char option) ;

#endif
