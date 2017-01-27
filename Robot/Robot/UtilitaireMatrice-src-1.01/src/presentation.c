
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
 * FILE: presentation.c
 */

#include <string.h> /* strdup, strcpy, strcat, strrchr */
#include <stdlib.h> /* malloc, free, exit */
#include <stdio.h>  /* sprintf */

#include "presentation.h"
#include "callbacks.h"

/* COMPILATION CONDITIONNELLE : Si le compilateur est celui de Visual Studio */
#ifdef _MSC_VER
#include "vs10settings.h"
#endif

Presentation presentation_create (GtkBuilder *builder) {
  int i, j ;
  char txt[20] ;
  Presentation res = (struct presentation *) malloc (sizeof(struct presentation)) ;

  /* Verifier le succes de l'allocation memoire */
  if (res == NULL) {
    perror ("Erreur allocation memoire") ;
    exit (1) ;
  }

  /* Recuperer les widgets construits par le builder GTK */
  res->mainwindow = GTK_WINDOW (gtk_builder_get_object (builder, "mainwindow"));
  res->commandwindow = GTK_WINDOW (gtk_builder_get_object (builder, "commandwindow"));
  res->aboutdialog = GTK_ABOUT_DIALOG (gtk_builder_get_object (builder, "aboutdialog"));

  /*-- MAIN WINDOW --*/

  /*-- Recuperer les widgets construits par le builder GTK */
  res->table = GTK_TABLE (gtk_builder_get_object (builder, "table1"));
  res->label_message = GTK_LABEL (gtk_builder_get_object (builder, "label_message"));

  /*-- Initialiser */

  /* Recuperer le titre actuel de la fenetre */
  strcpy (res->application_titre, gtk_window_get_title (res->mainwindow)) ;

  res->N = 0 ;
  res->M = 0 ;

  /* Initialisation du tableau qui contiendra tous les champs de saisie pour la matrice */
  for (i=0 ; i<DIM_MAXI ; i++) {
    for (j=0 ; j<DIM_MAXI ; j++) {
      /* Creer un nouveau GtkEntry */
      res->entries[i][j] = (GtkEntry *)gtk_entry_new () ;

      /* Lui associer une etiquette avec ses coordonnees */
      sprintf (txt, "( %d ; %d )", i, j) ;
      gtk_widget_set_tooltip_text (GTK_WIDGET(res->entries[i][j]), txt) ;
      gtk_widget_set_size_request (GTK_WIDGET(res->entries[i][j]), 80, 20) ;

      /* Le placer dans la grille d'agencement prevue a cet effet */
      gtk_table_attach (res->table, GTK_WIDGET(res->entries[i][j]), j, j+1, i, i+1, 0, 0, 0, 0) ;
    }
  }

  /* Redimenssioner la grille d'agencement des champs de saisie */
  presentation_set_dimension (res, DIM_INIT, DIM_INIT) ;

  /* Initialiser le nombre de chiffres affiches apres la virgule */
  presentation_set_chiffres_apres_virgule (res, VIRGULE_INIT) ;

  /*-- COMMAND WINDOW --*/

  /*-- Recuperer les widgets construits par le builder GTK */

  res->radio_non_carree = (GtkRadioButton *)gtk_builder_get_object (builder, "radiobutton_non_carree");
  res->radio_carree = (GtkRadioButton *)gtk_builder_get_object (builder, "radiobutton_carree");

  res->button_redimensionner = (GtkButton *) gtk_builder_get_object (builder, "button_redimensionner") ;

  res->spin_lignes = (GtkSpinButton *) gtk_builder_get_object (builder, "spinbutton_lignes");
  res->spin_colonnes = (GtkSpinButton *) gtk_builder_get_object (builder, "spinbutton_colonnes");
  res->spin_chiffres = (GtkSpinButton *) gtk_builder_get_object (builder, "spinbutton_chiffres");

  res->entry_x = (GtkEntry *)gtk_builder_get_object (builder, "entry_x");

  res->button_fill_idx = (GtkButton *) gtk_builder_get_object (builder, "button_fill_idx") ;
  res->button_diag_alea_x = (GtkButton *) gtk_builder_get_object (builder, "button_diag_alea_x") ;
  res->button_mult_idx = (GtkButton *) gtk_builder_get_object (builder, "button_mult_idx") ;
  res->button_carre = (GtkButton *) gtk_builder_get_object (builder, "button_carre") ;
  res->button_cube = (GtkButton *) gtk_builder_get_object (builder, "button_cube") ;
  res->button_symetrique = (GtkButton *) gtk_builder_get_object (builder, "button_symetrique") ;
  res->button_trace = (GtkButton *) gtk_builder_get_object (builder, "button_trace") ;

  res->label_resultat = (GtkLabel *)gtk_builder_get_object (builder, "label_resultat");

  /*-- Initialiser les widgets */

  /* Intervalle de valeurs pour la saisie de la dimension lignes */
  gtk_spin_button_set_range (res->spin_lignes, DIM_MINI, DIM_MAXI) ;
  gtk_spin_button_set_value (res->spin_lignes, DIM_INIT) ;
  gtk_spin_button_set_increments (res->spin_lignes, DIM_STEP, DIM_STEP) ;

  /* Intervalle de valeurs pour la saisie de la dimension colonnes */
  gtk_spin_button_set_range (res->spin_colonnes, DIM_MINI, DIM_MAXI) ;
  gtk_spin_button_set_value (res->spin_colonnes, DIM_INIT) ;
  gtk_spin_button_set_increments (res->spin_colonnes, DIM_STEP, DIM_STEP) ;

  /* Intervalle de valeurs pour la saisie du nombre de chiffres apres la virguel */
  gtk_spin_button_set_range (res->spin_chiffres, VIRGULE_MINI, VIRGULE_MAXI) ;
  gtk_spin_button_set_value (res->spin_chiffres, VIRGULE_INIT) ;
  gtk_spin_button_set_increments (res->spin_chiffres, VIRGULE_STEP, VIRGULE_STEP) ;

  /* Griser ou degriser le bouton de redimenssionnement */
  presentation_update_button_redimensionner (res) ;

  return res ;
}

