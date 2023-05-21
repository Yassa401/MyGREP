
#ifndef RECHERCHE_SANS_AFFICHE_H
#define RECHERCHE_SANS_AFFICHE_H

/*! Fonction qui récupère ligne par ligne d'un fichier donné
 * et cherche le(s) motif(s) dans chaque ligne
 * renvoie 1 si au moins une correspondance trouvée
 * sinon renvoie 0
 */
int recherche_fichier_sans_affiche(FILE * fichier, char ** motifs, int nb_motifs, int * compte_ligne, int * nb_lignes_totale, int existe_option_i) ;

/*! Fonction qui recupere fichier par fichier dans les arguments donnés
 * cherche le motif dans chacun des fichiers
 * et affiche le résultat de l'option -c
 * ne renvoie rien
 */
void recherche_fichiers_option_c(int argc , char **argv, char ** motifs, int nb_motifs, int indice_arg, char * liste_options) ;

/*! Fonction qui recupere fichier par fichier dans les arguments donnés
 * cherche le(s) motif(s) dans chacun des fichiers
 * et affiche le résultat de l'option -L
 * ne renvoie rien
 */
void recherche_fichiers_option_L(int argc, char ** argv, char ** motifs, int nb_motifs, int indice_arg, char * liste_options) ;

/*! Fonction qui recupere fichier par fichier dans les arguments donnés
 * cherche le(s) motif(s) dans chacun des fichiers
 * et affiche le résultat de l'option -l
 * ne renvoie rien
 */
void recherche_fichiers_option_l(int argc, char ** argv, char ** motifs, int nb_motifs, int indice_arg, char * liste_options) ;

#endif