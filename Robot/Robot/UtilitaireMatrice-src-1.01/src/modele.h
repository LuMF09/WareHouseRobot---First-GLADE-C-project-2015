
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
 * FILE: modele.h
 */

#ifndef MODELE_H
#define MODELE_H

#include <gtk/gtk.h>

#include "matrice.h"
#include "parametres.h"

typedef struct modele {
  Matrice mat ; /* Type defini dans matrice.h et matrice.h */
  int N ;
  int M ;
} *Modele ;

Modele modele_create () ;
void   modele_delete (Modele m) ;

void   modele_set_dimension (Modele m, int N, int M) ;
double modele_get_value (Modele m, int i, int j) ;
void   modele_set_value (Modele m, int i, int j, double val) ;

void modele_reset (Modele m) ;
void modele_fill_x (Modele m, double x) ;
void modele_fill_idx (Modele m, double x) ;
void modele_add_x (Modele m, double x) ;
void modele_mult_idx (Modele m, double x) ;
void modele_mult_x (Modele m, double x) ;
void modele_carre (Modele m) ;
void modele_cube (Modele m) ;
void modele_tranposer (Modele m) ;
char modele_symetrique (Modele m) ;
double modele_trace (Modele m) ;
void modele_fill_alea (Modele m, int min, int max) ;
void modele_diag_alea (Modele m, int min, int max) ;

void modele_set_from_file (Modele m, const char *filename) ;
void modele_save_to_file (Modele m, const char *filename) ;
void modele_export_to_csv_file (Modele m, const char *filename) ;

#endif /* MODELE_H */
