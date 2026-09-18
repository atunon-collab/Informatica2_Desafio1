cmake_minimum_required(VERSION 3.16)

project(Desafio_1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Desafio_1 main.cpp
    bits.h bits.cpp
    tablero.h tablero.cpp
    combinaciones.h combinaciones.cpp
    reorganizar.h reorganizar.cpp
    estado.h estado.cpp
    estructura.h estructura.cpp
    interfaz.h interfaz.cpp)

include(GNUInstallDirs)
install(TARGETS Desafio_1
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
