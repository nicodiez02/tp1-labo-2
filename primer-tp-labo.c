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


struct esIntEsChar
{
  int datoEntero;
  char datoCadena[30];
  float datoFlotante;
};



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

int comprobarId(int id) {
  FILE *pArchivo;
  pArchivo = fopen("propiedades.dat", "rb");

  propiedad otraPropiedad;
  int error = 0;
  int flag = 0;

  if (id < 0) {
    printf("El numero ingresado no puede ser negativo, intentelo de nuevo\n");
    error = 1;
  } else {

    if (pArchivo != NULL) {
      fread(&otraPropiedad, sizeof(propiedad), 1, pArchivo);
      while (!feof(pArchivo)) {
        if (id == otraPropiedad.id) {
          flag = 1;
        }
        fread(&otraPropiedad, sizeof(propiedad), 1, pArchivo);
      }

      if (flag == 1) {
        printf("El numero ingresado ya existe, intentelo de nuevo\n");
        error = 1;
      } 

    } else {
      printf("Error en la apertura del archivo");
      exit(-1);
    }
  }

  return error;
}

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
    // seleccionoTipo(nuevaPropiedad);
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
    // seleccionoOperacion(nuevaPropiedad);
  }

  return error;
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

bool validarTipoDato(struct esIntEsChar* nuevaValidacion,char queValidar[10]){
    bool pasoLaValidacion = true;

    if(strcmp(queValidar, "entero") == 0){
      if(scanf("%i", &(nuevaValidacion->datoEntero)) != 1){
        pasoLaValidacion = false;  
      }
    }else if(strcmp(queValidar, "cadena") == 0){
      scanf("%s", &(nuevaValidacion->datoCadena));
      int num;
      if (sscanf( &(nuevaValidacion->datoCadena), "%d", &num) == 1){
        pasoLaValidacion = false; 
      }
    } else if(strcmp(queValidar, "flotante") == 0){
      if(scanf("%f", &(nuevaValidacion->datoFlotante)) != 1){
        pasoLaValidacion = false;  
      }
    }

    //agregar mas validaciones de tipado si es necesario.
    return pasoLaValidacion;
}

