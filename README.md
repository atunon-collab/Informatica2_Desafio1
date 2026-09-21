# 🍬 Sweet Crush — Desafío I

Implementación del juego **Sweet Crush** en consola con **C++ (Qt / CMake)**, donde el tablero completo se guarda como una secuencia continua de bits: **3 bits por ficha**, sin desperdiciar espacio para alinear a byte.

Proyecto del curso **Informática II** · Universidad de Antioquia · Facultad de Ingeniería · Semestre 2026-2.

📺 **Video de sustentación:** [https://youtu.be/Go2UlIINBt8]

---

## 👥 Autores

- Andrés Felipe Tuñón Conde
- Melissa Sthefania Ardila Becerra

Profesor: Aníbal José Guerra Soler

---

## 📋 Tabla de contenido

1. [Descripción](#-descripción)
2. [Características](#-características)
3. [Compilación y ejecución](#-compilación-y-ejecución)
4. [Cómo se juega](#-cómo-se-juega)
5. [Representación del tablero en memoria](#-representación-del-tablero-en-memoria)
6. [Gestión dinámica de la memoria](#-gestión-dinámica-de-la-memoria)
7. [Estructura del proyecto](#-estructura-del-proyecto)
8. [Decisiones de diseño](#-decisiones-de-diseño)
9. [Restricciones del desafío](#-restricciones-del-desafío)

---

## 🎮 Descripción

El jugador crea un tablero de `F × C` posiciones, elimina fichas una a una y el programa se encarga del resto: detecta combinaciones de **3 o más fichas iguales** (horizontal y vertical), las elimina, hace caer las fichas restantes, rellena los huecos con fichas aleatorias y repite el proceso mientras sigan apareciendo combinaciones (**cascadas**).

Además, el tablero se puede modificar durante la partida: **agregar o eliminar filas y columnas en cualquier posición**, no solo en los extremos, conservando todas las fichas que deban permanecer.

## ✨ Características

- Tablero dinámico de **3 a 99** filas y columnas, elegido al iniciar la partida.
- Fichas generadas con **distribución uniforme**.
- Visualización en pantalla del tablero de **símbolos** junto a un segundo tablero con la **representación binaria** de cada casilla.
- Detección de combinaciones horizontales y verticales; una misma ficha puede pertenecer a ambas y se elimina una sola vez.
- Gravedad, relleno y **cascadas automáticas**.
- Agregar / eliminar fila y agregar / eliminar columna en **posiciones intermedias**.
- Memoria reservada acorde a las **dimensiones actuales** del tablero.
- Estado de la partida: dimensiones, eliminaciones del usuario, fichas eliminadas, combinaciones, cascadas y puntuación.
- Se puede escribir `C` o `c` en cualquier ingreso para **cancelar** la acción.

---


## 🕹️ Cómo se juega

Al ejecutar aparece el menú principal:

```
========================================
          SWEET CRUSH - MENU
+--------------------------------------+
1. Iniciar Partida
2. Ver Instrucciones
3. Salir del Juego
========================================
```

Dentro de la partida se muestra el tablero (símbolos a la izquierda, bits a la derecha) y las opciones de juego:

```
     1   2   3   4   5
   +---+---+---+---+---+     +-----+-----+-----+-----+-----+
 1 | % | @ | X | @ | O |     | 100 | 001 | 110 | 001 | 101 |
   +---+---+---+---+---+     +-----+-----+-----+-----+-----+
 2 | O | O | ? | X | @ |     | 101 | 101 | 011 | 110 | 001 |
   +---+---+---+---+---+     +-----+-----+-----+-----+-----+
 3 | O | % | @ | @ | % |     | 101 | 100 | 001 | 001 | 100 |
   +---+---+---+---+---+     +-----+-----+-----+-----+-----+
 4 | # | # | % | O | # |     | 010 | 010 | 100 | 101 | 010 |
   +---+---+---+---+---+     +-----+-----+-----+-----+-----+

============================================
            OPCIONES DE JUEGO
============================================
1. Eliminar una ficha
2. Agregar fila
3. Eliminar fila
4. Agregar columna
5. Eliminar columna
6. Ver estado actual del juego
7. Salir al menu principal
============================================
```

| Opción | Acción |
|:------:|--------|
| 1 | Elimina la ficha en la `(fila, columna)` indicada (coordenadas desde 1) y dispara gravedad, relleno y cascadas. |
| 2 / 4 | Inserta una fila / columna en la posición elegida (`1` hasta `n + 1`). |
| 3 / 5 | Elimina la fila / columna elegida. El tablero no baja de 3 filas ni de 3 columnas. |
| 6 | Muestra dimensiones, fichas eliminadas, combinaciones y puntuación. |
| 7 | Vuelve al menú principal y libera la memoria de la partida. |

### Fichas y puntuación

| Código | Elemento | Símbolo |
|:------:|----------|:-------:|
| `000` | Vacío | ` ` |
| `001` | Ficha 1 | `@` |
| `010` | Ficha 2 | `#` |
| `011` | Ficha 3 | `?` |
| `100` | Ficha 4 | `%` |
| `101` | Ficha 5 | `O` |
| `110` | Ficha 6 | `X` |

**Puntuación:** cada ficha eliminada suma **3 puntos**, ya sea eliminada por el jugador o por una combinación / cascada.

Se eligió `000` como vacío porque `new unsigned char[n]()` deja el tablero en ceros al crearlo, y porque es el valor que se escribe en las casillas eliminadas antes de que las fichas caigan.

---

## 🧠 Representación del tablero en memoria

El tablero es un único bloque `unsigned char *` donde las fichas se guardan **una tras otra en grupos de 3 bits**, empezando por el bit menos significativo. Ningún byte representa una ficha: los bits de fichas distintas comparten byte.

Para una posición `(fila, columna)`:

```
indice        = fila × columnas + columna
bit inicial   = indice × 3
byte          = bit inicial / 8      →  (indice × 3) / 8
desplazamiento = bit inicial % 8     →  (indice × 3) % 8
bytes totales = (3 × filas × columnas + 7) / 8
```

Según el desplazamiento dentro del byte hay dos casos:

| Desplazamiento | Caso | Operación |
|:--------------:|------|-----------|
| 0 a 5 | La ficha cabe en **un solo byte** | `(tablero[byte] >> desp) & 7` |
| 6 o 7 | La ficha queda **repartida en dos bytes** | `((tablero[byte] >> desp) \| (tablero[byte+1] << (8 - desp))) & 7` |

**Ejemplo:** el índice 2 empieza en el bit 6 del byte 0. Sus 3 bits se reparten: 2 en el byte 0 y 1 en el byte 1.

Para escribir, primero se **apagan** los bits viejos con una máscara invertida (`~(7 << desp)`) y luego se **encienden** los nuevos con un OR. En el caso repartido se hace lo mismo en ambos bytes (`~(7 >> (8 - desp))` en el segundo).

### Arreglo de marcas

Para señalar qué fichas se eliminarán se usa un segundo bloque dinámico con **1 bit por casilla** (`(filas × columnas + 7) / 8` bytes). Al marcar en lugar de borrar directamente, una ficha que participa en una combinación horizontal y otra vertical al mismo tiempo se elimina una sola vez.

---

## 💾 Gestión dinámica de la memoria

Todo el tablero vive en memoria dinámica (`new[]` / `delete[]`) y se reserva con el tamaño justo para las dimensiones actuales.

| Operación | Comportamiento |
|-----------|----------------|
| **Insertar fila / columna** | Si los bytes necesarios caben en lo ya reservado, las fichas se desplazan **dentro del mismo bloque** (`desplazarInsertados`, recorriendo de atrás hacia adelante para no pisar datos sin leer). Si no caben, se reserva un bloque nuevo, se copian las fichas ajustando coordenadas y se libera el anterior (`copiarConNuevasDimensiones`). |
| **Eliminar fila / columna** | La memoria física **solo se reduce** cuando los bytes necesarios caen por debajo del **65 %** de lo reservado (`requiereEncogimiento`). En ese caso se reasigna; si no, las fichas se desplazan dentro del mismo bloque (`desplazarEliminadas`). |
| **Marcas** | `actualizarMarcas` aplica la misma regla del 65 %: reutiliza el bloque (limpiándolo) o lo reasigna según el tamaño requerido. |

Los punteros que pueden cambiar de bloque se reciben por referencia (`unsigned char *&`), de modo que `main` siempre apunta al bloque vigente. Al salir de la partida se libera todo con `delete[]`.

---

## 🗂️ Estructura del proyecto

```
.
├── CMakeLists.txt
├── main.cpp               # Ciclo principal: menú, partida y liberación de memoria
├── bits.h / bits.cpp      # Acceso a nivel de bits: fichas y marcas
├── tablero.h / .cpp       # Creación, aleatoriedad y visualización del tablero
├── combinaciones.h / .cpp # Detección y eliminación de combinaciones
├── reorganizar.h / .cpp   # Gravedad, relleno y cascadas
├── estructura.h / .cpp    # Agregar/eliminar filas y columnas, redimensionado
├── estado.h / .cpp        # Contadores de la partida y puntuación
└── interfaz.h / .cpp      # Menús y validación de entradas
```

| Módulo | Responsabilidad | Funciones principales |
|--------|-----------------|-----------------------|
| **bits** | Traducir entre posición lógica y bits en memoria | `calcularIndice`, `bytesNecesarios`, `leerFicha`, `escribirFicha`, `leerMarca`, `escribirMarca`, `actualizarMarcas` |
| **tablero** | Crear, liberar, llenar y mostrar el tablero | `crearTablero`, `liberarTablero`, `fichaAleatoria`, `simboloDeFicha`, `llenarAleatorio`, `mostrarTablero` |
| **combinaciones** | Encontrar y eliminar grupos de 3 o más | `marcarHorizontales`, `marcarVerticales`, `eliminarMarcadas`, `limpiarMarcas` |
| **reorganizar** | Reacomodar el tablero tras eliminar | `aplicarGravedad`, `rellenarVacios`, `procesarCascadas` |
| **estructura** | Modificar las dimensiones del tablero | `insertarFila`, `eliminarFila`, `insertarColumna`, `eliminarColumna`, `copiarConNuevasDimensiones`, `desplazarInsertados`, `desplazarEliminadas`, `requiereEncogimiento` |
| **estado** | Llevar el registro de la partida | `iniciarEstado`, `calcularPuntaje`, `actualizarVariableSuma`, `mostrarEstado` |
| **interfaz** | Menús y lectura segura de datos | `mostrarMenu`, `mostrarInstrucciones`, `mostrarMenuPartida`, `leerOpcion`, `posicionValida`, `mostrarResultadoTurno` |

---

## 🧩 Decisiones de diseño

- **`unsigned char *`** para el bloque del tablero y de marcas: evita problemas con el bit de signo al hacer desplazamientos.
- **`unsigned short`** para filas, columnas, índices, bytes reservados y contadores: con tableros de hasta 99 × 99 los índices no superan 9 800, así que caben de sobra y se ahorra memoria frente a `unsigned int`.
- **`short`** solo donde hace falta un valor negativo (por ejemplo, el lector de `aplicarGravedad`, que baja hasta −1 para terminar el ciclo).
- **`enum operacion`** para nombrar las cuatro operaciones estructurales y reutilizar la misma lógica de reubicación de fichas.
- **`leerOpcion`** lee la entrada como arreglo de `char` con ancho limitado y la valida carácter por carácter (ASCII), sin usar `string`.
- Solo `leerFicha` y `escribirFicha` (y sus equivalentes para marcas) tocan los bits directamente; el resto del programa trabaja con índices.

---

## ✅ Restricciones del desafío

- Lenguaje **C++** (sin sintaxis de ANSI C), proyecto **Qt / CMake**.
- Programación **modular** en varios archivos `.h` / `.cpp`.
- **Sin** `struct`, `class`, `template`, objetos `string` ni contenedores de la STL.
- Uso de **punteros, arreglos y memoria dinámica** en el núcleo de la solución.
- Uso de operadores a nivel de bits (`&`, `|`, `~`, `<<`, `>>`) en el núcleo de la solución.
- Sin desempaquetar el tablero en una estructura auxiliar de un byte por ficha.
- Librerías utilizadas: `<iostream>` y `<random>`.

---

<p align="center">Universidad de Antioquia · Informática II · 2026-2</p>
