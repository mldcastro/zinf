#include <raylib.h>

#include "menu.h"

int main() {
    const int screenWidth = 1200;
    const int screenHeight = 860;

    bool exitWindow = false;

    Menu menu = {true, false, false, false};

    InitWindow(screenWidth, screenHeight, "Menu");

    SetTargetFPS(30);

    while (!exitWindow) {
        if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE) || menu.exitGame) {
            exitWindow = true;
        }

        DisplayMenu(&menu, screenWidth, screenHeight);

        if (menu.startGame) {
            BeginDrawing();

            ClearBackground(GRAY);
            DrawText("You pressed ENTER", screenWidth / 2, screenHeight / 2, 30, GREEN);

            EndDrawing();

        } else if (menu.openScoreboard) {
            BeginDrawing();

            ClearBackground(YELLOW);
            DrawText("You pressed S", screenWidth / 2, screenHeight / 2, 30, BLUE);

            EndDrawing();
        }
    }

    CloseWindow();

    return 0;
}
