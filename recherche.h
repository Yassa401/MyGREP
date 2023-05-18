#include "utilitaire.h"

#ifndef RECHERCHE_H
#define RECHERCHE_H

void affiche_n_lignes(FILE * fichier, char * nom_fichier, int n, int existe_option_h, int existe_option_n, int indice_ligne) ;

int chercher_motif(char * motif, char * ligne, int existe_option_i) ;

int chercher_motif_debut(char * motif, char * ligne, int existe_option_i) ;

int chercher_motif_fin(char * motif , char * ligne, int existe_option_i) ;

int chercher_motif_debut_fin(char * motif, char * ligne, int existe_option_i) ;

void recherche_fichier(char * nom_fichier , FILE * fichier, char ** motifs, int nb_motifs, char * liste_options, option_A_B * option_a_b) ;

void recherche_fichiers(int argc ,char **argv, char ** motifs, int nb_motifs, int indice_arg, char * liste_options, option_A_B * option_a_b) ;

#endif