#pragma once
#include "Puntuaciones.h"

// Muestra el reporte de puntuaciones ordenado de mayor a menor
class VistaPuntuaciones
{
public:
    // Dibuja la tabla con la posición, el alias, los puntos y la fecha de cada jugador
    void Draw(const RegistroPuntuaciones &registro) const;
};