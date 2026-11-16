#include "raylib.h"

int main() {
    InitWindow(800, 450, "Prueba raylib");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Funciona raylib!", 250, 200, 30, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}