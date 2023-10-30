void bajaFisica() {
    FILE *pArchivo = fopen("propiedades.dat", "rb+");
    if (pArchivo == NULL) {
        perror("Error al abrir propiedades.dat");
    }

    FILE *pArchivoCsv;
    char nombreArchivo[50];
    time_t tiempo = time(NULL);
    struct tm *tm_info = localtime(&tiempo);
    strftime(nombreArchivo, sizeof(nombreArchivo), "propiedades_bajas_%d-%m-%Y.xyz", tm_info);

    pArchivoCsv = fopen(nombreArchivo, "w");
    if (pArchivoCsv == NULL) {
        perror("Error al abrir archivo de pArchivoCsv");
    }

    propiedad prop;
    int modificado = 0;
    
    while (fread(&prop, sizeof(propiedad), 1, pArchivo) == 1) {
        if (prop.activo == 0) {
            fprintf(pArchivoCsv, "%.2d | %11s | %21s | %14s | %.1d | %.1d | %5f | %5f | %8f | %3s | %10s | %10s | %1s | %d\n",
               prop.id, prop.fecha_de_ingreso, prop.zona, prop.ciudad, prop.dormitorios,
               prop.banos, prop.superficie_total, prop.superficie_cubierta, prop.precio, prop.moneda,
               prop.tipo, prop.operacion, prop.fecha_de_salida, prop.activo);

            fseek(pArchivo, -sizeof(propiedad), SEEK_CUR);

            prop.id = 0;
            strcpy(prop.fecha_de_ingreso, "0");
            strcpy(prop.zona, "0");
            strcpy(prop.ciudad, "0");
            prop.dormitorios = 0;
            prop.banos = 0;
            prop.superficie_total = 0.0;
            prop.superficie_cubierta = 0.0;
            prop.precio = 0.0;
            strcpy(prop.moneda, "0");
            strcpy(prop.tipo, "0");
            strcpy(prop.operacion, "0");
            strcpy(prop.fecha_de_salida, "0");
            
            fwrite(&prop, sizeof(propiedad), 1, pArchivo);
            modificado = 1;
        }
    }


    fclose(pArchivo);
    fclose(pArchivoCsv);

    if (modificado) {
        printf("Se han guardado las propiedades inactivas en %s y se han actualizado los registros en propiedades.dat.\n", nombreArchivo);
    } else {
        printf("No se encontraron propiedades inactivas.\n");
    }

}
