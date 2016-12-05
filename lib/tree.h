#ifndef TREE_H
#define TREE_H

typedef struct ub_node {
  struct ub_node* child[2];
} UB;


void free_tree(UB* tree);

#endif
