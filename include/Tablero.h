#pragma once

// Estado del tablero del 8-puzzle (3x3).
// El espacio vacío se representa con el valor 0.
class Tablero {
public:
    static constexpr int kFilas = 3;     // Número de filas del tablero
    static constexpr int kColumnas = 3;  // Número de columnas del tablero
    static constexpr int kVacio = 0;     // Valor que representa el espacio libre

    // Crea el tablero en estado meta: 1 2 3 / 4 5 6 / 7 8 _
    Tablero();

    // Regresa el valor de la casilla indicada (kVacio si es el espacio libre)
    int ObtenerPieza(int fila, int columna) const;

    // Indica si la casilla indicada está al lado del espacio libre
    bool EsMovimientoValido(int fila, int columna) const;

    // Mueve la pieza de la casilla indicada al espacio libre, si es adyacente.
    // Regresa true si el movimiento se realizó.
    bool MoverPieza(int fila, int columna);

    // Indica si el tablero está en la configuración meta
    bool EstaResuelto() const;

    // Indica si la configuración actual puede llegar a la meta
    bool EsResoluble() const;

    // Deja el tablero en la configuración meta
    void Reiniciar();

    // Mezcla el tablero con movimientos legales a partir de la meta.
    // Como parte de la meta, el resultado siempre es resoluble.
    void MezclarAleatorio(int cantidadMovimientos);

    // Indica si dos tableros tienen las mismas piezas en las mismas casillas
    bool EsIgualA(const Tablero& otro) const;

private:
    // Busca la fila y columna del espacio libre y las guarda en los parámetros
    void BuscarVacio(int& fila, int& columna) const;

    int piezas[kFilas][kColumnas];  // Valor de cada casilla
};