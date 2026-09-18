#include <iostream>
#include "bits.h"
#include "tablero.h"
#include "reorganizar.h"
#include "estructura.h"
#include "estado.h"
#include "interfaz.h"

using namespace std;
int main()
{
    // Medidas máximas y mínimas para una buena jugabilidad
    const unsigned short MaximoTablero = 99;
    const unsigned short MinimoTablero = 3;

    bool salirDelJuego = false;

    while (!salirDelJuego) {
        mostrarMenu();
        unsigned short opcionMenu = leerOpcion(1, 3);

        if (opcionMenu == 3 || opcionMenu == 0) {
            salirDelJuego = true;
            continue;
        }

        if (opcionMenu == 2) {
            mostrarInstrucciones();
            continue;
        }

        // opcionMenu == 1, iniciar partida

        unsigned short filas, columnas, eliminaciones, puntuacion;
        iniciarEstado(filas, columnas, eliminaciones, puntuacion);
        unsigned short combinacionesTotales = 0;

        cout << "\nIngrese la cantidad de filas deseadas\n";
        filas = leerOpcion(MinimoTablero, MaximoTablero);
        if (filas == 0) continue; // cancelado, vuelve al menu principal

        cout << "\n\n";

        cout << "Ingrese la cantidad de columnas deseadas\n";
        columnas = leerOpcion(MinimoTablero, MaximoTablero);
        if (columnas == 0) continue; // cancelado

        cout << "\n";

        // Reserva del tablero y del arreglo auxiliar de marcas
        unsigned char * tablero = crearTablero(filas, columnas);
        unsigned short bytesReservados = bytesNecesarios(filas, columnas);
        unsigned char * marcas = nullptr;
        unsigned short bytesReservadosMarcas = 0;
        actualizarMarcas(marcas, filas, columnas, bytesReservadosMarcas);

        llenarAleatorio(tablero, filas, columnas);

        // Por si el tablero aleatorio se genera con combinacion
        unsigned short eliminacionesInicial = 0, combinacionesInicial = 0, puntuacionInicial = 0;
        unsigned short eliminadasRonda = 0;
        procesarCascadas(tablero, marcas, filas, columnas, eliminacionesInicial, combinacionesInicial, puntuacionInicial, eliminadasRonda);
        eliminadasRonda = 0; // que la primera jugada no herede el valor de la limpieza inicial

        bool enPartida = true;
        while (enPartida) {
            mostrarTablero(tablero, filas, columnas);
            mostrarMenuPartida();
            unsigned short opcion = leerOpcion(1, 7);

            switch (opcion) {
            case 1: { // Eliminar fichas
                cout << "Ingrese la fila (1 - " << filas << ")\n";
                unsigned short fila = leerOpcion(1, filas);
                if (fila == 0) break; // cancelado

                cout << "Ingrese la columna (1 - " << columnas << ")\n";
                unsigned short columna = leerOpcion(1, columnas);
                if (columna == 0) break; // cancelado

                if (!posicionValida(fila, columna, filas, columnas)) {
                    cout << "Posicion invalida.\n";
                    break;
                }


                unsigned short indice = calcularIndice(fila - 1, columnas, columna - 1);
                escribirFicha(tablero, indice, 0);
                actualizarVariableSuma(eliminaciones, 1);
                actualizarVariableSuma(puntuacion, calcularPuntaje(1));

                aplicarGravedad(tablero, filas, columnas);
                rellenarVacios(tablero, filas, columnas);

                // Si la caída de fichas formó nuevas combinaciones, se hacen cascadas
                unsigned short cascadasActuales = (1 + procesarCascadas(tablero, marcas, filas, columnas, eliminaciones, combinacionesTotales, puntuacion, eliminadasRonda));
                mostrarResultadoTurno(eliminadasRonda, cascadasActuales);
                break;
            }
            case 2: { // Agregar fila
                cout << "Posicion donde insertar la fila (1 - " << (filas + 1) << ")\n";
                unsigned short posicion = leerOpcion(1, filas + 1);
                if (posicion == 0) break;

                insertarFila(tablero, filas, columnas, posicion - 1, bytesReservados);
                actualizarMarcas(marcas, filas, columnas, bytesReservadosMarcas);
                unsigned short cascadasActuales = procesarCascadas(tablero, marcas, filas, columnas, eliminaciones, combinacionesTotales, puntuacion, eliminadasRonda);
                mostrarResultadoTurno(eliminadasRonda, cascadasActuales);
                break;
            }
            case 3: { // Eliminar fila
                if (filas <= MinimoTablero) {
                    cout << "El tablero ya esta en su tamano minimo.\n";
                    break;
                }
                cout << "Fila a eliminar (1 - " << filas << ")\n";
                unsigned short posicion = leerOpcion(1, filas);
                if (posicion == 0) break;

                eliminarFila(tablero, filas, columnas, posicion - 1, bytesReservados);
                actualizarMarcas(marcas, filas, columnas, bytesReservadosMarcas);
                unsigned short cascadasActuales = procesarCascadas(tablero, marcas, filas, columnas, eliminaciones, combinacionesTotales, puntuacion, eliminadasRonda);
                mostrarResultadoTurno(eliminadasRonda, cascadasActuales);
                break;
            }
            case 4: { // Agregar columna
                cout << "Posicion donde insertar la columna (1 - " << (columnas + 1) << ")\n";
                unsigned short posicion = leerOpcion(1, columnas + 1);
                if (posicion == 0) break;

                insertarColumna(tablero, filas, columnas, posicion - 1, bytesReservados);
                actualizarMarcas(marcas, filas, columnas, bytesReservadosMarcas);
                unsigned short cascadasActuales = procesarCascadas(tablero, marcas, filas, columnas, eliminaciones, combinacionesTotales, puntuacion, eliminadasRonda);
                mostrarResultadoTurno(eliminadasRonda, cascadasActuales);
                break;
            }
            case 5: { // Eliminar columna
                if (columnas <= MinimoTablero) {
                    cout << "El tablero ya esta en su tamano minimo.\n";
                    break;
                }
                cout << "Columna a eliminar (1 - " << columnas << ")\n";
                unsigned short posicion = leerOpcion(1, columnas);
                if (posicion == 0) break;

                eliminarColumna(tablero, filas, columnas, posicion - 1, bytesReservados);
                actualizarMarcas(marcas, filas, columnas, bytesReservadosMarcas);
                unsigned short cascadasActuales = procesarCascadas(tablero, marcas, filas, columnas, eliminaciones, combinacionesTotales, puntuacion, eliminadasRonda);
                mostrarResultadoTurno(eliminadasRonda, cascadasActuales);
                break;
            }
            case 6: // Ver estado actual del juego
                mostrarEstado(filas, columnas, eliminaciones, combinacionesTotales, puntuacion);
                break;
            case 7: // Salir al menu principal
                enPartida = false;
                break;
            }
        }

        liberarTablero(tablero);
        delete[] marcas;
        marcas = nullptr;
    }

    cout << "\nGracias por jugar Sweet Crush.\n";
    return 0;
}