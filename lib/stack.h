#ifndef STACK_H
#define STACK_H


struct stack_t {
  int MAX_SIZE;
  void** data;
  int top;
};
typedef struct stack_t Stack;


Stack* create();
Stack* create_with_size(int initial_size);
int empty(Stack* stack);
int full(Stack* stack);
int resize(Stack* stack);
void* pop(Stack* stack);
void* peek(Stack* stack);
int push(Stack* stack, void* data);
void clear(Stack* stack);

#endif
