#ifndef __CALLBACKS_H
#define __CALLBACKS_H
#include <gtk/gtk.h>

G_MODULE_EXPORT void on_window1_destroy (GtkObject *object, gpointer user_data) ;
G_MODULE_EXPORT void on_button_start_clicked (GtkObject *object, gpointer user_data) ;
G_MODULE_EXPORT void on_button_stop_clicked (GtkObject *object, gpointer user_data) ; 
G_MODULE_EXPORT void on_button_gauche_clicked (GtkObject *object, gpointer user_data) ; 
G_MODULE_EXPORT void on_button_droite_clicked (GtkObject *object, gpointer user_data) ; 
G_MODULE_EXPORT void on_button_haut_clicked (GtkObject *object, gpointer user_data) ; 
G_MODULE_EXPORT void on_button_bas_clicked (GtkObject *object, gpointer user_data) ; 
G_MODULE_EXPORT void on_button_charge_clicked (GtkObject *object, gpointer user_data) ; 
G_MODULE_EXPORT void on_radiobutton_manuel_toggled (GtkObject *object, gpointer user_data) ;
G_MODULE_EXPORT void on_radiobutton_automatique_toggled (GtkObject *object, gpointer user_data);

#endif /* __CALLBACKS_H */