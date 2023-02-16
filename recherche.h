
#ifndef RECHERCHE_H
#define RECHERCHE_H

int chercher_motif(char * motif, char * ligne) ;
void recherche_fichier(char * nom_fichier , FILE * fichier, char * motif) ;
void recherche_fichiers(int argc , char **argv, char * motif) ;

#endif