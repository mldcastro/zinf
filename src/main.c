#include <raylib.h>

#include "level.h"
#include "menu.h"
#include "ranking.h"

int main() {
    const int screenWidth = 1200;
    const int screenHeight = 860;

    bool exitWindow = false;
    bool shouldReadLayoutFile = true;

    Menu menu = {true, false, false, false};
    Player player = {(Rectangle){0, 100, TILE_SIZE, TILE_SIZE}, true};
    Enemy enemies[MAX_NUMBER_OF_ENEMIES];
    Obstacle obstacles[MAX_NUMBER_OF_OBSTACLES];
    Layout layout;

    char levelFile[] = "levels/level_1.txt";
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
                LoadLevelLayoutFromFile(levelFile, &layout, enemies, obstacles);
                shouldReadLayoutFile = false;
            }

            DrawMapFromMatrix(&layout);
            DrawStatusBar(lives, level, score);

            float deltaTime = GetFrameTime();

            UpdatePlayer(&player, deltaTime, obstacles);

            for (int i = 0; i < sizeof(enemies) / sizeof(enemies[0]); i++) {
                UpdateEnemy(&enemies[i], deltaTime, obstacles);
            }

            EndDrawing();

        } else if (menu.openScoreboard) {
            ShowScores(RANKING_FILE_NAME);
        }
    }

    CloseWindow();

    return 0;
}
