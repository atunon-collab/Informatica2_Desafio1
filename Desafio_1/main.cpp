//#include <iostream>
//#include "bits.h"
#include "tablero.h"

int main()
{
    unsigned short filas = 5;
    unsigned short columnas = 5;

    unsigned char * tablero = crearTablero(filas, columnas);

    llenarAleatorio(tablero, filas, columnas);

    mostrarTablero(tablero, filas, columnas);

    liberarTablero(tablero);

    return 0;
}