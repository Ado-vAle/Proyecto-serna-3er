#pragma once
#include <string>

// Pantalla donde el usuario escribe su alias antes de jugar
class CapturaAlias
{
public:
    static constexpr int kLongitudMaxima = 12; // Caracteres máximos del alias

    // Borra el texto anterior y deja la captura lista para una nueva partida
    void Reiniciar();

    // Lee las teclas del frame: escritura, borrar y confirmar con ENTER
    void Update();

    // Dibuja el cuadro de texto y las instrucciones
    void Draw() const;

    // true cuando el alias tiene texto y el usuario presionó ENTER
    bool Confirmado() const;

    // Alias escrito por el usuario
    const std::string &Alias() const;

private:
    std::string texto = "";
    bool confirmado = false;
};