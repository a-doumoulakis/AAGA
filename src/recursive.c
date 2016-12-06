#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "../lib/randint.h"
#include "../lib/unarybinary.h"
#include "../lib/randint.h"
#include "../lib/print.h"


mpz_t* array_catalan;

void get_catalan(unsigned long index){
  if(index == 0){
    mpz_set_ui(*array_catalan, 1);
    return;
  }
  //mpz_set_ui(*(cat_list+index), 0);
  /* 2 * (2n-1) * catalan(num - 1)*/
  mpz_mul_ui(*(array_catalan+index), *(array_catalan+(index-1)), 2*((index*2)-1));
  mpz_cdiv_q_ui(*(array_catalan+index), *(array_catalan+index), (index+1));
}

void cat_mpz_array(unsigned long size){
  unsigned int i;
  array_catalan = malloc(sizeof(mpz_t) * size);
  for(i = 0; i < size; i++){
    mpz_init(array_catalan[i]);
    get_catalan(i);
  }
}

void free_mpz_array(mpz_t* array, unsigned long size){
   unsigned int i;
   for(i = 0; i < size; i++) mpz_clear(array[i]);
   free(array);
}

UB* recursive_generation(int size){
  if(size <= 0) return NULL;
  UB* result = malloc(sizeof(UB));
  if(size == 1){
    result -> child[0] = NULL;
    result -> child[1] = NULL;
    return result;
  }
  mpz_t* r = rand_mpz(array_catalan+(size-1));
  gmp_printf("R = %Zd\n", *r);
  mpz_t* dec_n = malloc((sizeof(mpz_t) * (size-1)));
  int i;
  int n_i = size-2;
  for(i = 0; i < size-1; i++){
    mpz_init(dec_n[i]);
    if(i == 0 || i == size-2) mpz_set(dec_n[i], array_catalan[size-2]);
    else mpz_mul(dec_n[i], array_catalan[i], array_catalan[n_i]);
    gmp_printf("i = %i, j = %i, val = %Zd\n", i, n_i, dec_n[i]);
    n_i--;
  }

  i = 0;
  while(mpz_cmp_ui(*r, 0) > 0){
    mpz_sub(*r, *r, dec_n[i]);
    i++;
  }
  i--;
  mpz_add(*r, *r, dec_n[i]);
  int size_l = i+1;
  gmp_printf("REC: %Zd | %i -- %i\n", *r, size_l, size-(size_l+1));

  mpz_clear(*r);
  for(i = 0; i < size-1; i++) mpz_clear(dec_n[i]);
  free(dec_n);
  free(r);

  result -> child[0] = recursive_generation(size_l);
  result -> child[1] = recursive_generation(size-(size_l+1));
  return result;
}

int main(int argc, char* argv[]){
  unsigned long size;
  if(argc == 1) return EXIT_FAILURE;

  size = strtoul(argv[1], NULL, 10);
  if(size <= 0) return EXIT_FAILURE;

  init_mpz();
  cat_mpz_array(size);
  UB* tree = recursive_generation(size);
  print(tree, "essai.dot");
  free_tree(tree);
  free_mpz_array(array_catalan, size);
  clear_mpz();
  return EXIT_SUCCESS;
}
