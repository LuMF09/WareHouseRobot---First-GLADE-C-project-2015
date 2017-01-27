
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
 * FILE: controle.c
 */

#include <stdlib.h> /* malloc, free, atof, exit */
#include <string.h> /* strcmp, strcpy */
#include <ctype.h>  /* isdigit, isspace */
#include <math.h>   /* round */

#include "controle.h"

/* COMPILATION CONDITIONNELLE : Si le compilateur est celui de Visual Studio */
#ifdef _MSC_VER
#include "vs10settings.h"
#endif

Controle controle_create (Presentation p, Modele m) {
  Controle res = (struct controle *) malloc (sizeof(struct controle)) ;

  /* Verifier le succes de l'allocation memoire */
  if (res == NULL) {
    perror ("Erreur allocation memoire") ;
    exit (1) ;
  }

  /* Initialiser les champs */
  res->m = m ;
  res->p = p ;

  /* Valeurs par defaut pour les chemins */
  strcpy (res->current_save_folder, DATA_DEFAULT_DIR) ;
  strcpy (res->current_save_filename, "") ;
  strcpy (res->current_export_folder, DATA_DEFAULT_DIR) ;

  /* Mettre a jour le titre de la fenetre */
  presentation_set_title (p, res->current_save_filename) ;

  return res ;
}

void controle_delete (Controle c) {
  /* Liberer la memoire qui a ete allouee */
  free (c) ;
}

void controle_refresh_matrice_view (Controle c) {
  int i, j ;
  double val ;
  char txt[256] ;

  for (i=0 ; i < c->p->N ; i++) {
    for (j=0 ; j < c->p->M ; j++) {
      /* Recuperer la valeur de l'element de la matrice */
      val = modele_get_value(c->m, i, j) ;

      /* Preparer la chaine de caractere
       * selon le formatage des nombres de la matrice 
       * qui definit le nombre de chiffres apres la virgule */
      sprintf (txt, c->p->formatage, val) ;

      /* Afficher la valeur dans le champs de saisie */
      gtk_entry_set_text (c->p->entries[i][j], txt) ;
    }
  }
}

void controle_refresh_element_view (Controle c, int i, int j) {
  double val ;
  char txt[20] ;

  /* Recuperer la valeur de la case de la matrice concernee */
  val = modele_get_value(c->m, i, j) ;

  /* Preparer la chaine de caractere
   * selon le formatage des nombres de la matrice 
   * qui definit le nombre de chiffres apres la virgule */
  sprintf (txt, c->p->formatage, val) ;

  /* Afficher la valeur */
  gtk_entry_set_text (c->p->entries[i][j], txt) ;
}

char est_nombre_reel (const char *s) {
  int i, len ;
  char res = 1 ; /* true */
  int nb_separateurs = 0 ; /* separateur decimal */
  int nb_chiffres = 0 ;

  len = strlen(s) ;
  i=0 ;
  
  /* Ignorer les blancs eventuels */
  while (i<len && isspace(s[i]))
    i++ ;

  /* Ignorer un signe + ou - eventuel */
  if (i<len && (s[i]=='+' || s[i]=='-'))
    i++ ;

  /* Lire les chiffres du nombre reel */
  while (i<len && res) {
    if (isdigit(s[i]))
      nb_chiffres++ ;
    else if (s[i] == '.') { /* separateur decimal */
      if (nb_separateurs == 0 && nb_chiffres > 0)
	nb_separateurs++ ;
      else
	res = 0 ; /* false */
    }
    else if (isspace(s[i]) && nb_chiffres>0)
      i = len ; /* pour stopper la boucle */
    else
      res = 0 ; /* false */
    i++ ;
  }

  return res ;
}

