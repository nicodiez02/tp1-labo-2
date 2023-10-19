#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

struct propiedad{
  int id;
  char fecha_de_ingreso[10];
  char zona[30];
  char ciudad[30];
  int dormitorios;
  int banos;
  float superficie_total;
  float superficie_cubierta;
  float precio;
  char moneda[10];
  char tipo[30];
  char operacion[30];
  char fecha_de_salida[10];
  int activo;
};

void cargarArchivo(){
  struct propiedad nuevaPropiedad;
  FILE *pArchivo;
  pArchivo = fopen("propiedades.dat", "ab");

  if(pArchivo != NULL){
    for(int i = 0; i < 15; i++){
      nuevaPropiedad.id = i;
      strcpy(nuevaPropiedad.zona, "zona1");
      strcpy(nuevaPropiedad.fecha_de_ingreso, "10/10/2021");
      strcpy(nuevaPropiedad.ciudad, "ciudad1");
      nuevaPropiedad.dormitorios = i;
      nuevaPropiedad.banos = i;
      nuevaPropiedad.superficie_cubierta = i;
      nuevaPropiedad.superficie_total = i;
      nuevaPropiedad.precio = i;    
      strcpy(nuevaPropiedad.moneda, "moneda");
      strcpy(nuevaPropiedad.tipo, "tipo");
      strcpy(nuevaPropiedad.operacion, "operacion"); 
      strcpy(nuevaPropiedad.fecha_de_salida, "08/11/2002");  
      nuevaPropiedad.activo = 1;   
      fwrite(&nuevaPropiedad,sizeof(struct propiedad),1,pArchivo);  
    }
    fclose(pArchivo);
  }
}

void creoArchivoBinario(FILE ** pArchivo){
  *pArchivo = fopen("propiedades.dat","wb+");
  if((*pArchivo) != NULL){
    printf("%s", "Archivo binario creado");
  }

  cargarArchivo();
  obtenerSeleccion();
}

void submenuListar(){
    char opcion;
    char * opcionElegida = &opcion;

    printf("\n¿Qué operación desea listar?\n");
    printf("A) Listar todos (altas y bajas)\n"
           "B) Listar solo el campo activo\n"
           "C) Ingreso por teclado de un tipo de propiedad\n"
           "D) Ingreso de un rango de tiempo de ingreso (mínimo y máximo)\n"
           "E) Volver al menú principal\n");
    scanf(" %c", opcionElegida);  
    listoArchivoBinario(*opcionElegida);
}

void listoArchivoBinario(char opcion){
    char opcionToLower = tolower(opcion);
    FILE * pArchivo;
    struct propiedad prop;
    pArchivo = fopen("propiedades.dat","rb");

  if(opcionToLower == 'a'){
    if((pArchivo) != NULL){
      fread(&prop,  sizeof(struct propiedad), 1, pArchivo);
      while( !feof(pArchivo) ){
        printf("%.2d | %15s | %10s | %10s | %.2d | %.2d | %5.2f | %5.2f | %5.2f | %10s | %10s | %10s | %20s | %d\n",
        prop.id, prop.fecha_de_ingreso, prop.zona, prop.ciudad, prop.dormitorios,
        prop.banos, prop.superficie_total, prop.superficie_cubierta, prop.precio, prop.moneda,
        prop.tipo, prop.operacion, prop.fecha_de_salida, prop.activo);
        fread(&prop,  sizeof(struct propiedad), 1, pArchivo);
      }
    fclose(pArchivo);
    }else{
      printf("Error en la apertura del archivo");
      exit(-1);
    }
    getchar();
      //Otras opciones..
  }else if(opcionToLower == 'e'){
      obtenerSeleccion();
  }
  submenuListar();
}

void procedaOperacion(char opcionElegida, FILE ** pArchivo) {
    printf("Opción elegida: %c\n", opcionElegida);
    char opcionElegidaMinuscula = tolower(opcionElegida);

    if(opcionElegidaMinuscula == 'a'){
      creoArchivoBinario(pArchivo);
    }else if (opcionElegidaMinuscula == 'b'){
      submenuListar();
    }else if(opcionElegidaMinuscula == 'c'){
      alta();
    }else if(opcionElegidaMinuscula == 'd'){

    }else if(opcionElegidaMinuscula == 'e'){

    }else if(opcionElegidaMinuscula == 'f'){

    }else if(opcionElegidaMinuscula == 'g'){

    }else if(opcionElegidaMinuscula == 'h'){
      
    }else{
      printf("------------------------- La opcion ingresada no es valida -------------------------\n");
      obtenerSeleccion(&opcionElegida, pArchivo);
    }
}

