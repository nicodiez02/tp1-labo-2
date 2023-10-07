// Este es el primer TP de labo II.
// Sientanse libres de cambiar el nombre del archivo por el que querramos todos.
// Les dejo una base para que arranquemos ;)
// Configurense el VsCode para que formatee automaticamente los archivos al guardar. Asi estamos todos en la misma sintonia

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void creoArchivoBinario(FILE ** pArchivo){
  *pArchivo = fopen("propiedades.dat","wb+");
  if((*pArchivo) != NULL){
    printf("%s", "Archio binario creado");
  }
}
void listoArchivoBinario(FILE ** pArchivo){
  //INTENTO COMPLETAMENTE FALLIDO, PERO CREO QUE VA POR ACA
  int num;
  *pArchivo = fopen("propiedades.dat","rb");
  if((*pArchivo) != NULL){
    //fread(&num, sizeof(struct),1,pArchivo);
    while(!feof(pArchivo)){
    printf("%d\n", num);
    fread(&num,sizeof(int),1,pArchivo);
    }
    fclose(pArchivo);
}

  /*} else {
    printf("%s", "Error en la apertura del archivo")
    exit(-1);
  }
  */
}

void procedaOperacion(char opcionElegida, FILE ** pArchivo) {
    printf("Opción elegida: %c\n", opcionElegida);
    char opcionElegidaMinuscula = tolower(opcionElegida);

    if(opcionElegidaMinuscula == 'a'){
      creoArchivoBinario(pArchivo);

    } else if (opcionElegidaMinuscula == 'b'){

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

void obtenerSeleccion(char * opcionElegida, FILE ** pArchivo) {
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
    char opcion;
    char *opcionElegida = &opcion;
    FILE * pArchivo;

    obtenerSeleccion(opcionElegida, &pArchivo);

    return 0;
}
