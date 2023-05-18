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


void affiche_n_lignes(FILE * fichier, char * nom_fichier, int n, int existe_option_h, int existe_option_n, int indice_ligne){
	char car ;
	int i = 0 ;
	int acc_lignes = 0 ;
	char * ligne = (char *) calloc( 200,sizeof(char) ) ;
	car = fgetc(fichier) ;
	while(car != EOF && acc_lignes < n){
		if(car == '\n'){
			*(ligne + i) = '\0' ;
			i = 0 ;
            acc_lignes += 1 ;
            if (!existe_option_h)
                fprintf(stderr,"\033[36;01m%s\033[34m-", nom_fichier) ;
            if (existe_option_n)
                fprintf(stderr,"\033[32m%d\033[34m-",indice_ligne + acc_lignes) ;
            fprintf(stderr,"\033[00m%s \n",ligne) ;
		}
		else{
			*(ligne + i) = car ;
			i += 1 ;
		}
		car = fgetc(fichier) ;
        if (car == EOF){
            *(ligne + i) = '\0' ;
			i = 0 ;
            acc_lignes += 1 ;
            if (!existe_option_h)
                fprintf(stderr,"\033[36;01m%s\033[34m:", nom_fichier) ;
            if (existe_option_n)
                fprintf(stderr,"\033[32m%d\033[34m:",indice_ligne + acc_lignes) ;
            fprintf(stderr,"\033[00m%s \n",ligne) ;
        }
	}
	free(ligne) ;
	return ;
}

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
                    if ( *(motif + j) != *(ligne + i + j) && (*(motif + j) + 'A' -'a') != *(ligne +i +j) && (*(motif+j) + 'a' - 'A') != *(ligne +i +j))
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
        for (i = 1 ; i < (int) strlen(motif) ; i++){
        if ( *(motif + i) != *(ligne + i - 1) && (*(motif + i) + 'a' - 'A') != *(ligne + i - 1) && (*(motif + i) + 'A' - 'a') != *(ligne + i - 1))
            return 0 ;
        }
    }
    else{
        for (i = 1 ; i < (int) strlen(motif) ; i++){
            if ( *(motif + i) != *(ligne + i - 1) )
                return 0 ;
        }
    }
    return 1 ;
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
            if ( *(motif + i) != *(ligne + i - 1) && (*(motif + i) + 'a' - 'A') != *(ligne + i - 1) && (*(motif + i) + 'A' - 'a') != *(ligne + i - 1))
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
void recherche_fichier(char * nom_fichier ,FILE * fichier, char ** motifs, int nb_motifs, char * liste_options, option_A_B * option_a_b){
    int i = 0 , indice_ligne = 0 ; /* indice_ligne stocke le numéro de ligne */
    int indice_motif = 0 ; /* indice qui indique quel motif parmi les motifs cherche le programme*/
    int motif_trouve = 0 ; /* variable qui prend 1 si l'un des motifs est trouvé dans ligne, sinon 0 */
    int existe_option_i = 0 ;
    int existe_option_n = 0 ;
    int existe_option_h = 0 ;
    int existe_option_v = 0 ;
    char car ;
    char * ligne = (char *) calloc( NB_CHAR,sizeof(char) ) ;
    char * motif ;
    fpos_t pos_fin ;
    existe_option_i = existe_option(liste_options, 'i') ;
    existe_option_n = existe_option(liste_options, 'n') ;
    existe_option_h = existe_option(liste_options, 'h') ;
    existe_option_v = existe_option(liste_options, 'v') ;
    /* lecture d'un caractere par caractere dans le fichier et constitue une ligne
    si on arrive a un saut de ligne */
    car = fgetc(fichier) ;
    while( car != EOF){
        if (car == '\n'){
            *(ligne + i ) = '\0' ;
            fgetpos(fichier, &pos_fin) ;
            indice_ligne += 1 ;
            indice_motif = 0 ; /* pour reparcourir la liste des motifs du début */
            motif_trouve = 0 ;
            i = 0 ;
            /* si ligne construit , on recherche le motif la dedans on faisant appel 
            a une des fonctions de recherche de motif dans une ligne 
            */
            while(indice_motif < nb_motifs){
                motif = *(motifs + indice_motif) ;
                if ( *(motif) == '^' && *(motif + strlen(motif) - 1) == '$' ){
                    if ( chercher_motif_debut_fin(motif, ligne, existe_option_i) ){
                        if (!existe_option_v){
                            if (!existe_option_h) /* on affiche le nom du fichier */
                                printf("\033[31;01m%s\033[34m:", nom_fichier) ;
                            if (existe_option_n)
                                printf("\033[32m%d\033[34m:",indice_ligne) ;

                            printf("\033[00m%s \n",ligne) ;

                            if(option_a_b->existe_option_A){
                                /*fprintf(stderr,"option A existe -> %d \n", option_a_b->n_A) ; */
                                affiche_n_lignes(fichier, nom_fichier, option_a_b->n_A, existe_option_h, existe_option_n, indice_ligne) ;
                                fsetpos(fichier, &pos_fin) ;    
                            }
                        }
                        motif_trouve = 1 ;
                        break ;   
                    }
                }
                else{
                    if ( *(motif) == '^'){
                        if ( chercher_motif_debut(motif, ligne, existe_option_i) ){
                            if (!existe_option_v){
                                if (!existe_option_h) /* on affiche le nom du fichier */
                                    printf("\033[31;01m%s\033[34m:", nom_fichier) ;
                                if (existe_option_n)
                                    printf("\033[32m%d\033[34m:",indice_ligne) ;

                                printf("\033[00m%s \n",ligne) ;

                                if(option_a_b->existe_option_A){
                                    /*fprintf(stderr,"option A existe -> %d \n", option_a_b->n_A) ; */
                                    affiche_n_lignes(fichier, nom_fichier, option_a_b->n_A, existe_option_h, existe_option_n, indice_ligne) ;
                                    fsetpos(fichier, &pos_fin) ;    
                                }
                            }
                            motif_trouve = 1 ;
                            break ;          
                        }
                    }
                    if ( *(motif + strlen(motif) - 1) == '$'){
                        if ( chercher_motif_fin(motif, ligne, existe_option_i) ){
                            if (!existe_option_v){
                                if (!existe_option_h) /* on affiche le nom du fichier */
                                    printf("\033[31;01m%s\033[34m:", nom_fichier) ;
                                if (existe_option_n)
                                    printf("\033[32m%d\033[34m:",indice_ligne) ;

                                printf("\033[00m%s \n",ligne) ; 

                                if(option_a_b->existe_option_A){
                                    /*fprintf(stderr,"option A existe -> %d \n", option_a_b->n_A) ; */
                                    affiche_n_lignes(fichier, nom_fichier, option_a_b->n_A, existe_option_h, existe_option_n, indice_ligne) ;
                                    fsetpos(fichier, &pos_fin) ;    
                                }
                            }
                            motif_trouve = 1 ;
                            break ;  
                        }    
                    }
                    else {
                        if ( chercher_motif(motif, ligne, existe_option_i) ){
                            if (!existe_option_v){
                                if (!existe_option_h) /* on affiche le nom du fichier */
                                    printf("\033[31;01m%s\033[34m:", nom_fichier) ;
                                if (existe_option_n)
                                    printf("\033[32m%d\033[34m:",indice_ligne) ;

                                printf("\033[00m%s \n",ligne) ;

                                if(option_a_b->existe_option_A){
                                    /*fprintf(stderr,"option A existe -> %d \n", option_a_b->n_A) ; */
                                    affiche_n_lignes(fichier, nom_fichier, option_a_b->n_A, existe_option_h, existe_option_n, indice_ligne) ;
                                    fsetpos(fichier, &pos_fin) ;    
                                }
                            }
                            motif_trouve = 1 ;
                            break ;
                        }
                    }
                }
                indice_motif += 1 ;
            }
            if (existe_option_v && !motif_trouve) /* si parcours tous les motifs sans trouver un dans ligne , affiche ligne */
                printf("\033[31;01m%s\033[34m:\033[00m%s \n",nom_fichier ,ligne) ;

            car =fgetc(fichier) ;
        }
        /* si plusieurs saut de lignes on les ignorent */
        while (car == '\n' ){
            car =fgetc(fichier) ;
            indice_ligne += 1 ;
        }
        *(ligne + i) = car ;
        i++;
        car = fgetc(fichier);
        /* teste si la fin du fichier , dernière ligne*/
        if (car == EOF){
            *(ligne + i ) = '\0' ;
            indice_ligne += 1 ;
            indice_motif = 0 ; /* pour reparcourir la liste des motifs du début */
            motif_trouve = 0 ;
            /* si ligne construit , recherche le motif la dedans on faisant appel 
            a une des fonctions de recherche de motif dans une ligne */
            while(indice_motif < nb_motifs){
                motif = *(motifs + indice_motif) ;
                if ( *(motif) == '^' && *(motif + strlen(motif) - 1) == '$' ){
                    if ( chercher_motif_debut_fin(motif, ligne, existe_option_i) ){
                        if (!existe_option_v){
                            if (!existe_option_h) /* on affiche le nom du fichier */
                                printf("\033[31;01m%s\033[34m:", nom_fichier) ;
                            if (existe_option_n)
                                printf("\033[32m%d\033[34m:",indice_ligne) ;

                            printf("\033[00m%s \n",ligne) ;
                        }
                        motif_trouve = 1 ;
                        break ;
                    }
                }
                else{
                    if ( *(motif) == '^'){
                        if ( chercher_motif_debut(motif, ligne, existe_option_i) ){
                            if (!existe_option_v){
                                if (!existe_option_h) /* on affiche le nom du fichier */
                                    printf("\033[31;01m%s\033[34m:", nom_fichier) ;
                                if (existe_option_n)
                                    printf("\033[32m%d\033[34m:",indice_ligne) ;

                                printf("\033[00m%s \n",ligne) ;  
                            }
                            motif_trouve = 1 ;        
                            break ;
                        }
                    }
                    if ( *(motif + strlen(motif) - 1) == '$'){
                        if ( chercher_motif_fin(motif, ligne, existe_option_i) ){
                            if (!existe_option_v){
                                if (!existe_option_h) /* on affiche le nom du fichier */
                                    printf("\033[31;01m%s\033[34m:", nom_fichier) ;
                                if (existe_option_n)
                                    printf("\033[32m%d\033[34m:",indice_ligne) ;

                                printf("\033[00m%s \n",ligne) ;
                            }
                            motif_trouve = 1 ;
                            break ;
                        }    
                    }
                    else {
                        if ( chercher_motif(motif, ligne, existe_option_i) ){
                            if (!existe_option_v){
                                if (!existe_option_h) /* on affiche le nom du fichier */
                                    printf("\033[31;01m%s\033[34m:", nom_fichier) ;
                                if (existe_option_n)
                                    printf("\033[32m%d\033[34m:",indice_ligne) ;

                                printf("\033[00m%s \n",ligne) ;
                            }
                            motif_trouve = 1 ;    
                            break ;
                        }
                    }
                }
                indice_motif += 1 ;
            }
            if (existe_option_v && !motif_trouve) /* si parcours tous les motifs sans trouver un dans ligne , affiche ligne */
                printf("\033[31;01m%s\033[34m:\033[00m%s \n",nom_fichier ,ligne) ;
        }
    }
    free(ligne) ;
    return ;
}

/*! Fonction qui recupere fichier par fichier dans les arguments donnés
 * et cherche le motif dans chacun des fichiers
 * ne renvoie rien
 */
void recherche_fichiers(int argc ,char **argv, char ** motifs, int nb_motifs, int indice_arg, char * liste_options, option_A_B * option_a_b){
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
        else{
            recherche_fichier(*(argv + i) ,fichier , motifs, nb_motifs, liste_options, option_a_b) ;
            fclose(fichier) ;
        }
    }
    return ;
}
