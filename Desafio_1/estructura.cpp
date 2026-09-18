#include "estructura.h"
#include "bits.h"
#include "tablero.h"
#include "reorganizar.h"

// Redimensiona el tablero en memoria dinámica según la operación estructural realizada (agregar/eliminar fila o columna).
// Reubica las fichas existentes ajustando sus coordenadas, libera la memoria del tablero anterior y asigna el nuevo bloque.
void copiarConNuevasDimensiones(unsigned char *& tablero, unsigned short filasViejas, unsigned short columnasViejas, unsigned short filasNuevas,
                                unsigned short columnasNuevas, unsigned short filaAfectada, unsigned short columnaAfectada, operacion tipoOperacion)
{
    unsigned short nuevosBytes = bytesNecesarios(filasNuevas, columnasNuevas);
    // Reserva e inicializa a cero
    unsigned char * nuevoBloque = new unsigned char[nuevosBytes]();

    // recorrido filas y columnas
    for (unsigned short filNueva = 0; filNueva < filasNuevas; filNueva++) {
        for (unsigned short colNueva = 0; colNueva < columnasNuevas; colNueva++) {

            short filVieja = filNueva;
            short colVieja = colNueva;
            bool noExistia = false;

            switch (tipoOperacion) {
            case agregarFila:
                if (filNueva == filaAfectada) noExistia = true;
                else if (filNueva > filaAfectada) filVieja = filNueva - 1;
                break;

            case borrarFila:
                if (filNueva >= filaAfectada) filVieja = filNueva + 1;
                break;

            case agregarColumna:
                if (colNueva == columnaAfectada) noExistia = true;
                else if (colNueva > columnaAfectada) colVieja = colNueva - 1;
                break;

            case borrarColumna:
                if (colNueva >= columnaAfectada) colVieja = colNueva + 1;
                break;
            }

            // Solo leemos y escribimos si la ficha existía en el tablero previo
            if (!noExistia) {
                unsigned short indiceViejo = calcularIndice(filVieja, columnasViejas, colVieja);
                unsigned char ficha = leerFicha(tablero, indiceViejo);

                if (ficha != 0) {
                    unsigned short indiceNuevo = calcularIndice(filNueva, columnasNuevas, colNueva);
                    escribirFicha(nuevoBloque, indiceNuevo, ficha);
                }
            }
        }
    }

    // Libera la memoria vieja y reasigna el puntero por referencia
    liberarTablero(tablero);
    tablero = nuevoBloque;
}

//Reorganiza y desplaza las fichas dentro del mismo bloque de memoria existente sin destruirlo ni pedir memoria nueva
void desplazarEliminadas(unsigned char * tablero, unsigned short filasViejas, unsigned short columnasViejas,unsigned short filasNuevas,
                         unsigned short columnasNuevas, unsigned short filaAfectada, unsigned short columnaAfectada, short tipoOperacion) {

    unsigned short totalNuevas = filasNuevas * columnasNuevas;

    // Recorremos las posiciones
    for (unsigned short indNuevo = 0; indNuevo < totalNuevas; indNuevo++) {
        unsigned short filNueva = indNuevo / columnasNuevas;
        unsigned short colNueva = indNuevo % columnasNuevas;

        unsigned short filVieja = filNueva;
        unsigned short colVieja = colNueva;

        // determina que ficha original corresponde a la nueva ubicación
        switch (tipoOperacion) {
        case borrarFila:
            if (filNueva >= filaAfectada) {
                filVieja = filNueva + 1;
            }
            break;

        case borrarColumna:
            if (colNueva >= columnaAfectada) {
                colVieja = colNueva + 1;
            }
            break;
        }

        // Lee la coordenada vieja del mismo arreglo
        unsigned short indiceViejo = calcularIndice(filVieja, columnasViejas, colVieja);
        unsigned char ficha = leerFicha(tablero, indiceViejo);

        // Escribe de forma empaquetada en la posición continua
        escribirFicha(tablero, indNuevo, ficha);
    }
}

void eliminarFila(unsigned char *& tablero, unsigned short & filas, unsigned short columnas,
                  unsigned short filaAfectada, unsigned short & bytesReservados)
{
    if (filas <= 1) return; //validación mínima

    unsigned short filasNuevas = filas - 1;
    unsigned short nuevosBytes = bytesNecesarios(filasNuevas, columnas);

    // Si los bytes requeridos caen por debajo del 65% de lo reservado, liberamos y reasignamos
    if (requiereEncogimiento(nuevosBytes, bytesReservados)) {
        copiarConNuevasDimensiones(tablero, filas, columnas, filasNuevas, columnas, filaAfectada, 0, borrarFila);
        bytesReservados = nuevosBytes; // Actualiza capacidad física
    } else {
        // Mantenemos la memoria física y desplazamos
        desplazarEliminadas(tablero, filas, columnas, filasNuevas, columnas, filaAfectada, 0, borrarFila);
    }

    filas = filasNuevas; // Actualiza tamaño
}

