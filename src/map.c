#include <raylib.h>
#include <stdio.h>

#define LINHAS 16
#define COLUNAS 24
#define TILE_SIZE 30

void le_nivel(char mat[][COLUNAS], char *nomearq) {
    FILE *arq;
    int i, j;
    arq = fopen(nomearq, "r");
    if (arq == NULL) {
        printf("erro de abertura");
    } else {
        for (i = 0; i < LINHAS; i++) {
            for (j = 0; j < COLUNAS; j++) {
                fscanf(arq, " %c", &mat[i][j]);
            }
        }
    }
    fclose(arq);
}

void DrawMapFromData(char mat[][COLUNAS]) {
    int i, j;
    for (i = 0; i < LINHAS; i++) {
        for (j = 0; j < COLUNAS; j++) {
            char tile = mat[i][j];
            Color color = BLANK;

            if (tile == 'B') {
                color = DARKGRAY;
            } else if (tile == 'P') {
                color = GREEN;
            }

            DrawRectangle(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE, color);
        }
    }
}

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Raylib Map Drawing");

    char nome[100] = "../nivel1.txt";
    char m[LINHAS][COLUNAS];

    le_nivel(m, nome);

    int playerX = 0;
    int playerY = 0;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_RIGHT)) {
            playerX++;
        } else if (IsKeyDown(KEY_LEFT)) {
            playerX--;
        } else if (IsKeyDown(KEY_DOWN)) {
            playerY++;
        } else if (IsKeyDown(KEY_UP)) {
            playerY--;
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawMapFromData(m);

        DrawRectangle(playerX * TILE_SIZE, playerY * TILE_SIZE, TILE_SIZE, TILE_SIZE, BLUE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
