#include <stdio.h>
#include <stdlib.h>

#include "../lib/print.h"

void print(UB* tree, char* name) {
  printf("BEGIN PRINT FUNCTION");
  FILE *f = fopen(name, "w");
  if (f == NULL)
  {
      printf("Error : unable to open file\n");
      exit(1);
  }
  fprintf(f, "digraph t {\n");
  Stack* stack = create();
  Stack* treeStack = create();
  int* label = (int*)malloc(sizeof(int));
  *label=0;
  push(stack, label);
  push(treeStack, tree);

  while(!empty(treeStack)) {
    int ind = *(int*)pop(stack);
    printf("ind : %d\n", ind);
    UB* node = pop(treeStack);
    if(node->child[0]!=NULL) {
      *label+=1;
      push(stack, label);
      push(treeStack, node->child[0]);
      fprintf(f, "%d -> %d\n", ind, *label);
    }

    if(node->child[1]!=NULL) {
      *label+=1;
      push(stack, label);
      push(treeStack, node->child[1]);
      fprintf(f, "%d -> %d\n", ind, *label);
    }
  }

  fprintf(f, "}\n");
  fclose(f);
}
