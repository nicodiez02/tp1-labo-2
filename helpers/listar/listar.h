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

    printf(" %c", opcionToLower);
if (opcionToLower == 'a'){
    if ((pArchivo) != NULL){
      printf("%2s | %22s| %10s | %10s | %11s | %6s  | %15s| %18s | %7s | %10s | %10s | %10s | %21s | %5s\n",
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
    //  scanf(" %s", campoAPrintear);
        scanf(" %29[^\n]", campoAPrintear);
            //dnd guardar, //cant. caractares a leer,
    
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

        printf("INGRESANDO FECHA DE INICIO:\n\n");
        printf("DIA:");
        scanf("%i", diaInicio);

        prinf("\n");

        printf("MES:");
        scanf("%i", mesInicio);

        prinf("\n");

        printf("AÑO:");
        scanf("%i", añoInicio);

        prinf("\n");

        printf("INGRESANDO FECHA DE FIN:\n\n");
        printf("DIA:");
        scanf("%i", diaFin);

        prinf("\n");

        printf("MES:");
        scanf("%i", mesFin);

        prinf("\n");

        printf("AÑO:");
        scanf("%i", añoFin);

        while (!feof(pArchivo)){
            //Ir comparando cada fecha del archivo con las fechas ingresadas. La fecha del archivo debe ser > a la fecha inicial y < a la final.
            fread(&prop, sizeof(propiedad), 1, pArchivo);
            printf("FECHA DE INGRESO: %s\n", prop.fecha_de_ingreso);

            int longitud = strlen(prop.fecha_de_ingreso);
            int contadorDeBarras = 0;
            char diaStruct[3];
            char mesStruct[3];
            char añoStruct[5];

            for (int i = 0; i < longitud; i++) {
                //La idea es recorrer la fecha para separar los strings DD MM AA, convertirlos en numeros y compararlos con la fecha ingresada
                char caracter = prop.fecha_de_ingreso[i];
                printf("%c\n", caracter);

                if(caracter != "/"){
                    if(contadorDeBarras == 0){
                        //dia

                        //Aca iria pusheando el caracter del dia para formar el string del dia. Dsps este string hay que convertirlo a numero
                        diaStruct[i];

                    }else if(contadorDeBarras == 1){
                        //mes

                    }else{
                        //año

                    }
                }

                contadorDeBarras++;
                

            }
        }
            
    }else if (opcionToLower == 'e')
    {
        // obtenerSeleccion();
        return;
    }
  // submenuListar();
}

char submenuListar()
{
  char opcionElegida = "";

  printf("\n¿Qué operación desea listar?\n");
  printf("A) Listar todos (altas y bajas)\n"
         "B) Listar solo el campo activo\n"
         "C) Ingreso por teclado de un tipo de propiedad\n"
         "D) Ingreso de un rango de tiempo de ingreso (mínimo y máximo)\n"
         "E) Volver al menú principal\n");
  scanf(" %c", &opcionElegida);

  return opcionElegida;
}
