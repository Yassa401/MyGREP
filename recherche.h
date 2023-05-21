#include "utilitaire.h"

#ifndef RECHERCHE_H
#define RECHERCHE_H


/*! Fonction qui affiche les n lignes après la correspondance
 * ne renvoie rien
 */
void affiche_n_lignes(FILE * fichier, char * nom_fichier, int n, int existe_option_h, int existe_option_n, int indice_ligne) ;

/*! Fonction qui affiche les n lignes avant la correspondance
 * ne renvoie rien 
 */
void affiche_n_lignes_avant(FILE * fichier, char * nom_fichier, int n, int existe_option_h, int existe_option_n, int indice_ligne) ;

/*! Fonction qui parcourt la ligne en recherche du motif
 * renvoie 1 si le motif se trouve dans la ligne
 * renvoie 0 sinon
 */
int chercher_motif(char * motif, char * ligne, int existe_option_i) ;

/*! Fonction qui cherche le motif au debut de la ligne
 * si c'est le cas on renvoie 1
 * sinon 0
 */
int chercher_motif_debut(char * motif, char * ligne, int existe_option_i) ;

/*! Fonction qui cherche le motif à la fin de la ligne
 * si c'est le cas on renvoie 1
 * sinon 0
 */
int chercher_motif_fin(char * motif , char * ligne, int existe_option_i) ;

/*! Fonction qui verifie si le motif correspond à la ligne récupéré 
 * si c'est le cas on renvoie 1
 * sinon 0
 */
int chercher_motif_debut_fin(char * motif, char * ligne, int existe_option_i) ;

/*! Fonction qui récupère ligne par ligne d'un fichier donné
 * et cherche le(s) motif(s) dans chaque ligne en affichant un résultat selon les options d'affichage
 * ne renvoie rien
 */
void recherche_fichier(char * nom_fichier , FILE * fichier, char ** motifs, int nb_motifs, char * liste_options, option_A_B * option_a_b) ;

/*! Fonction qui recupere fichier par fichier dans les arguments donnés
 * et cherche le(s) motif(s) dans chacun des fichiers
 * ne renvoie rien
 */
void recherche_fichiers(int argc ,char **argv, char ** motifs, int nb_motifs, int indice_arg, char * liste_options, option_A_B * option_a_b) ;

#endif