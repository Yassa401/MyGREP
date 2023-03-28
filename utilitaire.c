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
    char * opstring = ":H" ;
    int val , existe_option_H ;
    
    /* on verifie si l'option H n'est pas mentionné 
     * si vrai , pas besoin d'avoir les autres arguments et on affiche le menu d'aide
     * sinon un message d'usage s'affiche 
     */
    existe_option_H = 0 ;
    val = getopt(argc,argv,opstring) ;
    while ( val != EOF && !existe_option_H){
        switch (val){
            case 'H' :
                existe_option_H = 1 ;
                break ;
        }
    }

    if (argc < 3 && !existe_option_H){
        printf("Usage: %s <motif> <fichier1> [<fichier2> ...] \n",*(argv)) ;
        exit(EXIT_SUCCESS) ;
    }
    else {
        if (argc < 3 && existe_option_H){
            print_help() ;
        }
    }
    return ;
} 

void print_help(){
    printf("Usage : ./mygrep [option(s)] <motif(s)> <fichier(s)> \n");
    printf("Cherche motif(s) dans <fichier(s)> \n");
    printf("Exemple : ./mygrep -c \'Blabla\' fichier1.txt fichier2.txt \n\n");
    printf("Options disponibles et leurs utilisations : \n\n-H  Affiche le menu d\'aide de la commande mygrep \n" ) ;
    printf("-c  Affiche seulement le nombre de lignes contenant le motif dans fichier(s) \n") ;
    printf("-l  n\'affiche pas les lignes trouvées mais le nom des fichiers avec au moins une correspondance \n") ;
    printf("-L  n\'affiche pas les lignes trouvées mais le nom des fichiers avec aucune correspondance \n") ;
    printf("-v  inverse la correspondance \n") ;
    printf("\n");
    return ;
}

char * traitement_option(int argc ,char **argv, int * indice_arg){
    char *opstring = ":HlLvch" ;
    int val , continuer = 0 , i = 0 ;
    char * liste_options ;
    /* allocation de mémoire pour la chaine de caracteres qui contient toute les options*/
    liste_options = (char *) malloc( 12 * sizeof(char) ) ;
    if (liste_options == NULL){
        printf("Erreur dans l'allocation de la memoire \n") ;
        exit(EXIT_FAILURE) ;
    }
    val = getopt(argc, argv, opstring) ;
    while( val != EOF && ! continuer ){
        switch (val){
    
            case 'H' :
                * (liste_options + i) = 'H' ;
                i++ ;
                /*si l'option H est mentionne on traite plus les autres options
                et on affiche le menu d'aide */
                print_help() ;
                continuer = 1 ;
                break ;
            case 'l' :
                * (liste_options + i) = 'l' ;
                i++ ;
                break ;
            case 'L' :
                * (liste_options + i) = 'L' ;
                i++ ;
                break ;
            case 'v' :
                * (liste_options + i) = 'v' ;
                i++ ;
                break ;
            case 'c' :
                * (liste_options + i)= 'c' ;
                i++ ;
                break ;
            case 'h' :
                * (liste_options + i) = 'h' ;
                i++ ;
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

    *(liste_options + i)= '\0' ;    
    *indice_arg = optind ;
    return liste_options ;
}

int existe_option(char * liste_options, char option){
    while( * liste_options != '\0'){
        if (*liste_options == option)
            return 1 ;
        liste_options ++ ;
    }
    return 0 ;
}