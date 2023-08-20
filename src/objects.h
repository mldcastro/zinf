#ifndef OBJECTS_H

#include <raylib.h>

#include "level.h"

#define OBJECTS_H
#define PLAYER_WALK_SPEED 200.0f
#define ENEMY_WALK_SPEED 150.0f

typedef struct Player {
    Vector2 position;
    bool canWalk;
} Player;

typedef struct Enemy {
    Vector2 position;
    bool canWalk;
    bool moveHorizontally;
} Enemy;

typedef struct Obstacle {
    Vector2 position;
} Obstacle;

void UpdatePlayer(Player *player, float delta);

void UpdateEnemy(Enemy *enemy, float delta);

void ReadEnemies(char layoutMatrix[LAYOUT_ROWS][LAYOUT_COLUMNS], Enemy *enemy);

bool IsBlocked(Player *player, Vector2 positionDelta);

#endif // OBJECTS_H
