#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifndef defines
#define definesb
#endif
#include "./helpers/index.h"

void cargarArchivo(int *posicionColumnaActivo) {
  propiedad propiedad;
  FILE *pArchivo = fopen("propiedades.dat", "ab");

  if (pArchivo != NULL) {
    for (int i = 0; i < 15; i++) {
      int dia = (rand() % 28) + 1;
      int mes = (rand() % 12) + 1;
      int ano = (rand() % 23) + 2000;
      char fecha[12];

      sprintf(fecha, "%02d/%02d/%04d", dia, mes, ano);

      propiedad.id = i;
      strcpy(propiedad.zona, "zona");
      strcpy(propiedad.fecha_de_ingreso, fecha);
      strcpy(propiedad.ciudad, "ciudad");
      propiedad.dormitorios = i;
      propiedad.banos = i;
      propiedad.superficie_cubierta = i;
      propiedad.superficie_total = i;
      propiedad.precio = i;
      strcpy(propiedad.moneda, "moneda");
      strcpy(propiedad.tipo, "Departamento");
      strcpy(propiedad.operacion, "operacion");
      strcpy(propiedad.fecha_de_salida, "08/11/2002");
      propiedad.activo = 1;

      if (i == 0) {
        (*posicionColumnaActivo) = ftell(pArchivo);
      }

      fwrite(&propiedad, sizeof(propiedad), 1, pArchivo);
    }
    fclose(pArchivo);
  }
}

void creoArchivoBinario(FILE **pArchivo) {
  *pArchivo = fopen("propiedades.dat", "wb+");
  if ((*pArchivo) != NULL) {
    printf("%s", "Archivo binario creado");
  }
}

char obtenerSeleccion() {
  char opcionElegida;

  printf("\n¿Qué operación desea realizar?\n");
  printf(
      "A) Crear archivo binario\n"
      "B) Listar dat\n"
      "C) Alta\n"
      "D) Buscar\n"
      "E) Modificar\n"
      "F) Baja lógica\n"
      "G) Baja física\n"
      "H) Listar xyz\n");

  scanf(" %c", &opcionElegida);

  return opcionElegida;
}

int main() {
  srand(time(NULL));
  int continuar = 1;
  int posicionColumnaActivo = 0;
  char *propiedades[] = {
      "id",
      "fecha de ingreso",
      "zona",
      "ciudad",
      "dormitorios",
      "banos",
      "superficie total",
      "superficie cubierta",
      "precio",
      "moneda",
      "tipo",
      "operacion",
      "fecha de salida",
      "activo"};

  while (continuar) {
    char opcionElegida, opcionElegidaMinuscula, subMenuOpcionElegida;
    FILE *pArchivo;

    opcionElegida = obtenerSeleccion();

    opcionElegidaMinuscula = tolower(opcionElegida);

    if (opcionElegidaMinuscula == 'a') {
      creoArchivoBinario(&pArchivo);
      cargarArchivo(&posicionColumnaActivo);

    } else if (opcionElegidaMinuscula == 'b') {
      subMenuOpcionElegida = submenuListar();
      listoArchivoBinario(subMenuOpcionElegida);
    } else if (opcionElegidaMinuscula == 'c') {
      int error = 1;
      int numPropiedades = sizeof(propiedades) / sizeof(propiedades[0]);
      propiedad persistePropiedad;

      for (int i = 0; i < numPropiedades; i++) {
        do {
          error = alta(propiedades[i], &persistePropiedad);

          if (error == 1) {
            printf("Revise la informacion introducida para el campo %s y reintentelo nuevamente \n", propiedades[i]);
          }
        } while (error == 1);
      }
      if (escriboPropiedad(&persistePropiedad) == 0) {
        printf("Propiedad escrita correctamente");
      } else {
        printf("Error al escribir la nueva propiedad al archivo.\n");
      }

    } else if (opcionElegidaMinuscula == 'd') {
      bool terminarBuscar = 0;
      while (!terminarBuscar) {
        terminarBuscar = buscar();
      }
    } else if (opcionElegidaMinuscula == 'q')  // 'q' para salir
    {
      continuar = 0;  // Cambia continuar a 0 para salir del bucle.
    } else {
      printf(
          "------------------------- La opcion ingresada no es valida "
          "-------------------------\n\n");
    }
  }

  return 0;
}
