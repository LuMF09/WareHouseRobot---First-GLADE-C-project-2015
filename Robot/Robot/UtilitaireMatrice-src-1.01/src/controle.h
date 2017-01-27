

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
 * FILE: controle.h
 */

#ifndef CONTROLE_H
#define CONTROLE_H

#include "modele.h"
#include "presentation.h"

typedef enum operation {
  OP_RESET,
  OP_FILL_X,
  OP_FILL_IDX,
  OP_ADD_X,
  OP_MULT_X,
  OP_MULT_IDX,
  OP_CARRE,
  OP_CUBE,
  OP_TRANS,
  OP_FILL_ALEA_X,
  OP_FILL_ALEA_XX,
  OP_DIAG_ALEA_X,
  OP_SYM,
  OP_TRACE
} OPERATION ;

typedef struct controle {
  Presentation p ;
  Modele m ;
  char current_save_folder[512] ;
  char current_save_filename[512] ;
  char current_export_folder[512] ;
} *Controle ;

Controle controle_create (Presentation p, Modele m) ;
void     controle_delete (Controle c) ;

void controle_refresh_matrice_view (Controle c) ;
void controle_refresh_element_view (Controle c, int i, int j) ;

void controle_update_value (Controle c, int i, int j) ;
void controle_check_values (Controle c) ;

void controle_calculer (Controle c, OPERATION op) ;
void controle_redimensionner (Controle c) ;

void controle_ouvrir (Controle c) ;
void controle_enregistrer (Controle c) ;
void controle_enregistrer_sous (Controle c) ;
void controle_exporter_csv (Controle c) ;

#endif /* CONTROLE_H */
