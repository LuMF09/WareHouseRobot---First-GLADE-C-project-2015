/**
 * This module provide functions for random numbers manipulation.
 *
 * Author: Guillaume RIVIERE
 * Date: November 2010
 */

#include <stdlib.h>
#include <time.h>

#include "hasard.h"

/* This function returns a random number in range 1..n
 *
 * Author: Jean-Marc Bourguet
 * Date: March 2006
 * URL: http://www.bourguet.org/v2/clang/random/random.pdf */
int hasard_alea (int n) {
  int partSize = 1 + (n == RAND_MAX ? 0 : (RAND_MAX - n) / (n + 1));
  int maxUsefull = partSize * n + (partSize-1);
  int draw;
  
  do {
    draw = rand();
  } while (draw > maxUsefull);
  
  return draw / partSize;
}

void hasard_initialiser_graine () {
  srand ((unsigned int)time (NULL)) ;
}

int hasard_generer_nombre (int min, int max) {
  return min + hasard_alea (max-min) ;
}
