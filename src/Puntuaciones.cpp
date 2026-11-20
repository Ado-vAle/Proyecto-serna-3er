#include "Puntuaciones.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <utility>

RegistroPuntuaciones::RegistroPuntuaciones() : primero(nullptr) {}

RegistroPuntuaciones::~RegistroPuntuaciones()
{
    // Libera cada nodo de la lista para no dejar memoria sin liberar
    Nodo *actual = primero;
    while (actual != nullptr)
    {
        Nodo *siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

bool RegistroPuntuaciones::Cargar(const std::string &ruta)
{
    std::ifstream archivo(ruta);
    if (!archivo)
    {
        // Si el archivo todavía no existe, no es un error: se crea al guardar
        return false;
    }

    std::string linea;
    while (std::getline(archivo, linea))
    {
        // Cada línea tiene el formato alias;puntos;fecha
        std::size_t separador1 = linea.find(';');
        if (separador1 == std::string::npos)
        {
            continue; // Línea mal formada: se ignora
        }
        std::size_t separador2 = linea.find(';', separador1 + 1);
        if (separador2 == std::string::npos)
        {
            continue;
        }

        std::string alias = linea.substr(0, separador1);
        int puntos = std::atoi(linea.substr(separador1 + 1, separador2 - separador1 - 1).c_str());
        std::string fecha = linea.substr(separador2 + 1);
        Registrar(alias, puntos, fecha);
    }
    return true;
}

bool RegistroPuntuaciones::Guardar(const std::string &ruta) const
{
    std::ofstream archivo(ruta); // Sobrescribe el archivo completo
    if (!archivo)
    {
        return false;
    }

    for (const Nodo *actual = primero; actual != nullptr; actual = actual->siguiente)
    {
        archivo << actual->dato.alias << ';'
                << actual->dato.puntos << ';'
                << actual->dato.fecha << '\n';
    }
    return true;
}

void RegistroPuntuaciones::Registrar(const std::string &alias, int puntos, const std::string &fecha)
{
    // Busca el alias; si ya existe, acumula los puntos y actualiza la fecha
    Nodo *actual = primero;
    Nodo *ultimo = nullptr;
    while (actual != nullptr)
    {
        if (actual->dato.alias == alias)
        {
            actual->dato.puntos += puntos;
            actual->dato.fecha = fecha;
            return;
        }
        ultimo = actual;
        actual = actual->siguiente;
    }

    // No existe: se agrega un nodo nuevo al final de la lista
    Nodo *nuevo = new Nodo{Puntuacion{alias, puntos, fecha}, nullptr};
    if (ultimo != nullptr)
    {
        ultimo->siguiente = nuevo;
    }
    else
    {
        primero = nuevo;
    }
}

void RegistroPuntuaciones::Ordenar()
{
    // Ordenamiento de burbuja sobre los datos de los nodos:
    // repite recorridos hasta que no haya intercambios
    bool huboCambios = true;
    while (huboCambios)
    {
        huboCambios = false;
        for (Nodo *actual = primero;
             actual != nullptr && actual->siguiente != nullptr;
             actual = actual->siguiente)
        {
            if (actual->dato.puntos < actual->siguiente->dato.puntos)
            {
                std::swap(actual->dato, actual->siguiente->dato);
                huboCambios = true;
            }
        }
    }
}

const Nodo *RegistroPuntuaciones::Primero() const
{
    return primero;
}

std::string RegistroPuntuaciones::FechaActual()
{
    std::time_t ahora = std::time(nullptr);
    std::tm *local = std::localtime(&ahora);
    char buffer[11]; // "AAAA-MM-DD" más el carácter nulo
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", local);
    return std::string(buffer);
}