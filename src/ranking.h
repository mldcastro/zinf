// Este arquivo lida com toda a lógica por trás das pontuações do jogo.

#ifndef RANKING_H

#include <stdio.h>

#define RANKING_H
#define NAME_MAX_LENGTH 20              // Não permitir nomes maiores do que 20 caracteres.
#define MAX_TOP_SCORES 5                // Serão apresentados somente as 5 maiores pontuações.
#define RANKING_FILE_NAME "ranking.bin" // Nome do arquivo que guarda as pontuações.

typedef struct {
    char name[NAME_MAX_LENGTH];
    int value;
} Score;

// Função que adiciona a nova pontuação no Top 5 e no arquivo das pontuações SE
// a nova pontuação for maior do que a menor pontuação no atual Top 5.
void AddNewScoreToRanking(Score newScore, char rankingFileName[]);

// Função que lê o arquivo de pontuações e mostra as 5 maiores pontuações quando o
// usuário seleciona a página de pontuações no menu.
void ShowScores(char rankingFileName[]);

// Função que lê o arquivo de pontuações e copia as pontuações para um array de struct Score.
void CopyScoresToArray(char rankingFileName[], Score destinationArray[MAX_TOP_SCORES]);

// Função que salva a nova tabela de pontuações no arquivo de pontuações.
void SaveScores(Score scores[MAX_TOP_SCORES], char rankingFileName[]);

void ReadScoreName(Score *score);

#endif // RANKING_H