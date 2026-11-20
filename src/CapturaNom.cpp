#include "CapturaNom.h"
#include "raylib.h"

namespace
{
    constexpr int kAncho = 800; // Ancho de la ventana, para centrar el texto

    // Dibuja texto centrado horizontalmente
    void DibujarTextoCentrado(const std::string &texto, int y, int tamano, Color color)
    {
        int ancho = MeasureText(texto.c_str(), tamano);
        DrawText(texto.c_str(), (kAncho - ancho) / 2, y, tamano, color);
    }
}

void CapturaAlias::Reiniciar()
{
    texto.clear();
    confirmado = false;
}

void CapturaAlias::Update()
{
    // GetCharPressed entrega los caracteres escritos en este frame
    int tecla = GetCharPressed();
    while (tecla > 0)
    {
        // Solo caracteres imprimibles de ASCII. El ';' se excluye porque separa campos en el archivo
        bool valido = tecla >= 32 && tecla <= 126 && tecla != ';';
        if (valido && static_cast<int>(texto.size()) < kLongitudMaxima)
        {
            texto += static_cast<char>(tecla);
        }
        tecla = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && !texto.empty())
    {
        texto.pop_back();
    }
    if (IsKeyPressed(KEY_ENTER) && !texto.empty())
    {
        confirmado = true;
    }
}

void CapturaAlias::Draw() const
{
    ClearBackground(RAYWHITE);
    DibujarTextoCentrado("Escribe tu alias", 150, 30, BLACK);

    Rectangle caja{200.0f, 260.0f, 400.0f, 50.0f};
    DrawRectangleLinesEx(caja, 2, DARKGRAY);
    DrawText(texto.c_str(), 215, 272, 26, DARKGRAY);

    DibujarTextoCentrado("ENTER: confirmar   BORRAR: corregir   ESC: cancelar", 360, 18, GRAY);
}

bool CapturaAlias::Confirmado() const
{
    return confirmado;
}

const std::string &CapturaAlias::Alias() const
{
    return texto;
}