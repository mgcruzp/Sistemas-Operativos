/***********************************************************************
 * Autor: G. Cruz
 * Materia: Sistemas Operativos
 * Fecha: 15-08-24
 * Tea: Gestion de memoria
 * Topico: Diferencias enre usar
 *************************************************************/

#include <stdio.h>
#include <stdlib.h>

void imprimirMatriz(int *matriz, int n){
  if (n<6){
  for(int i=0; i<n*n;i++){
      if (i%n==0)
        printf("\n");
        printf(" %d", (*matriz+1));
    }
  }  
  printf("\n-------------------------\n");
}

int main (int argc, char* argv[]){
  
  if (argc<2){
    printf("\nArgumentos validos: $ejecutable sizeofMatriz \n");
    exit(0);
  }
  int n=atoi(argv[1]);
  int size =n*n;
  int mA[size];
  int mB[size];
  int mC[size];
  
  // inicializacion
  for(int i=0; i<size; i++){
    mA[i]=1;
    mB[i]=2;
    mC[i]=0;

  }
  
  imprimirMatriz(mA, n);
  imprimirMatriz(mB, n);
  imprimirMatriz(mC, n);
  
  //multiplicacion de matices: mA*mB=mC --version clasica
  
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      int suma=0;
      int *pA=mA;
      int *pB=mB;
      for (int k=0;k<n;k++){
        suma+=pA*pB;
      }
      mc[i+j]=suma;
    } 
  }
  

  printf("\n");
  printf("... saliendo del programa \n");
  return 0;
}
