void bajaFisica(char *nombreArchivo) {
  FILE *pArchivo = fopen("propiedades.dat", "rb+");
  if (pArchivo == NULL) {
    perror("Error al abrir propiedades.dat");
    return;
  }

  FILE *pArchivoCsv;
  time_t tiempo = time(NULL);
  struct tm *tm_info = localtime(&tiempo);
  printf("%s", nombreArchivo);

  char nombreArchivoCsv[50];

  strftime(nombreArchivoCsv, sizeof(nombreArchivoCsv), "propiedades_bajas_%d-%m-%Y.xyz", tm_info);

  pArchivoCsv = fopen(nombreArchivoCsv, "w");
  if (pArchivoCsv == NULL) {
    perror("Error al abrir archivo de pArchivoCsv");
    fclose(pArchivo);
    return;
  }

  propiedad prop;
  int modificado = 0;

  propiedad prop_temp = {0};  // Inicializa todos los campos en 0 o cadenas vacías

  while (fread(&prop, sizeof(propiedad), 1, pArchivo) == 1) {
    if (prop.activo == 0) {
      fprintf(pArchivoCsv, "%.2d | %11s | %21s | %14s | %.1d | %.1d | %5f | %5f | %8f | %3s | %10s | %10s | %1s | %d\n",
              prop.id, prop.fecha_de_ingreso, prop.zona, prop.ciudad, prop.dormitorios,
              prop.banos, prop.superficie_total, prop.superficie_cubierta, prop.precio, prop.moneda,
              prop.tipo, prop.operacion, prop.fecha_de_salida, prop.activo);

      fseek(pArchivo, -sizeof(propiedad), SEEK_CUR);

      fwrite(&prop_temp, sizeof(propiedad), 1, pArchivo);  // Sobreescribe con valores iniciales
      modificado = 1;
    }
  }

  fclose(pArchivo);
  fclose(pArchivoCsv);

  if (modificado) {
    printf("Se han guardado las propiedades inactivas en %s y se han actualizado los registros en propiedades.dat.\n", nombreArchivoCsv);
    // Copiamos el nombre del archivo en la cadena proporcionada.
    strcpy(nombreArchivo, nombreArchivoCsv);
  } else {
    printf("No se encontraron propiedades inactivas.\n");
  }
}