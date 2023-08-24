#include <string.h> // memset

#include "elements.h"

void ResetPlayer(Player *player)
{
    player->lives = PLAYER_MAX_LIVES;
    player->canWalk = true;
    player->score.value = 0;
    memset(player->score.name, 0, NAME_MAX_LENGTH);
}

void ResetEnvironmentObjects(EnvironmentObjects *envObjects)
{
    for (int i = 0; i < envObjects->enemyCount; i++) {
        envObjects->enemies[i].isDead = false;
    }
    envObjects->enemyCount = 0;
    envObjects->obstacleCount = 0;
    envObjects->deadEnemies = 0;
}
