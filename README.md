# Puzzle 8-Piezas

Juego del 8-puzzle en C++ con raylib, desarrollado como proyecto para las materias de programacion y de estructura de datos de tercer semestre de la universidad autonoma de aguascalientes para la carrera de ingenieria en sistemas. Incluye modo manual e inteligente con sugerencias mediante el algoritmo A*.

**Integrantes:** 

    Diego Alejandro Rodriguez Garcia
    Caroll Alexa Virgen Rivera 
    Alexa Dileny

Requisitos
Lo que debe estar instalado antes de compilar:

    Git
    CMake (3.16 o superior)
    Compilador g++ (se probó con w64devkit, GCC 16.2.0)
    Conexión a internet la primera vez, para descargar raylib

Compilación y ejecución
Los comandos exactos, para que cualquiera pueda replicarlos:
    
    git clone <enlace del repositorio>
    cd Proyecto_Serna
    cmake -B build -G "MinGW Makefiles" -DCMAKE_C_COMPILER=<ruta>/gcc.exe -DCMAKE_CXX_COMPILER=<ruta>/g++.exe
    cmake --build build
    .\build\puzzle8.exe

Estructura del proyecto
Un árbol corto de carpetas, para que encuentre los archivos rápido:

    include/   → archivos de cabecera (.h)
    src/       → código fuente (.cpp)
    docs/      → documento de reglas, bitácora y manual


Compilar y ejecutar 

    cmake --build build
    .\build\puzzle8.exe
