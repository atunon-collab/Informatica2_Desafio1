#include "bits.h"
#include "tablero.h"
#include "reorganizar.h"
#include "combinaciones.h"
#include "estado.h"

//Por cada columna, hace que las fichas que quedaron caigan hasta ocupar los huecos de abajo.
void aplicarGravedad(unsigned char * tablero, unsigned short filas, unsigned short columnas) {

    for (unsigned short col = 0; col < columnas; col++) {
        // apunta al espacio libre más bajo disponible en la columna
        short escritor = filas - 1;

        // Recorre la columna de abajo hacia arriba en busca de fichas
        for (short lector = filas - 1; lector >= 0; lector--) {
            unsigned short indiceLector = calcularIndice(lector, columnas, col);
            unsigned char ficha = leerFicha(tablero, indiceLector);

            if (ficha != 0) {
                // si la ficha necesita caer
                if (escritor != lector) {
                    unsigned short indiceEscritor = calcularIndice(escritor, columnas, col);

                    escribirFicha(tablero, indiceEscritor, ficha); // Coloca la ficha abajo
                    escribirFicha(tablero, indiceLector, 0);  // Deja el espacio libre arriba
                }
                // Prepara la casilla superior para la siguiente ficha
                escritor--;
            }
        }
    }
}

// Recorre el tablero y pone una ficha aleatoria en cada posición vacía
void rellenarVacios(unsigned char * tablero, unsigned short filas, unsigned short columnas)
{
    unsigned short total = filas * columnas;

    for (unsigned short indice = 0; indice < total; indice++) {
        if (leerFicha(tablero, indice) == 0) {
            escribirFicha(tablero, indice, fichaAleatoria());
        }
    }
}

// procesa combinaciones y gravedad en bucle hasta que se estabilice el tablero
unsigned short procesarCascadas(unsigned char * tablero, unsigned char * marcas, unsigned short filas, unsigned short columnas, unsigned short & eliminaciones,
                                unsigned short & combinaciones, unsigned short & puntaje, unsigned short & eliminadasActuales){
    unsigned short cascadas=0;
    bool continua=true;

    while (continua){
        // Detectar y marcar combinaciones
        unsigned short combHoriz = marcarHorizontales(tablero, marcas, filas, columnas);
        unsigned short combVert  = marcarVerticales(tablero, marcas, filas, columnas);

        if (combHoriz==0 && combVert==0){
            continua=false;
        }
        else{
            cascadas++;

            // Eliminar del tablero las fichas marcadas y guardar cantidad de eliminadas
            eliminadasActuales = eliminarMarcadas(tablero, marcas, filas, columnas);

            // Se calcula tamaño y se limpia el tablero de marcas
            limpiarMarcas(marcas, (bytesNecesariosMarcas(filas,columnas)));

            // Actualizar variable de eliminaciones
            actualizarVariableSuma(eliminaciones, eliminadasActuales);

            // Actualizar total de combinaciones detectadas en esta ronda
            actualizarVariableSuma(combinaciones, combHoriz + combVert);

            // Actualizar puntuación
            actualizarVariableSuma(puntaje, (calcularPuntaje(eliminadasActuales)));

            // Aplicar gravedad
            aplicarGravedad(tablero, filas, columnas);
            rellenarVacios(tablero, filas, columnas);
        }
    }
    return cascadas;
}