void controle_update_value (Controle c, int i, int j) {
  /* Recuperer le champs de la matrice */
  GtkEntry *entry = c->p->entries[i][j] ;
  const char *s = gtk_entry_get_text (entry) ;

  /* Si le champs est vide ou que ce n'est pas un reel */
  if (!strcmp(s, "") || !est_nombre_reel(s)) {
    /* Remettre en place la valeur du modele */
    controle_refresh_element_view (c, i, j) ;
  }
  else {
    /* Mettre la valeur dans le modele */
    modele_set_value (c->m, i, j, atof(s)) ;
  }
}

void controle_check_values (Controle c) {
  int i, j ;

  /* Verifier tous les champs de saisie de la matrice */
  for (i=0 ; i < c->p->N ; i++) {
    for (j=0 ; j < c->p->M ; j++) {
      controle_update_value (c, i, j) ;
    }
  }
}

void controle_calculer (Controle c, OPERATION op) {
  char reussie = 1 ; /* true */
  char maj_matrice = 0 ; /* false */

  /* Si l'operation utilise la valeur x */
  if (op == OP_FILL_X
      || op == OP_FILL_IDX
      || op == OP_ADD_X
      || op == OP_MULT_X
      || op == OP_MULT_IDX
      || op == OP_FILL_ALEA_X
      || op == OP_FILL_ALEA_XX
      || op == OP_DIAG_ALEA_X) {
    /* Champs de la valeur x */
    const char *sx = gtk_entry_get_text (c->p->entry_x) ;

    if (!strcmp(sx, "")) { /* Si le champs est vide */
      presentation_set_label_resultat_text (c->p, "attention, x doit etre defini") ;
      reussie = 0 ; /* false */
    }
    else if (!est_nombre_reel(sx)) { /* Si le champs n'est pas un nombre reel */
      presentation_set_label_resultat_text (c->p, "attention, x doit etre un nombre") ;
      reussie = 0 ; /* false */
    }
    else {
      double x = atof(sx) ;
      int max ;

      switch (op) {
      case OP_FILL_X :
	modele_fill_x (c->m, x) ;
	break ;
      case OP_FILL_IDX :
	modele_fill_idx (c->m, x) ;
	break ;
      case OP_ADD_X :
	controle_check_values (c) ;
	modele_add_x (c->m, x) ;
	break ;
      case OP_MULT_X :
	controle_check_values (c) ;
	controle_check_values (c) ;
	modele_mult_x (c->m, x) ;
	break ;
      case OP_MULT_IDX :
	controle_check_values (c) ;
	modele_mult_idx (c->m, x) ;
	break ;
      case OP_FILL_ALEA_X :	
	max = (int)round (x) ; /* Determiner la valeur ENTIERE maximum pour le tirage aleatoire */
	modele_fill_alea (c->m, 0, max) ;
	break ;
      case OP_FILL_ALEA_XX :
	max = (int)round (x) ; /* Determiner la valeur ENTIERE maximum pour le tirage aleatoire */
	modele_fill_alea (c->m, -max, max) ;
	break ;
      case OP_DIAG_ALEA_X :
	controle_check_values (c) ;
	max = (int)round (x) ; /* Determiner la valeur ENTIERE maximum pour le tirage aleatoire */
	modele_diag_alea (c->m, 0, max) ;
	break ;
      default:
	fprintf (stderr, "controle_calculer: operation inconnue\n") ;
	reussie = 0 ; /* false */
      }
      maj_matrice = 1 ;
    }
  }
  else { /* Si l'operation n'a pas besoin de x */
    char est_sym ;
    double tr ;

    switch (op) {
    case OP_RESET :
      modele_reset (c->m) ;
      maj_matrice = 1 ;
      break ;
    case OP_CARRE :
      controle_check_values (c) ;
      modele_carre (c->m) ;
      maj_matrice = 1 ;
      break ;
    case OP_CUBE :
      controle_check_values (c) ;
      modele_cube (c->m) ;
      maj_matrice = 1 ;
      break ;
    case OP_TRANS :
      controle_check_values (c) ;
      modele_tranposer (c->m) ;
      presentation_set_dimension (c->p, c->m->N, c->m->M) ;
      maj_matrice = 1 ;
      break ;
    case OP_SYM:
      controle_check_values (c) ;
      est_sym = modele_symetrique (c->m) ;
      presentation_set_label_resultat_bool (c->p, est_sym) ;
      break;
    case OP_TRACE:
      controle_check_values (c) ;
      tr = modele_trace (c->m) ;
      presentation_set_label_resultat_real (c->p, tr) ;
      break ;
    default:
      fprintf (stderr, "controle_calculer: operation inconnue\n") ;
      reussie = 0 ; /* false */
    }
  }

  /* Si le calcul n'a pas echoue et que l'affichage de la matrice doit etre recharge */
  if (reussie && maj_matrice) {
    presentation_set_label_resultat_text (c->p, "operation reussie") ;
    controle_refresh_matrice_view (c) ;
  }
}

