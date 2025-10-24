#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

void playGame(int* board, int size, int scoreToWin);
bool moveUp(int* board, int size, int* score);
bool moveDown(int* board, int size, int* score);
bool moveLeft(int* board, int size, int* score);
bool moveRight(int* board, int size, int* score);


void initializeBoard(int* board, int size);
void displayBoard(int* board, int size);
void spawnTile(int* board, int size);
bool checkWin(int* board, int size, int scoreToWin);
bool checkLoss(int* board, int size);

#endif // GAME_H
