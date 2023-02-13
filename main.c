
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    if (argc < 3){
        printf("Usage: %s <motif> <fichier> \n",*(argv)) ;
        exit(EXIT_FAILURE);
    }
    else{
        printf("motif = %s et fichier = %s \n",*(argv + 1), *(argv + 2));
    }

    exit(EXIT_SUCCESS); 
}