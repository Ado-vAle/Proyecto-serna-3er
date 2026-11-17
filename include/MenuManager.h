#pragma once
#include <functional>
#include <string>
#include <vector>
#include "Button.h"

// Pantallas del menú
enum class Screen { Main, Manual, IntelligentStart, IntelligentGoal, Summary };

// Modo de juego elegido
enum class GameMode { None, Manual, Intelligent };

// Opciones del modo manual
enum class ManualOption { None, NewRandom, ContinueSaved };

// Punto de inicio en modo inteligente
enum class StartOption { None, UserChoice, Random };

// Meta en modo inteligente
enum class GoalOption { None, UserChoice, Standard };

// Administra las pantallas del menú y los botones de cada una
class MenuManager {
public:
    static constexpr int kScreenWidth = 800;  // Ancho de la ventana (usado para centrar)

    MenuManager();

    // Revisa si se presionó algún botón y ejecuta su acción
    void Update();

    // Dibuja la pantalla actual con sus botones
    void Draw() const;

    // Indica si el usuario eligió salir del programa
    bool IsExitRequested() const;

private:
    // Asociación entre un botón y la acción que ejecuta al presionarlo
    struct MenuItem {
        Button button;
        std::function<void()> onClick;
    };

    // Cambia a otra pantalla y reconstruye sus botones
    void GoTo(Screen next);

    // Regresa al menú principal y borra las selecciones previas
    void BackToMain();

    // Crea los botones que corresponden a la pantalla actual
    void BuildButtons();

    // Agrega un botón debajo de los existentes con su acción
    void AddButton(const std::string& label, std::function<void()> onClick);

    // Regresa las líneas de texto que resumen las selecciones
    std::vector<std::string> SummaryLines() const;

    // Dibuja el título de la pantalla actual
    void DrawTitle() const;

    // Dibuja texto centrado horizontalmente en la altura indicada
    static void DrawCenteredText(const std::string& text, int y, int fontSize, Color color);

    Screen currentScreen;
    GameMode mode;
    ManualOption manualOption;
    StartOption startOption;
    GoalOption goalOption;
    bool exitRequested;
    std::vector<MenuItem> items;
};