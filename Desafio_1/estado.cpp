#include "estado.h"
#include <iostream>

using namespace std;

void iniciarEstado(unsigned short & filas, unsigned short & columnas, unsigned short & eliminaciones, unsigned short & puntuacion){
    filas=columnas=eliminaciones=puntuacion=0;
}

unsigned short calcularPuntaje(unsigned short fichasEliminadas){
    return fichasEliminadas*3;
}

void actualizarVariableSuma(unsigned short & variable, unsigned short valor){
    variable+=valor;
}

// Imprime datos importantes para la jugabilidad
void mostrarEstado(unsigned short filas, unsigned short columnas, unsigned short eliminaciones,
                   unsigned short combinaciones, unsigned short puntuacion) {
    cout << "\n=========== ESTADO ACTUAL ===========\n";
    cout << "Tamano del tablero : " << filas << " x " << columnas << "\n";
    cout << "Fichas eliminadas  : " << eliminaciones << "\n";
    cout << "Combinaciones      : " << combinaciones << "\n";
    cout << "Puntuacion         : " << puntuacion << "\n";
    cout << "======================================\n";
}