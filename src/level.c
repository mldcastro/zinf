#include <raylib.h>
#include <stdio.h>

#include "level.h"

void LoadLevelLayoutFromFile(char levelFileName[],
                             Layout *layout,
                             Player *player,
                             EnvironmentObjects *envObjects)
{
    FILE *levelFile;
    levelFile = fopen(levelFileName, "r");

    if (levelFile == NULL) {
        printf("Could not open the file.\n");
        return; // Se o arquivo não pôde ser aberto, então a função deve parar por aqui.
    }

    envObjects->enemyCount = 0;
    envObjects->obstacleCount = 0;

    for (int row = 0; row < LAYOUT_ROWS; row++) {
        for (int col = 0; col < LAYOUT_COLUMNS; col++) {
            fscanf(levelFile, " %c", &(layout->matrix[row][col]));

            char tile = layout->matrix[row][col];

            if (tile == 'M') {
                Enemy enemy;
                enemy.dimensions.x = col * TILE_SIZE;
                enemy.dimensions.y = row * TILE_SIZE + STATUS_BAR_HEIGHT;
                enemy.dimensions.width = TILE_SIZE;
                enemy.dimensions.height = TILE_SIZE;
                enemy.moveHorizontally = (bool)((row + col) % 2);
                enemy.reverse = (bool)((row + col) % 2);

                envObjects->enemies[envObjects->enemyCount] = enemy;
                (envObjects->enemyCount)++;
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

void UpdatePlayer(Player *player,
                  float delta,
                  EnvironmentObjects *envObjects)
{
    Texture2D sprite = LoadTexture("sprites/Link_front.png");

    float positionDelta = PLAYER_WALK_SPEED * delta;
    Vector2 deltaDirection = {0, 0};

    if (IsKeyDown(KEY_LEFT)) {
        deltaDirection = (Vector2){-positionDelta, 0};
        if (!IsPlayerBlocked(player, deltaDirection, envObjects->obstacles)) {
            player->dimensions.x -= positionDelta;
            sprite = LoadTexture("sprites/Link_left.png");
        }
    }
    if (IsKeyDown(KEY_RIGHT)) {
        deltaDirection = (Vector2){positionDelta, 0};
        if (!IsPlayerBlocked(player, deltaDirection, envObjects->obstacles)) {
            player->dimensions.x += positionDelta;
            sprite = LoadTexture("sprites/Link_right.png");
        }
    }
    if (IsKeyDown(KEY_DOWN)) {
        deltaDirection = (Vector2){0, positionDelta};
        if (!IsPlayerBlocked(player, deltaDirection, envObjects->obstacles)) {
            player->dimensions.y += positionDelta;
        }
    }
    if (IsKeyDown(KEY_UP)) {
        deltaDirection = (Vector2){0, -positionDelta};
        if (!IsPlayerBlocked(player, deltaDirection, envObjects->obstacles)) {
            player->dimensions.y -= positionDelta;
            sprite = LoadTexture("sprites/Link_back.png");
        }
    }

    DrawTexture(sprite, player->dimensions.x, player->dimensions.y, WHITE);

    for (int i = 0; i < envObjects->enemyCount; i++) {
        if (WasPlayerHit(player, &(envObjects->enemies[i]))) {
            player->lives -= 1;
        }
    }
}

bool IsPlayerBlocked(Player *player,
                     Vector2 deltaDirection,
                     Obstacle obstacles[MAX_NUMBER_OF_OBSTACLES])
{
    Rectangle nextPosition = (Rectangle){player->dimensions.x + deltaDirection.x,
                                         player->dimensions.y + deltaDirection.y,
                                         player->dimensions.width,
                                         player->dimensions.height};

    bool isPlayerLeavingScreen
        = (nextPosition.x < 0 || nextPosition.x + nextPosition.width > GetScreenWidth()
           || nextPosition.y < STATUS_BAR_HEIGHT
           || nextPosition.y + nextPosition.height > GetScreenHeight());

    bool isPlayerCollidingWithObstacle;

    for (int i = 0; i < MAX_NUMBER_OF_OBSTACLES; i++) {
        isPlayerCollidingWithObstacle = CheckCollisionRecs(nextPosition, obstacles[i].dimensions);

        if (isPlayerCollidingWithObstacle || isPlayerLeavingScreen) {
            player->canWalk = false;
            return true;
        }
    }
    player->canWalk = true;
    return false;
}

bool WasPlayerHit(Player *player, Enemy *enemy)
{
    return CheckCollisionRecs(player->dimensions, enemy->dimensions);
}

void UpdateEnemy(Enemy *enemy, float delta, Obstacle obstacles[MAX_NUMBER_OF_OBSTACLES])
{
    Texture2D sprite;

    float positionDelta = ENEMY_WALK_SPEED * delta;
    Vector2 deltaDirection = {0, 0};

    if (enemy->moveHorizontally) {
        if (!enemy->reverse) {
            deltaDirection = (Vector2){-positionDelta, 0};
            if (!IsEnemyBlocked(enemy, deltaDirection, obstacles)) {
                enemy->dimensions.x -= positionDelta;
                sprite = LoadTexture("sprites/Enemy_left.png");
            }
        }

        if (enemy->reverse) {
            deltaDirection = (Vector2){positionDelta, 0};
            if (!IsEnemyBlocked(enemy, deltaDirection, obstacles)) {
                enemy->dimensions.x += positionDelta;
                sprite = LoadTexture("sprites/Enemy_right.png");
            }
        }
    } else {
        if (!enemy->reverse) {
            deltaDirection = (Vector2){0, -positionDelta};
            if (!IsEnemyBlocked(enemy, deltaDirection, obstacles)) {
                enemy->dimensions.y -= positionDelta;
                sprite = LoadTexture("sprites/Enemy_back.png");
            }
        }

        if (enemy->reverse) {
            deltaDirection = (Vector2){0, positionDelta};
            if (!IsEnemyBlocked(enemy, deltaDirection, obstacles)) {
                enemy->dimensions.y += positionDelta;
                sprite = LoadTexture("sprites/Enemy_front.png");
            }
        }
    }

    DrawTexture(sprite, enemy->dimensions.x, enemy->dimensions.y, WHITE);
}

bool IsEnemyBlocked(Enemy *enemy,
                    Vector2 deltaDirection,
                    Obstacle obstacles[MAX_NUMBER_OF_OBSTACLES])
{
    Rectangle nextPosition = (Rectangle){enemy->dimensions.x + deltaDirection.x,
                                         enemy->dimensions.y + deltaDirection.y,
                                         enemy->dimensions.width,
                                         enemy->dimensions.height};

    bool isEnemyLeavingScreen
        = (nextPosition.x < 0 || nextPosition.x + nextPosition.width > GetScreenWidth()
           || nextPosition.y < STATUS_BAR_HEIGHT
           || nextPosition.y + nextPosition.height > GetScreenHeight());

    bool isEnemyCollidingWithObstacle;

    for (int i = 0; i < MAX_NUMBER_OF_OBSTACLES; i++) {
        isEnemyCollidingWithObstacle = CheckCollisionRecs(nextPosition, obstacles[i].dimensions);

        if (isEnemyCollidingWithObstacle || isEnemyLeavingScreen) {
            enemy->reverse = !enemy->reverse;
            return true;
        }
    }
    return false;
}

void GameOver(Score *score, Menu *menu, Player *player)
{
    const char gameOverText[] = "Game Over";
    const int gameOverTextSize = 160;
    const char *scoreText = TextFormat("Your score was: %d", score->value);
    const int scoreTextSize = 50;

    WaitTime(1);

    BeginDrawing();

    ClearBackground(BLACK);

    DrawText(gameOverText,
             GetScreenWidth() / 2 - MeasureText(gameOverText, gameOverTextSize) / 2,
             100,
             gameOverTextSize,
             YELLOW);

    DrawText(scoreText,
             GetScreenWidth() / 2 - MeasureText(scoreText, scoreTextSize) / 2,
             300,
             scoreTextSize,
             YELLOW);

    EndDrawing();

    ReadScoreName(score);

    AddNewScoreToRanking(*score, RANKING_FILE_NAME);

    menu->display = true;
    menu->startGame = false;

    player->dimensions = (Rectangle){0, 100, TILE_SIZE, TILE_SIZE};
    player->canWalk = true;
    player->lives = PLAYER_MAX_LIVES;
}
