#include "MenuManager.h"

namespace {
// Medidas de los botones (valores fijos de diseño)
constexpr int kButtonWidth = 360;
constexpr int kButtonHeight = 50;
constexpr int kFirstButtonY = 200;
constexpr int kButtonSpacing = 70;
}

MenuManager::MenuManager()
    : currentScreen(Screen::Main),
      mode(GameMode::None),
      manualOption(ManualOption::None),
      startOption(StartOption::None),
      goalOption(GoalOption::None),
      exitRequested(false) {
    BuildButtons();
}

void MenuManager::Update() {
    // Busca el botón presionado; se copia la acción antes de ejecutarla
    // porque ejecutarla reconstruye la lista de botones
    for (const MenuItem& item : items) {
        if (item.button.IsClicked()) {
            std::function<void()> action = item.onClick;
            action();
            return;
        }
    }
}

void MenuManager::Draw() const {
    ClearBackground(RAYWHITE);
    DrawTitle();

    // Resumen de selecciones, solo en la pantalla final
    if (currentScreen == Screen::Summary) {
        std::vector<std::string> lines = SummaryLines();
        int y = 110;
        for (const std::string& line : lines) {
            DrawCenteredText(line, y, 20, DARKGRAY);
            y += 30;
        }
        DrawCenteredText("(La pantalla de juego se agregará después)", 400, 18, GRAY);
    }

    for (const MenuItem& item : items) {
        item.button.Draw();
    }
}

bool MenuManager::IsExitRequested() const {
    return exitRequested;
}

void MenuManager::GoTo(Screen next) {
    currentScreen = next;
    BuildButtons();
}

void MenuManager::BackToMain() {
    mode = GameMode::None;
    manualOption = ManualOption::None;
    startOption = StartOption::None;
    goalOption = GoalOption::None;
    GoTo(Screen::Main);
}

void MenuManager::BuildButtons() {
    items.clear();

    switch (currentScreen) {
        case Screen::Main:
            AddButton("Modo manual", [this]() {
                mode = GameMode::Manual;
                GoTo(Screen::Manual);
            });
            AddButton("Modo inteligente", [this]() {
                mode = GameMode::Intelligent;
                GoTo(Screen::IntelligentStart);
            });
            AddButton("Salir", [this]() {
                exitRequested = true;
            });
            break;

        case Screen::Manual:
            AddButton("Nueva partida aleatoria", [this]() {
                manualOption = ManualOption::NewRandom;
                GoTo(Screen::Summary);
            });
            AddButton("Continuar partida guardada", [this]() {
                manualOption = ManualOption::ContinueSaved;
                GoTo(Screen::Summary);
            });
            AddButton("Volver", [this]() {
                BackToMain();
            });
            break;

        case Screen::IntelligentStart:
            AddButton("Yo elijo el punto de inicio", [this]() {
                startOption = StartOption::UserChoice;
                GoTo(Screen::IntelligentGoal);
            });
            AddButton("Punto de inicio aleatorio", [this]() {
                startOption = StartOption::Random;
                GoTo(Screen::IntelligentGoal);
            });
            AddButton("Volver", [this]() {
                BackToMain();
            });
            break;

        case Screen::IntelligentGoal:
            AddButton("Yo elijo la meta", [this]() {
                goalOption = GoalOption::UserChoice;
                GoTo(Screen::Summary);
            });
            AddButton("Meta estándar (1 2 3 / 4 5 6 / 7 8 _)", [this]() {
                goalOption = GoalOption::Standard;
                GoTo(Screen::Summary);
            });
            AddButton("Volver", [this]() {
                goalOption = GoalOption::None;
                GoTo(Screen::IntelligentStart);
            });
            break;

        case Screen::Summary:
            AddButton("Volver al menú principal", [this]() {
                BackToMain();
            });
            break;
    }
}

void MenuManager::AddButton(const std::string& label, std::function<void()> onClick) {
    // Cada botón nuevo se coloca debajo del anterior, centrado en la ventana
    int index = static_cast<int>(items.size());
    Rectangle bounds{
        static_cast<float>((kScreenWidth - kButtonWidth) / 2),
        static_cast<float>(kFirstButtonY + index * kButtonSpacing),
        static_cast<float>(kButtonWidth),
        static_cast<float>(kButtonHeight)
    };
    items.push_back(MenuItem{Button(bounds, label), std::move(onClick)});
}

std::vector<std::string> MenuManager::SummaryLines() const {
    std::vector<std::string> lines;

    if (mode == GameMode::Manual) {
        lines.push_back("Modo: Manual");
        lines.push_back(manualOption == ManualOption::NewRandom
                            ? "Partida nueva aleatoria"
                            : "Continuar partida guardada");
    } else if (mode == GameMode::Intelligent) {
        lines.push_back("Modo: Inteligente");
        lines.push_back(std::string("Inicio: ") +
                        (startOption == StartOption::UserChoice ? "elegido por ti" : "aleatorio"));
        lines.push_back(std::string("Meta: ") +
                        (goalOption == GoalOption::UserChoice ? "elegida por ti" : "estándar"));
    }

    return lines;
}

void MenuManager::DrawTitle() const {
    std::string title;
    switch (currentScreen) {
        case Screen::Main:            title = "PUZZLE 8-PIEZAS"; break;
        case Screen::Manual:          title = "Modo manual"; break;
        case Screen::IntelligentStart: title = "Modo inteligente: punto de inicio"; break;
        case Screen::IntelligentGoal:  title = "Modo inteligente: meta"; break;
        case Screen::Summary:         title = "Configuración seleccionada"; break;
    }
    DrawCenteredText(title, 60, 30, BLACK);
}

void MenuManager::DrawCenteredText(const std::string& text, int y, int fontSize, Color color) {
    int textWidth = MeasureText(text.c_str(), fontSize);
    DrawText(text.c_str(), (kScreenWidth - textWidth) / 2, y, fontSize, color);
}