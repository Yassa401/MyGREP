
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macro.h"
#include "recherche.h"
#include "recherche_sans_affiche.h"
#include "utilitaire.h"


int main(int argc,char **argv){
    char * motif ;
    int indice_arg = 1 ;
    usage(argc, argv) ;
    traitement_option(argc , argv, &indice_arg) ;
    motif = *( argv + indice_arg) ;
    printf("le motif est --%s--\n", motif) ;
    indice_arg += 1 ;
    recherche_fichiers(argc , argv, motif, indice_arg );

    exit(EXIT_SUCCESS) ; 
}

