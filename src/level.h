#ifndef LEVEL_H

#include "elements.h"
#include "layout.h"
#include "menu.h"
#include "ranking.h"

#define LEVEL_H

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

void GameOver(Menu *menu, Layout *layout, Player *player, EnvironmentObjects *envObjects);

#endif // LEVEL_H
