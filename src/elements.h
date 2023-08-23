#ifndef ELEMENTS_H

#include <raylib.h>

#define ELEMENTS_H
#define PLAYER_WALK_SPEED 200.0f
#define PLAYER_MAX_LIVES 3
#define ENEMY_WALK_SPEED 150.0f
#define MAX_NUMBER_OF_ENEMIES 10
#define MAX_NUMBER_OF_OBSTACLES 150

typedef struct Player {
    Rectangle dimensions;
    bool canWalk;
    int lives;
} Player;

typedef struct Enemy {
    Rectangle dimensions;
    bool reverse;
    bool moveHorizontally;
} Enemy;

typedef struct Obstacle {
    Rectangle dimensions;
} Obstacle;

typedef struct EnvironmentObjects {
    Enemy enemies[MAX_NUMBER_OF_ENEMIES];
    Obstacle obstacles[MAX_NUMBER_OF_OBSTACLES];
    int enemyCount;
    int obstacleCount;
} EnvironmentObjects;

#endif // ELEMENTS_H
