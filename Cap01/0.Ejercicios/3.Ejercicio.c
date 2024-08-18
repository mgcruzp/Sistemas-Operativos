/***********************************************************************
 * Autor: G. Cruz
 * Materia: Sistemas Operativos
 * Fecha: 1-08-24
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv){
  
  int *vP1=calloc(4,sizeof(int));
  int *vP2=calloc(1,sizeof(int[4]));
  int *vP3=calloc(4,sizeof*vP3);
  
  if(vp2){
    for(int i=0;i<4;i++)
      printf("vP2[%d]\t == %d\n",i,vP2[i]);
  }
    
  printf("Se libera memoria reservada\n");
  free(varptr1);
  free(varptr2);
   free(varptr3); 
  return 0;
}
