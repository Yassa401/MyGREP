
#ifndef UTILITAIRE_H
#define UTILITAIRE_H

typedef struct {
    int existe_option_A , existe_option_B ; /* si l'option A ou B existe on met la valeur à 1*/
    int n_A , n_B ; /* on stocke le nombre de lignes qui va avec les options dans les variables n_A et n_B */
} option_A_B ;

/*! Fonction qui affiche un première aide si l'entrée en ligne de commande n'est pas bonne
 * ne renvoie rien
 */
void usage(int argc,char **argv, char * liste_options, option_A_B * option_a_b) ;

/*! Fonction qui affiche le menu d'aide complet 
 * cette fonction est appelé si l'option -H est mentionnée
 */
void print_help() ;

/*! Fonction qui traite l'entrée en ligne de commande pour récupérer les options et leurs arguments
 * en plus des motifs s'il y en a plusieurs
 * renvoie la liste d'options récupérées
 */
char * traitement_option(int argc ,char **argv, char ***motifs, int * nb_motif,  int * indice_arg, option_A_B * option_a_b) ;

/*! Fonction si une option se trouve dans la liste d'options récupérée de la fonction traitement_option
 * renvoie 1 si c'est la cas
 * sinon renvoie 0
 */
int existe_option(char * liste_options, char option) ;

#endif
