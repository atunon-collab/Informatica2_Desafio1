#include "combinaciones.h"
#include "bits.h"


// Pone la máscara de marcas en cero
void limpiarMarcas(unsigned char *marcas, unsigned short nBytesMarcas) {
    for (unsigned short i = 0; i < nBytesMarcas; i++) // recorre cada byte del bloque de marcas
    {
        marcas[i] = 0; // apaga todos los bits de ese byte
    }
}


// Recorre fila por fila contando cuántas fichas iguales consecutivas lleva
unsigned short marcarHorizontales(const unsigned char *tablero, unsigned char *marcas, unsigned short filas, unsigned short columnas)
{
    unsigned short totalCombinaciones = 0; // cuenta cuántas rachas se marcaron

    for (unsigned short fila = 0; fila < filas; fila++) // procesa una fila completa
    {
        unsigned short inicioDeRacha = 0; // columna donde empezó la racha actual
        unsigned short largoDeRacha = 0; // cuántas fichas iguales van seguidas
        unsigned char fichaAnterior = 0; // última ficha vista
        bool hayRachaActiva = false; // si venimos contando una racha

        for (unsigned short columna = 0; columna < columnas; columna++)
        {
            unsigned short indice = calcularIndice(fila, columnas, columna); // posición lineal
            unsigned char fichaActual = leerFicha(tablero, indice); // ficha en esa posición
            bool esVacia = (fichaActual == 0); // 000 = vacío

            if (!esVacia && hayRachaActiva && fichaActual == fichaAnterior) // sigue la misma racha
            {
                largoDeRacha++;
            }
            else
            {
                if (largoDeRacha >= 3)
                {
                    for (unsigned short c = inicioDeRacha; c < inicioDeRacha + largoDeRacha; c++)
                        escribirMarca(marcas, calcularIndice(fila, columnas, c), true); // marca cada posición
                    totalCombinaciones++; // cuenta la combinación
                }

                if (!esVacia) // esta ficha arranca una racha nueva
                {
                    inicioDeRacha = columna;
                    largoDeRacha = 1;
                    hayRachaActiva = true;
                }
                else // un vacío corta cualquier racha
                {
                    largoDeRacha = 0;
                    hayRachaActiva = false;
                }
            }

            fichaAnterior = fichaActual; // guarda para comparar en la próxima vuelta
        }

        if (largoDeRacha >= 3) // la racha llegó hasta el final de la fila
        {
            for (unsigned short c = inicioDeRacha; c < inicioDeRacha + largoDeRacha; c++)
                escribirMarca(marcas, calcularIndice(fila, columnas, c), true);
            totalCombinaciones++;
        }
    }

    return totalCombinaciones; // total de combinaciones horizontales encontradas
}

// Exactamente la misma lógica pero recorriendo por columnas: el ciclo externo va sobre las columnas y el interno sobre las filas
// Exactamente la misma lógica pero recorriendo por columnas: el ciclo externo va sobre las columnas y el interno sobre las filas
unsigned short marcarVerticales(const unsigned char *tablero, unsigned char *marcas, unsigned short filas, unsigned short columnas){

    unsigned short totalCombinaciones = 0;

    for (unsigned short columna = 0; columna < columnas; columna++)
    {
        unsigned short inicioDeRacha = 0;
        unsigned short largoDeRacha = 0;
        unsigned char fichaAnterior = 0;
        bool hayRachaActiva = false;

        for (unsigned short fila = 0; fila < filas; fila++)
        {
            unsigned short indice = calcularIndice(fila, columnas, columna);
            unsigned char fichaActual = leerFicha(tablero, indice);
            bool esVacia = (fichaActual == 0);

            if (!esVacia && hayRachaActiva && fichaActual == fichaAnterior)
            {
                largoDeRacha++;
            }
            else
            {
                if (largoDeRacha >= 3)
                {
                    for (unsigned short f = inicioDeRacha; f < inicioDeRacha + largoDeRacha; f++)
                        escribirMarca(marcas, calcularIndice(f, columnas, columna), true);
                    totalCombinaciones++;
                }

                if (!esVacia)
                {
                    inicioDeRacha = fila;
                    largoDeRacha = 1;
                    hayRachaActiva = true;
                }
                else
                {
                    largoDeRacha = 0;
                    hayRachaActiva = false;
                }
            }

            fichaAnterior = fichaActual;
        }

        if (largoDeRacha >= 3)
        {
            for (unsigned short f = inicioDeRacha; f < inicioDeRacha + largoDeRacha; f++)
                escribirMarca(marcas, calcularIndice(f, columnas, columna), true);
            totalCombinaciones++;
        }
    }

    return totalCombinaciones; // total de combinaciones verticales encontradas
}

//Recorre la máscara y escribe el código VACÍO (000) en cada posición marcada
unsigned short eliminarMarcadas(unsigned char * tablero, const unsigned char * marcas, unsigned short filas, unsigned short columnas)
{
    unsigned short fichasEliminadas = 0; // cuenta cuántas fichas se borraron de verdad

    for(unsigned short i = 0; i < (filas*columnas); i++){ // recorre todas las posiciones del tablero
        bool marca = leerMarca(marcas, i); // esta posición quedó marcada?

        if(marca){
            escribirFicha(tablero, i, 0); // borra la ficha (0 = vacío)
            fichasEliminadas++; // suma una eliminación
    }
    }
    return fichasEliminadas; // total de fichas borradas en esta ronda
}