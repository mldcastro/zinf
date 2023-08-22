#include <raylib.h>

#include "menu.h"

void DisplayMenu(Menu *menu, int screenWidth, int screenHeight)
{
    if (menu->display) {
        int initialHeight = 400;
        const int width = 100;

        Texture2D linkSprite = LoadTexture("sprites/Link_left.png");
        Vector2 spritePosition = {screenWidth - 400, screenHeight - 600};
        float spriteRotation = 0.0f;
        int spriteScale = 7;

        BeginDrawing();

        ClearBackground(BLACK);
        DrawTextureEx(linkSprite, spritePosition, spriteRotation, spriteScale, YELLOW);

        int textWidth = MeasureText("ZINF", 160);
        int xPos = screenWidth / 2 - textWidth / 2;
        DrawText("ZINF", xPos, initialHeight - 250, 160, YELLOW);

        DrawText("Press ENTER to start", width, initialHeight, 30, YELLOW);
        DrawText("Press S to enter the Scoreboard", width, initialHeight + 75, 30, YELLOW);
        DrawText("Press X to exit", width, initialHeight + 2 * 75, 30, YELLOW);

        EndDrawing();

        if (IsKeyPressed(KEY_ENTER)) {
            // Se o usuário pressiona o ENTER, então a opção de Novo Jogo foi escolhida
            menu->display = false;
            menu->startGame = true;
        }

        if (IsKeyPressed(KEY_S)) {
            // Se o usuário pressiona o S, a opção de Abrir a Tabela de Pontuações foi escolhida
            menu->display = false;
            menu->openScoreboard = true;
        }

        if (IsKeyPressed(KEY_X)) {
            // Se o usuário pressiona o X, então a opção de Sair do Jogo foi escolhida
            menu->display = false;
            menu->exitGame = true;
        }
    }
}
