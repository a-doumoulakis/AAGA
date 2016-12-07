#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <gmp.h>
#include "../lib/randint.h"
#include "../lib/tree.h"


/* We use Knuth & Lewis generator (from Seminumerical Algorithms) */
long m = 4294967296; // 2^32
long x_n;
/*Will hold the number of random bits generated*/
long ran_bits = 0;
gmp_randstate_t r_state;


void init_random() {
  x_n = time(NULL) % m;
}

long rand_int(long upper_bound) {
  int a = 1664525;
  int c = 1013904223;
  x_n = (a * x_n + c) % m;
  ran_bits = ran_bits + (long)(ceil(log2(upper_bound)));
  return x_n % upper_bound;
}

void init_mpz(){
  gmp_randinit_default(r_state);
  long seed;
  time(&seed);
  gmp_randseed_ui(r_state, seed);
}

void clear_mpz(){
   gmp_randclear(r_state);
}

mpz_t* rand_mpz(mpz_t* upper_bound){
  mpz_t* result = malloc(sizeof(mpz_t));
  //mpz_t tmp;

  /*TODO calculer log de upper_bound pour ajouter au nombre de bit aleatoires requis*/
  mpz_init(*result);
  //mpz_init_set(tmp, *upper_bound);
  //mpz_add_ui(tmp, tmp, 1);

  //gmp_printf("upper: %Zd | %Zd\n", *upper_bound, tmp);

  mpz_urandomm(*result, r_state, *upper_bound);

  //gmp_printf("res: %Zd \n", *result);
  return result;
}

long get_rand_bits(){
  return ran_bits;
}

/*
int main(void) {
   init_random();
   for(int i = 0; i < 10; i++) {
     printf("%ld \n", rand_int(100000L));
   }
   return EXIT_SUCCESS;
 }*/