void controle_redimensionner (Controle c) {
  gboolean option_carree_checked = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (c->p->radio_carree)) ;
  int nb_lignes, nb_colonnes ;

  /* Nouveau nombre de lignes souhaite */
  nb_lignes = gtk_spin_button_get_value_as_int (c->p->spin_lignes) ;

  /* Nouveau nombre de colonnes souhaite */
  if (option_carree_checked)
    nb_colonnes = nb_lignes ;
  else
    nb_colonnes = gtk_spin_button_get_value_as_int (c->p->spin_colonnes) ;

  /* Griser/Degriser les boutons des operations reservees pour les matrices carrees */
  presentation_update_operations_buttons (c->p, nb_lignes == nb_colonnes) ;

  /* Redimensionner le modele */
  modele_set_dimension (c->m, nb_lignes, nb_colonnes) ;

  /* Redimensionner la grille pour l'affichage de la matrice */
  presentation_set_dimension (c->p, nb_lignes, nb_colonnes) ;

  /* Rafraichir l'affichage de la matrice */
  controle_refresh_matrice_view (c) ;
  presentation_set_label_resultat_text (c->p, "") ;
}

void controle_ouvrir (Controle c) {
  int reponse ;
  GtkFileChooser *dialog ;
  GtkFileFilter *filter_txt, *filter_all ;

  /* Creer une nouvelle fenetre de dialogue de selection de fichier */
  dialog = (GtkFileChooser *)gtk_file_chooser_dialog_new ("Ourvir matrice...",
							  NULL,
							  GTK_FILE_CHOOSER_ACTION_OPEN,
							  GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
							  GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
							  NULL);

  /* Filtre pour noms de fichiers en .txt */
  filter_txt = gtk_file_filter_new();
  gtk_file_filter_set_name(filter_txt, "Fichiers textes (*.txt)");
  gtk_file_filter_add_pattern(filter_txt, "*.txt");
  gtk_file_chooser_add_filter(dialog, filter_txt);

  /* Filtre pour tout nom de fichier */
  filter_all = gtk_file_filter_new();
  gtk_file_filter_set_name(filter_all, "Tous les fichiers (*.*)");
  gtk_file_filter_add_pattern(filter_all, "*");
  gtk_file_chooser_add_filter(dialog, filter_all);

  /* Specifier le repertoire de depart */
  gtk_file_chooser_set_current_folder (dialog, c->current_save_folder) ;

  /* Lancer la fenetre de dialogue de selection de fichier */
  reponse = gtk_dialog_run (GTK_DIALOG (dialog)) ;

  /* Si l'utilisateur a valide son choix (c.a.d. pas annule) */
  if (reponse == GTK_RESPONSE_ACCEPT) {
    int nb_lignes, nb_colonnes ;
    char *filename = gtk_file_chooser_get_filename (dialog) ;          /* Chemin absolu du nom du fichier selectionne par l'utilisateur */
    char *folder = gtk_file_chooser_get_current_folder (dialog) ; /* Chemin absolu du repertoire du fichier selectionne par l'utilisateur */

    /* Charger le fichier */
    modele_set_from_file (c->m, filename) ;

    /* Maj des dimensions */
    nb_lignes = c->m->N ;
    nb_colonnes = c->m->M ;
    presentation_set_dimension (c->p, nb_lignes, nb_colonnes) ;

    /* Degriser/Griser les boutons (si la matrice est carree ou non) */
    presentation_update_operations_buttons (c->p, nb_lignes == nb_colonnes) ;

    /* Degriser/Griser le bouton de redimensionnement */
    presentation_update_button_redimensionner (c->p) ;

    /* Maj des valeurs affichees */
    controle_refresh_matrice_view (c) ;

    /* Pour se souvenir des chemins */
    strcpy(c->current_save_filename, filename) ;
    strcpy(c->current_save_folder, folder) ;

    /* Liberer la memoire qui a ete allouee */
    /* ATTENTION d'utiliser g_free() car a ete alloue avec g_malloc()
     * dans les fonctions gtk_file_chooser_get_...() */
    g_free (filename);
    g_free (folder);

    /* Mettre a jour le titre de la fenetre */
    presentation_set_title (c->p, c->current_save_filename) ;
  }

  /* Destruction de la fenetre de dialogue */
  gtk_widget_destroy (GTK_WIDGET(dialog));
}

