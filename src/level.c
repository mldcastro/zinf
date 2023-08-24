#include <raylib.h>

#include "level.h"

void UpdatePlayer(Player *player, float delta, EnvironmentObjects *envObjects, Layout *layout)
{
    Texture2D sprite = LoadTexture("sprites/Link_front.png");
    Texture2D attackSprite = LoadTexture("sprites/Attack_down.png");

    float positionDelta = PLAYER_WALK_SPEED * delta;
    Vector2 deltaDirection = {0, 0};

    if (IsKeyDown(KEY_A)) {
        deltaDirection = (Vector2){-positionDelta, 0};
        if (!IsPlayerBlocked(player, deltaDirection, envObjects->obstacles)) {
            player->dimensions.x -= positionDelta;
            sprite = LoadTexture("sprites/Link_left.png");
        }

        if (IsKeyDown(KEY_J)) {
            player->attack.x = player->dimensions.x - TILE_SIZE;
            player->attack.y = player->dimensions.y;
            player->attacked = true;

            attackSprite = LoadTexture("sprites/Attack_left.png");
        }
    } else if (IsKeyDown(KEY_D)) {
        deltaDirection = (Vector2){positionDelta, 0};
        if (!IsPlayerBlocked(player, deltaDirection, envObjects->obstacles)) {
            player->dimensions.x += positionDelta;
            sprite = LoadTexture("sprites/Link_right.png");
        }

        if (IsKeyDown(KEY_J)) {
            player->attack.x = player->dimensions.x + TILE_SIZE;
            player->attack.y = player->dimensions.y;
            player->attacked = true;

            attackSprite = LoadTexture("sprites/Attack_right.png");
        }
    } else if (IsKeyDown(KEY_S)) {
        deltaDirection = (Vector2){0, positionDelta};
        if (!IsPlayerBlocked(player, deltaDirection, envObjects->obstacles)) {
            player->dimensions.y += positionDelta;
        }

        if (IsKeyDown(KEY_J)) {
            player->attack.x = player->dimensions.x;
            player->attack.y = player->dimensions.y + TILE_SIZE;
            player->attacked = true;
        }
    } else if (IsKeyDown(KEY_W)) {
        deltaDirection = (Vector2){0, -positionDelta};
        if (!IsPlayerBlocked(player, deltaDirection, envObjects->obstacles)) {
            player->dimensions.y -= positionDelta;
            sprite = LoadTexture("sprites/Link_back.png");
        }

        if (IsKeyDown(KEY_J)) {
            player->attack.x = player->dimensions.x;
            player->attack.y = player->dimensions.y - TILE_SIZE;
            player->attacked = true;

            attackSprite = LoadTexture("sprites/Attack_up.png");
        }
    }

    DrawTexture(sprite, player->dimensions.x, player->dimensions.y, WHITE);
    if (player->attacked) {
        DrawTexture(attackSprite, player->attack.x, player->attack.y, WHITE);

        player->attacked = false;
    }

    for (int i = 0; i < envObjects->enemyCount; i++) {
        if (!envObjects->enemies[i].isDead
            && CheckCollisionRecs(player->attack, envObjects->enemies[i].dimensions)) {
            envObjects->enemies[i].isDead = true;
            (envObjects->deadEnemies)++;

            player->score.value += SCORE_INCREMENT;
        }

        if (WasPlayerHit(player, &(envObjects->enemies[i]))) {
            player->lives -= 1;
            layout->shouldReadFile = true;
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
    if (enemy->isDead) {
        return false;
    }
    return CheckCollisionRecs(player->dimensions, enemy->dimensions);
}

void UpdateEnemy(Enemy *enemy, float delta, Obstacle obstacles[MAX_NUMBER_OF_OBSTACLES])
{
    if (enemy->isDead) {
        return;
    }

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

bool AreAllEnemiesDead(EnvironmentObjects *envObjects)
{
    return (envObjects->deadEnemies == envObjects->enemyCount);
}

void GameOver(Menu *menu, Layout *layout, Player *player, EnvironmentObjects *envObjects)
{
    const char gameOverText[] = "Game Over";
    const int gameOverTextSize = 160;
    const char *scoreText = TextFormat("Your score was: %d", player->score.value);
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

    ReadScoreName(&(player->score));

    AddNewScoreToRanking(player->score, RANKING_FILE_NAME);

    ResetPlayer(player);
    ResetEnvironmentObjects(envObjects);
    ResetMenu(menu);
    ResetLayout(layout);
}

void GameWon(Menu *menu, Layout *layout, Player *player, EnvironmentObjects *envObjects)
{
    const char gameWonText[] = "You Win!!!";
    const int gameWonTextSize = 160;
    const char *scoreText = TextFormat("Your score was: %d", player->score.value);
    const int scoreTextSize = 50;

    WaitTime(1);

    BeginDrawing();

    ClearBackground(BLACK);

    DrawText(gameWonText,
             GetScreenWidth() / 2 - MeasureText(gameWonText, gameWonTextSize) / 2,
             100,
             gameWonTextSize,
             YELLOW);

    DrawText(scoreText,
             GetScreenWidth() / 2 - MeasureText(scoreText, scoreTextSize) / 2,
             300,
             scoreTextSize,
             YELLOW);

    EndDrawing();

    ReadScoreName(&(player->score));

    AddNewScoreToRanking(player->score, RANKING_FILE_NAME);

    ResetPlayer(player);
    ResetEnvironmentObjects(envObjects);
    ResetMenu(menu);
    ResetLayout(layout);
}