void presentation_delete (Presentation p) {
  /* Liberer la memoire qui a ete allouee */
  free (p) ;
}

/*-- MAIN WINDOW functions --*/

void presentation_set_title (Presentation p, const char *filename) {
  char txt[100] ;

  /* Copier le nom du fichier */
  if (filename != NULL && strlen(filename)>0) {
    char *pos = strrchr(filename, '\\') ;
    
    if (pos == NULL)
      strcpy (txt, filename) ;
    else
      strcpy (txt, pos+1) ;
  }
  else
    strcpy (txt, NONAME_TXT) ;

  /* Ajouter le nom de l'application */
  strcat (txt, " - ") ;
  strcat (txt, p->application_titre) ;

  /* Remplacer le titre de la fenetre */
  gtk_window_set_title (p->mainwindow, txt) ;
}

void presentation_set_dimension (Presentation p, int n, int m) {
  int i, j ;
  char msg[20] ;

  /* Cacher tous les champs de saisie */
  for (i=0 ; i < p->N ; i++) {
    for (j=0 ; j < p->M ; j++) {
      if (p->entries[i][j] != NULL) {
	gtk_widget_hide (GTK_WIDGET(p->entries[i][j])) ;
      }
    }
  }

  /* Nouvelles dimmensions */
  p->N = n ;
  p->M = m ;

  /* Redimenssionner la grille d'agencement */
  gtk_table_resize (p->table, n, m) ;

  /* Montrer uniquement les champs de saisie utiles */
  for (i=0 ; i<n ; i++) {
    for (j=0 ; j<m ; j++) {
      gtk_widget_show (GTK_WIDGET(p->entries[i][j])) ;
    }
  }

  gtk_widget_queue_resize (GTK_WIDGET(p->mainwindow)) ;

  /* Mettre a jour le message d'affichage des dimension de la matrice */
  sprintf (msg, "Matrice %d x %d", n, m) ;
  presentation_set_label_message_text (p, msg) ;
}

