#include <ctype.h>
#include <signal.h>
#include <stdio.h>

#include "../../defines.h"
#include "../preguntarContinuar/index.h"
#include "../printPropiedad/index.h"

int CONTNUAR_BUSCAR_POR_ID = 1;
int TERMINAR_BUSCAR_POR_ID = 0;

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
    return 2;
  }

  return 0;
};

int buscarPorID(FILE *pArchivo, int id, propiedad propiedadLeida) {
  fseek(pArchivo, 0, SEEK_END);
  fseek(pArchivo, (id - 1) * sizeof(propiedad), SEEK_SET);
  fread(&propiedadLeida, sizeof(propiedad), 1, pArchivo);
  if (propiedadLeida.id != id) {
    printf("\nNo existe un registro con ese ID.\n");
    printf("\nVuelva a intentarlo\n");
    return CONTNUAR_BUSCAR_POR_ID;
  } else {
    printPropiedad(propiedadLeida);
    return TERMINAR_BUSCAR_POR_ID;
  }
};

bool buscar() {
  FILE *pArchivo;
  propiedad propiedadLeida;
  pArchivo = fopen("propiedades.dat", "r+b");
  int numeroRegistros;
  if (pArchivo) {
    numeroRegistros = ftell(pArchivo) / sizeof(int);

    char seleccion = printBuscar();
    int id;

    if (tolower(seleccion) == 2) return 0;

    if (!seleccion) {
      int continuarPaso = CONTNUAR_BUSCAR_POR_ID;
      while (continuarPaso) {
        id = ingresarID();
        continuarPaso = buscarPorID(pArchivo, id, propiedadLeida);
      }
    } else {
      char *tipoVar[15];
      int propiedadesEncontradas = 0;
      while (fread(&propiedadLeida, sizeof(propiedad), 1, pArchivo) == 1) {
        if (seleccion == 'a') *tipoVar = "PH";
        if (seleccion == 'b') *tipoVar = "Departamento";
        if (seleccion == 'c') *tipoVar = "Casa";
        if (strcmp(propiedadLeida.tipo, *tipoVar) == 0) {
          printPropiedad(propiedadLeida);
          propiedadesEncontradas += 1;
        }
      };
      if (propiedadesEncontradas == 0) {
        printf("\nNo existen registros de propiedades de tipo \"%s\"\n", *tipoVar);
        return preguntarContinuar();
      }
    }

    fclose(pArchivo);

    return preguntarContinuar();
  } else {
    printf("Error en la apertura del archivo\n");
    return 0;
  }
};