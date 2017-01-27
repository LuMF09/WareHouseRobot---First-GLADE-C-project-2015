/**
 * This module provide functions for random numbers manipulation.
 */

#ifndef MY_RANDOM_H
#define MY_RANDOM_H

/* This function initializes seed for random numbers.
 *
 * NB: This function must be called only one time in a program. */
void hasard_initialiser_graine () ;

/* This function returns a random number in a range [min,max].
 * NB: hasard_initialiser() must be called before.              */
int hasard_generer_nombre (int min, int max) ;

#endif /* MY_RANDOM_H */
