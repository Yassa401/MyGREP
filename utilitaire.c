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
    printf("Options disponibles et leurs utilisations : \n-H : Affiche le menu d\'aide de la commande mygrep \n-c : Affiche seulement le nombre de lignes contenant le motif dans fichier(s)\n-h : n\'affiche pas le nom du fichier devant la ligne contenant le motif \n\n" ) ;    
    return ;
}

void traitement_option(int argc ,char **argv, int * indice_arg){
    char *opstring = ":Hch" ; 
    int val ;
    val = getopt(argc, argv, opstring) ;
    while( val != EOF){
        switch (val){
            case 'H' :
                print_help() ;
                *indice_arg += 1 ;
                break ;
            case 'c' :
                printf("option -c pris en charge \n") ;
                *indice_arg += 1 ;
                recherche_fichiers_option_c(argc ,argv, *indice_arg) ;
                break ;
            case 'h' :
                printf("option -h pris en charge \n");
                *indice_arg += 1 ;
                break ;
        }
        val = getopt(argc, argv, opstring) ;
    }
}