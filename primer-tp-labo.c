// Este es el primer TP de labo II.
// Sientanse libres de cambiar el nombre del archivo por el que querramos todos.
// Les dejo una base para que arranquemos ;)
// Configurense el VsCode para que formatee automaticamente los archivos al guardar. Asi estamos todos en la misma sintonia

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void procedaOperacion(char opcionElegida) {
    printf("Opción elegida: %c\n", opcionElegida);
    char opcionElegidaMinuscula = tolower(opcionElegida);

    if(opcionElegidaMinuscula == 'a'){
      printf("Testing a");

    }else if(opcionElegidaMinuscula == 'b'){

    }else if(opcionElegidaMinuscula == 'c'){

    }else if(opcionElegidaMinuscula == 'd'){

    }else if(opcionElegidaMinuscula == 'e'){

    }else if(opcionElegidaMinuscula == 'f'){

    }else if(opcionElegidaMinuscula == 'g'){

    }else if(opcionElegidaMinuscula == 'h'){
      
    }else{
      printf("------------------------- La opcion ingresada no es valida -------------------------\n");
      obtenerSeleccion(&opcionElegida);
    }
}

void obtenerSeleccion(char * opcionElegida) {
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
    procedaOperacion(*opcionElegida);

}

int main() {
    char opcion;
    char *opcionElegida = &opcion;

    obtenerSeleccion(opcionElegida);

    return 0;
}
