#include <raylib.h>

#include "level.h"
#include "menu.h"
#include "ranking.h"

int main() {
    const int screenWidth = 1200;
    const int screenHeight = 860;

    bool exitWindow = false;

    Menu menu = {true, false, false, false};

    char levelFile[] = "levels/level_1.txt";
    char layoutMatrix[LAYOUT_ROWS][LAYOUT_COLUMNS];
    int lives = 3;
    int level = 1;
    int score = 0;

    LoadLevelLayoutFromFile(levelFile, layoutMatrix);

    InitWindow(screenWidth, screenHeight, "Menu");

    SetTargetFPS(30);

    while (!exitWindow) {
        if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE) || menu.exitGame) {
            exitWindow = true;
        }

        DisplayMenu(&menu, screenWidth, screenHeight);

        if (menu.startGame) {
            BeginDrawing();

            ClearBackground(BLACK);

            DrawStatusBar(lives, level, score);
            DrawMapFromMatrix(layoutMatrix);

            EndDrawing();

        } else if (menu.openScoreboard) {
            ShowScores(RANKING_FILE_NAME);
        }
    }

    CloseWindow();

    return 0;
}
