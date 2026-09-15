#ifndef COMBINACIONES_H
#define COMBINACIONES_H

// Pone la máscara de marcas en cero
void limpiarMarcas(unsigned char * marcas, unsigned short nBytes);

// Recorre fila por fila contando cuántas fichas iguales consecutivas lleva
unsigned short marcarHorizontales(const unsigned char * tablero, unsigned char * marcas, unsigned short filas, unsigned short columnas);

// Exactamente la misma lógica pero recorriendo por columnas: el ciclo externo va sobre las columnas y el interno sobre las filas
unsigned short marcarVerticales(const unsigned char * tablero, unsigned char * marcas, unsigned short filas, unsigned short columnas);

//Recorre la máscara y escribe el código VACÍO (000) en cada posición marcada
unsigned short eliminarMarcadas(unsigned char * tablero, const unsigned char * marcas, unsigned short filas, unsigned short columnas);

bool hayCombinaciones(const unsigned char * tablero, unsigned short filas, unsigned short columnas);

#endif // COMBINACIONES_H
