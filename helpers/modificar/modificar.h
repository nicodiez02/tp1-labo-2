#include <stdio.h>

const int CONTINUAR_MODIFICAR = true;

bool confirmarOperacion(char dato[10]) {
  char seleccion;
  printf("\n¿Esta seguro que desea modificar los datos de %s?\n", dato);
  printf("\nA) Si\nB) No\n");
  scanf(" %c", &seleccion);
  if (tolower(seleccion) == 'a') {
    return true;
  }
  if (tolower(seleccion) == 'b') {
    return false;
  }
  return false;
};

int modificar() {
  propiedad propiedadLeida;

  FILE *pArchivo;
  pArchivo = fopen("propiedades.dat", "r+b");

  if (!pArchivo) return CONTINUAR_MODIFICAR;

  int id;
  char seleccion;
  char nuevoBarrio[50];
  float nuevoPrecio;

  printf("\nIngrese el ID de la propiedad a modificar\n");
  printf("\nIngrese \"00\" para volver al menu\n");
  scanf(" %i", &id);

  if (id == 00) return !CONTINUAR_MODIFICAR;

  fseek(pArchivo, 0, SEEK_END);
  fseek(pArchivo, (id - 1) * sizeof(propiedad), SEEK_SET);
  fread(&propiedadLeida, sizeof(propiedad), 1, pArchivo);

  // validar que ingrese un numero y no letras

  if (propiedadLeida.id != id) {
    printf("\nNo existe un registro con ese ID.\n");
    printf("\nVuelva a intentarlo\n");
    return CONTNUAR_BUSCAR_POR_ID;
  }

  printPropiedad(propiedadLeida);
  printf("\n¿Que dato desea modificar?\n");
  printf("\nA) Ciudad\nB) Precio\n");
  printf("\nPresione cualquier tecla para volver al menu principal\n");
  scanf(" %c", &seleccion);
  if (tolower(seleccion) == 'a') {
    printf("\nIngrese el nuevo ciudad:\n");
    scanf(" %s", nuevoBarrio);
    bool confirmar = confirmarOperacion("Ciudad");
    if (confirmar) {
      strcpy(propiedadLeida.ciudad, nuevoBarrio);
      
      fseek(pArchivo, -sizeof(propiedad), SEEK_CUR);
      fwrite(&propiedadLeida, sizeof(propiedad), 1, pArchivo);
      printPropiedad(propiedadLeida);
      fclose(pArchivo);
      return preguntarContinuar();
    } else {
      fclose(pArchivo);
      return preguntarContinuar();
    }
  } else if (tolower(seleccion) == 'b') {
    printf("\nIngrese el nuevo precio:\n");
    scanf(" %f", &nuevoPrecio);
    bool confirmar = confirmarOperacion("Precio");
    if (confirmar) {
      propiedadLeida.precio = nuevoPrecio;
      fseek(pArchivo, -sizeof(propiedad), SEEK_CUR);
      fwrite(&propiedadLeida, sizeof(propiedad), 1, pArchivo);
      printPropiedad(propiedadLeida);
      fclose(pArchivo);
      return preguntarContinuar();
    } else {
      fclose(pArchivo);
      return preguntarContinuar();
    }
  }
  fclose(pArchivo);
  return !CONTINUAR_MODIFICAR;
};