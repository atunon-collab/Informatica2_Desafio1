#include "interfaz.h"
#include <iostream>

using namespace std;

void mostrarMenu() {
    cout << "\n========================================\n";
    cout << "          SWEET CRUSH - MENU            \n";
    cout << "+--------------------------------------+\n";
    cout << "1. Iniciar Partida\n";
    cout << "2. Ver Instrucciones\n";
    cout << "3. Salir del Juego\n";
    cout << "========================================\n";
}

void mostrarInstrucciones() {
    cout << "\n============================================================\n";
    cout << "                 INSTRUCCIONES DE JUEGO                \n";
    cout << "============================================================\n";
    cout << "1. El juego consiste en formar combinaciones de 3 o mas\n";
    cout << "   fichas iguales en sentido horizontal o vertical.\n";
    cout << "============================================================\n"; // separador
    cout << "2. Puede seleccionar una ficha para eliminarla manualmente.\n";
    cout << "============================================================\n"; // separador
    cout << "3. Al eliminar una ficha del tabler, las fichas superiores\n";
    cout << "   caen por gravedad y se rellenan los espacios vacios\n";
    cout << "   con nuevas fichas.\n";
    cout << "============================================================\n"; // separador
    cout << "4. Si la reorganizacion genera nuevas combinaciones, se\n";
    cout << "   produciran cascadas automaticamente.\n";
    cout << "============================================================\n";
    cout << "5. Puede modificar la estructura del tablero agregando o\n";
    cout << "   eliminando filas o columnas en cualquier posicion.\n";
    cout << "============================================================\n";
    cout << "6. En cualquier momento de ingreso de datos o coordenadas,\n";
    cout << "   puede ingresar 'C' o 'c' para CANCELAR la accion.\n";
    cout << "============================================================\n";
}
void mostrarMenuPartida() {
    cout << "\n============================================\n";
    cout << "            OPCIONES DE JUEGO           \n";
    cout << "============================================\n";
    cout << "1. Eliminar una ficha\n";
    cout << "2. Agregar fila\n";
    cout << "3. Eliminar fila\n";
    cout << "4. Agregar columna\n";
    cout << "5. Eliminar columna\n";
    cout << "6. Ver estado actual del juego\n";
    cout << "7. Salir al menu principal\n";
    cout << "============================================\n";
}

// Lee un número entero de la consola, se verifica que sea válido como número y que esté entre el rango de [mínimo,máximo]
unsigned short leerOpcion(short minimo, short maximo) {
    char entrada[3];

    while (true) {
        cout << "Seleccione una opcion en el intervalo de [" << minimo << " - " << maximo << "] (o 'C' para cancelar): ";

        cin.width(3); // Evita desbordamiento de memoria si el usuario ingresa > 20 caracteres
        cin >> entrada;

        // Verificamos si es una 'C' o 'c' usando los índices del arreglo
        if ((entrada[0] == 'C' || entrada[0] == 'c') && entrada[1] == '\0') {
            cout << "Cancelaste el ingreso del numero\n";
            return 0;
        }

        bool esNumero = true;
        unsigned short opcion = 0;

        // El ciclo se detiene al encontrar el caracter nulo '\0' que marca el fin de la palabra
        for (unsigned short i = 0; entrada[i] != '\0'; i++) {
            // Utilizamos el código ASCII: "0" = 48, "9" = 57
            if (entrada[i] >= '0' && entrada[i] <= '9') {
                opcion = (opcion * 10) + (entrada[i] - '0'); // Resta el valor ASCII para obtener el entero
            } else {
                esNumero = false;
                break;
            }
        }

        if (esNumero && entrada[0] != '\0') {
            if (opcion >= minimo && opcion <= maximo) {
                return opcion;
            } else {
                cout << "Opcion fuera del rango permitido (" << minimo << " - " << maximo << "). Intente de nuevo.\n";
            }
        } else {
            cout << "Entrada invalida. Debe ingresar un numero entero o 'C' para cancelar.\n";
        }
    }
}

// Verifica si la coordenada ingresada es válida
bool posicionValida(unsigned short fila, unsigned short columna, unsigned short filas, unsigned short columnas) {
    return (fila > 0 && fila <= filas && columna > 0 && columna <= columnas);
}

// Muestra el resultado inmediato de la jugada: cuantas fichas se eliminaron
// en la ultima ronda de procesarCascadas y cuantas cascadas se dispararon
void mostrarResultadoTurno(unsigned short eliminadasActuales, unsigned short cascadasActuales) {
    cout << "\n=== Resultado de la jugada ===\n";
    cout << "Eliminaciones actuales : " << eliminadasActuales << "\n";
    cout << "Cascadas actuales      : " << cascadasActuales << "\n";
    cout << "===============================\n";
}