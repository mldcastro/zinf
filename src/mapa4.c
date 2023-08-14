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
                fscanf(arq, "%c", &mat[i][j]);
            }
            fgetc(arq);
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
    const int screenWidth = 1280; // Largura da janela
    const int screenHeight = 720; // Altura da janela

    InitWindow(screenWidth, screenHeight, "Raylib Map Drawing");

    char nome[100] = "nive1.txt";
    char m[LINHAS][COLUNAS];

    le_nivel(m, nome);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawMapFromData(m);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
