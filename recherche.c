/* Fichier contenant les fonctions de recherche de motifs
dans les fichiers.
Date de création : 15/02/2023
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macro.h"
#include "recherche.h"

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

/*! Fonction qui récupère ligne par ligne de un fichier donné
 * et cherche le motif dans chaque ligne
 * ne renvoie rien
 */
void recherche_fichier(char * nom_fichier ,FILE * fichier, char * motif){
    int i = 0;
    char car ;
    char * ligne = (char *) calloc(NB_CHAR,sizeof(char)) ;
    /* lecture d'un caractere par caractere dans le fichier et constitue un ligne
    si on arrive a un saut de ligne */
    car = fgetc(fichier) ;
    while( car != EOF){
        if (car == '\n'){
            /* si plusieurs saut de lignes on les ignorent */
            while (car == '\n'){
                car =fgetc(fichier) ;
            }
            i++;
            *(ligne + i) = '\0' ;
            i = 0 ;
            /* si ligne construit , on recherche le motif la dedans on faisant appel a la
            fonction precedente 
            */
            if (chercher_motif(motif, ligne)){
                printf("\033[34;01m%s\033[00m :%s \n",nom_fichier ,ligne);
            }
        }
        *(ligne + i) = car ;
        i++;
        car = fgetc(fichier) ;
    }

    return ;
}

/*! Fonction qui recupere fichier par fichier dans les arguments donnés
 * et cherche le motif dans chacun des fichiers
 * ne renvoie rien
 */
void recherche_fichiers(int argc , char **argv, char * motif){
    int i ;
    FILE * fichier = NULL ;
    /* Parcours les differents fichiers un à un pour les ouvrir 
    en mode lecture seulement */
    for (i = 2 ; i < argc ; i++){
        fichier = fopen(*(argv + i) ,"r") ;
        if (fichier == NULL){
            printf("Impossible de lire le fichier %s ! \n",*(argv + i)) ;
            exit(EXIT_FAILURE) ;
        }
        /*si fichier ouvert, on cherche le motif la dedans en faisant 
        appel a la fonction precedente */
        else {
            recherche_fichier(*(argv + i) ,fichier , motif ) ;
            fclose(fichier) ;
        }
    }
    return ;
}