void insertarFila(unsigned char *& tablero, unsigned short & filas, unsigned short columnas,
                  unsigned short filaAfectada, unsigned short & bytesReservados)
{
    unsigned short filasNuevas = filas + 1;
    unsigned short bytesNecesariosNuevos = bytesNecesarios(filasNuevas, columnas);

    if (bytesNecesariosNuevos <= bytesReservados) {
        // Ya hay espacio: desplazamos dentro del mismo bloque, sin pedir memoria nueva
        desplazarInsertados(tablero, filas, columnas, filasNuevas, columnas, filaAfectada, 0, agregarFila);
    } else {
        copiarConNuevasDimensiones(tablero, filas, columnas, filasNuevas, columnas, filaAfectada, 0, agregarFila);
        bytesReservados = bytesNecesariosNuevos; // actualiza capacidad solo cuando de verdad se reserva
    }

    filas = filasNuevas;
    rellenarVacios(tablero, filas, columnas); // llena la fila nueva con fichas aleatorias
}

void eliminarColumna(unsigned char *& tablero, unsigned short filas, unsigned short & columnas,
                     unsigned short columnaAfectada, unsigned short & bytesReservados)
{
    if (columnas <= 1) return; //validación mínima

    unsigned short columnasNuevas = columnas - 1;
    unsigned short nuevosBytes = bytesNecesarios(filas, columnasNuevas);

    if (requiereEncogimiento(nuevosBytes, bytesReservados)) {
        copiarConNuevasDimensiones(tablero, filas, columnas, filas, columnasNuevas, 0, columnaAfectada, borrarColumna);
        bytesReservados = nuevosBytes; // Actualiza capacidad física
    } else {
        // Mantenemos la memoria física y desplazamos
        desplazarEliminadas(tablero, filas, columnas, filas, columnasNuevas, 0, columnaAfectada, borrarColumna);
    }

    columnas = columnasNuevas; // Actualizamos tamaño
}

void insertarColumna(unsigned char *& tablero, unsigned short filas, unsigned short & columnas,
                     unsigned short columnaAfectada, unsigned short & bytesReservados)
{
    unsigned short columnasNuevas = columnas + 1;
    unsigned short bytesNecesariosNuevos = bytesNecesarios(filas, columnasNuevas);

    if (bytesNecesariosNuevos <= bytesReservados) {
        desplazarInsertados(tablero, filas, columnas, filas, columnasNuevas, 0, columnaAfectada, agregarColumna);
    } else {
        copiarConNuevasDimensiones(tablero, filas, columnas, filas, columnasNuevas, 0, columnaAfectada, agregarColumna);
        bytesReservados = bytesNecesariosNuevos;
    }

    columnas = columnasNuevas;
    rellenarVacios(tablero, filas, columnas);
}

// Evalúa si el tamaño útil ocupado ha caído por debajo del 65% del tamaño reservado
bool requiereEncogimiento(unsigned short bytesNecesarios, unsigned short bytesReservados) {
    return (bytesNecesarios * 100) < (bytesReservados * 65);
}

// Abre espacio para una fila o columna nueva dentro del mismo bloque de memoria ya reservado,
// desplazando las fichas existentes (de atras hacia adelante, para no sobrescribir datos
// que aun no se han leido), y deja en 0 las celdas de la fila/columna insertadas
void desplazarInsertados(unsigned char * tablero, unsigned short filasViejas, unsigned short columnasViejas,
                         unsigned short filasNuevas, unsigned short columnasNuevas,
                         unsigned short filaAfectada, unsigned short columnaAfectada, short tipoOperacion)
{
    unsigned short totalNuevas = filasNuevas * columnasNuevas;

    // Recorre de la ultima posicion a la primera (idiom seguro con unsigned short)
    for (unsigned short indNuevo = totalNuevas; indNuevo-- > 0; ) {
        unsigned short filNueva = indNuevo / columnasNuevas;
        unsigned short colNueva = indNuevo % columnasNuevas;

        short filVieja = filNueva;
        short colVieja = colNueva;
        bool esNueva = false; // celda que pertenece a la fila/columna recien insertada

        switch (tipoOperacion) {
        case agregarFila:
            if (filNueva == filaAfectada) esNueva = true;
            else if (filNueva > filaAfectada) filVieja = filNueva - 1;
            break;

        case agregarColumna:
            if (colNueva == columnaAfectada) esNueva = true;
            else if (colNueva > columnaAfectada) colVieja = colNueva - 1;
            break;
        }

        if (esNueva) {
            escribirFicha(tablero, indNuevo, 0); // celda nueva: queda vacia, la llena rellenarVacios despues
        } else {
            unsigned short indiceViejo = calcularIndice(filVieja, columnasViejas, colVieja);
            unsigned char ficha = leerFicha(tablero, indiceViejo);
            escribirFicha(tablero, indNuevo, ficha);
        }
    }
}
