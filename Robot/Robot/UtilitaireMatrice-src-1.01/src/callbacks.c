
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
 * FILE: callbacks.c
 */

#include <gtk/gtk.h>
#include "callbacks.h"

#include "presentation.h"
#include "controle.h"

/* Variables Globales externes (declarees dans main.c) */
extern Presentation G_presentation ;
extern Controle     G_controle ;

/*-- CALLBACKS MAIN WINDOW --*/

G_MODULE_EXPORT void on_mainwindow_destroy (GtkObject *object, gpointer user_data) {
  /* Envoyer le signal de destruction de la fenetre principale */
  gtk_object_destroy (GTK_OBJECT(G_presentation->commandwindow)) ;

  /* Stopper la boucle GTK */
  gtk_main_quit () ;
}

G_MODULE_EXPORT void on_imagemenuitem_commandes_activate (GtkObject *object, gpointer user_data) {
  gtk_widget_show(GTK_WIDGET(G_presentation->commandwindow)) ;
}

G_MODULE_EXPORT void on_imagemenuitem_about_activate (GtkObject *object, gpointer user_data) {
  gtk_widget_show(GTK_WIDGET(G_presentation->aboutdialog)) ;
}

G_MODULE_EXPORT void on_imagemenuitem_open_activate (GtkObject *object, gpointer user_data) {
  controle_ouvrir (G_controle) ;
}

G_MODULE_EXPORT void on_imagemenuitem_save_activate (GtkObject *object, gpointer user_data) {
  controle_enregistrer (G_controle) ;
}

G_MODULE_EXPORT void on_imagemenuitem_saveas_activate (GtkObject *object, gpointer user_data) {
  controle_enregistrer_sous (G_controle) ;
}

G_MODULE_EXPORT void on_imagemenuitem_export_csv_activate (GtkObject *object, gpointer user_data) {
  controle_exporter_csv (G_controle) ;
}

/*-- CALLBACKS COMMAND WINDOW --*/

G_MODULE_EXPORT void on_button_fermer_clicked (GtkObject *object, gpointer user_data) {
  gtk_widget_hide(GTK_WIDGET(G_presentation->commandwindow)) ;
}

G_MODULE_EXPORT void on_radiobutton_non_carree_clicked (GtkObject *object, gpointer user_data) {
  presentation_set_visibility_spin_colonnes (G_presentation, 1) ; /* vrai */
}

G_MODULE_EXPORT void on_radiobutton_carree_clicked (GtkObject *object, gpointer user_data) {
  presentation_set_visibility_spin_colonnes (G_presentation, 0) ; /* faux */
}

G_MODULE_EXPORT void on_spinbutton_lignes_value_changed (GtkObject *object, gpointer user_data) {
  if (G_presentation != NULL)
    presentation_update_button_redimensionner (G_presentation) ;
}

G_MODULE_EXPORT void on_spinbutton_colonnes_value_changed (GtkObject *object, gpointer user_data) {
  if (G_presentation != NULL)
    presentation_update_button_redimensionner (G_presentation) ;
}

G_MODULE_EXPORT void on_spinbutton_chiffres_value_changed (GtkObject *object, gpointer user_data) {
  if (G_controle != NULL) {
    int nb_chiffres = gtk_spin_button_get_value_as_int (G_presentation->spin_chiffres) ;
    presentation_set_chiffres_apres_virgule (G_presentation, nb_chiffres) ;
    controle_refresh_matrice_view (G_controle) ;
  }
}

G_MODULE_EXPORT void on_button_redimensionner_clicked (GtkObject *object, gpointer user_data) {
  controle_redimensionner (G_controle) ;
  presentation_update_button_redimensionner (G_presentation) ;
}

G_MODULE_EXPORT void on_button_reset_clicked (GtkObject *object, gpointer user_data) {
  controle_calculer (G_controle, OP_RESET) ;
}

G_MODULE_EXPORT void on_button_fill_x_clicked (GtkObject *object, gpointer user_data) {
  controle_calculer (G_controle, OP_FILL_X) ;
}

G_MODULE_EXPORT void on_button_fill_alea_x_clicked (GtkObject *object, gpointer user_data) {
  controle_calculer (G_controle, OP_FILL_ALEA_X) ;
}

G_MODULE_EXPORT void on_button_fill_alea_xx_clicked (GtkObject *object, gpointer user_data) {
  controle_calculer (G_controle, OP_FILL_ALEA_XX) ;
}

G_MODULE_EXPORT void on_button_add_x_clicked (GtkObject *object, gpointer user_data) {
  controle_calculer (G_controle, OP_ADD_X) ;
}

G_MODULE_EXPORT void on_button_mult_x_clicked (GtkObject *object, gpointer user_data) {
  controle_calculer (G_controle, OP_MULT_X) ;
}

G_MODULE_EXPORT void on_button_transpose_clicked (GtkObject *object, gpointer user_data) {
  controle_calculer (G_controle, OP_TRANS) ;
}

G_MODULE_EXPORT void on_button_fill_idx_clicked (GtkObject *object, gpointer user_data) {
  controle_calculer (G_controle, OP_FILL_IDX) ;
}

G_MODULE_EXPORT void on_button_diag_alea_x_clicked (GtkObject *object, gpointer user_data) {
  controle_calculer (G_controle, OP_DIAG_ALEA_X) ;
}

G_MODULE_EXPORT void on_button_carre_clicked (GtkObject *object, gpointer user_data) {
  controle_calculer (G_controle, OP_CARRE) ;
}

G_MODULE_EXPORT void on_button_cube_clicked (GtkObject *object, gpointer user_data) {
  controle_calculer (G_controle, OP_CUBE) ;
}

G_MODULE_EXPORT void on_button_mult_idx_clicked (GtkObject *object, gpointer user_data) {
  controle_calculer (G_controle, OP_MULT_IDX) ;
}

G_MODULE_EXPORT void on_button_symetrique_clicked (GtkObject *object, gpointer user_data) {
  controle_calculer (G_controle, OP_SYM) ;
}

G_MODULE_EXPORT void on_button_trace_clicked (GtkObject *object, gpointer user_data) {
  controle_calculer (G_controle, OP_TRACE) ;
}
