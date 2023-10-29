#include <stdio.h>

FILE *abrirEditarArchivo() {
  FILE *pArchivo;
  pArchivo = fopen("propiedades.dat", "r+b");

  if (pArchivo != NULL) {
    return pArchivo;
  } else {
    printf("Error en la apertura del archivo");
    printf("ERROR EN ABRIRYEDITARARCHIVO");
    return 0;
  }
}