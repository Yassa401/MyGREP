
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macro.h"
#include "recherche.h"
#include "recherche_sans_affiche.h"
#include "utilitaire.h"


int main(int argc,char **argv){
    char * motif ;
    char * liste_options = NULL ;
    int indice_arg = 1 ;

    liste_options = (char *) malloc( 12 * sizeof(char) ) ;
    if (liste_options == NULL){
        printf("Erreur dans l'allocation de la memoire \n") ;
        exit(EXIT_FAILURE) ;
    }

    usage(argc, argv) ;
    indice_arg = traitement_option(argc , argv, liste_options) ;    
    motif = *( argv + indice_arg) ;
    printf("Le motif est %s \n",motif) ;

    printf("la liste d'options est : %s \n",liste_options) ;

    if ( existe_option(liste_options,'c') || existe_option(liste_options,'L') || existe_option(liste_options,'l') || existe_option(liste_options,'v') ){
        if(existe_option(liste_options,'L'))
                recherche_fichiers_option_L(argc, argv, indice_arg, liste_options) ;
        
        else {
            if (existe_option(liste_options,'l'))
                recherche_fichiers_option_l(argc, argv, indice_arg, liste_options) ;
            else { 
                if(existe_option(liste_options,'c'))
                    recherche_fichiers_option_c(argc, argv, indice_arg, liste_options) ;
            }
        }
    }
    free(liste_options) ;
    exit(EXIT_SUCCESS) ; 
}

