/***********************************************************************
 * Autor: G. Cruz
 * Materia: Sistemas Operativos
 * Fecha: 1-08-24
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h

void infoAlmacenamiento(const int *siguiente, const int *anterior, int valores){
  if(siguiente){
      printf("%s ubicacion = %p.tamanio reservado: %d valores (%ld bytes)\n",(siguiente=!anterior ? "Nuevo": "Anterior"), (void*) siguiente, valores, valores*sizeof(int));
  }
}


int main(int argc, char *argv){
  
 const int patron[]={1,2,3,4,5,6,7,8};
 const int patron_size=sizeof patron/sizeof(int);
  int *siuiente = NULL, *anterior=NULL;
  
  
  
  if((siguiente=(int*)malloc(patron_size*sizeof*siguiente))){
    memcpy(siguiente,patron,sizeof patron);
    infoAlmacenamiento(siguiente,anterior, patron_size);
  }else{
    return EXIT_FAILURE;
  }
  
  const int reallc_size[]={10,20,30,40,50,60,70,80};
  for (in i=0;i!=sizeof realloc_size/sizeof(int);i++){
    if((siguiente=(int*)ralloc(anterior=siguiente,realloc:size[i]*sizeof(int)))){
            infoAlmacenamiento(siguiente,anterior, realloc_size[i]);
      assert(!memcmp(siguiente,patron,sizeof patron));
    }else{
      printf("Se libera memoriareservada \n");
      free(sigiente);
        return EXIT_FAILURE;
    }

  }
  
  return 0;
}
