
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
 * FILE: modele.c
 */

#include <stdlib.h> /* malloc, free, exit */

#include "modele.h"
#include "hasard.h"

Modele modele_create () {
  Modele res = (struct modele *) malloc (sizeof(struct modele)) ;

  /* Verifier le succes de l'allocation memoire */
  if (res == NULL) {
    perror ("Erreur allocation memoire") ;
    exit (1) ;
  }

  /* Initialiser les champs */
  res->mat = NULL ;
  res->N = 0 ;
  res->M = 0 ;

  hasard_initialiser_graine () ;

  return res ;
}

void modele_delete (Modele m) {
  /* Detruire la matrice si elle existe */
  if (m->mat != NULL)
    matrice_detruire (m->mat) ;

  /* Liberer la memoire qui a ete allouee */
  free (m) ;
}

void modele_set_dimension (Modele m, int N, int M) {
  /* Creer une nouvelle structure Matrice */
  Matrice nouvelle = matrice_creer (N, M) ;

  /* Remplir la nouvelle matrice*/
  if (m->mat != NULL) {
    /* Copie a minima a partir de l'ancienne matrice si elle existe */
    matrice_recopier (nouvelle, m->mat) ;

    /* Destruction de l'ancienne matrice */
    matrice_detruire (m->mat) ;
  }
  else {
    /* Remplir avec des 0 si pas dans de matrice deja existante */
    matrice_remplir (nouvelle, 0.) ;
  }

  /* Utiliser la nouvelle matrice */
  m->mat = nouvelle ;
  m->N = N ;
  m->M = M ;
}

double modele_get_value (Modele m, int i, int j) {
  return matrice_get_val(m->mat, i, j) ;
}

void modele_set_value (Modele m, int i, int j, double val) {
  matrice_set_val(m->mat, i, j, val) ;
}

void modele_reset (Modele m) {
  matrice_remplir (m->mat, 0.) ;
}

void modele_fill_x (Modele m, double x) {
  matrice_remplir (m->mat, x) ;
}

void modele_fill_idx (Modele m, double x) {
  int i, j ;

  /* Mettre la valeur x sur la diagonale
   * et des zeros en dehors de la diagonale */
  for (i=0 ; i < matrice_get_lignes(m->mat) ; i++) {
    for (j=0 ; j < matrice_get_colonnes(m->mat) ; j++) {
      if (i == j)
	matrice_set_val (m->mat, i, j, x) ;
      else
	matrice_set_val (m->mat, i, j, 0.) ;
    }
  }
}

void modele_add_x (Modele m, double x) {
  int i, j ;
  double val ;
  
  /* Ajouter x a chacun des elements de la matrice */
  for (i=0 ; i < matrice_get_lignes(m->mat) ; i++) {
    for (j=0 ; j < matrice_get_colonnes(m->mat) ; j++) {
      val = matrice_get_val (m->mat, i, j) ;
      matrice_set_val (m->mat, i, j, val + x) ;
    }
  }
}

void modele_mult_idx (Modele m, double x) {
  int i, j ;
  int dim = matrice_get_lignes (m->mat) ;
  Matrice ancienne = m->mat ;
  Matrice IDx = matrice_creer (dim, dim) ;
  Matrice nouvelle = matrice_creer (dim, dim) ;

  /* Remplir IDx avec des x sur la diagonale
   * et des zeros en dehors de la diagonale */
  for (i=0 ; i < dim ; i++)
    for (j=0 ; j < dim ; j++)
      matrice_set_val (IDx, i, j, (i==j ? x : 0.)) ;
 
  /* Faire le produit de l'ancienne matrice et de IDx */
  matrice_produit (nouvelle, ancienne, IDx) ;

  /* Detruire IDx et l'ancienne matrice */
  matrice_detruire (IDx) ;
  matrice_detruire (ancienne) ;

  /* Affecter la nouvelle matrice */
  m->mat = nouvelle ;
  m->N = matrice_get_lignes (nouvelle) ;
  m->M = matrice_get_colonnes (nouvelle) ;  
}


void modele_mult_x (Modele m, double x) {
  matrice_scalaire (m->mat, x) ;
}

void modele_carre (Modele m) {
  int dim = matrice_get_lignes (m->mat) ;
  Matrice ancienne = m->mat ;
  Matrice nouvelle = matrice_creer (dim, dim) ;

  /* Faire le produit de l'ancienne matrice par elle-meme */
  matrice_produit (nouvelle, ancienne, ancienne) ;

  /* Detruire l'ancienne matrice */  
  matrice_detruire (ancienne) ;

  /* Affecter la nouvelle matrice */
  m->mat = nouvelle ;
  m->N = matrice_get_lignes (nouvelle) ;
  m->M = matrice_get_colonnes (nouvelle) ;  
}

void modele_cube (Modele m) {
  int dim = matrice_get_lignes (m->mat) ;
  Matrice ancienne = m->mat ;
  Matrice temp = matrice_creer (dim, dim) ;
  Matrice nouvelle = matrice_creer (dim, dim) ;

  /* Faire le produit de l'ancienne matrice par elle-meme */
  matrice_produit (temp, ancienne, ancienne) ;

  /* Faire le produit du carre de l'ancienne matrice par l'ancienne matrice */
  matrice_produit (nouvelle, temp, ancienne) ;

  /* Detruire l'ancienne matrice et sa matrice carree temporaire */
  matrice_detruire (ancienne) ;
  matrice_detruire (temp) ;

  /* Affecter la nouvelle matrice */
  m->mat = nouvelle ;
  m->N = matrice_get_lignes (nouvelle) ;
  m->M = matrice_get_colonnes (nouvelle) ;  
}

