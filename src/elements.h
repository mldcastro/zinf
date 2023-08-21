#ifndef ELEMENTS_H

#include <raylib.h>

#define ELEMENTS_H
#define PLAYER_WALK_SPEED 200.0f
#define ENEMY_WALK_SPEED 150.0f

typedef struct Player {
    Rectangle dimensions;
    bool canWalk;
} Player;

typedef struct Enemy {
    Rectangle dimensions;
    bool reverse;
    bool moveHorizontally;
} Enemy;

typedef struct Obstacle {
    Rectangle dimensions;
} Obstacle;

#endif // ELEMENTS_H
