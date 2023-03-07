
#ifndef RECHERCHE_SANS_AFFICHE_H
#define RECHERCHE_SANS_AFFICHE_H

int recherche_fichier_sans_affiche(FILE * fichier, char * motif, int * compte_ligne, int * nb_lignes_totale) ;

void recherche_fichiers_option_c(int argc ,char **argv, int indice_arg, char * liste_options) ;

#endif