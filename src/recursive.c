#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "../lib/randint.h"
#include "../lib/unarybinary.h"


void get_catalan(unsigned long index, mpz_t* cat_list){

  if(index == 0){
    mpz_set_ui(*cat_list, 1);
    return;
  }
  //mpz_set_ui(*(cat_list+index), 0);
  /* 2 * (2n-1) * catalan(num - 1)*/
  mpz_mul_ui(*(cat_list+index), *(cat_list+(index-1)), 2*((index*2)-1));
  mpz_cdiv_q_ui(*(cat_list+index), *(cat_list+index), (index+1));
}

mpz_t* cat_mpz_array(unsigned long size){
  unsigned int i;
  mpz_t* cat_list = malloc(sizeof(mpz_t) * size);
  for(i = 0; i < size; i++){
    mpz_init(cat_list[i]);
    get_catalan(i, cat_list);
  }
  return cat_list;
}

void free_mpz_array(mpz_t* array, unsigned long size){
   unsigned int i;
   for(i = 0; i < size; i++) mpz_clear(array[i]);
   free(array);
}

UB* recursiveGenerationo(int size){
  return NULL;
}

int main(int argc, char* argv[]){
  unsigned long size;
  if(argc == 1) return EXIT_FAILURE;
  size = strtoul(argv[1], NULL, 10);
  mpz_t* cat = cat_mpz_array(size);
  gmp_printf("Result: 1th - %Zd | last - %Zd\n", cat[5], cat[size-1]);
  free_mpz_array(cat, size);
  return EXIT_SUCCESS;
}
