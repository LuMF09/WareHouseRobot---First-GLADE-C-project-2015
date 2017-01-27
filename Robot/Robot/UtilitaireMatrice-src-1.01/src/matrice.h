/* Module de manipulation de matrices.
 * FILE: matrice.h
 * AUTHOR: Guillaume Riviere (C) 2010  */
#ifndef __MATRICE_H
#define __MATRICE_H

/* Structure de donnee */
typedef struct matrice {
  int n, m ;
  double **elt ;
} *Matrice ;

/* Creation / Destruction */
Matrice matrice_creer (int N, int M) ; /* La matrice retournee devra etre detruite */
void    matrice_detruire (Matrice T) ;

/* Acces a la structure */
double matrice_get_val (Matrice T, int i, int j) ;
void   matrice_set_val (Matrice T, int i, int j, double val) ;
int    matrice_get_lignes (Matrice T) ;
int    matrice_get_colonnes (Matrice T) ;

/* Fonctions de manipulation */
void    matrice_remplir (Matrice T, double val) ;
void    matrice_afficher (Matrice T) ;
void    matrice_copier (Matrice dst, Matrice src) ;
void    matrice_recopier (Matrice dst, Matrice src) ;
Matrice matrice_dupliquer (Matrice T) ; /* La matrice retournee devra etre detruite */
void    matrice_scalaire (Matrice T, double k) ;
char    matrice_egal (Matrice T1, Matrice T2) ;
void    matrice_addition (Matrice C, Matrice A, Matrice B) ;
void    matrice_produit (Matrice C, Matrice A, Matrice B) ;
Matrice matrice_transposee (Matrice T) ; /* La matrice retournee devra etre detruite */
char    matrice_est_carree (Matrice T) ;
char    matrice_est_symetrique (Matrice T) ;
double  matrice_trace (Matrice T) ;

#endif /* __MATRICE_H */
