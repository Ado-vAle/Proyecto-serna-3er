#include "Button.h"
#include <utility>

Button::Button(Rectangle bounds, std::string label)
    : bounds(bounds), label(std::move(label)) {}

void Button::Draw() const
{
    // Si el mouse está sobre el botón, se pinta de otro color para dar retroalimentación
    bool hovered = CheckCollisionPointRec(GetMousePosition(), bounds);
    Color background = hovered ? SKYBLUE : LIGHTGRAY;

    DrawRectangleRec(bounds, background);
    DrawRectangleLinesEx(bounds, 2, BLACK); // Borde negro de 2 píxeles

    // Centra el texto horizontal y verticalmente dentro del botón
    const int fontSize = 24;
    int textWidth = MeasureText(label.c_str(), fontSize);
    int textX = static_cast<int>(bounds.x + (bounds.width - textWidth) / 2);
    int textY = static_cast<int>(bounds.y + (bounds.height - fontSize) / 2);
    DrawText(label.c_str(), textX, textY, fontSize, DARKGRAY);
}

bool Button::IsClicked() const
{
    // Clic izquierdo que cae dentro del área del botón
    return CheckCollisionPointRec(GetMousePosition(), bounds) &&
           IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}