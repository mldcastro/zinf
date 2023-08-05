#include <raylib.h>
#include <stdio.h>

#include "ranking.h"

void MoveScoresToArray(char rankingFileName[], Score destinationArray[MAX_TOP_SCORES]) {
    FILE *rankingFile;
    rankingFile = fopen(rankingFileName, "rb");

    if (rankingFile == NULL) {
        printf("Could not open the file.\n");
        return;
    }

    Score buffer;

    for (int i = 0; i < MAX_TOP_SCORES; i++) {
        if (fread(&buffer, sizeof(Score), 1, rankingFile) == 1) {
            destinationArray[i] = buffer;
        }
    }

    fclose(rankingFile);
}

void SaveScores(Score scores[MAX_TOP_SCORES], char rankingFileName[]) {
    FILE *rankingFile;
    rankingFile = fopen(rankingFileName, "rb+");

    if (rankingFile == NULL) {
        printf("Could not open the file.\n");
        return;
    }

    for (int i = 0; i < MAX_TOP_SCORES; i++) {
        if (fwrite(&scores[i], sizeof(Score), 1, rankingFile) != 1) {
            printf("Could not write the file.\n");
            break;
        }
    }

    fclose(rankingFile);
}

void AddNewScoreToRanking(Score newScore, char rankingFileName[]) {
    Score scores[MAX_TOP_SCORES];
    MoveScoresToArray(rankingFileName, scores);

    if (newScore.value > scores[MAX_TOP_SCORES - 1].value) {
        scores[MAX_TOP_SCORES - 1] = newScore;
    } else {
        return;
    }

    Score tmpScore;

    for (int i = MAX_TOP_SCORES - 2; i >= 0; i--) {
        if (scores[i].value < newScore.value) {
            tmpScore = scores[i];
            scores[i] = newScore;
            scores[i + 1] = tmpScore;
        } else {
            break;
        }
    }

    SaveScores(scores, rankingFileName);
}

void ShowScores(char rankingFileName[]) {
    FILE *rankingFile;
    rankingFile = fopen(rankingFileName, "rb");

    if (rankingFile == NULL) {
        printf("Could not open the file.\n");
        return;
    }

    Score buffer;

    BeginDrawing();
    ClearBackground(BLACK);

    int initialHeight = 300;
    int textWidth = MeasureText("High Scores", 80);
    int xPos = GetScreenWidth() / 2 - textWidth / 2;
    DrawText("High Scores", xPos, 100, 80, YELLOW);

    for (int i = 0; i < MAX_TOP_SCORES; i++) {
        if (fread(&buffer, sizeof(Score), 1, rankingFile) == 1) {
            DrawText(TextFormat("%-20s", buffer.name), 100, initialHeight + i * 75, 30, YELLOW);
            DrawText(TextFormat("%10d", buffer.value), 800, initialHeight + i * 75, 30, YELLOW);
        }
    }

    EndDrawing();

    fclose(rankingFile);
}
