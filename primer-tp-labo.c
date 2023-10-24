#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifndef defines
#define defines
#endif
#include "./helpers/index.h"

void cargarArchivo(int *posicionColumnaActivo) {
  propiedad propiedad;
  FILE *pArchivo = fopen("propiedades.dat", "ab");

  if (pArchivo != NULL) {
    for (int i = 0; i < 15; i++) {
      int dia = (rand() % 28) + 1;
      int mes = (rand() % 12) + 1;
      int año = (rand() % 23) + 2000;
      char fecha[12];

      sprintf(fecha, "%02d/%02d/%04d", dia, mes, año);

      propiedad.id = i;
      strcpy(propiedad.zona, "zona1");
      strcpy(propiedad.fecha_de_ingreso, fecha);
      strcpy(propiedad.ciudad, "ciudad1");
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

int comprobar_id(float *id, propiedad *nuevaPropiedad) {
  FILE *pArchivo;
  pArchivo = fopen("propiedades.dat", "rb");

  propiedad otraPropiedad;
  int ent;
  int flag = 0;
  ent = (*id);

  if ((*id) < 0) {
    printf("El numero ingresado no puede ser negativo, intentelo de nuevo\n");
    return 1;
  } else if ((*id) - ent) {
    printf(
        "El numero ingresado no puede ser decimal, intentelo de nuevo, "
        "%f\n",
        ((*id) - ent));
    return 1;
  } else {
    if (pArchivo != NULL) {
      fread(&otraPropiedad, sizeof(propiedad), 1, pArchivo);
      while (!feof(pArchivo)) {
        if ((*id) == otraPropiedad.id) {
          flag = 1;
        }
        fread(&otraPropiedad, sizeof(propiedad), 1, pArchivo);
      }
      if (flag == 1) {
        printf("El numero ingresado ya existe, intentelo de nuevo\n");
        return 1;
      } else {
        (*nuevaPropiedad).id = ent;
        fclose(pArchivo);
        return 0;
      }
    } else {
      printf("Error en la apertura del archivo");
      exit(-1);
    }
  }
}

void seleccionoMoneda(propiedad *nuevaPropiedad) {
  char opcion;

  printf("a) Dolar\n");
  printf("b) Peso arg\n");
  printf("Seleccione una moneda (a/b): ");
  scanf(" %c", &opcion);

  if (tolower(opcion) == 'a') {
    strcpy((*nuevaPropiedad).moneda, "Dolar");
  } else if (tolower(opcion) == 'b') {
    strcpy((*nuevaPropiedad).moneda, "Peso arg");
  } else {
    printf("Seleccion no valida. Debe elegir 'a' o 'b'.\n");
    // seleccionoMoneda(nuevaPropiedad);
  }
}

void seleccionoTipo(propiedad *nuevaPropiedad) {
  char opcion;

  printf("a) PH\n");
  printf("b) Departamento\n");
  printf("c) Casa\n");
  printf("Seleccione un tipo (a/b/c): ");
  scanf(" %c", &opcion);

  if (tolower(opcion) == 'a') {
    strcpy((*nuevaPropiedad).tipo, "PH");
  } else if (tolower(opcion) == 'b') {
    strcpy((*nuevaPropiedad).tipo, "Departamento");
  } else if (tolower(opcion) == 'c') {
    strcpy((*nuevaPropiedad).tipo, "Casa");
  } else {
    printf("Seleccion no valida. Debe elegir 'a' o 'b' o 'c'.\n");
    // seleccionoTipo(nuevaPropiedad);
  }
}

void seleccionoOperacion(propiedad *nuevaPropiedad) {
  char opcion;

  printf("a) Venta\n");
  printf("b) Alquiler\n");
  printf("c) Alquiler temporal\n");
  printf("Seleccione una operacion (a/b/c): ");
  scanf(" %c", &opcion);

  if (tolower(opcion) == 'a') {
    strcpy((*nuevaPropiedad).operacion, "Venta");
  } else if (tolower(opcion) == 'b') {
    strcpy((*nuevaPropiedad).operacion, "Alquiler");
  } else if (tolower(opcion) == 'c') {
    strcpy((*nuevaPropiedad).operacion, "Alquiler temporal");
  } else {
    printf("Seleccion no valida. Debe elegir 'a' o 'b' o 'c'.\n");
    // seleccionoOperacion(nuevaPropiedad);
  }
}

void validacion_comprobar_id(float *id, propiedad nuevaPropiedad) {
  int cerrarComprobar = 1;
  while (cerrarComprobar) {
    printf("Ingrese el ID de la nueva propiedad:\n");
    scanf("%f", id);
    cerrarComprobar = comprobar_id(id, &nuevaPropiedad);
  }
}

void obtengoFechaActual(propiedad *nuevaPropiedad) {
  char fecha[11];
  time_t tiempo;
  struct tm *infoTiempo;
  char formato[] = "%d/%m/%Y";  // Formato DD/MM/AAAA

  time(&tiempo);
  infoTiempo = localtime(&tiempo);

  strftime(fecha, 11, formato, infoTiempo);
  strcpy((*nuevaPropiedad).fecha_de_ingreso, fecha);
}

void alta() {
  propiedad nuevaPropiedad;
  FILE *pArchivo;
  pArchivo = fopen("propiedades.dat", "ab");
  float *id;

  if (pArchivo != NULL) {
    printf("ALTA DE PROPIEDAD:\n");

    validacion_comprobar_id(id, nuevaPropiedad);

    obtengoFechaActual(&nuevaPropiedad);

    printf("Ingrese la zona de la nueva propiedad (max. 30 caracteres):\n");
    printf("Ingrese la ciudad de la nueva propiedad:\n");
    scanf("%s", nuevaPropiedad.ciudad);
    printf("Ingrese los dormitorios de la nueva propiedad:\n");
    scanf("%d", &nuevaPropiedad.dormitorios);
    printf("Ingrese los banos de la nueva propiedad:\n");
    scanf("%d", &nuevaPropiedad.banos);
    printf("Ingrese el total de la superficie de la nueva propiedad:\n");
    scanf("%f", &nuevaPropiedad.superficie_total);
    printf("Ingrese la superficie cubierta de la nueva propiedad:\n");
    scanf("%f", &nuevaPropiedad.superficie_cubierta);
    printf("Ingrese el precio de la nueva propiedad:\n");
    scanf("%f", &nuevaPropiedad.precio);
    printf("Ingrese la moneda de la nueva propiedad:\n");
    seleccionoMoneda(&nuevaPropiedad);
    printf("Ingrese el tipo de la nueva propiedad:\n");
    seleccionoTipo(&nuevaPropiedad);
    printf("Ingrese el tipo de operacion de la nueva propiedad:\n");
    seleccionoOperacion(&nuevaPropiedad);
    printf(
        "Ingrese la fecha de salida de la nueva propiedad en el formato "
        "DD/MM/YYYY:\n");
    /*  nuevaPropiedad.fecha_de_salida = funcion para ingresar una fecha
     * valida(); */
    nuevaPropiedad.activo = 1;
  } else {
    printf("Error en la apertura del archivo");
    exit(-1);
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

#include <ctype.h>
#include <stdio.h>

int main() {
  srand(time(NULL));
  int continuar = 1;
  int posicionColumnaActivo = 0;

  while (continuar) {
    char opcionElegida, opcionElegidaMinuscula, subMenuOpcionElegida;
    FILE *pArchivo;

    opcionElegida = obtenerSeleccion();

    printf("Opción elegida: %c\n", opcionElegida);
    opcionElegidaMinuscula = tolower(opcionElegida);

    if (opcionElegidaMinuscula == 'a') {
      creoArchivoBinario(&pArchivo);
      cargarArchivo(&posicionColumnaActivo);
      printf("POSICION COLUMNA ACTIVO: %i", posicionColumnaActivo);
    } else if (opcionElegidaMinuscula == 'b') {
      subMenuOpcionElegida = submenuListar();
      listoArchivoBinario(subMenuOpcionElegida);
    } else if (opcionElegidaMinuscula == 'c') {
      alta();
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
          "-------------------------\n");
    }
  }

  return 0;
}
