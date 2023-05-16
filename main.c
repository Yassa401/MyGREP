
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
    char * liste_options = NULL ;
    int indice_arg ;
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
    usage(argc, argv, liste_options) ;
    /*printf("indice_arg = %d\n",indice_arg) ; */ 
    /* ajoute le motif par défaut sans l'option -e qui se trouve à l'indice optind */
    nb_motifs += 1 ;
    motifs = (char **) realloc( motifs , nb_motifs * sizeof(char *) ) ;
    if (motifs == NULL){
        fprintf(stderr,"erreur dans l'allocation mémoire \n") ;
        exit(1) ;
    }
    motifs[nb_motifs - 1 ] = argv[indice_arg] ;

    /*for (i = 0 ; i < nb_motifs; i++){
        fprintf(stderr,"motif %d : %s ", i, motifs[i]) ;
    }
    fprintf(stderr,"\n") ;
    fprintf(stderr,"la liste d'options est : %s \n",liste_options) ;
    fprintf(stderr," %d -> %d et %d -> %d \n", option_a_b->existe_option_A, option_a_b->n_A, option_a_b->existe_option_B, option_a_b->n_B) ;
    */
    indice_arg += 1 ;


    if ( *(liste_options) != 0 ){
        if (existe_option(liste_options,'H')){
            free(liste_options) ;
            exit(EXIT_SUCCESS) ;
        }
        if ( existe_option(liste_options,'c') || existe_option(liste_options,'L') || existe_option(liste_options,'l') || existe_option(liste_options,'v') ){
            if(existe_option(liste_options,'L'))
                    recherche_fichiers_option_L(argc, argv, motifs, nb_motifs, indice_arg, liste_options) ;

            else {
                if (existe_option(liste_options,'l'))
                    recherche_fichiers_option_l(argc, argv, motifs, nb_motifs, indice_arg, liste_options) ;
                else { 
                    if(existe_option(liste_options,'c'))
                        recherche_fichiers_option_c(argc, argv, motifs, nb_motifs, indice_arg, liste_options) ;
                    else{
                        if(existe_option(liste_options, 'v'))
                            recherche_fichiers_option_v(argc, argv, indice_arg) ;
                    }
                }
            }
        }           
    }
    else{
        recherche_fichiers(argc, argv, motifs, nb_motifs, indice_arg, liste_options, option_a_b) ;
    }
    recherche_fichiers(argc, argv, motifs, nb_motifs, indice_arg, liste_options, option_a_b) ;

    free(option_a_b) ;
    free(liste_options) ;
    free(motifs) ;
    exit(EXIT_SUCCESS) ; 
}

