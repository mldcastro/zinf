#include <raylib.h>

#define TILE_SIZE 50
#define MAP_WIDTH 10
#define MAP_HEIGHT 10

void DrawMap(const char *mapFile);

int main() {
    const int screenWidth = 600;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Map Example");

    SetTargetFPS(60);

    const char *mapFile = "mapa.txt";

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawMap(mapFile);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void DrawMap(const char *mapFile) {
    // Código da função DrawMap aqui...
}

