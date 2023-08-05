#ifndef RANKING

#include <stdio.h>

#define RANKING
#define NAME_MAX_LENGTH 20
#define MAX_TOP_SCORES 5
#define RANKING_FILE_NAME "ranking.bin"

typedef struct {
    char name[NAME_MAX_LENGTH];
    int value;
} Score;

void AddNewScoreToRanking(Score newScore, char rankingFileName[]);
void ShowScores(char rankingFileName[]);
void MoveScoresToArray(char rankingFileName[], Score destinationArray[MAX_TOP_SCORES]);
void SaveScores(Score scores[MAX_TOP_SCORES], char rankingFileName[]);

#endif
