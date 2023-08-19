#include <raylib.h>

#include "level.h"
#include "menu.h"
#include "ranking.h"
#include "objects.h"

int main() {
    const int screenWidth = 1200;
    const int screenHeight = 860;

    bool exitWindow = false;
    bool shouldLoadLevel = true;

    Menu menu = {true, false, false, false};
    Player player = {
        (Vector2){100, 300},
        0,
        true
    };

    char levelFile[] = "levels/level_1.txt";
    char layoutMatrix[LAYOUT_ROWS][LAYOUT_COLUMNS];
    int lives = 3;
    int level = 1;
    int score = 0;

    InitWindow(screenWidth, screenHeight, "Menu");

    SetTargetFPS(30);

    while (!exitWindow) {
        if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE) || menu.exitGame) {
            exitWindow = true;
        }

        DisplayMenu(&menu, screenWidth, screenHeight);

        if (menu.startGame) {
            if (shouldLoadLevel) {
                LoadLevelLayoutFromFile(levelFile, layoutMatrix);
                DrawMapFromMatrix(layoutMatrix);
            }
            float deltaTime = GetFrameTime();
            
            BeginDrawing();

            ClearBackground(BLACK);

            DrawStatusBar(lives, level, score);
            UpdatePlayer(&player, deltaTime);

            EndDrawing();

        } else if (menu.openScoreboard) {
            ShowScores(RANKING_FILE_NAME);
        }
    }

    CloseWindow();

    return 0;
}
