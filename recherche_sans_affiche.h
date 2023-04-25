
#ifndef RECHERCHE_SANS_AFFICHE_H
#define RECHERCHE_SANS_AFFICHE_H

int recherche_fichier_sans_affiche(FILE * fichier, char * motif, int * compte_ligne, int * nb_lignes_totale, int existe_option_i) ;

void recherche_fichiers_option_c(int argc , char **argv, char * motif, int indice_arg, char * liste_options) ;

void recherche_fichiers_option_L(int argc, char ** argv, char * motif, int indice_arg, char * liste_options) ;

void recherche_fichiers_option_l(int argc, char ** argv, char * motif, int indice_arg, char * liste_options) ;

#endif