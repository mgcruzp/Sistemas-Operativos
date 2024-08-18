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
  int *ptr;
  ptr = malloc(15 * sizeof(*ptr)); /* a block of 15 integers */
  if (ptr != NULL) {
  *(ptr + 5) = 480; /* assign 480 to sixth integer */
  }
  return 0;
}


