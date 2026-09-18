#ifndef INTERFAZ_H
#define INTERFAZ_H

//Muestra el menú principal del juego
void mostrarMenu();

// Muestra las instrucciones detalladas del juego
void mostrarInstrucciones();

// Muestra el menú de opciones disponible durante una partida activa
void mostrarMenuPartida();

// Lee un número entero de la consola, se verifica que esté en el rango de mínimo y máximo
unsigned short leerOpcion(short minimo, short maximo);

// Verifica si la coordenada ingresada es válida
bool posicionValida(unsigned short fila, unsigned short columna, unsigned short filas, unsigned short columnas);

// Muestra el resultado inmediato de la jugada: cuantas fichas se eliminaron
// en la ultima ronda de procesarCascadas y cuantas cascadas se dispararon
void mostrarResultadoTurno(unsigned short eliminadasActuales, unsigned short cascadasActuales);
#endif // INTERFAZ_H
