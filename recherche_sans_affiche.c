/* Fichier contenant les fonctions de recherche de motifs 
sans afficher les lignes trouvees dans les fichiers 
Date de création : 26/02/2023
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macro.h"
#include "recherche.h"
#include "utilitaire.h"


int recherche_fichier_sans_affiche(FILE * fichier, char ** motifs, int nb_motifs, int * compte_ligne, int * nb_lignes_totale, int existe_option_i){
    int i = 0 , nb_totale = 0 ;
    int indice_motif = 0 ;
    char car ;
    char * ligne = (char *) calloc( NB_CHAR,sizeof(char) ) ;
    char * motif ;
    /* On remet le compteur de lignes trouvées à 0 après chaque appel de la fonction
     * Ce compteur peut etre renvoye en cas d'appel à l'option -c 
    */
    *compte_ligne = 0 ;
    /* lecture d'un caractere par caractere dans le fichier et constitue une ligne
    si on arrive a un saut de ligne */
    car = fgetc(fichier) ;
    while( car != EOF){
        if (car == '\n'){
            *(ligne + i ) = '\0' ;
            indice_motif = 0 ;
            nb_totale += 1 ;
            car = fgetc(fichier) ;
            i = 0 ;
            /* si ligne construit , on recherche le motif la dedans on faisant appel 
            a une des fonctions de recherche de motif dans une ligne 
            */
            /* si le motif commence par "^" on cherche le motif au debut de la ligne*/
            while(indice_motif < nb_motifs){
                motif = *(motifs + indice_motif) ;
                if ( *(motif) == '^' && *(motif + strlen(motif) - 1) == '$' ){
                    if ( chercher_motif_debut_fin(motif, ligne, existe_option_i) ){
                        *compte_ligne += 1 ;
                        break ;  
                    }
                }
                else{
                    if ( *(motif) == '^'){
                        if ( chercher_motif_debut(motif, ligne, existe_option_i) ){
                            *compte_ligne += 1 ; 
                            break ;   
                        }
                    }
                    if ( *(motif + strlen(motif) - 1) == '$'){
                        if ( chercher_motif_fin(motif, ligne, existe_option_i) ){
                            *compte_ligne += 1 ;
                            break ;
                        }
                    }
                    else {
                        if ( chercher_motif(motif, ligne, existe_option_i) ){
                            *compte_ligne += 1 ;
                            break ;
                        }
                    }
                }
                indice_motif += 1 ;
            }
        }
        /* si plusieurs saut de lignes on les ignorent */
        while (car == '\n'){
            car = fgetc(fichier) ;
            nb_totale += 1 ;
        }
        *(ligne + i) = car ;
        i++;
        car = fgetc(fichier) ;
        if ( car == EOF ){
            *(ligne + i ) = '\0' ;
            indice_motif = 0 ;
            /* si ligne construit , on recherche le motif la dedans on faisant appel 
            a une des fonctions de recherche de motif dans une ligne 
            */
            /* si le motif commence par "^" on cherche le motif au debut de la ligne*/

            while(indice_motif < nb_motifs){
                motif = *(motifs + indice_motif) ;
                if ( *(motif) == '^' && *(motif + strlen(motif) - 1) == '$' ){
                    if ( chercher_motif_debut_fin(motif, ligne, existe_option_i) ){
                        *compte_ligne += 1 ;
                        break ; 
                    }
                }
                else{
                    if ( *(motif) == '^'){
                        if ( chercher_motif_debut(motif, ligne, existe_option_i) ){
                            *compte_ligne += 1 ;
                            break ;    
                        }
                    }
                    if ( *(motif + strlen(motif) - 1) == '$'){
                        if ( chercher_motif_fin(motif, ligne, existe_option_i) ){
                            *compte_ligne += 1 ;
                            break ;
                        }
                    }
                    else {
                        if ( chercher_motif(motif, ligne, existe_option_i) ){
                            *compte_ligne += 1 ;
                            break ;    
                        }
                    }
                }
                indice_motif += 1 ;
            }
        }
    }
    free(ligne) ;
    /*si la valeur de compte_ligne différente de 0 , le motif est trouve
    au moins une fois dans le fichier
    */
    * nb_lignes_totale = nb_totale ;
    if (*compte_ligne){
        return 1 ;
    }
    return 0 ;
}

/*! Fonction qui recupere fichier par fichier dans les arguments donnés
 * et cherche le motif dans chacun des fichiers
 * ne renvoie rien
 */
