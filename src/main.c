#include <raylib.h>

#include "level.h"
#include "menu.h"
#include "ranking.h"

int main()
{
    const int screenWidth = 1200;
    const int screenHeight = 860;

    bool exitWindow = false;
    bool shouldReadLayoutFile = true;

    Menu menu;
    menu.display = true;
    menu.startGame = false;
    menu.openScoreboard = false;
    menu.exitGame = false;

    Player player;
    player.dimensions = (Rectangle){0, 100, TILE_SIZE, TILE_SIZE};
    player.canWalk = true;
    player.lives = PLAYER_MAX_LIVES;

    Enemy enemies[MAX_NUMBER_OF_ENEMIES];
    Obstacle obstacles[MAX_NUMBER_OF_OBSTACLES];
    Layout layout;

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

            if (shouldReadLayoutFile) {
                LoadLevelLayoutFromFile(levelFile, &layout, enemies, obstacles);
                shouldReadLayoutFile = false;
            }

            DrawMapFromMatrix(&layout);

            float deltaTime = GetFrameTime();

            UpdatePlayer(&player, deltaTime, enemies, obstacles);

            for (int i = 0; i < sizeof(enemies) / sizeof(enemies[0]); i++) {
                UpdateEnemy(&enemies[i], deltaTime, obstacles);
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
        }
    }

    CloseWindow();

    return 0;
}