void presentation_set_chiffres_apres_virgule (Presentation p, int nv) {
  /* Alterer la chaime de formatage des nombres de la matrice
  * qui definira le nombre de chiffre apres la virgule a afficher */
  sprintf (p->formatage, "%%.%df", nv) ;
  printf ("Nouveau format : \"%s\"\n", p->formatage) ;
}

void presentation_set_label_message_text (Presentation p, const char *txt) {
  gtk_label_set_text (p->label_message, txt) ;
}

/*-- COMMAND WINDOW functions */

void presentation_set_label_resultat_int (Presentation p, int val) {
  static char txt[20] ;
  sprintf (txt, " %d ", val) ;
  gtk_label_set_text (p->label_resultat, txt) ;
}

void presentation_set_label_resultat_real (Presentation p, double val) {
  static char txt[20] ;
  sprintf (txt, " %f ", val) ;
  gtk_label_set_text (p->label_resultat, txt) ;
}

void presentation_set_label_resultat_text (Presentation p, const char *txt) {
  gtk_label_set_text (p->label_resultat, txt) ;
}

void presentation_set_label_resultat_bool (Presentation p, char b) {
    gtk_label_set_text (p->label_resultat, (b ? "VRAI" : "FAUX")) ;
}

void presentation_update_button_redimensionner (Presentation p) {
  gboolean option_carree_checked = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (p->radio_carree)) ;
  int nb_lignes = gtk_spin_button_get_value_as_int (p->spin_lignes) ;
  int nb_colonnes = gtk_spin_button_get_value_as_int (p->spin_colonnes) ;
  char sont_differentes ;

  /* Verifier si les dimensions affichees dans les champs de specification
   * des dimensions (lignes et colonnes) sont differentes des dimensions
   * actuelles de la matrice */
  if (option_carree_checked)
    sont_differentes = ((nb_lignes != p->N) || (nb_lignes != p->M)) ;
  else
    sont_differentes = ((nb_lignes != p->N) || (nb_colonnes != p->M)) ;

  /* Degriser le bouton redimensionner si les dimensions precisees
   * dans les champs de saisie des dimensions sont differentes
   * de celles de la matrice actuelle.
   * Par contre, le bouton sera desactive si les dimensions ne sont pas differentes */
  gtk_widget_set_sensitive (GTK_WIDGET (p->button_redimensionner), sont_differentes) ;
}

void presentation_update_operations_buttons (Presentation p, char est_carree) {
  /* Griser/Degriser les boutons qui ne concernent que les matrices carrees */
  gtk_widget_set_sensitive (GTK_WIDGET (p->button_fill_idx), est_carree) ;
  gtk_widget_set_sensitive (GTK_WIDGET (p->button_diag_alea_x), est_carree) ;
  gtk_widget_set_sensitive (GTK_WIDGET (p->button_mult_idx), est_carree) ;
  gtk_widget_set_sensitive (GTK_WIDGET (p->button_carre), est_carree) ;
  gtk_widget_set_sensitive (GTK_WIDGET (p->button_cube), est_carree) ;
  gtk_widget_set_sensitive (GTK_WIDGET (p->button_symetrique), est_carree) ;
  gtk_widget_set_sensitive (GTK_WIDGET (p->button_trace), est_carree) ;
}

void presentation_set_visibility_spin_colonnes (Presentation p, char est_visible) {
  /* Griser/Degriser le champs de saisie de la dimension colonnes */
  gtk_widget_set_sensitive (GTK_WIDGET (p->spin_colonnes), est_visible) ;
}
