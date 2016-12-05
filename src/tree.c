#include <stdio.h>
#include <stdlib.h>
#include "../lib/tree.h"


void free_tree(UB* tree){
  if(tree -> child[0] != NULL) free_tree(tree -> child[0]);
  if(tree -> child[1] != NULL) free_tree(tree -> child[1]);
  free(tree);
}
