#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  int seen[10];

  // Validar filas
  for(int i = 0; i < 9; i++){
    for(int k = 0; k < 10; k++) seen[k] = 0;
    for(int j = 0; j < 9; j++){
      int val = n->sudo[i][j];
      if(val == 0) continue;
      if(seen[val]) return 0;
      seen[val] = 1;
    }
  }

  // Validar columnas
  for(int j = 0; j < 9; j++){
    for(int k = 0; k < 10; k++) seen[k] = 0;
    for(int i = 0; i < 9; i++){
      int val = n->sudo[i][j];
      if(val == 0) continue;
      if(seen[val]) return 0;
      seen[val] = 1;
    }
  }

  // Validar submatrices 3x3
  for(int row = 0; row < 9; row += 3){
    for(int col = 0; col < 9; col += 3){
      for(int k = 0; k < 10; k++) seen[k] = 0;
      for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
          int val = n->sudo[row + i][col + j];
          if(val == 0) continue;
          if(seen[val]) return 0;
          seen[val] = 1;
        }
      }
    }
  }

  return 1;
}


List* get_adj_nodes(Node* n){
    List* listAdj=createList();
    int fila = -1;
    int col = -1;
    for(int i = 0; i<9 && fila == -1; i++){
      for(int j = 0; j < 9; j++){
        if(n->sudo[i][j] == 0){
          fila = i;
          col = j;
          break;
        }
      }
    }

    if (fila == -1)return listAdj;
    
    for(int v = 1; v <= 9; v++){
      Node *hijo = copy(n);
      hijo -> sudo[fila][col] = v;

      pushBack(listAdj, hijo);
    }

    return listAdj;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/