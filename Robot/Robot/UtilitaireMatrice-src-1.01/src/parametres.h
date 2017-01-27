
/**
 * Une application utilitaire de manipulation d'une matrice.
 *
 * Cette application permet d'afficher et modifier graphiquement les valeurs de la matrice. Les dimensions
 * de la matrice (lignes et colonnes) peuvent etre modifiees. Une douzaine d'operations sont proposees
 * via les boutons de l'interface. Certaines etant reservees aux matrices carrees. De maniere non exhaustive,
 * il est ainsi possible d'initialiser automatiquement la matrice avec des valeurs definies ou tirees au
 * hasard, d'additionner ou multiplier les cases de la matrice, de transposer la matrice ou encore, pour les
 * matrices carrees, d'elever la matrice au carre au cube, de calculer la trace et de verifier si elle est
 * symetrique. De plus, la matrice peut etre enregistree dans un fichier texte, pour etre rechargee plus tard
 * dans l'application, ou encore exportee au format CSV pour etre importee dans un tableur.
 *
 * AUTHOR: Guillaume Riviere (C) 2012
 * FILE: parametres.h
 */

#ifndef PARAMETRES_H
#define PARAMETRES_H

#define DIM_INIT  3
#define DIM_MINI  1
#define DIM_MAXI 10
#define DIM_STEP  1

#define VIRGULE_INIT 2
#define VIRGULE_MINI 0
#define VIRGULE_MAXI 9
#define VIRGULE_STEP 1

#define DATA_DEFAULT_DIR "./data/"

#define NONAME_TXT "Untitled.txt"
#define NONAME_CSV "Untitled.csv"

#endif /* PARAMETRES_H */
