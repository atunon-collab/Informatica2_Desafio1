#ifndef TABLERO_H
#define TABLERO_H

// Reserva con new el bloque del tamaño exacto que devuelve bytesNecesarios y lo deja limpio
unsigned char * crearTablero(unsigned short filas, unsigned short columnas);

// Libera con delete[] y deja el puntero en nullptr
void liberarTablero(unsigned char *& tablero);

// Devuelve uno de los seis códigos de ficha con distribución uniforme
unsigned char fichaAleatoria();

// Traduce un código de 3 bits al carácter que se muestra en pantalla
char simboloDeFicha(unsigned char codigo);

// Recorre todas las posiciones y escribe una ficha aleatoria en cada una
void llenarAleatorio(unsigned char * tablero, unsigned short filas, unsigned short columnas);

//Dibuja el tablero con sus números de fila y columna, incluyendo paralelamente un tablero con la representación de los bits
void mostrarTablero(const unsigned char * tablero, unsigned short filas, unsigned short columnas);

#endif // TABLERO_H
