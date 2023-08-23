#include <raylib.h>
#include <stdio.h>

#include "ranking.h"

void CopyScoresToArray(char rankingFileName[], Score destinationArray[MAX_TOP_SCORES])
{
    // Esta função lê o arquivo de pontuações e copia todas as pontuações nele
    // para um array de struct Score. Isto é feito para facilitar o trabalho com as
    // pontuações (verificação de valor, ordenação, salvamento).
    FILE *rankingFile;
    rankingFile = fopen(rankingFileName, "rb");

    if (rankingFile == NULL) {
        printf("Could not open the file.\n");
        return; // Se o arquivo não pôde ser aberto, então a função deve parar por aqui.
    }

    Score buffer; // Definindo um buffer para guardar os conteúdos da leitura do arquivo.

    for (int i = 0; i < MAX_TOP_SCORES; i++) {
        if (fread(&buffer, sizeof(Score), 1, rankingFile) == 1) {
            // Aqui estamos copiando o valor do buffer para uma célula do array.
            destinationArray[i] = buffer;
        }
    }

    fclose(rankingFile);
}

void SaveScores(Score scores[MAX_TOP_SCORES], char rankingFileName[])
{
    // Se houve modificação na tabela de pontuações, então essa função irá salvar essas
    // mudanças no arquivo de pontuações.
    FILE *rankingFile;
    rankingFile = fopen(rankingFileName, "rb+");

    if (rankingFile == NULL) {
        printf("Could not open the file.\n");
        return; // Se o arquivo não pôde ser aberto, então a função deve parar por aqui.
    }

    // Neste loop estamos sobrescrevendo cada uma das pontuações no arquivo de pontuações
    // com as pontuações contidas no array scores.
    for (int i = 0; i < MAX_TOP_SCORES; i++) {
        if (fwrite(&scores[i], sizeof(Score), 1, rankingFile) != 1) {
            printf("Could not write the file.\n");
        }
    }

    fclose(rankingFile);
}

void AddNewScoreToRanking(Score newScore, char rankingFileName[])
{
    // Se a nova pontuação for maior do que a menor pontuação no Top 5 atual,
    // então devemos atualizar o Top 5. Esta função faz isso.
    Score scores[MAX_TOP_SCORES];
    CopyScoresToArray(rankingFileName, scores); // Copiando as pontuações do arquivo para um array.

    // As pontuações no arquivo já estão ordenadas, de maneira que quando copiamos as pontuações
    // para um array, a pontuação mais alta está no índice 0 e a mais baixa está no último índice,
    // isto é, o índice de valor igual ao comprimento do array menos 1. Se a nova pontuação for
    // maior do que a pontuação no último índice, então substituímos essa última pontuação com
    // a nova pontuação, caso contrário não é feito nada e a função acaba.
    if (newScore.value > scores[MAX_TOP_SCORES - 1].value) {
        scores[MAX_TOP_SCORES - 1] = newScore;
    } else {
        return;
    }

    Score tmpScore; // Variável auxiliar para conseguirmos ordenar o array.

    // Este loop ordena o array de pontuações. O loop começa do penúltimo índice do array
    // pois o último índice está associado à nova pontuação. Na primeira iteração checamos
    // se a nova pontuação é maior que a penúltima. Se não for, então o array já está ordenado
    // e o loop acaba, se for então trocamos as duas pontuações de lugar e o loop continua.
    // Esse processo continua até a nova pontuação chegar na primeira posição ou até chegar
    // em uma posição onde ela seja menor do que a próxima.
    for (int i = MAX_TOP_SCORES - 2; i >= 0; i--) {
        if (scores[i].value < newScore.value) {
            tmpScore = scores[i];
            scores[i] = newScore;
            scores[i + 1] = tmpScore;
        } else {
            break;
        }
    }

    SaveScores(scores, rankingFileName); // Salva a nova organização de pontuações.
}

void ShowScores(char rankingFileName[])
{
    // Esta função irá mostrar o Top 5 de pontuações caso o usuário selecione
    // a opção da tabela de pontuações no menu.
    FILE *rankingFile;
    rankingFile = fopen(rankingFileName, "rb");

    if (rankingFile == NULL) {
        printf("Could not open the file.\n");
        return; // Se o arquivo não pôde ser aberto, então a função deve parar por aqui.
    }

    Score buffer; // Definindo um buffer para guardar os conteúdos da leitura do arquivo.

    BeginDrawing();
    ClearBackground(BLACK);

    const char title[] = "High Scores";
    const int titleSize = 80;
    const int titleWidth = MeasureText(title, titleSize);
    const int titleXPosition = GetScreenWidth() / 2 - titleWidth / 2;
    DrawText(title, titleXPosition, 100, titleSize, YELLOW);

    const int initialYPosition = 300;

    for (int i = 0; i < MAX_TOP_SCORES; i++) {
        if (fread(&buffer, sizeof(Score), 1, rankingFile) == 1) {
            DrawText(TextFormat("%-21s", buffer.name), 100, initialYPosition + i * 75, 30, YELLOW);
            DrawText(TextFormat("%10d", buffer.value), 800, initialYPosition + i * 75, 30, YELLOW);
        }
    }

    EndDrawing();

    fclose(rankingFile);
}

void ReadScoreName(Score *score)
{
    Rectangle textBox = {350, 400, 500, 80};
    int letterCount = 0;

    while (!IsKeyPressed(KEY_ENTER)) {
        int key = GetCharPressed();

        while (key > 0) {
            // NOTE: Only allow keys in range [32..125]
            if ((key >= 32) && (key <= 125) && (letterCount < NAME_MAX_LENGTH)) {
                score->name[letterCount] = (char)key;
                score->name[letterCount + 1] = '\0';
                (letterCount)++;
            }

            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            (letterCount)--;
            if (letterCount < 0)
                letterCount = 0;
            score->name[letterCount] = '\0';
        }

        BeginDrawing();

        DrawRectangleRec(textBox, LIGHTGRAY);

        DrawText(score->name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

        EndDrawing();
    }
}
