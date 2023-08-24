#include <raylib.h>
#include <stdlib.h>

#include "main.h"

int main()
{
    const int screenWidth = 1200;
    const int screenHeight = 860;

    bool exitWindow = false;

    Menu menu;
    Layout layout;
    Player player;
    EnvironmentObjects envObjects;

    InitialSetup(&menu, &layout, &player, &envObjects);

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
                LoadLevelLayoutFromFile(&layout, &player, &envObjects);
                layout.shouldReadFile = false;
                layout.wasFileReadOnce = true;
            }

            DrawMapFromMatrix(&layout);

            float deltaTime = GetFrameTime();

            UpdatePlayer(&player, deltaTime, &envObjects, &layout);

            for (int i = 0; i < envObjects.enemyCount; i++) {
                UpdateEnemy(&(envObjects.enemies[i]), deltaTime, envObjects.obstacles);
            }

            DrawStatusBar(player.lives, layout.level, player.score.value);

            EndDrawing();

        } else if (menu.openScoreboard) {
            ShowScores(RANKING_FILE_NAME);

            if (IsKeyPressed(KEY_BACKSPACE)) {
                menu.display = true;
                menu.openScoreboard = false;
            }
        }

        if (player.lives == 0) {
            GameOver(&menu, &layout, &player, &envObjects);
        }

        if (envObjects.deadEnemies > 0 && AreAllEnemiesDead(&envObjects)) {
            (layout.level)++;
            if (layout.level <= NUMBER_OF_LEVELS) {
                GetLevel(&layout);
                ResetEnvironmentObjects(&envObjects);
            } else {
                GameWon(&menu, &layout, &player, &envObjects);
            }
        }
    }

    CloseWindow();

    return 0;
}

void InitialSetup(Menu *menu, Layout *layout, Player *player, EnvironmentObjects *envObjects)
{
    ResetMenu(menu);
    ResetPlayer(player);

    envObjects->enemyCount = 0;
    envObjects->obstacleCount = 0;
    envObjects->deadEnemies = 0;

    layout->level = 1;
    GetLevel(layout);
}
