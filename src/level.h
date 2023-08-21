#ifndef LEVEL_H

#include "elements.h"

#define LEVEL_H
#define LAYOUT_ROWS 16
#define LAYOUT_COLUMNS 24
#define TILE_SIZE 50
#define STATUS_BAR_HEIGHT 60
#define MAX_NUMBER_OF_ENEMIES 7
#define MAX_NUMBER_OF_OBSTACLES 150

typedef struct Layout {
    char matrix[LAYOUT_ROWS][LAYOUT_COLUMNS];
} Layout;

void LoadLevelLayoutFromFile(
    char levelFileName[],
    Layout *layout,
    Enemy enemies[MAX_NUMBER_OF_ENEMIES],
    Obstacle obstacles[MAX_NUMBER_OF_OBSTACLES]);

void DrawMapFromMatrix(Layout *layout);

void DrawStatusBar(int lives, int level, int score);

void UpdatePlayer(Player *player, float delta, Obstacle obstacles[MAX_NUMBER_OF_OBSTACLES]);

void UpdateEnemy(Enemy *enemy, float delta, Obstacle obstacles[MAX_NUMBER_OF_OBSTACLES]);

bool IsPlayerBlocked(
    Player *player,
    Vector2 deltaDirection,
    Obstacle obstacles[MAX_NUMBER_OF_OBSTACLES]);

bool IsEnemyBlocked(
    Enemy *enemy,
    Vector2 deltaDirection,
    Obstacle obstacles[MAX_NUMBER_OF_OBSTACLES]);

#endif // LEVEL_H
