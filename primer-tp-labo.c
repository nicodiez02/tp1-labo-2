#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "./helpers/index.h"

void cargarArchivo(int *posicionColumnaActivo) {
  propiedad datos[15] = {
    {1,"23/12/2019","Capital Federal","San Cristobal",7,2,140.0,140.0,153000.0,"USD","Departamento","Venta","6/2/2020",1},
    {2,"21/11/2019","Capital Federal","Boedo",1,2,70,58,159000,"USD","PH","Venta","05/01/20",1},
    {3,"01/11/19","Capital Federal","Palermo",1,1,45,45,125000,"USD","Departamento","Venta",1},
    {4,"23/12/2019","Capital Federal","Palermo",1,1,85,50,295000,"PESOS","PH","Alquiler","01/04/20",1},
    {5,"11/03/20","Bs.As. G.B.A Zona Sur","La Plata",1,1,50,35,40000,"USD","Casa","Venta","24/7/2021",1},
    {6,"01/11/19","Capital Federal","Villa Crespo",1,1,56,56,150000,"USD","PH","Venta","09/02/20",1},
    {7,"31/10/2019","Capital Federal","Villa Crespo",1,1,70,70,159500,"USD","Departamento","Venta",1},
    {8,"31/10/2019","Capital Federal","Villa Crespo",1,1,70,70,159500,"PESOS","PH","Alquiler","08/02/20",1},
    {9,"23/12/2019","Capital Federal","Parque Patricios",1,1,45,37,2400.00,"USD","Departamento","Alquiler temporal","01/04/20",1},
    {10,"23/12/2019","Capital Federal","Parque Patricios",1,1,45,37,89000,"USD","Casa","Venta","05/01/20",1},
    {11,"07/12/19","Capital Federal","Villa Pueyrredón",1,2,66,49,170000,"USD","PH","Venta","16/3/2020",1},
    {12,"26/10/2019","Capital Federal","Boedo",1,1,68,59,149000,"PESOS","Departamento","Alquiler",1},
    {13,"19/12/2019","Capital Federal","Boedo",1,1,50,44,115000,"USD","Departamento","Venta","28/3/2020",1},
    {14,"30/11/2019","Bs.As. G.B.A. Zona Norte","Pilar",1,1,50,35,145000.00,"PESOS","PH","Alquiler",1}
  };
  propiedad propiedad;

  FILE *pArchivo = fopen("propiedades.dat", "ab");

  if (pArchivo != NULL) {
    for (int i = 0; i < 14; i++) {
      int dia = (rand() % 28) + 1;
      int mes = (rand() % 12) + 1;
      int ano = (rand() % 23) + 2000;
      char fecha[12];

      sprintf(fecha, "%02d/%02d/%04d", dia, mes, ano);

      propiedad.id = datos[i].id;
      strcpy(propiedad.zona, datos[i].zona);
      strcpy(propiedad.fecha_de_ingreso, datos[i].fecha_de_ingreso);
      strcpy(propiedad.ciudad, datos[i].ciudad);
      propiedad.dormitorios = datos[i].dormitorios;
      propiedad.banos = datos[i].banos;
      propiedad.superficie_cubierta = datos[i].superficie_cubierta;
      propiedad.superficie_total = datos[i].superficie_total;
      propiedad.precio = datos[i].precio;
      strcpy(propiedad.moneda, datos[i].moneda);
      strcpy(propiedad.tipo, datos[i].tipo);
      strcpy(propiedad.operacion, datos[i].operacion);
      strcpy(propiedad.fecha_de_salida, datos[i].fecha_de_salida);
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
};

int main() {
  srand(time(NULL));
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

  int continuar = 1;
  int numPropiedades = sizeof(propiedades) / sizeof(propiedades[0]);
  int idELiminar,posicionColumnaActivo,error;
  bool terminarBuscar,continuarModificar;

  while (continuar) {
    char opcionElegida,opcionElegidaMinuscula,subMenuOpcionElegida;
    FILE *pArchivo;

    opcionElegida = obtenerSeleccion();
    opcionElegidaMinuscula = tolower(opcionElegida);

    if (opcionElegidaMinuscula == 'a') {

      posicionColumnaActivo = 0;
      creoArchivoBinario(&pArchivo);
      cargarArchivo(&posicionColumnaActivo);

    } else if (opcionElegidaMinuscula == 'b') {

      subMenuOpcionElegida = submenuListar();
      listoArchivoBinario(subMenuOpcionElegida);

    } else if (opcionElegidaMinuscula == 'c') {

      error = 1;
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
      terminarBuscar = 1;
        while (terminarBuscar) {
          terminarBuscar = buscar();
        }

    } else if (opcionElegidaMinuscula == 'e') {
      continuarModificar = CONTINUAR_MODIFICAR;
      
      while (continuarModificar) {
        continuarModificar = modificar();
      }
    } else if (opcionElegidaMinuscula == 'f') {
      pArchivo = fopen("propiedades.dat", "rb+");
      error = 1;
      idELiminar = 0;;

      listoArchivoBinario('a');
      while (error == 1)
      {  
        printf("\nIngrese el id del registro que desea dar de baja:");
        
        if(idValido(&pArchivo)){
          error = 0;
        }

      }

      bajalogica(pArchivo);
      fclose(pArchivo);
    } else if (opcionElegidaMinuscula == 'q') {  // 'q' para salir

      continuar = 0;  // Cambia continuar a 0 para salir del bucle.
    } else {
      printf(
          "------------------------- La opcion ingresada no es valida "
          "-------------------------\n\n");
    }
  };

  return 0;
};
