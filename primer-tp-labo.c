#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

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
  _Bool activo;
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
    printf("%s", "Archio binario creado");
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
      while(  !feof(pArchivo) ){
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
