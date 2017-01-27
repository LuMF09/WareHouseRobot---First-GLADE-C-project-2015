
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
 * FILE: presentation.h
 */

#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <gtk/gtk.h>

#include "parametres.h"

typedef struct presentation {

  GtkWindow *mainwindow ;
  GtkWindow *commandwindow ;
  GtkAboutDialog *aboutdialog ;

  int N ; /* Nombre de lignes */
  int M ; /* Nombre de colonnes */

  char formatage[20] ;
  char application_titre[100] ;

  /*-- MAIN WINDOW widgets --*/

  GtkTable *table ;
  GtkEntry *entries[DIM_MAXI][DIM_MAXI] ;
  GtkLabel *label_message ;

  /*-- COMMAND WINDOW widgets --*/

  GtkRadioButton *radio_non_carree ;
  GtkRadioButton *radio_carree ;

  GtkButton *button_redimensionner ;

  GtkSpinButton *spin_lignes ;
  GtkSpinButton *spin_colonnes ;
  GtkSpinButton *spin_chiffres ;

  GtkEntry *entry_x ;

  GtkButton *button_fill_idx ;
  GtkButton *button_diag_alea_x ;
  GtkButton *button_mult_idx ;
  GtkButton *button_carre ;
  GtkButton *button_cube ;
  GtkButton *button_symetrique ;
  GtkButton *button_trace ;

  GtkLabel  *label_resultat ;

} *Presentation ;


Presentation presentation_create (GtkBuilder *builder) ;
void         presentation_delete(Presentation p) ;

/*-- MAIN WINDOW functions --*/

void presentation_set_title (Presentation p, const char *filename) ;

void presentation_set_dimension (Presentation p, int n, int m) ;
void presentation_set_chiffres_apres_virgule (Presentation p, int nv) ;
void presentation_set_label_message_text (Presentation p, const char *txt) ;

/*-- COMMAND WINDOW functions */

void presentation_set_label_resultat_int (Presentation p, int val) ;
void presentation_set_label_resultat_real (Presentation p, double val) ;
void presentation_set_label_resultat_text (Presentation p, const char *txt) ;
void presentation_set_label_resultat_bool (Presentation p, char b) ;

void presentation_update_button_redimensionner (Presentation p) ;
void presentation_update_operations_buttons (Presentation p, char est_carree) ;
void presentation_set_visibility_spin_colonnes (Presentation p, char est_visible) ;

#endif /* PRESENTATION_H */
