#include "raylib.h"
#include "MenuManager.h"
#include "Tablero.h"
#include "VistaTablero.h"
#include "CapturaNom.h"
#include "Puntuaciones.h"
#include "VerPuntos.h"

namespace
{
    // Archivo de puntuaciones; se crea en la carpeta desde donde se ejecuta el programa
    const char *const kArchivoPuntuaciones = "puntuaciones.txt";

    // Pantalla que se está mostrando
    enum class Estado
    {
        Menu,
        PedirAlias,
        Partida,
        Puntuaciones
    };
}

int main()
{
    const int screenHeight = 600;
    InitWindow(MenuManager::kScreenWidth, screenHeight, "Puzzle 8-Piezas");

    // ESC regresa al menú en lugar de cerrar la ventana
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);

    MenuManager menu;
    Tablero tablero;
    VistaTablero vistaManual(tablero);
    CapturaAlias captura;
    RegistroPuntuaciones registro;
    VistaPuntuaciones vistaPuntuaciones;
    Estado estado = Estado::Menu;

    registro.Cargar(kArchivoPuntuaciones);

    while (!WindowShouldClose() && !menu.IsExitRequested())
    {
        if (estado == Estado::Menu)
        {
            menu.Update();
            Accion accion = menu.TomarAccion();
            if (accion == Accion::NuevaPartida)
            {
                captura.Reiniciar();
                estado = Estado::PedirAlias;
            }
            else if (accion == Accion::VerPuntuaciones)
            {
                registro.Ordenar();
                estado = Estado::Puntuaciones;
            }
        }
        else if (estado == Estado::PedirAlias)
        {
            captura.Update();
            if (IsKeyPressed(KEY_ESCAPE))
            {
                menu.BackToMain();
                estado = Estado::Menu;
            }
            else if (captura.Confirmado())
            {
                vistaManual.IniciarPartida();
                estado = Estado::Partida;
            }
        }
        else if (estado == Estado::Partida)
        {
            vistaManual.Update();
            if (vistaManual.FinConfirmado())
            {
                // Guarda el puntaje del alias y regresa al menú
                registro.Registrar(captura.Alias(), vistaManual.PuntosObtenidos(),
                                   RegistroPuntuaciones::FechaActual());
                registro.Guardar(kArchivoPuntuaciones);
                menu.BackToMain();
                estado = Estado::Menu;
            }
            else if (vistaManual.VolverAlMenuSolicitado())
            {
                menu.BackToMain();
                estado = Estado::Menu;
            }
        }
        else
        {
            // Pantalla de puntuaciones
            if (IsKeyPressed(KEY_ESCAPE))
            {
                menu.BackToMain();
                estado = Estado::Menu;
            }
        }

        BeginDrawing();
        if (estado == Estado::Menu)
        {
            menu.Draw();
        }
        else if (estado == Estado::PedirAlias)
        {
            captura.Draw();
        }
        else if (estado == Estado::Partida)
        {
            vistaManual.Draw();
        }
        else
        {
            vistaPuntuaciones.Draw(registro);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}