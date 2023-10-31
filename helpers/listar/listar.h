#include "../printHeader/printHeader.h"

void listoArchivoBinario(char opcion) {
  int diaInicio, mesInicio, anoInicio;
  int diaFin, mesFin, anoFin;

  int encontrado = 0;  // Variable para rastrear si se encontró el campo
  char opcionToLower = tolower(opcion);
  char campoAPrintear[30];  // Declarar como un arreglo de caracteres

  FILE *pArchivo;
  propiedad prop;
  pArchivo = fopen("propiedades.dat", "rb");

  if (opcionToLower == 'a') {
    if ((pArchivo) != NULL) {
      fread(&prop, sizeof(propiedad), 1, pArchivo);

      printHeader();
      while (!feof(pArchivo)) {
        printPropiedad(prop);
        fread(&prop, sizeof(propiedad), 1, pArchivo);
      }

      fclose(pArchivo);
    } else {
      printf("Error en la apertura del archivo");
      exit(-1);
    }
    getchar();
  } else if (opcionToLower == 'b') {
    printHeader();
    while (!feof(pArchivo)) {
      fread(&prop, sizeof(propiedad), 1, pArchivo);

      if (prop.activo == 1) {
        printPropiedad(prop);
      }
    }

    return;

  } else if (opcionToLower == 'c') {
    char nombrePropiedad[15] = "";
    printf("\n¿Qué tipo de propiedad desea listar? - Tipee una opción (A, B, C)\n");
    printf("A) Departamento\nB) PH\nC) Casa\n");
    scanf(" %1[^\n]", campoAPrintear);
    char opcion = tolower(campoAPrintear[0]);

    if (opcion == 'a') {
      strcpy(nombrePropiedad, "Departamento");
    } else if (opcion == 'b') {
      strcpy(nombrePropiedad, "PH");
    } else if (opcion == 'c') {
      strcpy(nombrePropiedad, "Casa");
    } else {
      printf("Opción no válida\n");
    }

    printHeader();
    while (fread(&prop, sizeof(propiedad), 1, pArchivo) == 1) {
      if (strcmp(prop.tipo, nombrePropiedad) == 0) {
        printPropiedad(prop);
      }
    }

  } else if (opcionToLower == 'd') {
    // falta validar como ingresa la fecha, tiene que ser formato 00/00/0000
    // si ingresa 01,02, 03 etc se rompe. Creo que es porque lo lee como /0 y hace un salto de linea en vez de leer el dato
    int error = 0;
    while (error == 0) {
      printf("\nINGRESANDO FECHA DE INICIO:\n");
      printf("DIA:");
      scanf("%2d", &diaInicio);
      printf("MES:");
      scanf("%2d", &mesInicio);
      printf("ANO:");
      scanf("%4d", &anoInicio);

      printf("\nINGRESANDO FECHA DE FIN:\n");
      printf("DIA:");
      scanf("%2d", &diaFin);
      printf("MES:");
      scanf("%2d", &mesFin);
      printf("ANO:");
      scanf("%4d", &anoFin);

      if (diaInicio >= 1 &&
          diaInicio <= 31 &&
          diaFin >= 1 &&
          diaFin <= 31 &&
          mesInicio >= 1 &&
          mesInicio <= 12 &&
          mesFin >= 1 &&
          mesFin <= 12 &&
          anoInicio > 0 &&
          anoFin > 0) {
        error = 1;
      } else {
        printf("\nREVISE LAS FECHAS INGRESADAS E INTENTELO NUEVAMENTE. \n");
      }
    }

    printHeader();
    while (fread(&prop, sizeof(propiedad), 1, pArchivo) == 1) {
      struct tm fechaPropiedad_tm;

      if (sscanf(prop.fecha_de_ingreso, "%d/%d/%d", &fechaPropiedad_tm.tm_mday, &fechaPropiedad_tm.tm_mon, &fechaPropiedad_tm.tm_year)) {
        fechaPropiedad_tm.tm_year = fechaPropiedad_tm.tm_year - 1900;
        fechaPropiedad_tm.tm_mon = fechaPropiedad_tm.tm_mon - 1;
        fechaPropiedad_tm.tm_isdst = 0;
        fechaPropiedad_tm.tm_hour = 0;
        fechaPropiedad_tm.tm_min = 0;
        fechaPropiedad_tm.tm_sec = 0;

        // Convierte la fecha de propiedad a timestamp(time_t)
        time_t fechaPropiedad_timestamp = mktime(&fechaPropiedad_tm);

        // Convierte las fechas de inicio y fin a timestamp
        struct tm fechaInicio_tm = {0};
        fechaInicio_tm.tm_year = anoInicio - 1900;
        fechaInicio_tm.tm_mon = mesInicio - 1;
        fechaInicio_tm.tm_mday = diaInicio;

        struct tm fechaFin_tm = {0};
        fechaFin_tm.tm_year = anoFin - 1900;
        fechaFin_tm.tm_mon = mesFin - 1;
        fechaFin_tm.tm_mday = diaFin;

        time_t fechaInicio_timestamp = mktime(&fechaInicio_tm);
        time_t fechaFin_timestamp = mktime(&fechaFin_tm);

        if (fechaPropiedad_timestamp >= fechaInicio_timestamp &&
            fechaPropiedad_timestamp <= fechaFin_timestamp) {
          // La fecha de la propiedad está dentro del rango
          // Imprime los detalles de la propiedad
          printPropiedad(prop);
        }
      } else {
        return;
      }
    }

  } else if (opcionToLower == 'e') {
    return;
  }
}

char submenuListar() {
  char opcionElegida = '\0';

  printf("\n¿Qué operación desea listar?\n");
  printf(
      "A) Listar todos (altas y bajas)\n"
      "B) Listar solo el campo activo\n"
      "C) Ingreso por teclado de un tipo de propiedad\n"
      "D) Ingreso de un rango de tiempo de ingreso (mínimo y máximo)\n"
      "E) Volver al menú principal\n");
  scanf(" %c", &opcionElegida);

  return opcionElegida;
}
