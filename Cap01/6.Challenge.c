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
  char *q = NULL;
  printf("Requesting space for \”Goodbye\” \n");
  q = (char *)malloc(strlen(”Goodbye”)+1);
  if (!q) {
  perror("Failed to allocate space because");
  exit(1);
  }
  printf("About to copy \"Goodbye\" to q at address %s \n", q);
  strcpy(q, "Goodbye");
  printf("String copied\n");
  printf("%s \n", q);
  return 0;
}

