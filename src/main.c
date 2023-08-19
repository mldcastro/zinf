#include <raylib.h>

#include "level.h"
#include "menu.h"
#include "ranking.h"
#include "objects.h"

int main() {
    const int screenWidth = 1200;
    const int screenHeight = 860;

    bool exitWindow = false;
    bool shouldReadLayoutFile = true;

    Menu menu = {true, false, false, false};
    Player player = {
        (Vector2){0, 100},
        true
    };
    Enemy enemies[MAX_NUMBER_OF_ENEMIES];

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
            BeginDrawing();

            ClearBackground(BLACK);

            if (shouldReadLayoutFile) {
                LoadLevelLayoutFromFile(levelFile, layoutMatrix);
                ReadEnemies(layoutMatrix, enemies);

                shouldReadLayoutFile = false;
            }

            DrawMapFromMatrix(layoutMatrix);
            DrawStatusBar(lives, level, score);

            float deltaTime = GetFrameTime();

            UpdatePlayer(&player, deltaTime);

            for (int i = 0; i < sizeof(enemies) / sizeof(enemies[0]); i++) {
                UpdateEnemy(&enemies[i], deltaTime);
            }

            EndDrawing();

        } else if (menu.openScoreboard) {
            ShowScores(RANKING_FILE_NAME);
        }
    }

    CloseWindow();

    return 0;
}