void modele_tranposer (Modele m) {
  Matrice ancienne = m->mat ;
  Matrice nouvelle ;

  /* Calculer la transposee de l'ancienne matrice */
  nouvelle = matrice_transposee (ancienne) ;

  /* Detruire l'ancienne matrice */  
  matrice_detruire (ancienne) ;

  /* Affecter la nouvelle matrice */
  m->mat = nouvelle ;
  m->N = matrice_get_lignes (nouvelle) ;
  m->M = matrice_get_colonnes (nouvelle) ;  
}

char modele_symetrique (Modele m) {
  return matrice_est_symetrique (m->mat) ;
}

double modele_trace (Modele m) {
  return matrice_trace (m->mat) ;
}

void modele_fill_alea (Modele m, int min, int max) {
  int i, j ;
  double val ;

  /* Remplir la matrice avec des valeurs aleatoires entre 0 et max */
  for (i=0 ; i < matrice_get_lignes(m->mat) ; i++) {
    for (j=0 ; j < matrice_get_colonnes(m->mat) ; j++) {
      val = (double)hasard_generer_nombre (min, max) ;
      matrice_set_val (m->mat, i, j, val) ;
    }
  }
}

void modele_diag_alea (Modele m, int min, int max) {
  int i ;
  double val ;

  /* Remplir la diagonale avec des valeurs aleatoires entre 0 et max */
  for (i=0 ; i < matrice_get_lignes(m->mat) ; i++) {
    val = (double)hasard_generer_nombre (min, max) ;
    matrice_set_val (m->mat, i, i, val) ;
  }
}

void modele_set_from_file (Modele m, const char *filename) {
  FILE *fdin ;
  int nb_lignes, nb_colonnes ;
  int i, j ;
  double val ;
  Matrice nouvelle ;

  /* Ouvrir le descripteur de fichier en lecture */
  fdin = fopen (filename, "r") ;

  if (fdin == NULL) {
    perror("Erreur ouverture fichier en lecture") ;
  }
  else {
    /* Lire les dimensions de la matrice */
    fscanf (fdin, "%d", &nb_lignes) ;
    fscanf (fdin, "%d", &nb_colonnes) ;

    /* Creer la matrice */
    nouvelle = matrice_creer (nb_lignes, nb_colonnes) ;

    /* Lire les valeurs de la matrice depuis le fichier */
    for (i=0 ; i < nb_lignes ; i++)
      for (j=0 ; j < nb_colonnes ; j++) {
	fscanf (fdin, "%lf", &val) ;
	matrice_set_val (nouvelle, i, j, val) ;
      }

    /* Detruire l'ancienne matrice */
    matrice_detruire (m->mat) ;
  
    /* Affecter la nouvelle matrice */
    m->mat = nouvelle ;
    m->N = nb_lignes ;
    m->M = nb_colonnes ;  

    /* Fermer le descripteur de fichier */
    fclose (fdin) ;
  }
}

void modele_save_to_file (Modele m, const char *filename) {
  FILE *fdout ;
  int nb_lignes = m->N ;
  int nb_colonnes = m->M ;
  int i, j ;
  double val ;

  /* Ouvrir le descripteur de fichier en ecriture */
  fdout = fopen (filename, "w") ;

  if (fdout == NULL) {
    perror("Erreur ouverture fichier en ecriture") ;
  }
  else {
    /* Ecrire les dimensions de la matrice */
    fprintf (fdout, "%d %d\r\n", nb_lignes, nb_colonnes) ;

    /* Ecrire les valeurs de la matrice dans le fichier */
    for (i=0 ; i < nb_lignes ; i++) {
      for (j=0 ; j < nb_colonnes ; j++) {
	val = matrice_get_val (m->mat, i, j) ;
	fprintf (fdout, " %f", val) ;
      }
      fprintf (fdout, "\r\n") ;
    }

    /* Fermer le descripteur de fichier */
    fclose (fdout) ;
  }
}

void modele_export_to_csv_file (Modele m, const char *filename) {
  FILE *fdout ;
  int nb_lignes = m->N ;
  int nb_colonnes = m->M ;
  int i, j ;
  double val ;

  /* Ouvrir le descripteur de fichier en ecriture */
  fdout = fopen (filename, "w") ;

  if (fdout == NULL) {
    perror("Erreur ouverture fichier en ecriture") ;
  }
  else {
    /* Ecrire les valeurs de la matrice dans le fichier */
    for (i=0 ; i < nb_lignes ; i++) {
      for (j=0 ; j < nb_colonnes ; j++) {
	val = matrice_get_val (m->mat, i, j) ;
	fprintf (fdout, "%f;", val) ;
      }
      fprintf (fdout, "\r\n") ;
    }

    /* Fermer le descripteur de fichier */
    fclose (fdout) ;
  }
}



