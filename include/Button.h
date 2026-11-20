#pragma once
#include <string>
#include "raylib.h"

// Botón rectangular que se dibuja en pantalla y detecta clics del mouse
class Button
{
public:
    // Crea un botón con su área (posición y tamaño) y su texto
    Button(Rectangle bounds, std::string label);

    // Dibuja el botón; cambia de color cuando el mouse está encima
    void Draw() const;

    // Regresa true si el usuario hizo clic izquierdo sobre el botón en este frame
    bool IsClicked() const;

private:
    Rectangle bounds;  // Área del botón en pantalla
    std::string label; // Texto que muestra el botón
};