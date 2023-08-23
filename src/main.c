#include <raylib.h>

#include "level.h"
#include "menu.h"
#include "ranking.h"

int main()
{
    const int screenWidth = 1200;
    const int screenHeight = 860;

    bool exitWindow = false;

    Menu menu;
    menu.display = true;
    menu.startGame = false;
    menu.openScoreboard = false;
    menu.exitGame = false;

    Player player;
    player.lives = PLAYER_MAX_LIVES;

    EnvironmentObjects envObjects;
    Layout layout;
    layout.shouldReadFile = true;

    char levelFile[] = "levels/level_1.txt";
    int level = 1;
    Score score;
    score.value = 0;

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

            if (layout.shouldReadFile) {
                LoadLevelLayoutFromFile(levelFile, &layout, &player, &envObjects);
                layout.shouldReadFile = false;
            }

            DrawMapFromMatrix(&layout);

            float deltaTime = GetFrameTime();

            UpdatePlayer(&player, deltaTime, &envObjects, &layout);

            for (int i = 0; i < envObjects.enemyCount; i++) {
                UpdateEnemy(&(envObjects.enemies[i]), deltaTime, envObjects.obstacles);
            }

            DrawStatusBar(player.lives, level, score.value);

            EndDrawing();

        } else if (menu.openScoreboard) {
            ShowScores(RANKING_FILE_NAME);

            if (IsKeyPressed(KEY_BACKSPACE)) {
                menu.display = true;
                menu.openScoreboard = false;
            }
        }

        if (player.lives == 0) {
            GameOver(&score, &menu, &player);
            layout.shouldReadFile = true;
        }
    }

    CloseWindow();

    return 0;
}
