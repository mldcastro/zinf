#ifndef OBJECTS_H

#include <raylib.h>

#define OBJECTS_H
#define PLAYER_WALK_SPEED 200.0f

typedef struct {
    Vector2 position;
    float speed;
    bool canWalk;
} Player;

void UpdatePlayer(Player *player, float delta);

#endif // OBJECTS_H
