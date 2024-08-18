/***********************************************************************
 * Autor: G. Cruz
 * Materia: Sistemas Operativos
 * Fecha: 1-08-24
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv){
  int var=480;
  it *varptr=&var;
  int **doubleptr=&varptr;
  
  printf("Valor de la variable \t\t= %d\n",var);
  printf("Valor del puntero \t\t= %d\n",*varptr);
  
  printf("Valor del puntero doble \t= %d\n",**doubleptr);
  
  printf("Direccion de la variable \t= %p\n", &var);
  printf("Direccion del puntero \t\t= %p\n", &varptr);
  
  
}
