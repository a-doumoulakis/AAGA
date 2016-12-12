#include <stdio.h>
#include <stdlib.h>
#include "../lib/stack.h"
const int INITIAL_STACK_SIZE = 1024;

Stack* create_with_size(const int size) {
  Stack* stack = (Stack*)malloc(sizeof(Stack));
  stack->MAX_SIZE=size;
  stack->data = (void**)malloc(sizeof(void*)*stack->MAX_SIZE);
  stack->top = -1;
  return stack;
}

Stack* create() {
  return create_with_size(INITIAL_STACK_SIZE);
}

void freeStack(Stack* stack){
    free(stack -> data);
    free(stack);
}

int empty(Stack* stack) {
   return (stack->top==-1) ? 1 : 0;
}

int full(Stack* stack) {
   return (stack->top==stack->MAX_SIZE) ? 1 : 0;
}

int resize(Stack* stack) {
  printf("SIZE is %d, resize to ", stack->MAX_SIZE);
  stack->MAX_SIZE = stack->MAX_SIZE * 2;
  printf("%d\n", stack->MAX_SIZE);
  stack = realloc(stack, sizeof(stack->data)*2);
  if(stack==NULL) {
      fprintf(stderr, "Error : unable to allocate required memory\n");
      return 0;
   }
   else {
      return 1;
   }
}

void* pop(Stack* stack) {
   void* data;
   if(!empty(stack)) {
      data = stack->data[stack->top];
      stack->top -= 1;
      return data;
   } else {
      printf("Could not retrieve data, Stack is empty.\n");
   }
   return NULL;
}

void* peek(Stack* stack) {
  if(stack!=NULL && (stack->top >= 0)) return stack->data[stack->top];
  return NULL;
}

int push(Stack *stack, void*  data) {
  if(full(stack)) {
    int res = resize(stack);
    if(res==0) return 0;
  }
  stack->top += 1;
  stack->data[stack->top] = data;
  return 1;
}

void clear(Stack* stack) {
  //!\\ This is not going to clear the data inside the stack !
  free(stack->data);
  free(stack);
}


/*int main(int argc, char const *argv[]) {
  Stack* stack = create();
  for(int i = 0; i<100; i++) {
    int* k = (int*)malloc(sizeof(int));
    *k = i;
    push(stack, k);
    printf("inserted at %d : %d\n", i, *k);
  }

  for(int i =0; i<3700; i+=50) {
    int* val = (int*)pop(stack);
    if(val!=NULL) {
      printf("%d : %d\n", i, *val);
      free(val);
    } else { printf("VALUE WAS NULL"); }
  }

  while(!empty(stack)) {
    int* val = (int*)pop(stack);
    free(val);
    printf("free %d\n", stack->top);
  }
  printf("free all values\n");
  clear(stack);
  printf("free stack");

  return EXIT_SUCCESS;
}*/
