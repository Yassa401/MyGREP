
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macro.h"
#include "recherche.h"
#include "recherche_sans_affiche.h"
#include "utilitaire.h"


int main(int argc,char **argv){
    char ** motifs ;
    int nb_motifs = 0 ;
    int indice_arg ;
    char * liste_options = NULL ;
    option_A_B * option_a_b = NULL ;
    option_a_b = (option_A_B *) malloc (sizeof(option_A_B)) ;
    if (option_a_b == NULL){
        fprintf(stderr,"erreur dans l'allocation mémoire \n") ;
        exit(1) ;
    }
    option_a_b->existe_option_A = 0 ;
    option_a_b->existe_option_B = 0 ;
    option_a_b->n_A = 0 ;
    option_a_b->n_B = 0 ;

    liste_options = traitement_option(argc , argv, &motifs , &nb_motifs ,  &indice_arg, option_a_b) ;    
    usage(argc, argv, liste_options, option_a_b) ;
     
    /* ajoute le motif par défaut sans l'option -e qui se trouve à l'indice optind */
    nb_motifs += 1 ;
    motifs = (char **) realloc( motifs , nb_motifs * sizeof(char *) ) ;
    if (motifs == NULL){
        fprintf(stderr,"erreur dans l'allocation mémoire \n") ;
        free(liste_options) ;
        free(option_a_b) ;
        exit(EXIT_FAILURE) ;
    }
    motifs[nb_motifs - 1 ] = argv[indice_arg] ;

    indice_arg += 1 ;

    /* s'il y a au moins une option qui existe, teste si liste_options n'est pas une chaine vide */
    if ( *(liste_options) != 0 ){
        if (existe_option(liste_options,'H')){
            free(option_a_b) ;
            free(liste_options) ;
            free(motifs) ;
            exit(EXIT_SUCCESS) ;
        }
        if ( existe_option(liste_options,'c') || existe_option(liste_options,'L') || existe_option(liste_options,'l')){
            if(existe_option(liste_options,'L'))
                    recherche_fichiers_option_L(argc, argv, motifs, nb_motifs, indice_arg, liste_options) ;

            else {
                if (existe_option(liste_options,'l'))
                    recherche_fichiers_option_l(argc, argv, motifs, nb_motifs, indice_arg, liste_options) ;
                else { 
                    if(existe_option(liste_options,'c'))
                        recherche_fichiers_option_c(argc, argv, motifs, nb_motifs, indice_arg, liste_options) ;
                }
            }
        }           
        else{
        recherche_fichiers(argc, argv, motifs, nb_motifs, indice_arg, liste_options, option_a_b) ;
        }
    }
    else{
        recherche_fichiers(argc, argv, motifs, nb_motifs, indice_arg, liste_options, option_a_b) ;
    }
    
    free(option_a_b) ;
    free(liste_options) ;
    free(motifs) ;
    exit(EXIT_SUCCESS) ; 
}