void recherche_fichiers_option_c(int argc , char **argv, char ** motifs, int nb_motifs, int indice_arg, char * liste_options){
    int i , compte_ligne , nb_lignes_totale ;
    int existe_option_i = 0 ;
    FILE * fichier = NULL ;
    compte_ligne = 0 ;
    existe_option_i = existe_option(liste_options, 'i') ;
    /* Parcours les differents fichiers un à un pour les ouvrir 
    en mode lecture seulement */
    for (i = indice_arg ; i < argc ; i++){
        fichier = fopen(*(argv + i) ,"r") ;
        if (fichier == NULL){
            printf("Impossible de lire le fichier %s ! \n",*(argv + i)) ;
            exit(EXIT_FAILURE) ;
        }
        /*si fichier ouvert, on cherche le motif la dedans en faisant 
        appel à la fonction precedente */
        if (existe_option(liste_options, 'v') ){
            recherche_fichier_sans_affiche(fichier , motifs, nb_motifs, &compte_ligne, &nb_lignes_totale , existe_option_i) ;
            /* Le nom du fichier se trouve dans argv[i] */
            if (!existe_option(liste_options, 'h'))
                printf("\033[35;01m%s\033[34m:",*(argv + i)) ;
            printf("\033[00m%d \n", nb_lignes_totale - compte_ligne  ) ;
        }
        else{
            if( recherche_fichier_sans_affiche(fichier , motifs, nb_motifs, &compte_ligne, &nb_lignes_totale, existe_option_i ) ){
                /* Le nom du fichier se trouve dans argv[i] */
                if (!existe_option(liste_options, 'h'))
                    printf("\033[35;01m%s\033[34m:",*(argv + i)) ;
                printf("\033[00m%d \n", compte_ligne  ) ;
            }
        }

        fclose(fichier) ;
    }
    return ;
}

void recherche_fichiers_option_L(int argc, char ** argv, char ** motifs, int nb_motifs, int indice_arg, char * liste_options){
    int i , compte_ligne , nb_lignes_totale ;
    int existe_option_i = 0 ;
    FILE * fichier = NULL ;
    compte_ligne = 0 ;
    existe_option_i = existe_option(liste_options, 'i') ;
    for (i = indice_arg ; i < argc ; i++){
        fichier = fopen(*(argv + i) ,"r") ;
        if (fichier == NULL){
            printf("Impossible de lire le fichier %s ! \n",*(argv + i)) ;
            exit(EXIT_FAILURE) ;
        }
        /*si fichier ouvert, on cherche le motif la dedans en faisant 
        appel à la fonction precedente */
        if (existe_option(liste_options, 'v') ){
            if (recherche_fichier_sans_affiche(fichier , motifs, nb_motifs, &compte_ligne, &nb_lignes_totale, existe_option_i)){
            /* Le nom du fichier se trouve dans argv[i] */
            printf("\033[35;01m%s\033[34m\n",*(argv + i) ) ;
            }
        }
        else{
            if( ! recherche_fichier_sans_affiche(fichier , motifs, nb_motifs, &compte_ligne, &nb_lignes_totale, existe_option_i)){
                /* Le nom du fichier se trouve dans argv[i] */
                printf("\033[35;01m%s\033[34m\n",*(argv + i) ) ;
            }
        }

        fclose(fichier) ;
    }
    return ;
}

void recherche_fichiers_option_l(int argc, char ** argv, char ** motifs, int nb_motifs,  int indice_arg, char * liste_options){
    int i , compte_ligne , nb_lignes_totale ;
    int existe_option_i = 0 ;
    FILE * fichier = NULL ;
    compte_ligne = 0 ;
    existe_option_i = existe_option(liste_options, 'i') ;
    for (i = indice_arg ; i < argc ; i++){
        fichier = fopen(*(argv + i) ,"r") ;
        if (fichier == NULL){
            printf("Impossible de lire le fichier %s ! \n",*(argv + i)) ;
            exit(EXIT_FAILURE) ;
        }
        /*si fichier ouvert, on cherche le motif la dedans en faisant 
        appel à la fonction precedente */
        if (existe_option(liste_options, 'v') ){
            if ( !recherche_fichier_sans_affiche(fichier , motifs, nb_motifs, &compte_ligne, &nb_lignes_totale, existe_option_i )){
            /* Le nom du fichier se trouve dans argv[i] */
            printf("\033[35;01m%s\033[34m\n",*(argv + i) ) ;
            }
        }
        else{
            if(recherche_fichier_sans_affiche(fichier , motifs, nb_motifs, &compte_ligne, &nb_lignes_totale, existe_option_i )){
                /* Le nom du fichier se trouve dans argv[i] */
                printf("\033[35;01m%s\033[34m\n",*(argv + i) ) ;
            }
        }

        fclose(fichier) ;
    }
    return ;
}


