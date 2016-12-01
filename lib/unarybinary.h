#ifndef UNARY_BINARY_H
#define UNARY_BINARY_H

typedef struct ub_node {
  struct ub_node *child[2];
} UB;

UB* remyGeneration(int size);

#endif
