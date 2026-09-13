#include "bits.h"

// indice = fila * columnas + columna
unsigned short calcularIndice(unsigned short fila, unsigned short columnas, unsigned short columna) {;
    return (fila*columnas+columna);
}

// bytes = (3*filas*columnas + 7) / 8, el +7 redondea hacia arriba
unsigned short bytesNecesarios(unsigned short filas, unsigned short columnas) {
    return (3*filas*columnas+7)/8;
}

unsigned char leerFicha(const unsigned char* tablero, unsigned short indice){
    unsigned short byte = indice*3/8;          // byte donde empieza la ficha
    unsigned short desplazamiento = indice*3%8; // bit inicial dentro del byte

    if (desplazamiento <=5){
        // caso simple: la ficha cabe entera en un byte
        return ((tablero [byte] >> desplazamiento) & 7);
    }
    else{
        // caso repartido: la ficha cruza al byte siguiente
        return (((tablero[byte] >> desplazamiento) | (tablero[byte + 1] << (8 - desplazamiento))) & 7);
    }
}

void escribirFicha(unsigned char * tablero, unsigned int indice, unsigned char valor){
    unsigned short byte = indice*3/8;
    unsigned short desplazamiento = indice*3%8;

    if (desplazamiento <=5){
        // caso simple: apaga los bits viejos y enciende los nuevos en un solo byte
        tablero[byte] &= ~(7 << desplazamiento);   // apaga
        tablero[byte] |=  (valor << desplazamiento); // enciende
    }
    else{
        // caso repartido: se escribe una parte en "byte" y el resto en "byte+1"
        tablero[byte] &= ~(7 << desplazamiento);   // apaga la parte en el primer byte
        tablero[byte] |=  (valor << desplazamiento); // enciende la parte en el primer byte

        tablero[byte+1] &= ~(7 >> desplazamiento);   // apaga la parte en el segundo byte
        tablero[byte+1] |=  ( valor >> (8-desplazamiento)); // enciende la parte en el segundo byte
    }
}

// pone en cero todos los bytes del bloque (tablero vacío)
void limpiarBloque(unsigned char * bloque, unsigned short nBytes){
    for (unsigned short i = 0; i < nBytes; i++) {
        bloque[i] = 0;
    }
}

// lee un solo bit de marca en la posición "indice"
bool leerMarca(const unsigned char* marcas, unsigned int indice) {
    unsigned int byte = indice / 8;
    unsigned int desplazamiento = indice % 8;

    return (marcas[byte] >> desplazamiento) & 1;
}

// enciende o apaga el bit de marca en la posición "indice"
void escribirMarca(unsigned char* marcas, unsigned int indice, bool valor) {
    unsigned int byte = indice / 8;
    unsigned int desplazamiento = indice % 8;

    if (valor) {
        marcas[byte] |= (1 << desplazamiento);
    } else {
        marcas[byte] &= ~(1 << desplazamiento);
    }
}