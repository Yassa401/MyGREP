
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macro.h"
#include "recherche.h"
#include "utilitaire.h"


int main(int argc, char **argv){
    char * motif ;
    usage(argc, argv) ;

    /*printf("motif = %s et fichier = %s \n",*(argv + 1), *(argv + 2)) ;*/
    motif = *(argv + 1) ;
    recherche_fichiers(argc , argv, motif);

    exit(EXIT_SUCCESS) ; 
}

