#ifndef ESTRUCTURA_H
#define ESTRUCTURA_H

enum operacion {
    agregarFila = 1,
    borrarFila,
    agregarColumna,
    borrarColumna
};
// Redimensiona el tablero en memoria dinámica según la operación estructural realizada (agregar/eliminar fila o columna).
// Reubica las fichas existentes ajustando sus coordenadas, libera la memoria del tablero anterior y asigna el nuevo bloque.
void copiarConNuevasDimensiones(unsigned char *& tablero, unsigned short filasViejas, unsigned short columnasViejas, unsigned short filasNuevas,
                                unsigned short columnasNuevas, unsigned short filaAfectada, unsigned short columnaAfectada,short tipoOperacion);

//Reorganiza y desplaza las fichas dentro del mismo bloque de memoria existente sin destruirlo ni pedir memoria nueva
void desplazarEliminadas(unsigned char * tablero, unsigned short filasViejas, unsigned short columnasViejas,unsigned short filasNuevas,
                         unsigned short columnasNuevas, unsigned short filaAfectada, unsigned short columnaAfectada, short tipoOperacion) ;

void insertarFila(unsigned char *& tablero, unsigned short & filas, unsigned short columnas, unsigned short filaAfectada);

void eliminarFila(unsigned char *& tablero, unsigned short & filas, unsigned short columnas, unsigned short filaAfectada,unsigned short & bytesReservados);

void insertarColumna(unsigned char *& tablero, unsigned short filas, unsigned short & columnas, unsigned short columnaAfectada);

void eliminarColumna(unsigned char *& tablero, unsigned short filas, unsigned short & columnas,unsigned short columnaAfectada, unsigned short & bytesReservados);

bool requiereEncogimiento(unsigned short bytesNecesarios, unsigned short bytesReservados);
#endif // ESTRUCTURA_H
