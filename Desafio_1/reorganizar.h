#ifndef REORGANIZAR_H
#define REORGANIZAR_H

//Por cada columna, hace que las fichas que quedaron caigan hasta ocupar los huecos de abajo
void aplicarGravedad(unsigned char * tablero, unsigned short filas, unsigned short columnas);

// Recorre el tablero y pone una ficha aleatoria en cada posición vacía
void rellenarVacios(unsigned char * tablero, unsigned short filas, unsigned short columnas);

// Procesa combinaciones y gravedad en bucle hasta que se estabilice el tablero
unsigned short procesarCascadas(unsigned char * tablero, unsigned char * marcas, unsigned short filas, unsigned short columnas, unsigned short & eliminaciones,
                                unsigned short & combinaciones, unsigned short & puntaje, unsigned short & eliminadasActuales);
#endif // REORGANIZAR_H
