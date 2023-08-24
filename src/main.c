#include <raylib.h>
#include <stdlib.h>
#include <string.h> // memset

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

            if (AreAllEnemiesDead(&envObjects)) {
                if (layout.level <= NUMBER_OF_LEVELS) {
                    (layout.level)++;
                    GetLevel(&layout);
                    ResetEnvironmentObjects(&envObjects);
                }
            }

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
    }

    CloseWindow();

    return 0;
}

void InitialSetup(Menu *menu, Layout *layout, Player *player, EnvironmentObjects *envObjects)
{
    menu->display = true;
    menu->startGame = false;
    menu->openScoreboard = false;
    menu->exitGame = false;

    player->lives = PLAYER_MAX_LIVES;
    player->score.value = 0;
    memset(player->score.name, 0, NAME_MAX_LENGTH);

    envObjects->enemyCount = 0;
    envObjects->obstacleCount = 0;
    envObjects->deadEnemies = 0;

    layout->level = 1;
    GetLevel(layout);
}