void controle_enregistrer (Controle c) {
  /* Si aucun nom n'a ete precedemment selectionne (cad si la chaine est vide) */
  if (strlen(c->current_save_filename) == 0) {
    /* Ouvrir une boite de dialogue pour demander de selectionner un nom de fichier */
    controle_enregistrer_sous (c) ;
  }
  else {
    /* Verifier les valeurs presentes dans les champs de la matrice */
    controle_check_values (c) ;

    /* Enregistrer dans le nom de fichier deja selectionne */
    modele_save_to_file (c->m, c->current_save_filename) ;
  }
}

void controle_enregistrer_sous (Controle c) {
  int reponse ;
  GtkFileChooser *dialog ;
  GtkFileFilter *filter_txt, *filter_all ;

  /* Creer une nouvelle fenetre de dialogue de selection de fichier */
  dialog = (GtkFileChooser *)gtk_file_chooser_dialog_new ("Save File",
							  NULL,
							  GTK_FILE_CHOOSER_ACTION_SAVE,
							  GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
							  GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
							  NULL);

  /* Filtre pour noms de fichiers en .txt */
  filter_txt = gtk_file_filter_new();
  gtk_file_filter_set_name(filter_txt, "Fichiers textes (*.txt)");
  gtk_file_filter_add_pattern(filter_txt, "*.txt");
  gtk_file_chooser_add_filter(dialog, filter_txt);

  /* Filtre pour tout nom de fichier */
  filter_all = gtk_file_filter_new();
  gtk_file_filter_set_name(filter_all, "Tous les fichiers (*.*)");
  gtk_file_filter_add_pattern(filter_all, "*");
  gtk_file_chooser_add_filter(dialog, filter_all);

  /* Activer le mode de confirmation au cas ou le fichier existe deja */
  gtk_file_chooser_set_do_overwrite_confirmation (dialog, TRUE);

  /* Si aucun nom n'a ete precedemment selectionne (cad si la chaine est vide) */
  if (strlen(c->current_save_filename) == 0) {
    gtk_file_chooser_set_current_name (dialog, NONAME_TXT);
    gtk_file_chooser_set_current_folder (dialog, c->current_save_folder) ;
  }
  else {
    /* Remettre le nom du fichier precedemment selectionne */
    gtk_file_chooser_set_filename (dialog, c->current_save_filename);
  }

  /* Lancer la fenetre de dialogue de selection de fichier */
  reponse = gtk_dialog_run (GTK_DIALOG (dialog)) ;

  /* Si l'utilisateur a valide son choix (c.a.d. pas annule) */
  if (reponse == GTK_RESPONSE_ACCEPT) {
    char *filename = gtk_file_chooser_get_filename (dialog);           /* Chemin absolu du nom du fichier selectionne par l'utilisateur */
    char *folder = gtk_file_chooser_get_current_folder (dialog) ; /* Chemin absolu du repertoire du fichier selectionne par l'utilisateur */

    /* Verifier les valeurs presentes dans les champs de la matrice */
    controle_check_values (c) ;

    /* Enregistrer dans le fichier */
    modele_save_to_file (c->m, filename);

    /* Pour se souvenir des chemins */
    strcpy(c->current_save_filename, filename) ;
    strcpy(c->current_save_folder, folder) ;

    /* Liberer la memoire qui a ete allouee */
    /* ATTENTION d'utiliser g_free() car a ete alloue avec g_malloc()
     * dans les fonctions gtk_file_chooser_get_...() */
    g_free (filename);
    g_free (folder) ;

    /* Mettre a jour le titre de la fenetre */
    presentation_set_title (c->p, c->current_save_filename) ;
  }

  /* Destruction de la fenetre de dialogue */
  gtk_widget_destroy (GTK_WIDGET(dialog));

}

