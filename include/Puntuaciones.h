#pragma once
#include <string>

// Datos de un jugador: alias, puntos acumulados y fecha de su última partida
struct Puntuacion
{
    std::string alias;
    int puntos;
    std::string fecha;
};

// Elemento de la lista enlazada propia que guarda las puntuaciones
struct Nodo
{
    Puntuacion dato;
    Nodo *siguiente;
};

// Guarda las puntuaciones en una lista enlazada y las sincroniza con un archivo de texto
class RegistroPuntuaciones
{
public:
    RegistroPuntuaciones();
    ~RegistroPuntuaciones();

    // La lista posee su memoria, así que no se puede copiar
    RegistroPuntuaciones(const RegistroPuntuaciones &) = delete;
    RegistroPuntuaciones &operator=(const RegistroPuntuaciones &) = delete;

    // Carga las puntuaciones desde el archivo. Si no existe, la lista queda vacía
    bool Cargar(const std::string &ruta);

    // Escribe todas las puntuaciones en el archivo, una por línea
    bool Guardar(const std::string &ruta) const;

    // Suma los puntos si el alias ya existe; si no, agrega un jugador nuevo al final
    void Registrar(const std::string &alias, int puntos, const std::string &fecha);

    // Ordena la lista de mayor a menor puntuación
    void Ordenar();

    // Primer elemento de la lista (nullptr si está vacía)
    const Nodo *Primero() const;

    // Fecha de hoy con formato AAAA-MM-DD
    static std::string FechaActual();

private:
    Nodo *primero;
};