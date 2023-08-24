#ifndef LEVEL_H

#include "elements.h"
#include "menu.h"
#include "ranking.h"

#define LEVEL_H
#define LAYOUT_ROWS 16
#define LAYOUT_COLUMNS 24
#define TILE_SIZE 50
#define STATUS_BAR_HEIGHT 60

typedef struct Layout {
    char matrix[LAYOUT_ROWS][LAYOUT_COLUMNS];
    bool shouldReadFile;
    bool wasFileReadOnce;
} Layout;

void LoadLevelLayoutFromFile(char levelFileName[],
                             Layout *layout,
                             Player *player,
                             EnvironmentObjects *envObjects);

void DrawMapFromMatrix(Layout *layout);

void DrawStatusBar(int lives, int level, int score);

void UpdatePlayer(Player *player, float delta, EnvironmentObjects *envObjects, Layout *layout);

void UpdateEnemy(Enemy *enemy, float delta, Obstacle obstacles[MAX_NUMBER_OF_OBSTACLES]);

bool IsPlayerBlocked(Player *player,
                     Vector2 deltaDirection,
                     Obstacle obstacles[MAX_NUMBER_OF_OBSTACLES]);

bool WasPlayerHit(Player *player, Enemy *enemy);

bool IsEnemyBlocked(Enemy *enemy,
                    Vector2 deltaDirection,
                    Obstacle obstacles[MAX_NUMBER_OF_OBSTACLES]);

bool AreAllEnemiesDead(EnvironmentObjects *envObjects);

void GameOver(Menu *menu, Player *player, EnvironmentObjects *envObjects);

#endif // LEVEL_H
