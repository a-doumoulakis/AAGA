#include <stdio.h>
#include <stdlib.h>

#include "../lib/randint.h"
#include "../lib/unarybinary.h"
#include "../lib/randint.h"


UB* remyGeneration(int size) {
  if(size <= 0) return NULL;
  //Container that provides efficient access to labelled node
  UB** node = malloc(sizeof(UB*) * (size+1));
  //Keep tracks of parents
  UB** parent = malloc(sizeof(UB*) * (size+1));
  //We allocate each node
  int i;
  for(i=1; i<size+1; i++) {
    node[i] = malloc(sizeof(UB));
    if(node[i]==NULL) { fprintf(stderr,"allocation error"); exit(EXIT_FAILURE); }
    node[i]->child[0] = NULL;
    node[i]->child[1] = NULL;
    parent[i] = NULL;
  }
  //At any time, node[0] contains the root. At the beginning, the root is node[1]
  node[0] = node[1];

  //We also need to keep the weight of the structure, at the beginning, the weight is 3
  int tree_weight = 3;

  //Initialization of the integer generator
  init_random();
  int k, j, weight, pos; //Weight and position of the node

  //Algorithm
  for(i=1; i<size; i++) {
    puts("yolo\n");
    //Pick a k integer between 1 and total_weight
    k = rand_int(tree_weight) +1;
    //Find the associate node
    j = 0; //index of the selected node

    while(k>0) {
      j++;
      if(node[j]->child[0] != NULL && node[j]->child[0] != NULL) weight = 1;      //Binary node
      else if(node[j]->child[0] == NULL && node[j]->child[1] == NULL) weight = 3; //Leaf
      else weight = 2;                                                            //Unary node
      k -= weight;
    }
    switch(weight) {
    case 1 : //Leaf
      pos = rand_int(6);
      if(pos<=1) { //P = 2/6
        node[j]->child[0] = node[i+1];
        parent[i+1] = node[j];
      }
      else if(pos<=3) { //P = 2/6
        node[j]->child[1] = node[i+1];
        parent[i+1] = node[j];
      }
      else {
        (pos==4) ? (node[i+1]->child[0] = node[j]) : (node[i+1]->child[1] = node[j]);
        //Le parent du noeud j a pour enfant (gauche|droit) le nouveau noeud i+1
        if(parent[j]!=NULL)(parent[j]->child[0]==node[j]) ? (parent[j]->child[0] = node[i+1]) : (parent[j]->child[1] = node[i+1]);
        else node[0] = node[i+1]; // The new node is the new root
        //Le parent de i+1 est le parent de j
        parent[i+1]=parent[j];
        //Le nouveau parent de j est le nouveau noeud i+1
        parent[j] = node[i+1];
      }
      break;
    case 2 : //Unary node
      //On tire si on insère le nouveau noeud en tant que fils de j, ou bien le noeud j en tant que fils (gauche|droit) du nouveau noeud i+1
      pos = rand_int(3);
      if(pos==0) { //P=1/3
        (node[j]->child[0]==NULL) ? (node[j]->child[0]=node[i+1]) : (node[j]->child[1]=node[i+1]);
        parent[i+1] = node[j];
      }
      else {
        (pos==1) ? (node[i+1]->child[0] = node[j]) : (node[i+1]->child[1] = node[j]);
        //Le parent du noeud j a pour enfant (gauche|droit) le nouveau noeud i+1
        if(parent[j]!=NULL)(parent[j]->child[0]==node[j]) ? (parent[j]->child[0] = node[i+1]) : (parent[j]->child[1] = node[i+1]);
        else node[0] = node[i+1]; // The new node is the new root
        //Le parent de i+1 est le parent de j
        parent[i+1]=parent[j];
        //Le nouveau parent de j est le nouveau noeud i+1
        parent[j] = node[i+1];
      }
      break;
    case 3 : //Binary node
      //On tire si on insère le noeud j en tant que fils (gauche|droit) du nouveau noeud i+1
      (rand_int(2)==0) ? (node[i+1]->child[0] = node[j]) : (node[i+1]->child[1] = node[j]);
      //Le parent du noeud j a pour enfant (gauche|droit) le nouveau noeud i+1
      if(parent[j]!=NULL)(parent[j]->child[0]==node[j]) ? (parent[j]->child[0] = node[i+1]) : (parent[j]->child[1] = node[i+1]);
      else node[0] = node[i+1]; // The new node is the new root
      //Le parent de i+1 est le parent de j
      parent[i+1]=parent[j];
      //Le nouveau parent de j est le nouveau noeud i+1
      parent[j] = node[i+1];
      break;
    }
    tree_weight += 2;
  }
  return node[0];
}

/*int main(void) {
  UB* res = remyGeneration(5);

  return EXIT_SUCCESS;
}*/