void comprobar_id(float * id, struct propiedad * nuevaPropiedad){
  FILE * pArchivo;
  pArchivo = fopen("propiedades.dat", "rb");

  struct propiedad otraPropiedad;
  int ent;
  int flag = 0;
  ent = (*id);

  if ((*id) < 0){
    printf("El numero ingresado no puede ser negativo, intentelo de nuevo\n");
    /* reingreso() */
  } else if((*id) - ent){
    printf("El numero ingresado no puede ser decimal, intentelo de nuevo, %f\n", ((*id) - ent));
    /* reingreso() */
  } else {
    if (pArchivo != NULL){
      fread(&otraPropiedad, sizeof(struct propiedad), 1, pArchivo);
      while (!feof(pArchivo)){
        if ((*id) == otraPropiedad.id){
          flag = 1;
        }
        fread(&otraPropiedad, sizeof(struct propiedad),1, pArchivo);
      }
      if (flag == 1){
        printf("El numero ingresado ya existe, intentelo de nuevo\n");
        /* reingreso() */
      } else {
        (*nuevaPropiedad).id = ent;
      }
      fclose(pArchivo);
    } else {
      printf("Error en la apertura del archivo");
      exit(-1);
    }
  }
}

void obtengoFechaActual(struct propiedad * nuevaPropiedad){
  char fecha[11];
  time_t tiempo;
  struct tm *infoTiempo;
  char formato[] = "%d/%m/%Y"; // Formato DD/MM/AAAA

  time(&tiempo);
  infoTiempo = localtime(&tiempo);

  strftime(&fecha, 11, formato, infoTiempo);
  strcpy((*nuevaPropiedad).fecha_de_ingreso, fecha);
}

void alta() {
    struct propiedad nuevaPropiedad;
    FILE * pArchivo;
    pArchivo = fopen("propiedades.dat", "ab");
    float * id;

    if(pArchivo != NULL){
      printf("ALTA DE PROPIEDAD:\n");
      printf("Ingrese el ID de la nueva propiedad:\n");
      scanf("%f", id);
      comprobar_id(id, &nuevaPropiedad);
      obtengoFechaActual(&nuevaPropiedad);
      printf("Ingrese la zona de la nueva propiedad (max. 30 caracteres):\n");
      scanf("%s", &nuevaPropiedad.zona);
      printf("Ingrese la ciudad de la nueva propiedad:\n");
      scanf("%s", &nuevaPropiedad.ciudad);
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
      printf("Ingrese la fecha de salida de la nueva propiedad en el formato DD/MM/YYYY:\n");
      /*  nuevaPropiedad.fecha_de_salida = funcion para ingresar una fecha valida(); */
      nuevaPropiedad.activo = 1;
    } else {
      printf("Error en la apertura del archivo");
      exit(-1);
    }
}

void seleccionoMoneda(struct propiedad * nuevaPropiedad){
    char opcion;

    printf("a) Dolar\n");
    printf("b) Peso arg\n");
    printf("Seleccione una moneda (a/b): ");
    scanf(" %c", &opcion);

    if (tolower(opcion) == 'a'){
      strcpy((*nuevaPropiedad).moneda, "Dolar");
    }else if(tolower(opcion) == 'b'){
      strcpy((*nuevaPropiedad).moneda, "Peso arg");
    } else {
      printf("Seleccion no valida. Debe elegir 'a' o 'b'.\n");
      seleccionoMoneda(nuevaPropiedad);
    }
}

void seleccionoTipo(struct propiedad * nuevaPropiedad){
    char opcion;

    printf("a) PH\n");
    printf("b) Departamento\n");
    printf("c) Casa\n");
    printf("Seleccione un tipo (a/b/c): ");
    scanf(" %c", &opcion);

    if(tolower(opcion) == 'a'){
      strcpy((*nuevaPropiedad).tipo, "PH");
    }else if(tolower(opcion) == 'b'){
      strcpy((*nuevaPropiedad).tipo, "Departamento");
    }else if(tolower(opcion) == 'c') {
      strcpy((*nuevaPropiedad).tipo, "Casa");
    }else{
      printf("Seleccion no valida. Debe elegir 'a' o 'b' o 'c'.\n");
      seleccionoTipo(nuevaPropiedad);
    }
}

void seleccionoOperacion(struct propiedad * nuevaPropiedad){
    char opcion;

    printf("a) Venta\n");
    printf("b) Alquiler\n");
    printf("c) Alquiler temporal\n");
    printf("Seleccione una operacion (a/b/c): ");
    scanf(" %c", &opcion);

    if(tolower(opcion) == 'a'){
      strcpy((*nuevaPropiedad).operacion, "Venta");
    }else if(tolower(opcion) == 'b'){
      strcpy((*nuevaPropiedad).operacion, "Alquiler");
    }else if(tolower(opcion) == 'c') {
      strcpy((*nuevaPropiedad).operacion, "Alquiler temporal");
    }else{
      printf("Seleccion no valida. Debe elegir 'a' o 'b' o 'c'.\n");
      seleccionoOperacion(nuevaPropiedad);
    }
}
void obtenerSeleccion() {
    char opcion;
    char * opcionElegida = &opcion;
    FILE * pArchivo;
    
    printf("¿Qué operación desea realizar?\n");
    printf("A) Crear archivo binario\n"
           "B) Listar dat\n"
           "C) Alta\n"
           "D) Buscar\n"
           "E) Modificar\n"
           "F) Baja lógica\n"
           "G) Baja física\n"
           "H) Listar xyz\n");

    scanf(" %c", opcionElegida); 
    procedaOperacion(*opcionElegida, pArchivo);
}

int main() {
  obtenerSeleccion();

  return 0;
}
