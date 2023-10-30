#include <stdio.h>
#include <stdlib.h>

#include "./validadoresAlta.h"

int seleccionoMoneda(propiedad *nuevaPropiedad) {
  char opcion;
  int error = 0;

  printf("\na) Dolar\n");
  printf("b) Peso arg\n");
  printf("Seleccione una moneda (a/b): ");
  scanf(" %c", &opcion);

  if (tolower(opcion) == 'a') {
    strcpy((*nuevaPropiedad).moneda, "Dolar");
  } else if (tolower(opcion) == 'b') {
    strcpy((*nuevaPropiedad).moneda, "Peso arg");
  } else {
    printf("Seleccion no valida. Debe elegir 'a' o 'b'.\n");
    error++;
  }

  return error;
}

int seleccionoTipo(propiedad *nuevaPropiedad) {
  char opcion;
  int error = 0;

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
    error++;
  }

  return error;
}

int seleccionoOperacion(propiedad *nuevaPropiedad) {
  char opcion;
  int error = 0;

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
    error++;
  }

  return error;
}

int alta(const char *campoAComprobar, propiedad *nuevaPropiedad) {
  int error = 0;
  int id, result;
  char inputId[10];
  esIntEsChar validacion;
  struct tm fechaIngreso, fechaEgreso;

  if (strcmp(campoAComprobar, "activo") == 0) {
    (*nuevaPropiedad).activo = 1;
  } else {
    printf("Ingrese %s: ", campoAComprobar);
  }

  if (strcmp(campoAComprobar, "id") == 0) {
    if (validarTipoDato(&validacion, "entero")) {
      error = comprobarId(validacion.datoEntero);

      if (error == 0) {
        (*nuevaPropiedad).id = validacion.datoEntero;
      }

    } else {
      error++;
    }
  }

  if (strcmp(campoAComprobar, "fecha de ingreso") == 0) {
    int contador = 3;
    int mess;
    char queEstoyValidando[10] = "ano";
    char fechaIngreso[11] = "";
    char dia[4] = "";
    char mes[4] = "";
    char ano[6] = "";

    printf("\n\n");
    while (contador >= 1) {
      printf("Ingrese %s de ingreso:", queEstoyValidando);
      if (validarTipoDato(&validacion, "entero")) {
        if (strcmp(queEstoyValidando, "ano") == 0) {
          if (validacion.datoEntero >= 1000 && validacion.datoEntero <= 2023) {
            sprintf(ano, "%d", validacion.datoEntero);
            contador--;
            strcpy(queEstoyValidando, "mes");
          } else {
            printf("\n- - - - - -  ANO INVALIDO - - - - - -\n\n");
          }
        } else if (strcmp(queEstoyValidando, "mes") == 0) {
          if (validacion.datoEntero >= 1 && validacion.datoEntero <= 12) {
            sprintf(mes, "%02d", validacion.datoEntero);
            mess = validacion.datoEntero;
            contador--;
            strcpy(queEstoyValidando, "dia");
          } else {
            printf("\n- - - - - -  MES INVALIDO - - - - - -\n\n");
          }
        } else if (strcmp(queEstoyValidando, "dia") == 0) {
          if (mess == 4 || mess == 6 || mess == 9 || mess == 11) {
            if (validacion.datoEntero >= 1 && validacion.datoEntero <= 30) {
              sprintf(dia, "%02d", validacion.datoEntero);
              contador--;
            } else {
              printf("El mes seleccionado solo tiene 30 dias\n");
            }
          } else if (mess == 2) {
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
      while (getchar() != '\n');
    }

    sprintf(fechaIngreso, "%s/%s/%s", dia, mes, ano);
    strcpy((*nuevaPropiedad).fecha_de_ingreso, fechaIngreso);
  }

  if (strcmp(campoAComprobar, "zona") == 0) {
    do {
      if (validarTipoDato(&validacion, "cadena")) {
        strcpy((*nuevaPropiedad).zona, validacion.datoCadena);
        error = 0;
      } else {
        printf("Error, intentelo nuevamente\n");
        printf("Ingrese %s: ", campoAComprobar);
        error++;
      }
    } while (error > 0);
  }
  if (strcmp(campoAComprobar, "ciudad") == 0) {
    do {
      if (validarTipoDato(&validacion, "cadena")) {
        strcpy((*nuevaPropiedad).ciudad, validacion.datoCadena);
        error = 0;
      } else {
        printf("Error, intentelo nuevamente\n");
        printf("Ingrese %s: ", campoAComprobar);
        error++;
      }
    } while (error > 0);
  }
  if (strcmp(campoAComprobar, "dormitorios") == 0) {
    if (validarTipoDato(&validacion, "entero")) {
      error = 0;
      (*nuevaPropiedad).dormitorios = validacion.datoEntero;
    } else {
      error++;
    }
  }
  if (strcmp(campoAComprobar, "banos") == 0) {
    if (validarTipoDato(&validacion, "entero")) {
      error = 0;
      (*nuevaPropiedad).banos = validacion.datoEntero;
    } else {
      error++;
    }
  }
  if (strcmp(campoAComprobar, "superficie total") == 0) {
    if (validarTipoDato(&validacion, "flotante")) {
      error = 0;
      (*nuevaPropiedad).superficie_total = validacion.datoFlotante;
    } else {
      error++;
    }
  }
  if (strcmp(campoAComprobar, "superficie cubierta") == 0) {
    if (validarTipoDato(&validacion, "flotante")) {
      error = 0;
      (*nuevaPropiedad).superficie_cubierta = validacion.datoFlotante;
    } else {
      error++;
    }
  }
  if (strcmp(campoAComprobar, "precio") == 0) {
    if (validarTipoDato(&validacion, "flotante")) {
      error = 0;
      (*nuevaPropiedad).precio = validacion.datoFlotante;
    } else {
      error++;
    }
  }
  if (strcmp(campoAComprobar, "moneda") == 0) {
    error = seleccionoMoneda(nuevaPropiedad);
  }
  if (strcmp(campoAComprobar, "tipo") == 0) {
    error = seleccionoTipo(nuevaPropiedad);
  }
  if (strcmp(campoAComprobar, "operacion") == 0) {
    error = seleccionoOperacion(nuevaPropiedad);
  }
  if (strcmp(campoAComprobar, "fecha de salida") == 0) {
    int diaIng, mesIng, anoIng;
    int diaEgr, mesEgr, anoEgr;
    char fecha_de_salida[11];
    pedirFechaValida(fecha_de_salida);

    if (sscanf(fecha_de_salida, "%d/%d/%d", &diaEgr, &mesEgr, &anoEgr) == 3) {
      printf("Dia: %d\n", diaEgr);
      printf("Mes: %d\n", mesEgr);
      printf("Ano: %d\n", anoEgr);
    } else {
      printf("Error al analizar la fecha.\n");
    }

    if (sscanf((*nuevaPropiedad).fecha_de_ingreso, "%d/%d/%d", &diaIng, &mesIng, &anoIng) == 3) {
      printf("Dia: %d\n", diaIng);
      printf("Mes: %d\n", mesIng);
      printf("Ano: %d\n", anoIng);
    } else {
      printf("Error al analizar la fecha.\n");
    }

    fechaIngreso.tm_year = anoIng;
    fechaIngreso.tm_mon = mesIng;
    fechaIngreso.tm_mday = diaIng;

    fechaEgreso.tm_year = anoEgr;
    fechaEgreso.tm_mon = mesEgr;
    fechaEgreso.tm_mday = diaEgr;

    int resultado = compararFechas(fechaIngreso, fechaEgreso);

    if (resultado > 0) {
      printf("Fecha valida\n");
      strcpy((*nuevaPropiedad).fecha_de_salida, fecha_de_salida);
    } else if (resultado < 0) {
      printf("Fecha invalida\n");
      error++;
    } else {
      printf("Fecha invalida por igualdad\n");
      error++;
    }
  }

  return error;
}

int escriboPropiedad(propiedad *nuevaProp) {
  int numeroRegistros;
  propiedad propiedadVacia = {
      0,
      '0',
      '0',
      '0',
      0,
      0,
      0,
      0,
      0,
      '0',
      '0',
      '0',
      '0',
      0,
  };

  FILE *pArchivo = fopen("propiedades.dat", "r+b");  // Abre el archivo en modo de adición binaria

  if (pArchivo != NULL) {
    fseek(pArchivo, 0, SEEK_END);
    numeroRegistros = ftell(pArchivo) / sizeof(propiedad);
    if (numeroRegistros < nuevaProp->id) {
      int cantidadACrear = nuevaProp->id - numeroRegistros;
      printf("%i", cantidadACrear);

      for (int i = 1; i < cantidadACrear; i++) {
        fwrite(&propiedadVacia, sizeof(propiedad), 1, pArchivo);
      }

      fwrite(nuevaProp, sizeof(propiedad), 1, pArchivo);
    } else {
      fseek(pArchivo, 0, SEEK_SET);
      fseek(pArchivo, ((nuevaProp->id) - 1) * sizeof(propiedad), SEEK_SET);
      fwrite(nuevaProp, sizeof(propiedad), 1, pArchivo);
    }
    fclose(pArchivo);
    return 0;
  } else {
    printf("Error en escriboPropiedad");
    return -1;
  }
};
