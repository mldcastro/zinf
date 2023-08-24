#ifndef LAYOUT_H

#include "elements.h"

#define LAYOUT_H
#define LAYOUT_ROWS 16
#define LAYOUT_COLUMNS 24
#define TILE_SIZE 50
#define STATUS_BAR_HEIGHT 60

typedef struct Layout {
    char matrix[LAYOUT_ROWS][LAYOUT_COLUMNS];
    char *file;
    bool shouldReadFile;
    bool wasFileReadOnce;
} Layout;

void LoadLevelLayoutFromFile(Layout *layout, Player *player, EnvironmentObjects *envObjects);

void DrawMapFromMatrix(Layout *layout);

void DrawStatusBar(int lives, int level, int score);

#endif // LAYOUT_H
