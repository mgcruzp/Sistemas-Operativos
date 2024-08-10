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
  char *a = NULL;
  char *b = NULL;
  a = function("Hi, It's fun to learn");
  b = function("systems engineer");
  printf("From main: %s %s\n", a, b);
}

char *function(char *p) {
  char q[strlen(p)+1];
  strcpy(q, p);
  printf("From q: the string is %s\n", q);
  return q;
}
