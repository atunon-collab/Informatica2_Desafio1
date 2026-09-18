#ifndef ESTADO_H
#define ESTADO_H

// Pone todos los contadores en cero al comenzar la partida
void iniciarEstado(unsigned short & filas, unsigned short & columnas, unsigned short & eliminaciones, unsigned short & puntuacion);

// Aplica la fórmula de puntaje
unsigned short calcularPuntaje(unsigned short fichasEliminadas);

// Actualiza las variables que funcionan mediante una suma acumulada
void actualizarVariableSuma(unsigned short & variable, unsigned short valor);

// Imprime datos importantes para la jugabilidad
void mostrarEstado(unsigned short filas, unsigned short columnas, unsigned short eliminaciones,
                   unsigned short combinaciones, unsigned short puntuacion);
#endif // ESTADO_H
