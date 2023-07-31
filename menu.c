#include <raylib.h>

// struct  ndo nosso "menu" recebe 
typedef struct {        
    bool display;        // display deve ser exibir
    bool startGame;      // startGame para um novo jogo
    bool openScoreboard; // scoreboard para a placar 
    bool exitGame;       // exitGame para sair
} Menu;

void DisplayMenu(Menu *menu, int screenWidth, int screenHeight);

int main() {
    const int screenWidth = 1200;
    const int screenHeight = 860;

    bool exitWindow = false;

    Menu menu = {true, false, false, false};

    InitWindow(screenWidth, screenHeight, "Menu");

    SetTargetFPS(30);

    while (!exitWindow) {
        if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE) || menu.exitGame) {
            exitWindow = true;
        }

        DisplayMenu(&menu, screenWidth, screenHeight);

        if (menu.startGame) {
            BeginDrawing();

            ClearBackground(GRAY);
            DrawText("You pressed ENTER", screenWidth / 2, screenHeight / 2, 30, GREEN);

            EndDrawing();

        } else if (menu.openScoreboard) {
            BeginDrawing();

            ClearBackground(YELLOW);
            DrawText("You pressed S", screenWidth / 2, screenHeight / 2, 30, BLUE);

            EndDrawing();
        }
    }

    CloseWindow();

    return 0;
}

void DisplayMenu(Menu *menu, int screenWidth, int screenHeight) { // funcão DispayMenu
    if (menu->display) {
        int initialHeight = 400;
        const int width = 100;

        Texture2D linkSprite = LoadTexture("sprites/Link_left.png");
        Vector2 spritePosition = {screenWidth - 400, screenHeight - 600};
        float spriteRotation = 0.0f;
        int spriteScale = 7;

        BeginDrawing();

        ClearBackground(BLACK);
        DrawTextureEx(linkSprite, spritePosition, spriteRotation, spriteScale, WHITE);
        // Ajustei a posição e o tamanho da fonte para a palavra *ZINF*****
        // usei a função MeasureText 
        DrawText("ZINF", screenWidth / 2 - MeasureText("ZINF", 160) / 2, initialHeight - 250, 160, YELLOW); // deixei amarelo**
        DrawText("Press ENTER to start", width, initialHeight, 30, YELLOW);
        DrawText("Press S to enter the Scoreboard", width, initialHeight + 75, 30, YELLOW);
        DrawText("Press X to exit", width, initialHeight + 2 * 75, 30, YELLOW);

        EndDrawing();

        if (IsKeyPressed(KEY_ENTER)) {  // pressionar "enter" para novo jogo
            menu->display = false;
            menu->startGame = true;
        }

        if (IsKeyPressed(KEY_S)) {        // pressionar "S" para placar 
            menu->display = false;
            menu->openScoreboard = true;
        }

        if (IsKeyPressed(KEY_X)) {        // pressionar "X' para sair do menu
            menu->display = false;
            menu->exitGame = true;
        }
    }
}
