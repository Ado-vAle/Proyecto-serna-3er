#include "raylib.h"
#include "MenuManager.h"

int main() {
    const int screenHeight = 600;
    InitWindow(MenuManager::kScreenWidth, screenHeight, "Puzzle 8-Piezas");
    SetTargetFPS(60);

    MenuManager menu;

    while (!WindowShouldClose() && !menu.IsExitRequested()) {
        menu.Update();

        BeginDrawing();
        menu.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}