#include <raylib.h>
#include <stdio.h>

#include "level.h"
#include "objects.h"

void UpdatePlayer(Player *player, float delta) {
    Texture2D sprite = LoadTexture("sprites/Link_front.png");

    float positionDelta = PLAYER_WALK_SPEED * delta;
    Vector2 deltaDirection = {0, 0};

    if (IsKeyDown(KEY_LEFT)) {
        deltaDirection = (Vector2){-positionDelta, 0};
        if (!IsPlayerBlocked(player, deltaDirection)) {
            player->position.x -= positionDelta;
            sprite = LoadTexture("sprites/Link_left.png");
        }
    }
    if (IsKeyDown(KEY_RIGHT)) {
        deltaDirection = (Vector2){positionDelta, 0};
        if (!IsPlayerBlocked(player, deltaDirection)) {
            player->position.x += positionDelta;
            sprite = LoadTexture("sprites/Link_right.png");
        }
    }
    if (IsKeyDown(KEY_DOWN)) {
        deltaDirection = (Vector2){0, positionDelta};
        if (!IsPlayerBlocked(player, deltaDirection)) {
            player->position.y += positionDelta;
        }
    }
    if (IsKeyDown(KEY_UP)) {
        deltaDirection = (Vector2){0, -positionDelta};
        if (!IsPlayerBlocked(player, deltaDirection)) {
            player->position.y -= positionDelta;
            sprite = LoadTexture("sprites/Link_back.png");
        }
    }

    DrawTexture(sprite, player->position.x, player->position.y, WHITE);
}

bool IsPlayerBlocked(Player *player, Vector2 deltaDirection) {
    if (player->position.x + deltaDirection.x < 0
        || player->position.x + deltaDirection.x + TILE_SIZE > GetScreenWidth()
        || player->position.y + deltaDirection.y < STATUS_BAR_HEIGHT
        || player->position.y + deltaDirection.y + TILE_SIZE > GetScreenHeight()) {
        player->canWalk = false;
        return true;
    }

    player->canWalk = true;
    return false;
}

void UpdateEnemy(Enemy *enemy, float delta) {
    Texture2D sprite;

    float positionDelta = ENEMY_WALK_SPEED * delta;
    Vector2 deltaDirection = {0, 0};

    if (enemy->moveHorizontally) {
        if (!enemy->reverse) {
            deltaDirection = (Vector2){-positionDelta, 0};
            if (!IsEnemyBlocked(enemy, deltaDirection)) {
                enemy->position.x -= positionDelta;
                sprite = LoadTexture("sprites/Enemy_left.png");
            }
        }

        if (enemy->reverse) {
            deltaDirection = (Vector2){positionDelta, 0};
            if (!IsEnemyBlocked(enemy, deltaDirection)) {
                enemy->position.x += positionDelta;
                sprite = LoadTexture("sprites/Enemy_right.png");
            }
        }
    } else {
        if (!enemy->reverse) {
            deltaDirection = (Vector2){0, -positionDelta};
            if (!IsEnemyBlocked(enemy, deltaDirection)) {
                enemy->position.y -= positionDelta;
                sprite = LoadTexture("sprites/Enemy_back.png");
            }
        }

        if (enemy->reverse) {
            deltaDirection = (Vector2){0, positionDelta};
            if (!IsEnemyBlocked(enemy, deltaDirection)) {
                enemy->position.y += positionDelta;
                sprite = LoadTexture("sprites/Enemy_front.png");
            }
        }
    }

    DrawTexture(sprite, enemy->position.x, enemy->position.y, WHITE);
}

bool IsEnemyBlocked(Enemy *enemy, Vector2 deltaDirection) {
    if (enemy->position.x + deltaDirection.x < 0
        || enemy->position.x + deltaDirection.x + TILE_SIZE > GetScreenWidth()
        || enemy->position.y + deltaDirection.y < STATUS_BAR_HEIGHT
        || enemy->position.y + deltaDirection.y + TILE_SIZE > GetScreenHeight()) {
        enemy->reverse = !enemy->reverse;
        return true;
    }
    return false;
}

void ReadEnemies(
    char layoutMatrix[LAYOUT_ROWS][LAYOUT_COLUMNS],
    Enemy enemies[MAX_NUMBER_OF_ENEMIES]) {
    int enemyCount = 0;

    for (int row = 0; row < LAYOUT_ROWS; row++) {
        for (int col = 0; col < LAYOUT_COLUMNS; col++) {
            char tile = layoutMatrix[row][col];

            if (tile == 'M') {
                Enemy enemy;
                enemy.position = (Vector2){col * TILE_SIZE, row * TILE_SIZE + STATUS_BAR_HEIGHT};
                enemy.moveHorizontally = (bool)((row + col) % 2);
                enemy.reverse = (bool)((row + col) % 2);

                enemies[enemyCount] = enemy;
                enemyCount++;
            }
        }
    }
}
