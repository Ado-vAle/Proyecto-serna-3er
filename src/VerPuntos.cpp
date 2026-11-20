#include "VerPuntos.h"
#include <string>
#include "raylib.h"

namespace
{
    constexpr int kAncho = 800;

    // Dibuja texto centrado horizontalmente
    void DibujarTextoCentrado(const std::string &texto, int y, int tamano, Color color)
    {
        int ancho = MeasureText(texto.c_str(), tamano);
        DrawText(texto.c_str(), (kAncho - ancho) / 2, y, tamano, color);
    }
}

void VistaPuntuaciones::Draw(const RegistroPuntuaciones &registro) const
{
    ClearBackground(RAYWHITE);
    DibujarTextoCentrado("REPORTE DE PUNTUACIONES", 40, 30, BLACK);

    // Encabezados de columna
    DrawText("#", 150, 110, 20, DARKGRAY);
    DrawText("Alias", 200, 110, 20, DARKGRAY);
    DrawText("Puntos", 450, 110, 20, DARKGRAY);
    DrawText("Fecha", 600, 110, 20, DARKGRAY);

    if (registro.Primero() == nullptr)
    {
        DibujarTextoCentrado("Aún no hay puntuaciones", 280, 24, GRAY);
    }

    // Una fila por jugador; se detiene antes del pie de página
    int y = 145;
    int posicion = 1;
    for (const Nodo *actual = registro.Primero(); actual != nullptr && y < 530;
         actual = actual->siguiente)
    {
        DrawText(std::to_string(posicion).c_str(), 150, y, 20, DARKGRAY);
        DrawText(actual->dato.alias.c_str(), 200, y, 20, DARKGRAY);
        DrawText(std::to_string(actual->dato.puntos).c_str(), 450, y, 20, DARKGRAY);
        DrawText(actual->dato.fecha.c_str(), 600, y, 20, DARKGRAY);
        y += 30;
        ++posicion;
    }

    DibujarTextoCentrado("ESC: volver al menú", 560, 18, GRAY);
}