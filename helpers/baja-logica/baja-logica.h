void mostrarPropiedad(propiedad prop) {
    printf("%.2d | %11s | %21s | %14s | %.1d | %.1d | %5f | %5f | %8f | %3s | %10s | %10s | %1s | %d\n",
        prop.id, prop.fecha_de_ingreso, prop.zona, prop.ciudad, prop.dormitorios,
        prop.banos, prop.superficie_total, prop.superficie_cubierta, prop.precio, prop.moneda,
        prop.tipo, prop.operacion, prop.fecha_de_salida, prop.activo);
                            
}

bool idValido(FILE ** pArchivo){
    bool idValido = true;
    esIntEsChar nuevaValidacion;
    propiedad prop;

    if(validarTipoDato(&nuevaValidacion,"entero")){
        if(nuevaValidacion.datoEntero > 0){
            long posicionFila = sizeof(prop) * (nuevaValidacion.datoEntero  - 1);

            if (fseek(*pArchivo, posicionFila, SEEK_SET) == 0) {
                if (fread(&prop, sizeof(propiedad), 1, *pArchivo) == 1) {
                    fseek(*pArchivo, posicionFila, SEEK_SET);
                }else{
                    idValido = false;
                    printf("\n- - - - -  NO EXISTE UN REGISTRO CON ESE ID - - - - - \n");
                }
            }

        }else{
            idValido = false;
        }
    }else{
        idValido = false;
    }

    return idValido;
}

void bajalogica(FILE * pArchivo){
    char eliminar;
    char cadena[2];
    bool seguirPreguntando = true;
    long posicionFila;
    propiedad prop;

    if(fread(&prop, sizeof(propiedad), 1, pArchivo) == 1){
        if(strlen(prop.fecha_de_salida) <= 1){
            if(prop.activo != 0){
            
                printf("¿Esta seguro que quiere dar de baja la siguiente fila?:\n");
                mostrarPropiedad(prop);
                posicionFila = ftell(pArchivo) - sizeof(propiedad);
                while (seguirPreguntando){
                
                    printf("\nPresione S o N:");
                    scanf("%1s", cadena);
                    
                    if(strlen(cadena) == 1){
                        eliminar = tolower(cadena[0]);
                        
                        if(eliminar == 's'){
                            prop.activo = 0;
                            fseek(pArchivo, posicionFila, SEEK_SET);
                            fwrite(&prop, sizeof(propiedad), 1, pArchivo);            
                            seguirPreguntando = false;

                            printf("REGISTRO ACTUALIZADO DE FILAS ACTIVAS:\n");
                            fseek(pArchivo, 0, SEEK_SET);
                            fread(&prop, sizeof(propiedad), 1, pArchivo);
        
                            while (!feof(pArchivo))
                            {
                                if(prop.activo == 1){

                                    printf("%.2d | %11s | %21s | %14s | %.1d | %.1d | %5f | %5f | %8f | %3s | %10s | %10s | %1s | %d\n",
                                    prop.id, prop.fecha_de_ingreso, prop.zona, prop.ciudad, prop.dormitorios,
                                    prop.banos, prop.superficie_total, prop.superficie_cubierta, prop.precio, prop.moneda,
                                    prop.tipo, prop.operacion, prop.fecha_de_salida, prop.activo);
                                }
                                
                                fread(&prop, sizeof(propiedad), 1, pArchivo);
                            }

                            
                            

                        }else if(eliminar == 'n'){
                            seguirPreguntando = false;
                        }else{
                            printf("\n- - - - -  VERIFIQUE LO INGRESADO Y REINTÉNTELO - - - - - \n");

                        }

                    }else{
                        printf("\n- - - - -  VERIFIQUE LO INGRESADO Y REINTÉNTELO - - - - - \n");

                    }
                    while (getchar() != '\n'); //Limpio buffer de entrada
                }

            }else{
                
                printf("\n- - - - -  EL REGISTRO YA FUE DADO DE BAJA CON ANTERIORIDAD - - - - - \n");

             }
        }else{
            printf("\n- - - - -  LA FILA ELEGIDA NO SE PUEDE ELIMINAR PORQUE SU FECHA DE SALIDA ES NO NULA - - - - - \n");

        }
    }
}