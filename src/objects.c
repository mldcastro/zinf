#include <raylib.h>

#include "objects.h"

void UpdatePlayer(Player *player, float delta) {
    Texture2D sprite;
    sprite = LoadTexture("sprites/Link_front.png");

    if (IsKeyDown(KEY_LEFT) && player->canWalk) {
        player->position.x -= PLAYER_WALK_SPEED * delta;
        sprite = LoadTexture("sprites/Link_left.png");
    }
    if (IsKeyDown(KEY_RIGHT) && player->canWalk) {
        player->position.x += PLAYER_WALK_SPEED * delta;
        sprite = LoadTexture("sprites/Link_right.png");
    }
    if (IsKeyDown(KEY_DOWN) && player->canWalk) {
        player->position.y += PLAYER_WALK_SPEED * delta;
    }
    if (IsKeyDown(KEY_UP) && player->canWalk) {
        player->position.y -= PLAYER_WALK_SPEED * delta;
        sprite = LoadTexture("sprites/Link_back.png");
    }

    DrawTexture(sprite, player->position.x, player->position.y, WHITE);
}