void controle_exporter_csv (Controle c) {
  int reponse ;
  GtkFileChooser *dialog ;
  GtkFileFilter *filter_csv, *filter_all ;

  /* Creer une nouvelle fenetre de dialogue de selection de fichier */
  dialog = (GtkFileChooser *)gtk_file_chooser_dialog_new ("Save File",
							  NULL,
							  GTK_FILE_CHOOSER_ACTION_SAVE,
							  GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
							  GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
							  NULL);

  /* Filtre pour noms de fichiers en .csv */
  filter_csv = gtk_file_filter_new();
  gtk_file_filter_set_name(filter_csv, "Fichiers textes (*.csv)");
  gtk_file_filter_add_pattern(filter_csv, "*.csv");
  gtk_file_chooser_add_filter(dialog, filter_csv);

  /* Filtre pour tout nom de fichier */
  filter_all = gtk_file_filter_new();
  gtk_file_filter_set_name(filter_all, "Tous les fichiers (*.*)");
  gtk_file_filter_add_pattern(filter_all, "*");
  gtk_file_chooser_add_filter(dialog, filter_all);

  /* Activer le mode de confirmation au cas ou le fichier existe deja */
  gtk_file_chooser_set_do_overwrite_confirmation (dialog, TRUE);

  /* Nom et repertoire de depart */
  gtk_file_chooser_set_current_name (dialog, NONAME_CSV);
  gtk_file_chooser_set_current_folder (dialog, c->current_export_folder) ;

  /* Lancer la fenetre de dialogue de selection de fichier */
  reponse = gtk_dialog_run (GTK_DIALOG (dialog)) ;

  /* Si l'utilisateur a valide son choix (c.a.d. pas annule) */
  if (reponse == GTK_RESPONSE_ACCEPT) {
    char *filename = gtk_file_chooser_get_filename (dialog) ;          /* Chemin absolu du nom du fichier selectionne par l'utilisateur */
    char *folder = gtk_file_chooser_get_current_folder (dialog) ; /* Chemin absolu du repertoire du fichier selectionne par l'utilisateur */

    /* Verifier les valeurs presentes dans les champs de la matrice */
    controle_check_values (c) ;

    /* Exporter dans le fichier */
    modele_export_to_csv_file (c->m, filename);

    /* Pour se souvenir du chemin du repertoire */
    strcpy(c->current_export_folder, folder) ;

    /* Liberer la memoire qui a ete allouee */
    /* ATTENTION d'utiliser g_free() car a ete alloue avec g_malloc()
     * dans les fonctions gtk_file_chooser_get_...() */
    g_free (filename);
    g_free (folder) ;
  }

  /* Destruction de la fenetre de dialogue */
  gtk_widget_destroy (GTK_WIDGET(dialog));
}

