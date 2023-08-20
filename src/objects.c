#include <raylib.h>

#include "objects.h"
#include "level.h"

void UpdatePlayer(Player *player, float delta) {
    Texture2D sprite = LoadTexture("sprites/Link_front.png");

    float positionDelta = PLAYER_WALK_SPEED * delta;
    Vector2 positionDeltaVector = {0, 0};

    if (IsKeyDown(KEY_LEFT)) {
        positionDeltaVector = (Vector2){-positionDelta, 0};
        if (!IsBlocked(player, positionDeltaVector)) {
            player->position.x -= positionDelta;
            sprite = LoadTexture("sprites/Link_left.png");
        }
    }
    if (IsKeyDown(KEY_RIGHT)) {
        positionDeltaVector = (Vector2){positionDelta, 0};
        if (!IsBlocked(player, positionDeltaVector)) {
            player->position.x += positionDelta;
            sprite = LoadTexture("sprites/Link_right.png");
        }
    }
    if (IsKeyDown(KEY_DOWN)) {
        positionDeltaVector = (Vector2){0, positionDelta};
        if (!IsBlocked(player, positionDeltaVector)) {
            player->position.y += positionDelta;
        }
    }
    if (IsKeyDown(KEY_UP)) {
        positionDeltaVector = (Vector2){0, -positionDelta};
        if (!IsBlocked(player, positionDeltaVector)) {
            player->position.y -= positionDelta;
            sprite = LoadTexture("sprites/Link_back.png");
        }
    }

    DrawTexture(sprite, player->position.x, player->position.y, WHITE);
}

bool IsBlocked(Player *player, Vector2 positionDelta) {
    if (player->position.x + positionDelta.x < 0
        || player->position.x + positionDelta.x + TILE_SIZE > GetScreenWidth()
        || player->position.y + positionDelta.y < STATUS_BAR_HEIGHT
        || player->position.y + positionDelta.y + TILE_SIZE > GetScreenHeight()) {
        player->canWalk = false;
        return true;
    }

    player->canWalk = true;
    return false;
}

void UpdateEnemy(Enemy *enemy, float delta) {
    Texture2D sprite;

    if (enemy->moveHorizontally) {
        if (enemy->canWalk) {
            enemy->position.x -= ENEMY_WALK_SPEED * delta;
            sprite = LoadTexture("sprites/Enemy_left.png");
        } else {
            enemy->position.x += ENEMY_WALK_SPEED * delta;
            sprite = LoadTexture("sprites/Enemy_left.png");
        }
    } else {
        if (enemy->canWalk) {
            enemy->position.y -= ENEMY_WALK_SPEED * delta;
            sprite = LoadTexture("sprites/Enemy_front.png");
        } else {
            enemy->position.y += ENEMY_WALK_SPEED * delta;
            sprite = LoadTexture("sprites/Enemy_back.png");
        }
    }

    DrawTexture(sprite, enemy->position.x, enemy->position.y, WHITE);
}

void ReadEnemies(
    char layoutMatrix[LAYOUT_ROWS][LAYOUT_COLUMNS],
    Enemy enemies[MAX_NUMBER_OF_ENEMIES]) {
    int enemyCount = 0;

    for (int row = 0; row < LAYOUT_ROWS; row++) {
        for (int col = 0; col < LAYOUT_COLUMNS; col++) {
            char tile = layoutMatrix[row][col];

            if (tile == 'M') {
                Enemy enemy
                    = {(Vector2){col * TILE_SIZE, row * TILE_SIZE + STATUS_BAR_HEIGHT}, true, true};

                enemies[enemyCount] = enemy;
                enemyCount++;
            }
        }
    }
}
