#ifndef defines
#define defines

typedef struct
{
  int id;
  char fecha_de_ingreso[11];
  char zona[30];
  char ciudad[30];
  int dormitorios;
  int banos;
  float superficie_total;
  float superficie_cubierta;
  float precio;
  char moneda[10];
  char tipo[30];
  char operacion[30];
  char fecha_de_salida[11];
  int activo;
} propiedad;

typedef struct {
  int datoEntero;
  char datoCadena[30];
  float datoFlotante;
} esIntEsChar;

#endif
