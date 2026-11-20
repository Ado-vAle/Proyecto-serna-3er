#pragma once
#include "Tablero.h"

// Dibuja el tablero en la ventana y convierte los clics en movimientos
class VistaTablero
{
public:
    // Recibe el tablero que va a mostrar; no lo copia
    explicit VistaTablero(Tablero &tableroJuego);

    // Mezcla el tablero y reinicia el contador de movimientos
    void IniciarPartida();

    // Procesa el clic del mouse, ESC y ENTER del frame actual
    void Update();

    // Dibuja el tablero, el contador y las instrucciones
    void Draw() const;

    // Indica si el usuario pidió regresar al menú principal
    bool VolverAlMenuSolicitado() const;

    // true cuando la partida está resuelta y el usuario confirmó con ENTER
    bool FinConfirmado() const;

    // Puntos de la partida actual según sus movimientos
    int PuntosObtenidos() const;

    // Regla de puntuación: 1000 puntos menos 10 por movimiento, con mínimo de 100
    static int CalcularPuntos(int movimientos);

private:
    // Convierte la posición del clic en fila y columna y mueve la pieza
    void ProcesarClic();

    // Dibuja una casilla; resalta las fichas que sí se pueden mover
    void DibujarCelda(int fila, int columna) const;

    Tablero &tablero;   // Estado del juego (referencia, no copia)
    int movimientos;    // Movimientos realizados en la partida actual
    bool volverAlMenu;  // true cuando el usuario presiona ESC
    bool finConfirmado; // true cuando el usuario confirma el fin de la partida
};