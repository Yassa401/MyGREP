/* Fichier contenant les fonctions de recherche de motifs
dans les fichiers.
Date de création : 15/02/2023
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "macro.h"
#include "recherche.h"
#include "utilitaire.h"

/*! Fonction qui parcourt la ligne en recherche du motif
 * renvoie 1 si le motif se trouve dans la ligne
 * renvoie 0 sinon
 */
int chercher_motif(char * motif, char * ligne, int existe_option_i){
    int i, j = 0;
    /* si on ignore la casse*/
    if (existe_option_i ){
        for ( i = 0 ; i < (int) strlen(ligne) ; i++){
            /*si le 1er caractere du motif se trouve dans la ligne */
            if ( *(motif) == *(ligne + i) || (*(motif) + 'A' -'a') == *(ligne +i) || (*(motif) + 'a' - 'A') == *(ligne +i)){
                /*on parcours la suite de caracteres du motif à la suite de caractères de la ligne*/
                for (j = 1 ; j < (int) strlen(motif) ; j++){
                    /*si un caractere de la suite ne correspond à un autre on arrete et revient à la 1ere condition */
                    if ( *(motif + j) != *(ligne + i + j) && (*(motif + j) + 'A' -'a') != *(ligne +i +j) && (*(motif) + 'a' - 'A') != *(ligne +i +j) )
                        break ;
                }
                /*apres le parcours de toute la chaine du motif sans interruption signifie que les suites se ressemblaient 
                donc le motif se trouve dans la ligne */
                if (*(motif + j) == '\0')
                    return 1 ;
            }
        }
    }
    /* si on n'ignore pas la casse */
    else {
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
    return 0 ;
}

/*! Fonction qui cherche le motif au debut de la ligne
 * si c'est le cas on renvoie 1
 * sinon 0
 */
int chercher_motif_debut(char * motif, char * ligne, int existe_option_i){
    int i ;
    if (existe_option_i){

    }
    for (i = 1 ; i < (int) strlen(motif) ; i++){
        if ( *(motif + i) != *(ligne + i - 1) ){
            return 0 ;
        }
    }
    return 1;
}

/*! Fonction qui cherche le motif a la fin de ligne
 * si c'est le cas on renvoie 1
 * sinon 0
 */
int chercher_motif_fin(char * motif , char * ligne, int existe_option_i){
    int i , j ;
    j = strlen(ligne) - 1 ;
    if (existe_option_i){
        for ( i = strlen(motif) - 2 ; i > 0 ; i--){
            if (  *(motif + i) != *(ligne + j) && *(motif + i) + 'a' - 'A' != *(ligne + j ) && *(motif + i) + 'A' - 'a' != *(ligne +j) )
                return 0 ;
            j -= 1 ;
        }
        return 1 ;
    }
    else {
        for ( i = strlen(motif) - 2 ; i > 0 ; i--){
            if ( *(motif + i) != *(ligne + j ) )
                return 0 ;
            j -= 1 ;
        }
        return 1 ;
    }
}

int chercher_motif_debut_fin(char * motif, char * ligne, int existe_option_i){
    int i = 1;
    if (existe_option_i){
        if ( *(motif + i) == *(ligne + i - 1)){
            for ( i = 2 ; i < (int) (strlen(motif) - 1) ; i++ ){
            /*On arrete si deux caracteres au meme indice sont differents*/
            if ( *(motif + i) != *(ligne + i - 1) && (*(motif + i) + 'a' + 'A') != *(ligne + i - 1) && (*(motif + i) + 'a' + 'A') != *(ligne + i - 1))
                return 0 ;
            }
            /*On verifie bien que le motif sans "^" et "$" a la meme longueur que la ligne*/
            if ( strlen(ligne) == (strlen(motif) - 2)){
                return 1 ;
            }
        }
        return 0 ;
    }
    else {
        /*si debut des deux chaines sont pareils on parcours le reste*/
        if ( *(motif + i) == *(ligne + i - 1)){
            for ( i = 2 ; i < (int) (strlen(motif) - 1) ; i++ ){
                /*On arrete si deux caracteres au meme indice sont differents*/
                if ( *(motif + i) != *(ligne + i - 1)){
                    return 0 ;
                }
            }
            /*On verifie bien que le motif sans "^" et "$" a la meme longueur que la ligne*/
            if ( strlen(ligne) == (strlen(motif) - 2)){
                return 1 ;
            }
        }
        return 0 ;
    }
}

/*! Fonction qui récupère ligne par ligne de un fichier donné
 * et cherche le motif dans chaque ligne
 * ne renvoie rien
 */
void recherche_fichier(char * nom_fichier ,FILE * fichier, char * motif, char * liste_options){
    int i = 0 , indice_ligne = 0 ; /* indice_ligne stocke le numéro de ligne */
    int existe_option_i = 0 ;
    int existe_option_n = 0 ;
    int existe_option_h = 0 ;
    char car ;
    char * ligne = (char *) calloc( NB_CHAR,sizeof(char) ) ;
    existe_option_i = existe_option(liste_options, 'i') ;
    existe_option_n = existe_option(liste_options, 'n') ;
    existe_option_h = existe_option(liste_options, 'h') ;
    /* lecture d'un caractere par caractere dans le fichier et constitue une ligne
    si on arrive a un saut de ligne */
    car = fgetc(fichier) ;
    while( car != EOF){
        if (car == '\n'){
            *(ligne + i ) = '\0' ;
            indice_ligne += 1 ;
            i = 0 ;
            car =fgetc(fichier) ;
            /* si ligne construit , on recherche le motif la dedans on faisant appel 
            a une des fonctions de recherche de motif dans une ligne 
            */
            /* si le motif commence par "^" on cherche le motif au debut de la ligne*/
            if ( *(motif) == '^' && *(motif + strlen(motif) - 1) == '$' ){
                if ( chercher_motif_debut_fin(motif, ligne, existe_option_i) ){
                    if (!existe_option_h) /* on affiche le nom du fichier */
                        printf("\033[31;01m%s\033[34m:", nom_fichier) ;
                    if (existe_option_n)
                        printf("\033[32m%d\033[34m:",indice_ligne) ;

                    printf("\033[00m%s \n",ligne) ;    
                }
            }
            else{
                if ( *(motif) == '^'){
                    if ( chercher_motif_debut(motif, ligne, existe_option_i) ){
                        if (!existe_option_h) /* on affiche le nom du fichier */
                            printf("\033[31;01m%s\033[34m:", nom_fichier) ;
                        if (existe_option_n)
                            printf("\033[32m%d\033[34m:",indice_ligne) ;

                        printf("\033[00m%s \n",ligne) ;          
                    }
                }
                if ( *(motif + strlen(motif) - 1) == '$'){
                    if ( chercher_motif_fin(motif, ligne, existe_option_i) ){
                        if (!existe_option_h) /* on affiche le nom du fichier */
                            printf("\033[31;01m%s\033[34m:", nom_fichier) ;
                        if (existe_option_n)
                            printf("\033[32m%d\033[34m:",indice_ligne) ;

                        printf("\033[00m%s \n",ligne) ;    
                    }    
                }
                else {
                    if ( chercher_motif(motif, ligne, existe_option_i) ){
                        if (!existe_option_h) /* on affiche le nom du fichier */
                            printf("\033[31;01m%s\033[34m:", nom_fichier) ;
                        if (existe_option_n)
                            printf("\033[32m%d\033[34m:",indice_ligne) ;

                        printf("\033[00m%s \n",ligne) ;    
                    }
                }
            } 
        }
        /* si plusieurs saut de lignes on les ignorent */
        while (car == '\n' ){
            car =fgetc(fichier) ;
            indice_ligne += 1 ;
        }
        *(ligne + i) = car ;
        i++;
        car = getc(fichier);
        if (car == EOF){
            *(ligne + i ) = '\0' ;
            indice_ligne += 1 ;
            /* si ligne construit , on recherche le motif la dedans on faisant appel 
            a une des fonctions de recherche de motif dans une ligne 
            */
            /* si le motif commence par "^" on cherche le motif au debut de la ligne*/
            if ( *(motif) == '^' && *(motif + strlen(motif) - 1) == '$' ){
                if ( chercher_motif_debut_fin(motif, ligne, existe_option_i) ){
                    if (!existe_option_h) /* on affiche le nom du fichier */
                        printf("\033[31;01m%s\033[34m:", nom_fichier) ;
                    if (existe_option_n)
                        printf("\033[32m%d\033[34m:",indice_ligne) ;

                    printf("\033[00m%s \n",ligne) ;    
                }
            }
            else{
                if ( *(motif) == '^'){
                    if ( chercher_motif_debut(motif, ligne, existe_option_i) ){
                        if (!existe_option_h) /* on affiche le nom du fichier */
                            printf("\033[31;01m%s\033[34m:", nom_fichier) ;
                        if (existe_option_n)
                            printf("\033[32m%d\033[34m:",indice_ligne) ;

                        printf("\033[00m%s \n",ligne) ;          
                    }
                }
                if ( *(motif + strlen(motif) - 1) == '$'){
                    if ( chercher_motif_fin(motif, ligne, existe_option_i) ){
                        if (!existe_option_h) /* on affiche le nom du fichier */
                            printf("\033[31;01m%s\033[34m:", nom_fichier) ;
                        if (existe_option_n)
                            printf("\033[32m%d\033[34m:",indice_ligne) ;

                        printf("\033[00m%s \n",ligne) ;    
                    }    
                }
                else {
                    if ( chercher_motif(motif, ligne, existe_option_i) ){
                        if (!existe_option_h) /* on affiche le nom du fichier */
                            printf("\033[31;01m%s\033[34m:", nom_fichier) ;
                        if (existe_option_n)
                            printf("\033[32m%d\033[34m:",indice_ligne) ;

                        printf("\033[00m%s \n",ligne) ;    
                    }
                }
            }
        }
    }
    free(ligne) ;
    return ;
}

/*! Fonction qui recupere fichier par fichier dans les arguments donnés
 * et cherche le motif dans chacun des fichiers
 * ne renvoie rien
 */
void recherche_fichiers(int argc ,char **argv, char * motif, int indice_arg, char * liste_options){
    int i ;
    FILE * fichier = NULL ;
    /* Parcours les differents fichiers un à un pour les ouvrir 
    en mode lecture seulement */
    for (i = indice_arg ; i < argc ; i++){
        fichier = fopen(*(argv + i) ,"r") ;
        if (fichier == NULL){
            printf("Impossible de lire le fichier %s ! \n",*(argv + i)) ;
            exit(EXIT_FAILURE) ;
        }
        /*si fichier ouvert, on cherche le motif la dedans en faisant 
        appel a la fonction precedente */
        else {
            recherche_fichier(*(argv + i) ,fichier , motif , liste_options) ;
            fclose(fichier) ;
        }
    }
    return ;
}


/*! Fonction qui inverse la correspondance de recherche de motif 
 * si le motif existe dans la ligne , elle n'est pas affiché
 * sinon elle est affiché
 */

void recherche_fichier_option_v(char * nom_fichier ,FILE * fichier, char * motif){
    int i = 0 ;
    char car ;
    char * ligne = (char *) calloc( NB_CHAR,sizeof(char) ) ;
    int existe_option_i = 0 ;

    /* lecture d'un caractere par caractere dans le fichier et constitue une ligne
    si on arrive a un saut de ligne */
    car = fgetc(fichier) ;
    while( car != EOF){
        if (car == '\n'){
            /* si plusieurs saut de lignes on les ignorent */
            while (car == '\n'){
                car =fgetc(fichier) ;
            }
            *(ligne + i ) = '\0' ;
            i = 0 ;
            /* si ligne construit , on recherche le motif la dedans on faisant appel 
            a une des fonctions de recherche de motif dans une ligne 
            */
            /* si le motif commence par "^" on cherche le motif au debut de la ligne*/
            if ( *(motif) == '^' && *(motif + strlen(motif) - 1) == '$' ){
                if ( !chercher_motif_debut_fin(motif, ligne, existe_option_i) ){
                    printf("\033[31;01m%s\033[34m:\033[00m%s \n",nom_fichier ,ligne);    
                }
            }
            else{
                if ( *(motif) == '^'){
                    if ( !chercher_motif_debut(motif, ligne, existe_option_i) ){
                        printf("\033[31;01m%s\033[34m:\033[00m%s \n",nom_fichier ,ligne);
                    }
                }
                if ( *(motif + strlen(motif) - 1) == '$'){
                    if ( !chercher_motif_fin(motif, ligne, existe_option_i) ){
                        printf("\033[31;01m%s\033[34m:\033[00m%s \n",nom_fichier ,ligne);
                    }
                }
                else {
                    if ( !chercher_motif(motif, ligne, existe_option_i) ){
                        printf("\033[31;01m%s\033[34m:\033[00m%s \n",nom_fichier ,ligne);
                    }
                }
            } 
        }
        *(ligne + i) = car ;
        i++;
        car = fgetc(fichier) ;
        if (car == EOF){
            *(ligne + i ) = '\0' ;
            /* si ligne construit , on recherche le motif la dedans on faisant appel 
            a une des fonctions de recherche de motif dans une ligne 
            */
            /* si le motif commence par "^" on cherche le motif au debut de la ligne*/
            if ( *(motif) == '^' && *(motif + strlen(motif) - 1) == '$' ){
                if ( !chercher_motif_debut_fin(motif, ligne, existe_option_i) ){
                    printf("\033[31;01m%s\033[34m:\033[00m%s \n",nom_fichier ,ligne);    
                }
            }
            else{
                if ( *(motif) == '^'){
                    if ( !chercher_motif_debut(motif, ligne, existe_option_i) ){
                        printf("\033[31;01m%s\033[34m:\033[00m%s \n",nom_fichier ,ligne);
                    }
                }
                if ( *(motif + strlen(motif) - 1) == '$'){
                    if ( !chercher_motif_fin(motif, ligne, existe_option_i) ){
                        printf("\033[31;01m%s\033[34m:\033[00m%s \n",nom_fichier ,ligne);
                    }
                }
                else {
                    if ( !chercher_motif(motif, ligne, existe_option_i) ){
                        printf("\033[31;01m%s\033[34m:\033[00m%s \n",nom_fichier ,ligne);
                    }
                }
            }
        }
    }
    free(ligne) ;
    return ;    
}

/* Fonction qui recupere fichier par fichier dans les arguments donnés
 * et cherche le motif dans chacun des fichiers avec l'option v
 * ne renvoie rien
 */
void recherche_fichiers_option_v(int argc ,char **argv, int indice_arg){
    int i ;
    FILE * fichier = NULL ;
    char * motif = *(argv + indice_arg) ;
    indice_arg += 1 ;
    /* Parcours les differents fichiers un à un pour les ouvrir 
    en mode lecture seulement */
    for (i = indice_arg ; i < argc ; i++){
        fichier = fopen(*(argv + i) ,"r") ;
        if (fichier == NULL){
            printf("Impossible de lire le fichier %s ! \n",*(argv + i)) ;
            exit(EXIT_FAILURE) ;
        }
        /*si fichier ouvert, on cherche le motif la dedans en faisant 
        appel a la fonction precedente */
        else {
            recherche_fichier_option_v(*(argv + i) ,fichier , motif ) ;
            fclose(fichier) ;
        }
    }
    return ;
}