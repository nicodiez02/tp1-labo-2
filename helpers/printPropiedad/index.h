#include <stdio.h>
#ifndef printPropiedad_h
#define printPropiedad_h

void printPropiedad(propiedad propiedadLeida) {
  printf(
      "\n%.2d | %15s | %10s | %10s | %.2d | %.2d | %5.2f | %5.2f | %5.2f | %10s | %10s | %10s | %20s | %d\n",
      propiedadLeida.id, propiedadLeida.fecha_de_ingreso, propiedadLeida.zona,
      propiedadLeida.ciudad, propiedadLeida.dormitorios, propiedadLeida.banos,
      propiedadLeida.superficie_total, propiedadLeida.superficie_cubierta,
      propiedadLeida.precio, propiedadLeida.moneda, propiedadLeida.tipo,
      propiedadLeida.operacion, propiedadLeida.fecha_de_salida,
      propiedadLeida.activo);
};

#endif