#ifndef _RAND_INT_H
#define _RAND_INT_H
#include <gmp.h>


void init_random();

long rand_int(long upper_bound);

void init_mpz();

void clear_mpz();

mpz_t* rand_mpz(mpz_t* upper_bound);

long get_rand_bits();

#endif
