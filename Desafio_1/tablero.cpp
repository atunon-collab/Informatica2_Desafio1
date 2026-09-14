#include <iostream>
#include <random>
#include "tablero.h"
#include "bits.h"

using namespace std;

// Reserva con new el bloque del tamaño exacto que devuelve bytesNecesarios y lo deja limpio
unsigned char * crearTablero(unsigned short filas, unsigned short columnas){
    unsigned short nBytes = bytesNecesarios(filas, columnas);
    unsigned char * tablero = new unsigned char[nBytes]();
    return tablero;
}

// Libera con delete[] y deja el puntero en nullptr
void liberarTablero(unsigned char *& tablero)
{
    delete[] tablero;
    tablero = nullptr;
}

// Devuelve uno de los seis códigos de ficha con distribución uniforme
unsigned char fichaAleatoria(){
    // Se usa 'static' para que el motor y la semilla se inicialicen solo una vez.
    // Si no usas static, la función generará el mismo número si se llama muy rápido.
    static random_device rd;
    static mt19937 gen(rd());

    // Distribución uniforme entre 1 y 6
    uniform_int_distribution<int> distrib(1, 6);

    // Convertimos el int obtenido a unsigned char
    return static_cast<unsigned char>(distrib(gen));
}

// Traduce un código de 3 bits al carácter que se muestra en pantalla
char simboloDeFicha(unsigned char codigo)
{
    // Índice 0 sin usar (000 = vacío, se maneja aparte)
    static const char simbolos[8] = {' ', '@', '#', '?', '%', 'O', 'X', '*'};

    return simbolos[codigo];
}

// Recorre todas las posiciones y escribe una ficha aleatoria en cada una
void llenarAleatorio(unsigned char * tablero, unsigned short filas, unsigned short columnas)
{
    unsigned short totalPosiciones = filas * columnas;

    for (unsigned short indice = 0; indice < totalPosiciones; indice++)
    {
        // Indice lineal, no hace falta fila/columna por separado
        unsigned char ficha = fichaAleatoria();
        escribirFicha(tablero, indice, ficha);
    }
}

//Dibuja el tablero con sus números de fila y columna, incluyendo paralelamente un tablero con la representación de los bits
void mostrarTablero(const unsigned char * tablero, unsigned short filas, unsigned short columnas)
{
    // Parte superior con los números
    cout << "    ";
    for (unsigned short j = 1; j <= columnas; j++) {
        if (j <= 9)
            cout << " " << j << "  ";
        else
            cout << " " << j << " ";
    }

    cout << '\n';

    // Linea superior de ambos tableros
    cout << "   +";
    for (unsigned short j = 0; j < columnas; j++) {
        cout << "---+";
    }
    cout << "     +"; // Primera separación entre tableros
    for (unsigned short j = 0; j < columnas; j++) {
        cout << "-----+"; // celdas del tablero de bits, más anchas (3 bits)
    }
    cout << '\n';

    // Filas
    for (unsigned short i = 1; i <= filas; i++) {

        // Tablero de simbolos
        if (i <= 9) {
            cout << " " << i << " |";
        } else {
            cout << i << " |";
        }

        for (unsigned short j = 1; j <= columnas; j++) {
            unsigned short indice = calcularIndice(i - 1, columnas, j - 1);
            unsigned char codigo = leerFicha(tablero, indice);
            char simbolo = simboloDeFicha(codigo);

            cout << " " << simbolo << " |";
        }

        // Tablero de bits
        cout << "     |";
        for (unsigned short j = 1; j <= columnas; j++) {
            unsigned short indice = calcularIndice(i - 1, columnas, j - 1);
            unsigned char codigo = leerFicha(tablero, indice);

            // Imprime los 3 bits del codigo, de mas significativo a menos
            cout << " " << ((codigo >> 2) & 1) << ((codigo >> 1) & 1) << (codigo & 1) << " |";
        }

        cout << '\n';

        // Separador de ambos tableros
        cout << "   +";
        for (unsigned short j = 0; j < columnas; j++) {
            cout << "---+";
        }
        cout << "     +";
        for (unsigned short j = 0; j < columnas; j++) {
            cout << "-----+";
        }
        cout << '\n';
    }
}