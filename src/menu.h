#ifndef MENU_H

#define MENU_H

// Esta struct irá controlar os estados do Menu do jogo
typedef struct {
    bool display;        // Variável display para dizer se o menu deve ou não ser exibido
    bool startGame;      // Variável startGame para começar um novo jogo
    bool openScoreboard; // Variável openScoreboard para abrir a tabela de pontuações
    bool exitGame;       // Variável exitGame para sair do menu e fechar a janela
} Menu;

void DisplayMenu(Menu *menu,
                 int screenWidth,
                 int screenHeight); // Função que irá mostrar o menu na tela

#endif
