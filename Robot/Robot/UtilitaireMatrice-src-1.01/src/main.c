
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
 * FILE: main.c
 */

#include <locale.h> /* setlocale */

#include <gtk/gtk.h>
#include "callbacks.h"

#include "presentation.h"
#include "modele.h"
#include "controle.h"

/* Variables Globales */
Presentation G_presentation = NULL ;
Controle     G_controle = NULL ;

int main (int argc, char *argv[]) {
  GtkBuilder   *builder ;
  Presentation  p1 ;
  Controle      c1 ;
  Modele        m1 ;

  gtk_init (&argc, &argv);

  /* Creer tous les widgets grace au builder GTK */
  builder = gtk_builder_new ();
  gtk_builder_add_from_file (builder, "matrice.glade", NULL);
  gtk_builder_connect_signals (builder, NULL);

  /*------------*/

  /* S'assurer que le separateur decimal soit le point (et non la virgule) */
  setlocale(LC_NUMERIC, "C");

  /* Presentation */
  p1 = presentation_create (builder) ;

  /* Modele */
  m1 = modele_create () ;
  modele_set_dimension (m1, DIM_INIT, DIM_INIT) ;

  /* Controle */
  c1 = controle_create (p1, m1) ;
  controle_refresh_matrice_view (c1) ;

  /* Globales pour callbacks.c */
  G_presentation = p1 ;
  G_controle = c1 ;

  /*------------*/

  gtk_widget_show (GTK_WIDGET(p1->mainwindow)); /* ATTENTION */

  /* Lancer la boucle GTK */
  gtk_main ();

  /* La boucle GTK est terminee, detruire maintenant tous les widgets */
  g_object_unref (G_OBJECT (builder));

  /* Fin normale du programme */
  return 0;
}