int alta(const char *campoAComprobar) {
  int error = 0;
  int id, result;
  char inputId[10];
  struct esIntEsChar validacion;
  propiedad nuevaPropiedad;

    if (strcmp(campoAComprobar, "activo") == 0){
      nuevaPropiedad.activo = 1;
    } else {
      printf("Ingrese %s: ", campoAComprobar);
    }
    
    if (strcmp(campoAComprobar, "id") == 0) {
        if(validarTipoDato(&validacion, "entero")){
          
          error = comprobarId(validacion.datoEntero);

          if(error == 0){
            nuevaPropiedad.id = validacion.datoEntero;
          }

        }else{
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
      while (contador >= 1){
        printf("Ingrese %s de ingreso:", queEstoyValidando);
        if(validarTipoDato(&validacion, "entero")){
          if(strcmp(queEstoyValidando, "ano") == 0){
            if(validacion.datoEntero >= 1000 && validacion.datoEntero <= 2023){
              sprintf(ano, "%d", validacion.datoEntero);
              contador--;
              strcpy(queEstoyValidando, "mes");
            }else{
              printf("\n- - - - - -  ANO INVALIDO - - - - - -\n\n");
            }
          } else if (strcmp(queEstoyValidando, "mes") == 0){
            if(validacion.datoEntero >= 1 && validacion.datoEntero <= 12){
              sprintf(mes, "%02d", validacion.datoEntero);
              mess = validacion.datoEntero;
              contador--;
              strcpy(queEstoyValidando, "dia");
            }else{
              printf("\n- - - - - -  MES INVALIDO - - - - - -\n\n");
            }
          } else if (strcmp(queEstoyValidando, "dia") == 0){
            if (mess == 4 || mess == 6 || mess == 9 || mess == 11){
              if (validacion.datoEntero >= 1 && validacion.datoEntero <= 30){
                sprintf(dia, "%02d", validacion.datoEntero);
                contador--;
              } else {
                printf("El mes seleccionado solo tiene 30 dias\n");
              }
            } else if (mess == 2) {
              if (validacion.datoEntero >= 1 && validacion.datoEntero <= 28){
                sprintf(dia, "%02d", validacion.datoEntero);
                contador--;
              } else {
                printf("El mes seleccionado solo tiene 28 dias\n");
              }
            } else {
              if (validacion.datoEntero >= 1 && validacion.datoEntero <= 31){
              sprintf(dia, "%02d", validacion.datoEntero);
              contador--;
              } else  {
              printf("\n- - - - - -  DIA INVALIDO - - - - - -\n\n");
              }
            }
          }

        }else{
          printf("\n- - - - - -  SOLO SE ADMITEN NUMEROS - - - - - -\n\n");
        }
        while (getchar() != '\n');
      }

      sprintf(fechaIngreso, "%s/%s/%s", dia, mes, ano);
      strcpy(nuevaPropiedad.fecha_de_ingreso, fechaIngreso);
    }

  if (strcmp(campoAComprobar, "zona") == 0) {
    do{
      if(validarTipoDato(&validacion, "cadena")){
      strcpy(nuevaPropiedad.zona, validacion.datoCadena);
      error = 0;
    } else {
      printf("Error, intentelo nuevamente\n");
      printf("Ingrese %s: ", campoAComprobar);
      error++;
    }
    } while (error > 0);
  }
  if (strcmp(campoAComprobar, "ciudad") == 0) {
    do{
      if(validarTipoDato(&validacion, "cadena")){
      strcpy(nuevaPropiedad.ciudad, validacion.datoCadena);
      error = 0;
    } else {
      printf("Error, intentelo nuevamente\n");
      printf("Ingrese %s: ", campoAComprobar);
      error++;
    }
    } while (error > 0);
  }
  if (strcmp(campoAComprobar, "dormitorios") == 0) {
      if(validarTipoDato(&validacion, "entero")){
      error = 0;
      nuevaPropiedad.dormitorios = validacion.datoEntero;
      } else {
      error++;
      }
  }
  if (strcmp(campoAComprobar, "banos") == 0) {
    if(validarTipoDato(&validacion, "entero")){
      error = 0;
      nuevaPropiedad.banos = validacion.datoEntero;
      } else {
      error++;
      }
  }
  if (strcmp(campoAComprobar, "superficie total") == 0) {
    if(validarTipoDato(&validacion, "flotante")){
      error = 0;
      nuevaPropiedad.superficie_total = validacion.datoFlotante;
      } else {
      error++;
      }
  }
  if (strcmp(campoAComprobar, "superficie cubierta") == 0) {
    if(validarTipoDato(&validacion, "flotante")){
      error = 0;
      nuevaPropiedad.superficie_cubierta = validacion.datoFlotante;
      } else {
      error++;
      }
  }
  if (strcmp(campoAComprobar, "precio") == 0) {
    if(validarTipoDato(&validacion, "flotante")){
      error = 0;
      nuevaPropiedad.precio = validacion.datoFlotante;
      } else {
      error++;
      }
  }
  if (strcmp(campoAComprobar, "moneda") == 0) {
    error = seleccionoMoneda(&nuevaPropiedad);
  }
  if (strcmp(campoAComprobar, "tipo") == 0) {
    error = seleccionoTipo(&nuevaPropiedad);
  }
  if (strcmp(campoAComprobar, "operacion") == 0) {
    error = seleccionoOperacion(&nuevaPropiedad);
  }
  if (strcmp(campoAComprobar, "fecha de salida") == 0) {
    printf("%s", nuevaPropiedad.fecha_de_ingreso);
  }
  
  while (getchar() != '\n');  // Limpiar el búfer de entrada
  return error;
}

/*
propiedad nuevaPropiedad;
  FILE *pArchivo;
  pArchivo = fopen("propiedades.dat", "ab");
  int id, result;

  if (pArchivo != NULL) {
    printf("ALTA DE PROPIEDAD:\n");


    nuevaPropiedad.id = id;
    obtengoFechaActual(&nuevaPropiedad);

    printf("Ingrese la zona de la nueva propiedad (max. 30 caracteres):");
    scanf("%s", nuevaPropiedad.zona);
    printf("Ingrese la ciudad de la nueva propiedad (max. 30 caracteres):");
    scanf("%s", nuevaPropiedad.ciudad);
    printf("Ingrese los dormitorios de la nueva propiedad:");
    scanf("%d", &nuevaPropiedad.dormitorios);
    printf("Ingrese los banos de la nueva propiedad:");
    scanf("%d", &nuevaPropiedad.banos);
    printf("Ingrese el total de la superficie de la nueva propiedad:");
    scanf("%f", &nuevaPropiedad.superficie_total);
    printf("Ingrese la superficie cubierta de la nueva propiedad:");
    scanf("%f", &nuevaPropiedad.superficie_cubierta);
    printf("Ingrese el precio de la nueva propiedad:");
    scanf("%f", &nuevaPropiedad.precio);
    printf("Ingrese la moneda de la nueva propiedad:");
    seleccionoMoneda(&nuevaPropiedad);
    printf("Ingrese el tipo de la nueva propiedad:");
    seleccionoTipo(&nuevaPropiedad);
    printf("Ingrese el tipo de operacion de la nueva propiedad:");
    seleccionoOperacion(&nuevaPropiedad);
    printf(
        "Ingrese la fecha de salida de la nueva propiedad en el formato "
        "DD/MM/YYYY:\n");

    nuevaPropiedad.activo = 1;
  } else {
    printf("Error en la apertura del archivo");
    exit(-1);
  }
}
*/
  


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
   "activo"
  };

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
      for (int i = 0; i < numPropiedades; i++) {

        do 
        { 
          error = alta(propiedades[i]);

          if(error == 1){
            printf("Revise la informacion introducida para el campo %s y reintentelo nuevamente \n", propiedades[i]);
          }
        }while (error == 1);
        

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
