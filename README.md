# MyGREP
Version personnel de la commande UNIX grep 

## Compilation 
Pour obtenir le programme exécutable :

commande : make

Pour supprimer l'exécutable et les fichiers obtenus par la compilation :

commande : make clean

## Version Actuelle :

le programme est capable de chercher un ou plusieurs motifs dans un ou plusieurs fichiers 

options pris en charge : -H -v -l -L -c -A -B -e -i -n -h

le programme reconnaît les deux caractères ^ et $ dans un motif

## Utilisation de la commande :

Pour tester la commande:

./mygrep [option(s)] motif [-e motif] exemple.txt  exemple2.txt <!-- pour chercher le motif 'motif' dans le fichier "exemple.txt" et "exemple2.txt" !-->

Pour afficher le menu d'aide complet :

./mygrep -H
 
