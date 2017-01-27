
/* Fichier genere automatiquement. Ne pas modifier.
 * AUTHOR: Guillaume Riviere (C) 2011
 */

#ifndef __CALLBACKS_H
#define __CALLBACKS_H

/*-- CALLBACKS MAIN WINDOW --*/

G_MODULE_EXPORT void on_mainwindow_destroy (GtkObject *object, gpointer user_data) ;

G_MODULE_EXPORT void on_imagemenuitem_commandes_activate (GtkObject *object, gpointer user_data) ;
G_MODULE_EXPORT void on_imagemenuitem_about_activate (GtkObject *object, gpointer user_data) ;
G_MODULE_EXPORT void on_imagemenuitem_open_activate (GtkObject *object, gpointer user_data) ;
G_MODULE_EXPORT void on_imagemenuitem_save_activate (GtkObject *object, gpointer user_data) ;
G_MODULE_EXPORT void on_imagemenuitem_saveas_activate (GtkObject *object, gpointer user_data) ;
G_MODULE_EXPORT void on_imagemenuitem_export_csv_activate (GtkObject *object, gpointer user_data) ;

/*-- CALLBACKS COMMAND WINDOW --*/

G_MODULE_EXPORT void on_button_fermer_clicked (GtkObject *object, gpointer user_data) ;

G_MODULE_EXPORT void on_radiobutton_non_carree_clicked (GtkObject *object, gpointer user_data) ;
G_MODULE_EXPORT void on_radiobutton_carree_clicked (GtkObject *object, gpointer user_data) ;

G_MODULE_EXPORT void on_spinbutton_lignes_value_changed (GtkObject *object, gpointer user_data) ;
G_MODULE_EXPORT void on_spinbutton_colonnes_value_changed (GtkObject *object, gpointer user_data) ;
G_MODULE_EXPORT void on_spinbutton_chiffres_value_changed (GtkObject *object, gpointer user_data) ;

G_MODULE_EXPORT void on_button_redimensionner_clicked (GtkObject *object, gpointer user_data) ;

/* Operations */

G_MODULE_EXPORT void on_button_reset_clicked (GtkObject *object, gpointer user_data) ;
G_MODULE_EXPORT void on_button_fill_x_clicked (GtkObject *object, gpointer user_data) ;
G_MODULE_EXPORT void on_button_fill_alea_x_clicked (GtkObject *object, gpointer user_data) ;
G_MODULE_EXPORT void on_button_fill_alea_xx_clicked (GtkObject *object, gpointer user_data) ;
G_MODULE_EXPORT void on_button_add_x_clicked (GtkObject *object, gpointer user_data) ;
G_MODULE_EXPORT void on_button_mult_x_clicked (GtkObject *object, gpointer user_data) ;
G_MODULE_EXPORT void on_button_transpose_clicked (GtkObject *object, gpointer user_data) ;

G_MODULE_EXPORT void on_button_fill_idx_clicked (GtkObject *object, gpointer user_data) ;
G_MODULE_EXPORT void on_button_diag_alea_x_clicked (GtkObject *object, gpointer user_data) ;
G_MODULE_EXPORT void on_button_carre_clicked (GtkObject *object, gpointer user_data) ;
G_MODULE_EXPORT void on_button_cube_clicked (GtkObject *object, gpointer user_data) ;
G_MODULE_EXPORT void on_button_mult_idx_clicked (GtkObject *object, gpointer user_data) ;
G_MODULE_EXPORT void on_button_symetrique_clicked (GtkObject *object, gpointer user_data) ;
G_MODULE_EXPORT void on_button_trace_clicked (GtkObject *object, gpointer user_data) ;

#endif /* __CALLBACKS_H */
