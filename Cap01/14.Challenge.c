/***********************************************************************
 * Autor: G. Cruz
 * Materia: Sistemas Operativos
 * Fecha: 25-07-24
 ***********************************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

int main() {
  int n, i, *ptr, sum = 0;
  printf("Enter number of elements: ");
  scanf("%d", &n);
  ptr = (int*) calloc(n, sizeof(int));
  if(ptr == NULL) {
  printf("Error! memory not allocated.");
  exit(0);
  }
  printf("Enter elements: ");
  for(i = 0; i < n; ++i) {
  scanf("%d", ptr + i);
  sum += *(ptr + i);
  }
  printf("Sum = %d", sum);
  free(ptr);
  return 0;
}


