
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NB_CHAR 200

/*! Fonction qui parcourt la ligne en recherche du motif
 * renvoie 1 si le motif se trouve dans la ligne
 * renvoie 0 sinon
 */
int chercher_motif(char * motif, char * ligne){
    int i, j = 0;
    for ( i = 0 ; i < (int) strlen(ligne) ; i++){
        /*si le 1er caractere du motif se trouve dans la ligne */
        if ( *(motif) == *(ligne + i) ){
            /*on parcours la suite de caracteres du motif à la suite de caractères de la ligne*/
            for (j = 1 ; j < (int) strlen(motif) ; j++){
                /*si un caractere de la suite ne correspond à un autre on arrete et revient à la 1ere condition */
                if (*(motif + j) != *(ligne + i + j)){
                    break ;
                }
            }
            /*apres le parcours de toute la chaine du motif sans interruption signifie que les suites se ressemblaient 
            donc le motif se trouve dans la ligne */
            if (*(motif + j) == '\0')
                return 1 ;
        }                    
    }
    return 0 ;
}


int main(int argc, char **argv){
    
    FILE * fichier = NULL ;
    char * ligne = (char *)calloc(NB_CHAR,sizeof(char));
    char car ;
    int i = 0 ;
    if (argc < 3){
        printf("Usage: %s <motif> <fichier> \n",*(argv)) ;
        exit(EXIT_FAILURE) ;
    }

    printf("motif = %s et fichier = %s \n",*(argv + 1), *(argv + 2)) ;
    fichier = fopen(*(argv + 2),"r") ;
    if (fichier == NULL){
        printf("Impossible de lire le fichier ! \n") ;
        exit(EXIT_FAILURE) ;
    }
    car = fgetc(fichier) ;
    while( car != EOF){
        if (car == '\n'){
            car =fgetc(fichier) ;
            i++;
            *(ligne + i) = '\0' ;
            i = 0 ;
            if (chercher_motif(*(argv + 1), ligne)){
                printf("%s \n",ligne);
            }
        }
        *(ligne + i) = car ;
        i++;
        car = fgetc(fichier) ;
    } 

    exit(EXIT_SUCCESS); 
}

