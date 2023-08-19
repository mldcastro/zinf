#ifndef LEVEL_H

#include "objects.h"

#define LEVEL_H
#define LAYOUT_ROWS 16
#define LAYOUT_COLUMNS 24
#define TILE_SIZE 50
#define STATUS_BAR_HEIGHT 60
#define MAX_NUMBER_OF_ENEMIES 7

void LoadLevelLayoutFromFile(char levelFileName[], char layoutMatrix[LAYOUT_ROWS][LAYOUT_COLUMNS]);

void DrawMapFromMatrix(char layoutMatrix[LAYOUT_ROWS][LAYOUT_COLUMNS]);

void DrawStatusBar(int lives, int level, int score);

void ReadEnemies(char layoutMatrix[LAYOUT_ROWS][LAYOUT_COLUMNS], Enemy *enemy);

#endif // LEVEL_H
