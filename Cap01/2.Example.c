/***********************************************************************
 * Autor: G. Cruz
 * Materia: Sistemas Operativos
 * Fecha: 1-08-24
 ***********************************************************************/

#include <stdlib.h>
#include <stdio.h>

int main (int argc, char * argv[]){
  
  int rows cols, i, j;
  int *matrix;
  
  rows=(int) atof(argv[1]);
  rows=(int) atof(argv[2]);
  
  matrix=(int**)malloc(rows*sizeof(int*));
  for (i=0;i<rows;i++){
     matrix[i]=(int*)malloc(cols*sizeof(int));
  }
  
  for (i=0;i<rows;i++){
    for(j=0;j<cols;j++){
        matrix[i][j]=i*j;
    }
  }
  
  for (i=0;i<rows;i++){
    for(j=0;j<cols;j++){
        printf("%d",matrix[i][j]);
    }
    printf("\n");
  }
  
   for (i=0;i<rows;i++){
     free(matrix[i]);
  }
 
  
  return 0;
}
