void listoArchivoBinario(char opcion){

  int diaInicio,mesInicio,añoInicio;
  int diaFin,mesFin,añoFin;

  int encontrado = 0;  // Variable para rastrear si se encontró el campo
  char opcionToLower = tolower(opcion);
  char campoAPrintear[30];  // Declarar como un arreglo de caracteres
  char *arrayComparativo[] = {
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

  FILE *pArchivo;
  propiedad prop;
  pArchivo = fopen("propiedades.dat", "rb");

if (opcionToLower == 'a'){
    if ((pArchivo) != NULL){

        printf("\n");
      printf("%2s | %22s | %10s | %10s | %11s | %6s  | %15s| %18s | %7s | %10s | %10s | %10s | %21s | %5s\n",
       "ID", "Fecha de Ingreso", "Zona", "Ciudad", "Dormitorios", "Baños", "Superficie Total",
       "Superficie Cubierta", "Precio", "Moneda", "Tipo", "Operación", "Fecha de Salida", "Activo");
      fread(&prop, sizeof(propiedad), 1, pArchivo);
      
      while (!feof(pArchivo))
      {
        printf("%.2d | %22s | %10s | %10s | %.11d | %.6d | %15f | %18f | %7f | %10s | %10s | %10s | %21s | %d\n",
               prop.id, prop.fecha_de_ingreso, prop.zona, prop.ciudad, prop.dormitorios,
               prop.banos, prop.superficie_total, prop.superficie_cubierta, prop.precio, prop.moneda,
               prop.tipo, prop.operacion, prop.fecha_de_salida, prop.activo);
        fread(&prop, sizeof(propiedad), 1, pArchivo);
      }

      
      fclose(pArchivo);
    }else{
      printf("Error en la apertura del archivo");
      exit(-1);
    }
    getchar();
    }else if(opcionToLower == 'b'){
      
      printf("ACTIVO\n");
      printf("------\n");

      while (!feof(pArchivo)){
        fread(&prop, sizeof(propiedad), 1, pArchivo);
        printf("%d\n", prop.activo);
      }

      return;


    }else if (opcionToLower == 'c') {
        printf("\n¿Qué campo desea listar?\n");
        scanf(" %29[^\n]", campoAPrintear);
    
        for (int i = 0; i < 14; i++) {
            if (strcmp(arrayComparativo[i], campoAPrintear) == 0) {
                while (!feof(pArchivo)) {
                    fread(&prop, sizeof(propiedad), 1, pArchivo);

                    if (strcmp("id", campoAPrintear) == 0) {
                        printf("ID: %i\n", prop.id);
                    } else if (strcmp("fecha de ingreso", campoAPrintear) == 0) {
                        printf("Fecha de Ingreso: %s\n", prop.fecha_de_ingreso);
                    } else if (strcmp("zona", campoAPrintear) == 0) {
                        printf("Zona: %s\n", prop.zona);
                    } else if (strcmp("ciudad", campoAPrintear) == 0) {
                        printf("Ciudad: %s\n", prop.ciudad);
                    } else if (strcmp("dormitorios", campoAPrintear) == 0) {
                        printf("Dormitorios: %i\n", prop.dormitorios);
                    } else if (strcmp("banos", campoAPrintear) == 0) {
                        printf("Baños: %i\n", prop.banos);
                    } else if (strcmp("superficie total", campoAPrintear) == 0) {
                        printf("Superficie Total: %.2f\n", prop.superficie_total);
                    } else if (strcmp("superficie cubierta", campoAPrintear) == 0) {
                        printf("Superficie Cubierta: %.2f\n", prop.superficie_cubierta);
                    } else if (strcmp("precio", campoAPrintear) == 0) {
                        printf("Precio: %.2f\n", prop.precio);
                    } else if (strcmp("moneda", campoAPrintear) == 0) {
                        printf("Moneda: %s\n", prop.moneda);
                    } else if (strcmp("tipo", campoAPrintear) == 0) {
                        printf("Tipo: %s\n", prop.tipo);
                    } else if (strcmp("operacion", campoAPrintear) == 0) {
                        printf("Operación: %s\n", prop.operacion);
                    } else if (strcmp("fecha de salida", campoAPrintear) == 0) {
                        printf("Fecha de Salida: %s\n", prop.fecha_de_salida);
                    } else if (strcmp("activo", campoAPrintear) == 0) {
                        printf("Activo: %i\n", prop.activo);
                    }
                }
                encontrado = 1;
                break;  // Terminar el bucle una vez que se encuentre el campo
            }
        }


        if (!encontrado) {
            printf("El campo '%s' no fue encontrado.\n", campoAPrintear);
            return;
        }
    }else if(opcionToLower == 'd'){

        //falta validar como ingresa la fecha, tiene que ser formato 00/00/0000
        //si ingresa 01,02, 03 etc se rompe. Creo que es porque lo lee como /0 y hace un salto de linea en vez de leer el dato
        int error = 0;
        while (error == 0)
        {

            printf("\nINGRESANDO FECHA DE INICIO:\n");
            printf("DIA:");
            scanf("%d", &diaInicio);

            printf("MES:");
            scanf("%d", &mesInicio);

            printf("AÑO:");
            scanf("%d", &añoInicio);

            printf("\nINGRESANDO FECHA DE FIN:\n");
            printf("DIA:");
            scanf("%d", &diaFin);

            printf("MES:");
            scanf("%d", &mesFin);

            printf("AÑO:");
            scanf("%d", &añoFin);

            if( diaInicio >= 1 && 
                diaInicio <= 31 && 
                diaFin >= 1 && 
                diaFin <= 31 &&
                mesInicio >= 1 &&
                mesInicio <= 12 &&
                mesFin >= 1 &&
                mesFin <= 12 &&
                añoInicio > 0 &&
                añoFin > 0 ){
                
                error = 1;
            }else{
                printf("\nREVISE LAS FECHAS INGRESADAS E INTENTELO NUEVAMENTE. \n");
            }


        }

        while (!feof(pArchivo)){
            fread(&prop, sizeof(propiedad), 1, pArchivo);

            int longitud = strlen(prop.fecha_de_ingreso);
            int contadorDeBarras = 0;
            int contadorAuxiliar = 0;
            char diaStruct[4];
            char mesStruct[4];
            char añoStruct[6];

            for (int i = 0; i < longitud; i++) {
                char caracter = prop.fecha_de_ingreso[i];

                if(caracter != '/'){

                    if(contadorDeBarras == 0){

                        diaStruct[contadorAuxiliar] = caracter;
                        contadorAuxiliar++;

                    }else if(contadorDeBarras == 1){

                        mesStruct[contadorAuxiliar] = caracter;
                        contadorAuxiliar++;

                    }else{

                        añoStruct[contadorAuxiliar] = caracter;
                        contadorAuxiliar++;

                    }
                }else{
                    contadorAuxiliar = 0;
                    contadorDeBarras++;
                }
            }


            diaStruct[3] = '\0'; 
            mesStruct[3] = '\0';
            añoStruct[5] = '\0';

            int diaStructNum = atoi(diaStruct);
            int mesStructNum = atoi(mesStruct);
            int añoStructNum = atoi(añoStruct);

            if(añoStructNum > añoInicio && añoStructNum < añoFin){
                
                  printf(
      "%.2d | %15s | %10s | %10s | %.2d | %.2d | %5.2f | %5.2f | %5.2f | %10s "
      "| %10s | %10s | %20s | %d\n",
      prop.id, prop.fecha_de_ingreso, prop.zona,
      prop.ciudad, prop.dormitorios, prop.banos,
      prop.superficie_total, prop.superficie_cubierta,
      prop.precio, prop.moneda, prop.tipo,
      prop.operacion, prop.fecha_de_salida,
      prop.activo);
                
            }else if(añoStructNum == añoInicio){

                if(mesStructNum > mesInicio){
                      printf(
      "%.2d | %15s | %10s | %10s | %.2d | %.2d | %5.2f | %5.2f | %5.2f | %10s "
      "| %10s | %10s | %20s | %d\n",
      prop.id, prop.fecha_de_ingreso, prop.zona,
      prop.ciudad, prop.dormitorios, prop.banos,
      prop.superficie_total, prop.superficie_cubierta,
      prop.precio, prop.moneda, prop.tipo,
      prop.operacion, prop.fecha_de_salida,
      prop.activo);
                }else if(mesStructNum == mesInicio){

                    if(diaStructNum > diaInicio){
                          printf(
      "%.2d | %15s | %10s | %10s | %.2d | %.2d | %5.2f | %5.2f | %5.2f | %10s "
      "| %10s | %10s | %20s | %d\n",
      prop.id, prop.fecha_de_ingreso, prop.zona,
      prop.ciudad, prop.dormitorios, prop.banos,
      prop.superficie_total, prop.superficie_cubierta,
      prop.precio, prop.moneda, prop.tipo,
      prop.operacion, prop.fecha_de_salida,
      prop.activo);
                    }
                    /*else if(diaStructNum == diaInicio){
                        printf("LA FECHA ES IGUAL A LA FECHA DE INICIO:\n");
                    }
                    */

                }


            }else if(añoStructNum == añoFin){

                if(mesStructNum > mesFin){
                      printf(
      "%.2d | %15s | %10s | %10s | %.2d | %.2d | %5.2f | %5.2f | %5.2f | %10s "
      "| %10s | %10s | %20s | %d\n",
      prop.id, prop.fecha_de_ingreso, prop.zona,
      prop.ciudad, prop.dormitorios, prop.banos,
      prop.superficie_total, prop.superficie_cubierta,
      prop.precio, prop.moneda, prop.tipo,
      prop.operacion, prop.fecha_de_salida,
      prop.activo);
                }else if(mesStructNum == mesFin){

                    if(diaStructNum > diaFin){
                          printf(
      "%.2d | %15s | %10s | %10s | %.2d | %.2d | %5.2f | %5.2f | %5.2f | %10s "
      "| %10s | %10s | %20s | %d\n",
      prop.id, prop.fecha_de_ingreso, prop.zona,
      prop.ciudad, prop.dormitorios, prop.banos,
      prop.superficie_total, prop.superficie_cubierta,
      prop.precio, prop.moneda, prop.tipo,
      prop.operacion, prop.fecha_de_salida,
      prop.activo);
                    }
                    /*else if(diaStructNum == diaFin){
                        printf("LA FECHA ES IGUAL A LA FECHA DE FIN:\n");
                    }
                    */

                }
            }
        }
            
    }else if (opcionToLower == 'e'){
        return;
    }
}

char submenuListar()
{
  char opcionElegida = '\0';

  printf("\n¿Qué operación desea listar?\n");
  printf("A) Listar todos (altas y bajas)\n"
         "B) Listar solo el campo activo\n"
         "C) Ingreso por teclado de un tipo de propiedad\n"
         "D) Ingreso de un rango de tiempo de ingreso (mínimo y máximo)\n"
         "E) Volver al menú principal\n");
  scanf(" %c", &opcionElegida);

  return opcionElegida;
}
