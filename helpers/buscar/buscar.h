#include <stdio.h>
#include "../../defines.h"

char printBuscar()
{
  char seleccion;
  printf("¿De que manera desea buscar una propiedad? \n");
  printf("a) Por ID\nb) Por tipo de operacion \n");
  scanf(" %c", &seleccion);

  if (seleccion == 'b')
  {
    printf("¿Qué tipo de propiedad es? \n");
    printf("a) PH\n");
    printf("b) Departamento\n");
    printf("c) Casa\n");
    printf("Seleccione un tipo (a/b/c): \n");
    scanf(" %c", &seleccion);
    return seleccion;
  } else {
    printf("Ingrese el ID a buscar \n");
    //scanf(" %i", &seleccion);
    return seleccion; 
  }
};

void buscar()
{
  FILE *pArchivo;
  pArchivo = fopen("propiedades.dat", "ab");
  int nReg;
  if (pArchivo != NULL)
  {
    char seleccion = printBuscar();
    fseek(pArchivo, 0, SEEK_END);
    nReg = ftell(pArchivo) / sizeof(propiedad);
    // Me falta banda pero subi un buen progreso
    printf("Nro de registros en el archivo = %d\n", nReg);
  }
  else
  {
    printf("Error en la apertura del archivo");
  }
};