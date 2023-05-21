/* Fichier contenant les fonctions qui gere les differentes
 exceptions du programme
Date de création : 15/02/2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "utilitaire.h"
#include "recherche_sans_affiche.h"

void usage(int argc, char **argv, char * liste_options, option_A_B * option_a_b){
    if (argc < 3 && !existe_option(liste_options, 'H')){
        printf("Usage: %s <motif> <fichier1> [<fichier2> ...] \n",*(argv)) ;
        free(option_a_b) ;
        free(liste_options) ;
        exit(EXIT_SUCCESS) ;
    }
    return ;
} 

void print_help(){
    printf("Usage : ./mygrep [OPTION(S)] <MOTIF(S)> <FICHIER(S)> \n\n");
    printf("Cherche <MOTIF(S)> dans <FICHIER(S)> \n\n");
    printf("EXEMPLE : ./mygrep -c \'Blabla\' fichier1.txt fichier2.txt \n\n");
    printf("OPTIONS disponibles et leurs utilisations : \n\n") ;
    printf("\033[36;01m-H \033[00m Affiche le menu d\'aide de la commande mygrep \n" ) ;
    printf("\033[36;01m-c \033[00m Affiche seulement le nombre de lignes contenant le motif dans fichier(s) \n") ;
    printf("\033[36;01m-l \033[00m N\'affiche pas les lignes trouvées mais le nom des fichiers avec au moins une correspondance \n") ;
    printf("\033[36;01m-L \033[00m N\'affiche pas les lignes trouvées mais le nom des fichiers avec aucune correspondance \n") ;
    printf("\033[36;01m-v \033[00m Inverse la mise en correspondance , si correspondance trouvée n'affiche pas la ligne \n") ;
    printf("\033[36;01m-e \033[34mmotif \033[00m Utiliser le motif indiqué, possibilié d'ajouter plusieurs motifs avec cette option \n") ;
    printf("\033[36;01m-i \033[00m Ignore les différences de casse (majuscules/minuscules) \n") ;
    printf("\033[36;01m-n \033[00m Préfixe chaque ligne par son numéro dans le fichier d'entrée \n") ;
    printf("\033[36;01m-h \033[00m Ne pas afficher le nom des fichiers dans les résultats \n") ;
    printf("\033[36;01m-A \033[34mnum \033[00m Affiche après chaque correspondance les num lignes se trouvant après la correspondance dans le fichier (=AFTER) \n") ;
    printf("\033[36;01m-B \033[34mnum \033[00m Affiche avant chaque correspondance les num lignes se trouvant avant la correspondance dans le fichier (=BEFORE) \n") ;
    printf("\n");
    return ;
}

char * traitement_option(int argc ,char **argv, char *** motif, int * nb_motif ,int * indice_arg, option_A_B * option_a_b){
    char *opstring = ":HlLvchnie:A:B:" ;
    char ** motifs = NULL ;
    int val , continuer = 0 , i = 0 ;
    char * liste_options ;
    /* allocation de mémoire pour la chaine de caracteres qui contient toute les options*/
    liste_options = (char *) malloc( 12 * sizeof(char) ) ;
    if (liste_options == NULL){
        printf("Erreur dans l'allocation de la memoire \n") ;
        free(option_a_b) ;
        exit(EXIT_FAILURE) ;
    }
    val = getopt(argc, argv, opstring) ;
    while( val != EOF && ! continuer ){
        switch (val){
            case 'H' :
                * (liste_options + i) = 'H' ;
                i++ ;
                /*si l'option H est mentionnée on ne traite plus les autres options
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
                * (liste_options + i) = 'n' ;
                i++ ;
                break ;
            case 'i' :
                * (liste_options + i) = 'i' ;
                i++ ;
                break ;
            case 'e' :
                * (liste_options + i) = 'e' ;
                if (optarg != NULL){
                    if (motifs == NULL){
                        motifs = (char **) malloc( sizeof(char *) ) ;
                        if (motifs == NULL){
                            fprintf(stderr,"erreur dans l'allocation mémoire \n") ;
                            free(option_a_b) ;
                            free(liste_options) ;
                            exit(EXIT_FAILURE) ;
                        }
                        *nb_motif += 1 ;
                    }
                    else{
                        *nb_motif += 1 ;
                        motifs = (char **) realloc( motifs , *nb_motif * sizeof(char *) ) ;
                        if (motifs == NULL){
                            fprintf(stderr,"erreur dans l'allocation mémoire \n") ;
                            free(option_a_b) ;
                            free(liste_options) ;
                            exit(EXIT_FAILURE) ;
                        }
                    }
                    motifs[*nb_motif-1] = optarg ; 
                }               
                i++ ;
                break ;
            case 'A' :
                option_a_b->existe_option_A = 1 ;
                if (optarg != NULL){
                    option_a_b->n_A = atoi(optarg) ;
                    if (option_a_b->n_A <= 0){
                        fprintf(stderr,"Entrez une valeur positive pour l'argument -A \n") ;
                        free(option_a_b) ;
                        free(liste_options) ;
                        free(motifs) ;
                        exit(EXIT_FAILURE) ;
                    }
                }
                break ;
            case 'B' :
                option_a_b->existe_option_B = 1 ;
                if (optarg != NULL){
                    option_a_b->n_B = atoi(optarg) ;
                    if (option_a_b->n_B <= 0){
                        fprintf(stderr,"Entrez une valeur positive pour l'argument -B \n") ;
                        free(option_a_b) ;
                        free(liste_options) ;
                        free(motifs) ;
                        exit(EXIT_FAILURE) ;
                    }
                }
                break ;
            case ':' :
                /*si un argument nécessaire à une option manque , quitte le programme */
                fprintf(stderr,"argument manquant pour l'option %c \n", optopt) ;
                free(option_a_b) ;
                free(liste_options) ;
                free(motifs) ;
                exit(EXIT_FAILURE) ;
        }
        val = getopt(argc, argv, opstring) ;
    }

    *motif = motifs ;
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