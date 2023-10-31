#include <stdio.h>
#ifndef printPropiedad_h
#define printPropiedad_h

void printPropiedad(propiedad propiedadLeida) {
  printf(
      "%.2d | %11s | %25s | %20s | %4d | %4d | %4.2f | %4.2f | %10.2f | %3s | %10s | %10s | %1s | %d\n",
      propiedadLeida.id, propiedadLeida.fecha_de_ingreso, propiedadLeida.zona,
      propiedadLeida.ciudad, propiedadLeida.dormitorios, propiedadLeida.banos,
      propiedadLeida.superficie_total, propiedadLeida.superficie_cubierta,
      propiedadLeida.precio, propiedadLeida.moneda, propiedadLeida.tipo,
      propiedadLeida.operacion, propiedadLeida.fecha_de_salida,
      propiedadLeida.activo);
};

#endif