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
  char *p;
  char *q = NULL;
  printf("Address of p = %s\n", p);
  strcpy(p, "Hello, I'm the best in Operating Systems!!!");
  printf("%s\n", p);
  printf("About to copy \"Goodbye\" to q\n");
  strcpy(q, "Goodbye");
  printf("String copied\n");
  printf("%s\n", q);
  return 0;
}

