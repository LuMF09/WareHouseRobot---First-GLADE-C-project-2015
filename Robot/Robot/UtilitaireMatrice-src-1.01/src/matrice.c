/* Module de manipulation de matrices.
 * FILE: matrice.c
 * AUTHOR: Guillaume Riviere (C) 2010  */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "matrice.h"

Matrice matrice_creer (int N, int M) {
  int i ;
  Matrice res ;

  /* Allocation de la structure */
  res = malloc (sizeof(struct matrice)) ;
  assert (res != NULL) ;

  res->n = N ;
  res->m = M ;
  
  /* Allocaton du premier tableau */
  res->elt = malloc (N * sizeof(double *)) ;
  assert (res->elt != NULL) ;

  /* Allocaton des tableaux de valeurs */
  for (i=0 ; i<N ; i++) {
    res->elt[i] = malloc (M * sizeof(double)) ;
    assert (res->elt != NULL) ;
  }
  return res ;
}

void matrice_detruire (Matrice T) {
  int i ;

  /* Liberer les tableaux de valeurs */
  for (i=0 ; i < T->n ; i++)
    free (T->elt[i]) ;

  /* Liberer le premier tableau */
  free (T->elt) ;

  /* Liberer la structure */
  free (T) ;
}

double matrice_get_val (Matrice T, int i, int j) {
  assert (i >= 0 && i < T->n) ;
  assert (j >= 0 && j < T->m) ;
  return T->elt[i][j] ;
}

void matrice_set_val (Matrice T, int i, int j, double val) {
  assert (i >= 0 && i < T->n) ;
  assert (j >= 0 && j < T->m) ;
  T->elt[i][j] = val ;
}

int matrice_get_lignes (Matrice T) {
  return T->n ;
}

int matrice_get_colonnes (Matrice T) {
  return T->m ;
}

void matrice_remplir (Matrice T, double val) {
  int i, j ;
  for (i=0 ; i < T->n ; i++)
    for (j=0 ; j < T->m ; j++)
      T->elt[i][j] = val ;
}

void matrice_afficher (Matrice T) {
  int i, j ;
  for (i=0 ; i < T->n ; i++) {
    for (j=0 ; j < T->m ; j++)
      printf ("%5.2f ", T->elt[i][j]) ;
    printf ("\n") ;
  }
}

void matrice_copier (Matrice dst, Matrice src) {
  int i, j ;

  assert (dst->n == src->n) ;
  assert (dst->m == src->m) ;

  for (i=0 ; i < dst->n ; i++)
    for (j=0 ; j < dst->m ; j++)
      dst->elt[i][j] = src->elt[i][j] ;
}

void matrice_recopier (Matrice dst, Matrice src) {
  int i, j ;

  for (i=0 ; i < dst->n ; i++)
    for (j=0 ; j < dst->m ; j++) {
      if (i < src->n && j < src->m)
	dst->elt[i][j] = src->elt[i][j] ;
      else
	dst->elt[i][j] = 0. ;
    }
}

Matrice matrice_dupliquer (Matrice T) {
  int i, j ;
  Matrice res = matrice_creer (T->n, T->m) ;

  for (i=0 ; i < T->n ; i++)
    for (j=0 ; j < T->m ; j++)
      res->elt[i][j] = T->elt[i][j] ;

  return res ;
}

void matrice_scalaire (Matrice T, double k) {
  int i, j ;
  for (i=0 ; i < T->n ; i++)
    for (j=0 ; j < T->m ; j++)
      T->elt[i][j] *= k ;
}

char  matrice_egal (Matrice T1, Matrice T2) {
  char egalite = (T1->n == T2->n) && (T1->m == T2->m) ;
  int i, j ;
  for (i=0 ; i < T1->n && egalite ; i++)
    for (j=0 ; j < T1->m && egalite ; j++)
      if (T1->elt[i][j] != T2->elt[i][j])
	egalite = 0 ;
  return egalite ;
}

void matrice_addition (Matrice C, Matrice A, Matrice B) {
  int i, j ;

  assert (C->n == A->n && C->n == B->n) ;
  assert (C->m == A->m && C->m == B->m) ;

  for (i=0 ; i < C->n ; i++)
    for (j=0 ; j < C->m ; j++)
      C->elt[i][j] = A->elt[i][j] + B->elt[i][j] ;
}

void matrice_produit (Matrice C, Matrice A, Matrice B) {
  int i, j, k ;
  double sum ;

  assert (A->m == B->n) ;
  assert (C->n == A->n) ;
  assert (C->m == B->m) ;

  for (i=0 ; i < C->n ; i++) {
    for (j=0 ; j < C->m ; j++) {
      sum = 0 ;
      for (k=0 ; k < A->m ; k++)
	sum += A->elt[i][k] * B->elt[k][j] ;
      C->elt[i][j] = sum ;
    }
  }
}

Matrice matrice_transposee (Matrice T) {
  int i, j ;
  Matrice res = matrice_creer (T->m, T->n) ;

  for (i=0 ; i < T->n ; i++) {
    for (j=0 ; j < T->m ; j++) {
      res->elt[j][i] = T->elt[i][j] ;
    }
  }  

  return res ;
}

char matrice_est_carree (Matrice T) {
  return (T->n == T->m) ;
}

char matrice_est_symetrique (Matrice T) {
  int i, j ;
  char res = 1 ; /* VRAI */

  for (i=0 ; res && i < T->n ; i++) {
    for (j=i+1 ; res && j < T->m ; j++) {
      if (T->elt[i][j] != T->elt[j][i])
        res = 0 ; /* FAUX */
    }
  }

  return res ;
}

double matrice_trace (Matrice T) {
  int i ;
  double sum = 0. ;

  if (matrice_est_carree(T)) {
    for (i=0 ; i < T->n ; i++) {
      sum += T->elt[i][i] ;
    }
  }

  return sum ; /* Attention, retournera zero si la matrice n'est pas symetrique */
}
