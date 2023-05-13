
#ifndef RECHERCHE_H
#define RECHERCHE_H

int chercher_motif(char * motif, char * ligne, int existe_option_i) ;

int chercher_motif_debut(char * motif, char * ligne, int existe_option_i) ;

int chercher_motif_fin(char * motif , char * ligne, int existe_option_i) ;

int chercher_motif_debut_fin(char * motif, char * ligne, int existe_option_i) ;

void recherche_fichier(char * nom_fichier , FILE * fichier, char ** motifs, int nb_motifs, char * liste_options) ;

void recherche_fichiers(int argc ,char **argv, char ** motifs, int nb_motifs, int indice_arg, char * liste_options) ;

void recherche_fichier_option_v(char * nom_fichier ,FILE * fichier, char * motif) ;

void recherche_fichiers_option_v(int argc ,char **argv, int indice_arg) ;

#endif