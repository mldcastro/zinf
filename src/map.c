#include <raylib.h>
#include <stdio.h>

#include "map.h"

void LoadLevelLayoutFromFile(char levelFileName[], char layoutMatrix[LAYOUT_ROWS][LAYOUT_COLUMNS]) {
    FILE *levelFile;
    levelFile = fopen(levelFileName, "r");

    if (levelFile == NULL) {
        printf("Could not open the file.\n");
        return; // Se o arquivo não pôde ser aberto, então a função deve parar por aqui.
    }
    for (int row = 0; row < LAYOUT_ROWS; row++) {
        for (int col = 0; col < LAYOUT_COLUMNS; col++) {
            fscanf(levelFile, " %c", &layoutMatrix[row][col]);
        }
    }

    fclose(levelFile);
}

void DrawMapFromMatrix(char layoutMatrix[LAYOUT_ROWS][LAYOUT_COLUMNS]) {
    Texture2D sprite;
    const Texture2D groundSprite = LoadTexture("sprites/Ground.png");

    for (int row = 0; row < LAYOUT_ROWS; row++) {
        for (int col = 0; col < LAYOUT_COLUMNS; col++) {
            char tile = layoutMatrix[row][col];

            DrawTexture(groundSprite, col * TILE_SIZE, row * TILE_SIZE + STATUS_BAR_HEIGHT, WHITE);

            if (tile == 'J') {
                sprite = LoadTexture("sprites/Link_right.png");
            } else if (tile == 'P') {
                sprite = LoadTexture("sprites/Obstacle.png");
            } else if (tile == 'M') {
                sprite = LoadTexture("sprites/Enemy_left.png");
            } else {
                continue;
            }

            DrawTexture(sprite, col * TILE_SIZE, row * TILE_SIZE + STATUS_BAR_HEIGHT, WHITE);
        }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
    }
}

void DrawStatusBar(int lives, int level, int score) {
    int initialXPosition = 30;
    const int yPosition = 20;

    DrawText(TextFormat("Lives: %02i", lives), initialXPosition, yPosition, 25, BLUE);
    DrawText(TextFormat("Level: %02i", level), initialXPosition + 300, yPosition, 25, BLUE);
    DrawText(TextFormat("Score: %02i", score), initialXPosition + 600, yPosition, 25, BLUE);
}

// int main() {
//     const int screenWidth = 800;
//     const int screenHeight = 600;

//     InitWindow(screenWidth, screenHeight, "Raylib Map Drawing");

//     char levelFile[] = "../levels/level_1.txt";
//     char layoutMatrix[LAYOUT_ROWS][LAYOUT_COLUMNS];

//     LoadLevelLayoutFromFile(levelFile, layoutMatrix);

//     int playerX = 0;
//     int playerY = 0;

//     SetTargetFPS(60);

//     while (!WindowShouldClose()) {
//         if (IsKeyDown(KEY_RIGHT)) {
//             playerX++;
//         } else if (IsKeyDown(KEY_LEFT)) {
//             playerX--;
//         } else if (IsKeyDown(KEY_DOWN)) {
//             playerY++;
//         } else if (IsKeyDown(KEY_UP)) {
//             playerY--;
//         }

//         BeginDrawing();

//         ClearBackground(RAYWHITE);

//         DrawMapFromMatrix(layoutMatrix);

//         DrawRectangle(playerX * TILE_SIZE, playerY * TILE_SIZE, TILE_SIZE, TILE_SIZE, BLUE);

//         EndDrawing();
//     }

//     CloseWindow();

//     return 0;
// }
