#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../defines.h"
#ifndef validadoresAlta_h
#define validadoresAlta_h

// validar que no meta superficies en cero
// validar que superficie cubierta sea menor o igual a la total
// validar que banos y dormis no sean letras

// ver por que rompe con loop infinito si pongo letra en bano y dormi

bool validarTipoDato(esIntEsChar *nuevaValidacion, char queValidar[10]) {
  bool pasoLaValidacion = true;

  if (strcmp(queValidar, "entero") == 0) {
    if (scanf("%i", &(nuevaValidacion->datoEntero)) != 1) {
      pasoLaValidacion = false;
    }
  } else if (strcmp(queValidar, "cadena") == 0) {
    scanf("%s", nuevaValidacion->datoCadena);
    
    int num;
    if (sscanf(nuevaValidacion->datoCadena, "%d", &num) == 1) {
      pasoLaValidacion = false;
    }
  } else if (strcmp(queValidar, "flotante") == 0) {
    if (scanf("%f", &(nuevaValidacion->datoFlotante)) != 1) {
      pasoLaValidacion = false;
    }
  }

  // agregar mas validaciones de tipado si es necesario.
  return pasoLaValidacion;
};

int comprobarId(int id) {
  FILE *pArchivo;
  pArchivo = fopen("propiedades.dat", "rb");

  propiedad otraPropiedad;
  int error = 0;

  if (id < 0) {
    printf("El numero ingresado no puede ser negativo, intentelo de nuevo\n");
    error = 1;
  } else {
    if (pArchivo != NULL) {
      fseek(pArchivo, (id - 1) * sizeof(propiedad), SEEK_SET);
      fread(&otraPropiedad, sizeof(propiedad), 1, pArchivo);
      if (id == otraPropiedad.id && otraPropiedad.id != 0) {
        printf("El numero ingresado ya existe, intentelo de nuevo\n");
        error = 1;
      }
    } else {
      printf("Error en la apertura del archivo");
      exit(-1);
    }
  }

  return error;
};

void pedirFechaValida(char *fechaa) {
  int contador = 3;
  int mesEntero;
  char queEstoyValidando[10] = "ano";
  char fecha[11] = "";
  char dia[4] = "";
  char mes[4] = "";
  char ano[6] = "";
  esIntEsChar validacion;

  while (contador >= 1) {
    printf("Ingrese %s valido:", queEstoyValidando);
    if (validarTipoDato(&validacion, "entero")) {
      if (strcmp(queEstoyValidando, "ano") == 0) {
        if (validacion.datoEntero >= 1900 && validacion.datoEntero <= 2023) {
          sprintf(ano, "%d", validacion.datoEntero);
          contador--;
          strcpy(queEstoyValidando, "mes");
        } else {
          printf("\n- - - - - -  ANO INVALIDO - - - - - -\n\n");
        }
      } else if (strcmp(queEstoyValidando, "mes") == 0) {
        if (validacion.datoEntero >= 1 && validacion.datoEntero <= 12) {
          sprintf(mes, "%02d", validacion.datoEntero);
          mesEntero = validacion.datoEntero;
          contador--;
          strcpy(queEstoyValidando, "dia");
        } else {
          printf("\n- - - - - -  MES INVALIDO - - - - - -\n\n");
        }
      } else if (strcmp(queEstoyValidando, "dia") == 0) {
        if (mesEntero == 4 || mesEntero == 6 || mesEntero == 9 || mesEntero == 11) {
          if (validacion.datoEntero >= 1 && validacion.datoEntero <= 30) {
            sprintf(dia, "%02d", validacion.datoEntero);
            contador--;
          } else {
            printf("El mes seleccionado solo tiene 30 dias\n");
          }
        } else if (mesEntero == 2) {
          if (validacion.datoEntero >= 1 && validacion.datoEntero <= 28) {
            sprintf(dia, "%02d", validacion.datoEntero);
            contador--;
          } else {
            printf("El mes seleccionado solo tiene 28 dias\n");
          }
        } else {
          if (validacion.datoEntero >= 1 && validacion.datoEntero <= 31) {
            sprintf(dia, "%02d", validacion.datoEntero);
            contador--;
          } else {
            printf("\n- - - - - -  DIA INVALIDO - - - - - -\n\n");
          }
        }
      }
    } else {
      printf("\n- - - - - -  SOLO SE ADMITEN NUMEROS - - - - - -\n\n");
    }
  }
  sprintf(fecha, "%s/%s/%s", dia, mes, ano);
  strcpy(fechaa, fecha);
};

int compararFechas(struct tm fechaIng, struct tm fechaEgr) {
  if (fechaIng.tm_year > fechaEgr.tm_year) {
    return -1;  // fechaIng es mayor que fechaEgr
  } else if (fechaIng.tm_year < fechaEgr.tm_year) {
    return 1;  // fechaIng es menor que fechaEgr
  } else {
    if (fechaIng.tm_mon > fechaEgr.tm_mon) {
      return -1;  // fechaIng es mayor que fechaEgr
    } else if (fechaIng.tm_mon < fechaEgr.tm_mon) {
      return 1;  // fechaIng es menor que fechaEgr
    } else {
      if (fechaIng.tm_mday > fechaEgr.tm_mday) {
        return -1;  // fechaIng es mayor que fechaEgr
      } else if (fechaIng.tm_mday < fechaEgr.tm_mday) {
        return 1;  // fechaIng es menor que fechaEgr
      } else {
        return 0;  // fechaIng y fechaEgr son iguales
      }
    }
  }
}

#endif