#include <stdio.h>
#include <stdlib.h>

#include "../lib/print.h"

void print(UB* tree, char* name) {
    FILE *f = fopen(name, "w");
    if(f == NULL){
        printf("Error : unable to open file\n");
        exit(1);
    }
    fprintf(f, "digraph t {\n");
    Stack* stack = create();
    Stack* tree_stack = create();
    Stack* ptr_label = create();
    int* label = (int*)malloc(sizeof(int));
    *label=0;
    push(ptr_label, label);
    push(stack, label);
    push(tree_stack, tree);

    while(!empty(tree_stack)) {
        int* ptr = (int*)pop(stack);
        int ind = *ptr;
        UB* node = pop(tree_stack);
        if(node->child[0]!=NULL) {
            int k = *label+1;
            label = (int*)malloc(sizeof(int));
            push(ptr_label, label);
            *label = k;
            push(stack, label);
            push(tree_stack, node->child[0]);
            fprintf(f, "%d -> %d\n", ind, *label);
        }

        if(node->child[1]!=NULL) {
            int k = *label+1;
            label = (int*)malloc(sizeof(int));
            push(ptr_label, label);
            *label = k;
            push(stack, label);
            push(tree_stack, node->child[1]);
            fprintf(f, "%d -> %d\n", ind, *label);
        }
    }
    
    while(!empty(ptr_label)){
        free(pop(ptr_label));
    }
    
    freeStack(ptr_label);
    freeStack(stack);
    freeStack(tree_stack);
    fprintf(f, "}\n");
    fclose(f);
}
