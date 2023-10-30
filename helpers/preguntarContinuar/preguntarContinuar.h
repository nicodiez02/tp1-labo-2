#include <stdio.h>
#ifndef preguntarContinuar_h
#define preguntarContinuar_h

bool preguntarContinuar() {
  char var;

  printf("\n¿Desea continuar?\n");
  printf("A) Si\nB) No\n");

  scanf(" %c", &var);

  if (var == 'b') {
    return false;
  }

  return true;
};

#endif