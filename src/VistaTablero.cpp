#include "VistaTablero.h"
#include <string>
#include "raylib.h"

namespace
{
    constexpr int kTamanoCelda = 100; // Ancho y alto de cada casilla en pixeles
    constexpr int kOrigenX = 250;     // Esquina superior izquierda del tablero (centrado en 800)
    constexpr int kOrigenY = 130;
    constexpr int kTamanoTexto = 40;       // Tamano de los numeros de las fichas
    constexpr int kMovimientosMezcla = 30; // Movimientos con los que se mezcla la partida

    // Dibuja texto centrado horizontalmente en la pantalla de 800 pixeles
    void DibujarTextoCentrado(const std::string &texto, int y, int tamano, Color color)
    {
        int ancho = MeasureText(texto.c_str(), tamano);
        DrawText(texto.c_str(), (800 - ancho) / 2, y, tamano, color);
    }
}

VistaTablero::VistaTablero(Tablero &tableroJuego)
    : tablero(tableroJuego), movimientos(0), volverAlMenu(false), finConfirmado(false) {}

void VistaTablero::IniciarPartida()
{
    tablero.MezclarAleatorio(kMovimientosMezcla);
    movimientos = 0;
    volverAlMenu = false;
    finConfirmado = false;
}

void VistaTablero::Update()
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        volverAlMenu = true;
        return;
    }

    if (tablero.EstaResuelto())
    {
        // Con el tablero resuelto los clics no mueven piezas; ENTER confirma el puntaje
        if (IsKeyPressed(KEY_ENTER))
        {
            finConfirmado = true;
        }
        return;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        ProcesarClic();
    }
}

void VistaTablero::Draw() const
{
    ClearBackground(RAYWHITE);
    DibujarTextoCentrado("PARTIDA MANUAL", 40, 30, BLACK);

    for (int fila = 0; fila < Tablero::kFilas; ++fila)
    {
        for (int columna = 0; columna < Tablero::kColumnas; ++columna)
        {
            DibujarCelda(fila, columna);
        }
    }

    DibujarTextoCentrado("Movimientos: " + std::to_string(movimientos), 470, 24, DARKGRAY);

    if (tablero.EstaResuelto())
    {
        DibujarTextoCentrado("Resuelto! Puntos: " + std::to_string(PuntosObtenidos()), 505, 30, DARKGREEN);
        DibujarTextoCentrado("ENTER: guardar puntaje   ESC: salir sin guardar", 555, 18, GRAY);
    }
    else
    {
        DibujarTextoCentrado("Clic en una ficha junto al espacio libre  |  ESC: menu", 555, 18, GRAY);
    }
}

bool VistaTablero::FinConfirmado() const
{
    return finConfirmado;
}

int VistaTablero::PuntosObtenidos() const
{
    return CalcularPuntos(movimientos);
}

int VistaTablero::CalcularPuntos(int movimientos)
{
    int puntos = 1000 - 10 * movimientos;
    return puntos < 100 ? 100 : puntos;
}

void VistaTablero::ProcesarClic()
{
    // Calcula la posición relativa al tablero; si cae fuera, no hay nada que hacer
    Vector2 raton = GetMousePosition();
    int x = static_cast<int>(raton.x) - kOrigenX;
    int y = static_cast<int>(raton.y) - kOrigenY;
    if (x < 0 || y < 0)
    {
        return;
    }

    int columna = x / kTamanoCelda;
    int fila = y / kTamanoCelda;
    if (fila >= Tablero::kFilas || columna >= Tablero::kColumnas)
    {
        return;
    }

    // Solo cuenta el movimiento si Tablero lo aceptó
    if (tablero.MoverPieza(fila, columna))
    {
        ++movimientos;
    }
}

void VistaTablero::DibujarCelda(int fila, int columna) const
{
    Rectangle area{
        static_cast<float>(kOrigenX + columna * kTamanoCelda),
        static_cast<float>(kOrigenY + fila * kTamanoCelda),
        static_cast<float>(kTamanoCelda),
        static_cast<float>(kTamanoCelda)};

    int valor = tablero.ObtenerPieza(fila, columna);
    if (valor == Tablero::kVacio)
    {
        // El espacio libre solo se marca con un contorno suave
        DrawRectangleLinesEx(area, 1, LIGHTGRAY);
        return;
    }

    // Azul si la ficha se puede mover, gris si no
    bool movible = tablero.EsMovimientoValido(fila, columna);
    Color fondo = movible ? SKYBLUE : LIGHTGRAY;
    DrawRectangleRec(area, fondo);
    DrawRectangleLinesEx(area, 3, DARKGRAY);

    std::string numero = std::to_string(valor);
    int ancho = MeasureText(numero.c_str(), kTamanoTexto);
    int textoX = static_cast<int>(area.x) + (kTamanoCelda - ancho) / 2;
    int textoY = static_cast<int>(area.y) + (kTamanoCelda - kTamanoTexto) / 2;
    DrawText(numero.c_str(), textoX, textoY, kTamanoTexto, DARKGRAY);
}

bool VistaTablero::VolverAlMenuSolicitado() const
{
    return volverAlMenu;
}