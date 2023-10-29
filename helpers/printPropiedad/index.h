#include <stdio.h>
#ifndef printPropiedad_h
#define printPropiedad_h

void printPropiedad(propiedad propiedadLeida) {
  printf(
      "\n%.2d | %22s | %10s | %10s | %.11d | %.6d | %15f | %18f | %7f | %10s | %10s | %10s | %21s | %d\n",
      propiedadLeida.id, propiedadLeida.fecha_de_ingreso, propiedadLeida.zona,
      propiedadLeida.ciudad, propiedadLeida.dormitorios, propiedadLeida.banos,
      propiedadLeida.superficie_total, propiedadLeida.superficie_cubierta,
      propiedadLeida.precio, propiedadLeida.moneda, propiedadLeida.tipo,
      propiedadLeida.operacion, propiedadLeida.fecha_de_salida,
      propiedadLeida.activo);
};

#endif