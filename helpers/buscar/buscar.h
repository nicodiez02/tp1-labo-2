#include <ctype.h>
#include <signal.h>
#include <stdio.h>

#include "../../defines.h"

bool continuar() {
  char var;
  printf("\n¿Desea continuar?\n");
  printf("A) Si\nB) No\n");

  scanf(" %c", &var);

  if (var == 'b') {
    return 1;
  }
  return 0;
};

int ingresarID() {
  int id;
  printf("Ingrese el ID que desea buscar \n");
  scanf(" %i", &id);
  return id;
};

char printBuscar() {
  char seleccion;
  printf("\n¿De que manera desea buscar una propiedad? \n");
  printf("A) Por ID\nB) Por tipo de operacion \n");
  printf("C) Para volver al menu de opciones \n");
  scanf(" %c", &seleccion);

  if (tolower(seleccion) == 'b') {
    printf("\n ¿Qué tipo de propiedad es? \n");
    printf("A) PH\n");
    printf("B) Departamento\n");
    printf("C) Casa\n");
    printf("Seleccione un tipo (A/B/C): \n");
    scanf(" %c", &seleccion);
    return seleccion;
  }

  if (tolower(seleccion) == 'c') {
    return 1;
  }

  return 0;
};

void buscarPorID(FILE *pArchivo, int id, propiedad propiedadLeida) {
  fseek(pArchivo, 0, SEEK_END);
  fseek(pArchivo, id * sizeof(propiedad), SEEK_SET);
  fread(&propiedadLeida, sizeof(propiedad), 1, pArchivo);
  printf(
      "%.2d | %15s | %10s | %10s | %.2d | %.2d | %5.2f | %5.2f | %5.2f | %10s "
      "| %10s | %10s | %20s | %d\n",
      propiedadLeida.id, propiedadLeida.fecha_de_ingreso, propiedadLeida.zona,
      propiedadLeida.ciudad, propiedadLeida.dormitorios, propiedadLeida.banos,
      propiedadLeida.superficie_total, propiedadLeida.superficie_cubierta,
      propiedadLeida.precio, propiedadLeida.moneda, propiedadLeida.tipo,
      propiedadLeida.operacion, propiedadLeida.fecha_de_salida,
      propiedadLeida.activo);
};

bool buscar() {
  FILE *pArchivo;
  propiedad propiedadLeida;
  pArchivo = fopen("propiedades.dat", "r+b");
  int nReg;
  if (pArchivo) {
    char seleccion = printBuscar();
    int id;

    if (seleccion == 1) return 1;

    if (!seleccion) {
      id = ingresarID();
      buscarPorID(pArchivo, id, propiedadLeida);
    } else {
      char *tipoVar[15];
      while (fread(&propiedadLeida, sizeof(propiedad), 1, pArchivo) == 1) {
        if (seleccion == 'a') *tipoVar = "PH";
        if (seleccion == 'b') *tipoVar = "Departamento";
        if (seleccion == 'c') *tipoVar = "Casa";
        if (strcmp(propiedadLeida.tipo, *tipoVar) == 0) {
          printf(
              "%.2d | %15s | %10s | %10s | %.2d | %.2d | %5.2f | %5.2f | %5.2f "
              "| %10s | %10s | %10s | %20s | %d\n",
              propiedadLeida.id, propiedadLeida.fecha_de_ingreso,
              propiedadLeida.zona, propiedadLeida.ciudad,
              propiedadLeida.dormitorios, propiedadLeida.banos,
              propiedadLeida.superficie_total,
              propiedadLeida.superficie_cubierta, propiedadLeida.precio,
              propiedadLeida.moneda, propiedadLeida.tipo,
              propiedadLeida.operacion, propiedadLeida.fecha_de_salida,
              propiedadLeida.activo);
        } else {
          printf("\nNo existen registros de propiedades de tipo \"%s\"\n", *tipoVar);
          continuar();
        }
      };
    }

    fclose(pArchivo);

    return continuar();
  } else {
    printf("Error en la apertura del archivo\n");
    return 0;
  }
};