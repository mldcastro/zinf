#ifndef OBJECTS_H

#include <raylib.h>

#define OBJECTS_H
#define PLAYER_WALK_SPEED 200.0f
#define ENEMY_WALK_SPEED 150.0f


typedef struct {
    Vector2 position;
    bool canWalk;
} Player;

typedef struct {
    Vector2 position;
    bool canWalk;
    bool moveHorizontally;
} Enemy;

void UpdatePlayer(Player *player, float delta);

void UpdateEnemy(Enemy *enemy, float delta);

#endif // OBJECTS_H
