/* Fichier contenant les fonctions qui gere les differentes
 exceptions du programme
Date de création : 15/02/2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "utilitaire.h"
#include "recherche_sans_affiche.h"

void usage(int argc, char **argv){
    if (argc < 3){
        printf("Usage: %s <motif> <fichier1> [<fichier2> ...] \n",*(argv)) ;
        exit(EXIT_FAILURE) ;
    }
    return ;
} 

void print_help(){
    printf("Usage : ./mygrep [option(s)] <motif(s)> <fichier(s)> \n");
    printf("Cherche motif(s) dans <fichier(s)> \n");
    printf("Exemple : ./mygrep -c \'Blabla\' fichier1.txt fichier2.txt \n\n");
    printf("Options disponibles et leurs utilisations : \n-H : Affiche le menu d\'aide de la commande mygrep \n" ) ;
    printf("-c : Affiche seulement le nombre de lignes contenant le motif dans fichier(s) \n") ;
    printf("-l : n\'affiche pas les lignes trouvées mais le nom des fichiers avec au moins une correspondance \n") ;
    printf("-L : n\'affiche pas les lignes trouvées mais le nom des fichiers avec aucune correspondance \n") ;
    printf("-v : inverse la mise en correspondance \n") ;
    return ;
}

int traitement_option(int argc ,char **argv, char * liste_options){
    char *opstring = ":HlLvch" ; 
    int val , continuer = 0 ;
    val = getopt(argc, argv, opstring) ;
    while( val != EOF && ! continuer ){
        switch (val){
    
            case 'H' :
                * liste_options = 'H' ;
                liste_options ++ ;
                /*si l'option H est mentionne on traite plus les autres options
                et on affiche le menu d'aide */
                print_help() ;
                continuer = 1 ;
                break ;
            case 'l' :
                * liste_options = 'l' ;
                liste_options ++ ;
                break ;
            case 'L' :
                * liste_options = 'L' ;
                liste_options ++ ;
                break ;
            case 'v' :
                * liste_options = 'v' ;
                liste_options ++ ;
                break ;
            case 'c' :
                * liste_options = 'c' ;
                liste_options ++ ;
                break ;
            case 'h' :
                * liste_options = 'h' ;
                liste_options ++ ;
                break ;
            case 'n' :
                break ;
            case 'A' :
                break ;
            case 'B' :
                break ;
        }
        val = getopt(argc, argv, opstring) ;
    }

    *liste_options = '\0' ; 
    return optind ;
}

int existe_option(char * liste_options, char option){
    while( *liste_options != '\0'){
        if (*liste_options == option)
            return 1 ;
        liste_options ++ ;
    }
    return 0 ;
}