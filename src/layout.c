#include <raylib.h>
#include <stdio.h>

#include "layout.h"

void LoadLevelLayoutFromFile(Layout *layout, Player *player, EnvironmentObjects *envObjects)
{
    FILE *levelFile;
    levelFile = fopen(layout->file, "r");

    if (levelFile == NULL) {
        printf("Could not open the file.\n");
        return; // Se o arquivo não pôde ser aberto, então a função deve parar por aqui.
    }

    int enemyID = 0;

    for (int row = 0; row < LAYOUT_ROWS; row++) {
        for (int col = 0; col < LAYOUT_COLUMNS; col++) {
            fscanf(levelFile, " %c", &(layout->matrix[row][col]));

            char tile = layout->matrix[row][col];

            if (tile == 'M') {
                if (envObjects->deadEnemies > 0) {
                    if (envObjects->enemies[enemyID].isDead) {
                        enemyID++;
                        continue;
                    }
                }

                Enemy enemy;
                enemy.isDead = false;
                enemy.dimensions.x = col * TILE_SIZE;
                enemy.dimensions.y = row * TILE_SIZE + STATUS_BAR_HEIGHT;
                enemy.dimensions.width = TILE_SIZE;
                enemy.dimensions.height = TILE_SIZE;
                enemy.moveHorizontally = (bool)((row + col) % 2);
                enemy.reverse = (bool)((row + col) % 2);

                envObjects->enemies[enemyID] = enemy;

                enemyID++;

                if (!layout->wasFileReadOnce) {
                    (envObjects->enemyCount)++;
                }
            }

            if (tile == 'P') {
                Obstacle obstacle;
                obstacle.dimensions.x = col * TILE_SIZE;
                obstacle.dimensions.y = row * TILE_SIZE + STATUS_BAR_HEIGHT;
                obstacle.dimensions.width = TILE_SIZE;
                obstacle.dimensions.height = TILE_SIZE;

                envObjects->obstacles[envObjects->obstacleCount] = obstacle;
                (envObjects->obstacleCount)++;
            }

            if (tile == 'J') {
                player->dimensions.x = col * TILE_SIZE;
                player->dimensions.y = row * TILE_SIZE + STATUS_BAR_HEIGHT;
                player->dimensions.width = TILE_SIZE;
                player->dimensions.height = TILE_SIZE;
                player->attack.width = TILE_SIZE;
                player->attack.height = TILE_SIZE;
                player->attacked = false;
                player->canWalk = true;
            }
        }
    }

    fclose(levelFile);
}

void DrawMapFromMatrix(Layout *layout)
{
    const Texture2D obstacleSprite = LoadTexture("sprites/Obstacle.png");
    const Texture2D groundSprite = LoadTexture("sprites/Ground.png");

    for (int row = 0; row < LAYOUT_ROWS; row++) {
        for (int col = 0; col < LAYOUT_COLUMNS; col++) {
            char tile = layout->matrix[row][col];

            DrawTexture(groundSprite, col * TILE_SIZE, row * TILE_SIZE + STATUS_BAR_HEIGHT, WHITE);

            if (tile == 'P') {
                DrawTexture(
                    obstacleSprite, col * TILE_SIZE, row * TILE_SIZE + STATUS_BAR_HEIGHT, WHITE);
            }
        }
    }
}

void DrawStatusBar(int lives, int level, int score)
{
    int initialXPosition = 30;
    const int yPosition = 20;

    DrawText(TextFormat("Lives: %02i", lives), initialXPosition, yPosition, 25, BLUE);
    DrawText(TextFormat("Level: %02i", level), initialXPosition + 300, yPosition, 25, BLUE);
    DrawText(TextFormat("Score: %02i", score), initialXPosition + 600, yPosition, 25, BLUE);
}

void GetLevel(Layout *layout)
{
    char levels[NUMBER_OF_LEVELS][PATH_TO_LEVEL_LENGTH] = {
        "levels/level_1.txt",
        "levels/level_2.txt",
    };

    layout->shouldReadFile = true;
    layout->wasFileReadOnce = false;

    for (int i = 0; i < PATH_TO_LEVEL_LENGTH; i++) {
        layout->file[i] = levels[layout->level - 1][i];
    }
}
