
#ifndef RECHERCHE_H
#define RECHERCHE_H

int chercher_motif(char * motif, char * ligne) ;

int chercher_motif_debut(char * motif, char * ligne) ;

int chercher_motif_fin(char * motif , char * ligne) ;

int chercher_motif_debut_fin(char * motif, char * ligne) ;

void recherche_fichier(char * nom_fichier , FILE * fichier, char * motif) ;

void recherche_fichiers(int argc ,char **argv, char * motif, int indice_arg) ;

void recherche_fichier_option_v(char * nom_fichier ,FILE * fichier, char * motif) ;

void recherche_fichiers_option_v(int argc ,char **argv, int indice_arg) ;

void recherche_fichier_option_affichage(char * nom_fichier,FILE * fichier, char * liste_options, char * motif) ;

void recherche_fichiers_option_affichage(int argc, char ** argv, char * liste_options, int indice_arg) ;


#endif