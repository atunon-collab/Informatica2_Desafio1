#ifndef ESTRUCTURA_H
#define ESTRUCTURA_H

enum operacion {
    agregarFila = 1,
    borrarFila,
    agregarColumna,
    borrarColumna
};
// Redimensiona el tablero en memoria dinámica según la operación realizada (agregar/eliminar fila o columna)
void copiarConNuevasDimensiones(unsigned char *& tablero, unsigned short filasViejas, unsigned short columnasViejas, unsigned short filasNuevas,
                                unsigned short columnasNuevas, unsigned short filaAfectada, unsigned short columnaAfectada, operacion tipoOperacion);

//Reorganiza y desplaza las fichas dentro del mismo bloque de memoria existente sin destruirlo ni pedir memoria nueva
void desplazarEliminadas(unsigned char * tablero, unsigned short filasViejas, unsigned short columnasViejas,unsigned short filasNuevas,
                         unsigned short columnasNuevas, unsigned short filaAfectada, unsigned short columnaAfectada, short tipoOperacion) ;

void insertarFila(unsigned char *& tablero, unsigned short & filas, unsigned short columnas,
                  unsigned short filaAfectada, unsigned short & bytesReservados);

void eliminarFila(unsigned char *& tablero, unsigned short & filas, unsigned short columnas, unsigned short filaAfectada,unsigned short & bytesReservados);

void insertarColumna(unsigned char *& tablero, unsigned short filas, unsigned short & columnas,
                     unsigned short columnaAfectada, unsigned short & bytesReservados);

void eliminarColumna(unsigned char *& tablero, unsigned short filas, unsigned short & columnas,unsigned short columnaAfectada, unsigned short & bytesReservados);

bool requiereEncogimiento(unsigned short bytesNecesarios, unsigned short bytesReservados);

// Abre espacio para una fila o columna nueva dentro del mismo bloque de memoria ya reservado,
// desplazando las fichas existentes (de atras hacia adelante, para no sobrescribir datos
// que aun no se han leido), y deja en 0 las celdas de la fila/columna insertadas
void desplazarInsertados(unsigned char * tablero, unsigned short filasViejas, unsigned short columnasViejas,
                         unsigned short filasNuevas, unsigned short columnasNuevas,
                         unsigned short filaAfectada, unsigned short columnaAfectada, short tipoOperacion);

#endif // ESTRUCTURA_H
