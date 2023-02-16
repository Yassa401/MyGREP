/* Fichier contenant les fonctions qui gere les differentes
 exceptions du programme
Date de création : 15/02/2023
*/

#include <stdio.h>
#include <stdlib.h>
#include "utilitaire.h"

void usage(int argc, char **argv){
    if (argc < 3){
        printf("Usage: %s <motif> <fichier1> [<fichier2> ...] \n",*(argv)) ;
        exit(EXIT_FAILURE) ;
    }
    return ;
}
