/***********************************************************************
 * Autor: G. Cruz
 * Materia: Sistemas Operativos
 * Fecha: 1-08-24
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv){
  
  int *varptr1=calloc(4*sizeof(int));
  int *varptr2=calloc(sizeof(int[4]));
  int *varptr3=calloc(4*sizeof*varptr3);
  
  if(varptr1){
    for(int i=0;i<4;i++)
      varptr1[i]=i*i;
    for(int i=0;i<4;i++)
      printf("varptr1[%d]\t == %d\n",i,varptr1[i]);
  }
    
  printf("Se libera memoria\n");
  free(varptr1);
  free(varptr2);
   free(varptr3); 
  return 0;
} 
