#ifndef BITS_H
#define BITS_H

// Convierte (fila, columna) en la posición lineal: indice = fila * columnas + columna
unsigned short calcularIndice(unsigned short fila, unsigned short columnas, unsigned short columna);

// Calcula los bytes necesarios para el tablero: (3*filas*columnas + 7) / 8
unsigned short bytesNecesarios(unsigned short filas, unsigned short columnas);

// Devuelve el código de 3 bits guardado en "indice" (maneja el caso repartido entre 2 bytes)
unsigned char leerFicha(const unsigned char * tablero, unsigned short indice);

// Escribe el código de 3 bits "valor" en "indice": apaga bits viejos y enciende los nuevos
void escribirFicha(unsigned char * tablero, unsigned short indice, unsigned char valor);

// Calcula los bytes necesarios para el tablero auxiliar de marcas
unsigned short bytesNecesariosMarcas(unsigned short filas, unsigned short columnas);

// Libera el arreglo de marcas viejo y reserva uno nuevo del tamaño correcto, en caso de que
// el tamaño actual sea util solo se limpia y desplaza
void actualizarMarcas(unsigned char *& marcas, unsigned short filas, unsigned short columnas, unsigned short & bytesReservadosMarcas);

// Lee un solo bit de marca en la posición "indice" (para señalar fichas a eliminar)
bool leerMarca(const unsigned char * marcas, unsigned short indice);

// Enciende o apaga el bit de marca en la posición "indice"
void escribirMarca(unsigned char * marcas, unsigned short indice, bool valor);

#endif // BITS_H