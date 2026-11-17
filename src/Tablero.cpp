#include "Tablero.h"
#include "raylib.h"

Tablero::Tablero() {
    Reiniciar();
}

int Tablero::ObtenerPieza(int fila, int columna) const {
    return piezas[fila][columna];
}

void Tablero::BuscarVacio(int& fila, int& columna) const {
    // Recorre el tablero hasta encontrar el espacio libre
    for (int f = 0; f < kFilas; ++f) {
        for (int c = 0; c < kColumnas; ++c) {
            if (piezas[f][c] == kVacio) {
                fila = f;
                columna = c;
                return;
            }
        }
    }
}

bool Tablero::EsMovimientoValido(int fila, int columna) const {
    // Descarta casillas fuera del tablero
    if (fila < 0 || fila >= kFilas || columna < 0 || columna >= kColumnas) {
        return false;
    }

    int vacioFila = 0;
    int vacioColumna = 0;
    BuscarVacio(vacioFila, vacioColumna);

    // Es válido si la distancia en filas más la distancia en columnas es 1
    int distanciaFila = fila > vacioFila ? fila - vacioFila : vacioFila - fila;
    int distanciaColumna = columna > vacioColumna ? columna - vacioColumna : vacioColumna - columna;
    return distanciaFila + distanciaColumna == 1;
}

bool Tablero::MoverPieza(int fila, int columna) {
    if (!EsMovimientoValido(fila, columna)) {
        return false;
    }

    // Intercambia la pieza con el espacio libre
    int vacioFila = 0;
    int vacioColumna = 0;
    BuscarVacio(vacioFila, vacioColumna);
    piezas[vacioFila][vacioColumna] = piezas[fila][columna];
    piezas[fila][columna] = kVacio;
    return true;
}

bool Tablero::EstaResuelto() const {
    // Cada casilla debe tener su número: 1, 2, ..., 8 y al final el vacío
    for (int f = 0; f < kFilas; ++f) {
        for (int c = 0; c < kColumnas; ++c) {
            int esperado = (f * kColumnas + c + 1) % (kFilas * kColumnas);
            if (piezas[f][c] != esperado) {
                return false;
            }
        }
    }
    return true;
}

bool Tablero::EsResoluble() const {
    // En un tablero de ancho impar, la configuración es resoluble
    // si el número de inversiones (piezas en orden incorrecto) es par.
    // El espacio libre no se cuenta.
    const int total = kFilas * kColumnas;
    int inversiones = 0;

    for (int i = 0; i < total; ++i) {
        int a = piezas[i / kColumnas][i % kColumnas];
        if (a == kVacio) {
            continue;
        }
        for (int j = i + 1; j < total; ++j) {
            int b = piezas[j / kColumnas][j % kColumnas];
            if (b != kVacio && a > b) {
                ++inversiones;
            }
        }
    }
    return inversiones % 2 == 0;
}

void Tablero::Reiniciar() {
    // Llena el tablero con los valores de la meta
    for (int f = 0; f < kFilas; ++f) {
        for (int c = 0; c < kColumnas; ++c) {
            piezas[f][c] = (f * kColumnas + c + 1) % (kFilas * kColumnas);
        }
    }
}

void Tablero::MezclarAleatorio(int cantidadMovimientos) {
    Reiniciar();

    // Repite movimientos legales al azar hasta completar la cantidad pedida.
    // Solo cuenta los movimientos que sí se realizaron.
    int realizados = 0;
    while (realizados < cantidadMovimientos) {
        int vacioFila = 0;
        int vacioColumna = 0;
        BuscarVacio(vacioFila, vacioColumna);

        // Elige una dirección al azar: 0 arriba, 1 abajo, 2 izquierda, 3 derecha
        int direccion = GetRandomValue(0, 3);
        int filaDestino = vacioFila + (direccion == 0 ? -1 : direccion == 1 ? 1 : 0);
        int columnaDestino = vacioColumna + (direccion == 2 ? -1 : direccion == 3 ? 1 : 0);

        if (MoverPieza(filaDestino, columnaDestino)) {
            ++realizados;
        }
    }
}

bool Tablero::EsIgualA(const Tablero& otro) const {
    for (int f = 0; f < kFilas; ++f) {
        for (int c = 0; c < kColumnas; ++c) {
            if (piezas[f][c] != otro.piezas[f][c]) {
                return false;
            }
        }
    }
    return true;
}