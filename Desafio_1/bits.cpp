#include "bits.h"

// Convierte (fila, columna) en la posición lineal: indice = fila * columnas + columna
unsigned short calcularIndice(unsigned short fila, unsigned short columnas, unsigned short columna) {;
    return (fila*columnas+columna);
}

// Calcula los bytes necesarios para el tablero: (3*filas*columnas + 7) / 8
unsigned short bytesNecesarios(unsigned short filas, unsigned short columnas) {
    return (3*filas*columnas+7)/8;
}

// Devuelve el código de 3 bits guardado en "indice" (maneja el caso repartido entre 2 bytes)
unsigned char leerFicha(const unsigned char* tablero, unsigned short indice){
    unsigned short byte = indice*3/8;          // byte donde empieza la ficha
    unsigned short desplazamiento = indice*3%8; // bit inicial dentro del byte

    if (desplazamiento <=5){
        // caso simple: la ficha cabe entera en un byte
        return ((tablero [byte] >> desplazamiento) & 7);
    }
    else{
        // caso repartido: la ficha cruza al byte siguiente
        return ((tablero[byte] >> desplazamiento) | (tablero[byte + 1] << (8 - desplazamiento))) & 7;
    }
}

// Escribe el código de 3 bits "valor" en "indice": apaga bits viejos y enciende los nuevos
void escribirFicha(unsigned char * tablero, unsigned short indice, unsigned char valor){
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


// Lee un solo bit de marca en la posición "indice" (para señalar fichas a eliminar)
bool leerMarca(const unsigned char* marcas, unsigned short indice) {
    unsigned short byte = indice / 8;           // byte donde vive el bit de marca
    unsigned short desplazamiento = indice % 8; // posición del bit dentro del byte

    return (marcas[byte] >> desplazamiento) & 1; // aisla ese bit con la máscara 1
}

// Enciende o apaga el bit de marca en la posición "indice"
void escribirMarca(unsigned char* marcas, unsigned short indice, bool valor) {
    unsigned short byte = indice / 8;
    unsigned short desplazamiento = indice % 8;

    if (valor) {
        marcas[byte] |= (1 << desplazamiento);  // enciende el bit (OR)
    } else {
        marcas[byte] &= ~(1 << desplazamiento); // apaga el bit (AND con máscara invertida)
    }
}