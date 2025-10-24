#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "game.h"

void spawnTile(int* board, int size);
void initializeBoard(int* board, int size);
void displayBoard(int* board, int size);
bool checkWin(int* board, int size, int scoreToWin);
bool checkLoss(int* board, int size);

void initializeBoard(int* board, int size) {
    for (int i = 0; i < size * size; i++) {
        board[i] = 0;
    }
    spawnTile(board, size);
    spawnTile(board, size);
}

void displayBoard(int* board, int size) {
    printf("\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%4d", board[i * size + j]);
        }
        printf("\n");
    }
    printf("\n");
}

void spawnTile(int* board, int size) {
    int emptyCount = 0;
    for (int i = 0; i < size * size; i++) {
        if (board[i] == 0) emptyCount++;
    }

    if (emptyCount == 0) return;

    int pos = rand() % emptyCount;
    int value = (rand() % 10 < 9) ? 2 : 4;

    for (int i = 0; i < size * size; i++) {
        if (board[i] == 0) {
            if (pos == 0) {
                board[i] = value;
                return;
            }
            pos--;
        }
    }
}

bool checkWin(int* board, int size, int scoreToWin) {
    for (int i = 0; i < size * size; i++) {
        if (board[i] >= scoreToWin) return true;
    }
    return false;
}

bool checkLoss(int* board, int size) {
    for (int i = 0; i < size * size; i++) {
        if (board[i] == 0) return false;

        int row = i / size, col = i % size;
        // בדוק שכנים
        if (row > 0 && board[i] == board[(row - 1) * size + col]) return false;
        if (row < size - 1 && board[i] == board[(row + 1) * size + col]) return false;
        if (col > 0 && board[i] == board[row * size + (col - 1)]) return false;
        if (col < size - 1 && board[i] == board[row * size + (col + 1)]) return false;
    }
    return true; // אם לא נמצאו מהלכים אפשריים
}
//some changes


bool moveUp(int* board, int size, int* score) {
    bool moved = false;
    for (int col = 0; col < size; col++) {
        int lastMergeRow = -1;
        for (int row = 1; row < size; row++) {
            if (board[row * size + col] == 0) continue;

            int targetRow = row;
            while (targetRow > 0 && board[(targetRow - 1) * size + col] == 0) {
                targetRow--;
            }

            if (targetRow > 0 && board[(targetRow - 1) * size + col] == board[row * size + col] && targetRow - 1 > lastMergeRow) {
                board[(targetRow - 1) * size + col] *= 2;
                *score += board[(targetRow - 1) * size + col];
                board[row * size + col] = 0;
                lastMergeRow = targetRow - 1;
                moved = true;
            } else if (targetRow != row) {
                board[targetRow * size + col] = board[row * size + col];
                board[row * size + col] = 0;
                moved = true;
            }
        }
    }
    return moved;
}

bool moveDown(int* board, int size, int* score) {
    bool moved = false;
    for (int col = 0; col < size; col++) {
        int lastMergeRow = size;
        for (int row = size - 2; row >= 0; row--) {
            if (board[row * size + col] == 0) continue;

            int targetRow = row;
            while (targetRow < size - 1 && board[(targetRow + 1) * size + col] == 0) {
                targetRow++;
            }

            if (targetRow < size - 1 && board[(targetRow + 1) * size + col] == board[row * size + col] && targetRow + 1 < lastMergeRow) {
                board[(targetRow + 1) * size + col] *= 2;
                *score += board[(targetRow + 1) * size + col];
                board[row * size + col] = 0;
                lastMergeRow = targetRow + 1;
                moved = true;
            } else if (targetRow != row) {
                board[targetRow * size + col] = board[row * size + col];
                board[row * size + col] = 0;
                moved = true;
            }
        }
    }
    return moved;
}

bool moveLeft(int* board, int size, int* score) {
    bool moved = false;
    for (int row = 0; row < size; row++) {
        int lastMergeCol = -1;
        for (int col = 1; col < size; col++) {
            if (board[row * size + col] == 0) continue;

            int targetCol = col;
            while (targetCol > 0 && board[row * size + (targetCol - 1)] == 0) {
                targetCol--;
            }

            if (targetCol > 0 && board[row * size + (targetCol - 1)] == board[row * size + col] && targetCol - 1 > lastMergeCol) {
                board[row * size + (targetCol - 1)] *= 2;
                *score += board[row * size + (targetCol - 1)];
                board[row * size + col] = 0;
                lastMergeCol = targetCol - 1;
                moved = true;
            } else if (targetCol != col) {
                board[row * size + targetCol] = board[row * size + col];
                board[row * size + col] = 0;
                moved = true;
            }
        }
    }
    return moved;
}

bool moveRight(int* board, int size, int* score) {
    bool moved = false;
    for (int row = 0; row < size; row++) {
        int lastMergeCol = size;
        for (int col = size - 2; col >= 0; col--) {
            if (board[row * size + col] == 0) continue;

            int targetCol = col;
            while (targetCol < size - 1 && board[row * size + (targetCol + 1)] == 0) {
                targetCol++;
            }

            if (targetCol < size - 1 && board[row * size + (targetCol + 1)] == board[row * size + col] && targetCol + 1 < lastMergeCol) {
                board[row * size + (targetCol + 1)] *= 2;
                *score += board[row * size + (targetCol + 1)];
                board[row * size + col] = 0;
                lastMergeCol = targetCol + 1;
                moved = true;
            } else if (targetCol != col) {
                board[row * size + targetCol] = board[row * size + col];
                board[row * size + col] = 0;
                moved = true;
            }
        }
    }
    return moved;
}

void playGame(int* board, int size, int scoreToWin) {
    int score = 0; // ניקוד
    bool gameWon = false;

    initializeBoard(board, size);
    displayBoard(board, size);

    while (true) {
        printf("Score: %d\n", score);
        printf("Enter move (u = up, d = down, l = left, r = right, e = exit, n = new game): ");
        char move;
        scanf(" %c", &move);
        move = tolower(move);

        bool moved = false;
        if (move == 'u') {
            moved = moveUp(board, size, &score);
        } else if (move == 'd') {
            moved = moveDown(board, size, &score);
        } else if (move == 'l') {
            moved = moveLeft(board, size, &score);
        } else if (move == 'r') {
            moved = moveRight(board, size, &score);
        } else if (move == 'e') {
            printf("Exiting game. Final score: %d\n", score);
            break;
        } else if (move == 'n') {
            printf("Starting a new game...\n");
            playGame(board, size, scoreToWin);
            return;
        }

        if (!moved) {
            printf("Invalid move. Try again.\n");
            continue;
        }

        if (!gameWon && checkWin(board, size, scoreToWin)) {
            printf("Congratulations! You've won the game!\n");
            gameWon = true;
        }

        if (checkLoss(board, size)) {
            printf("Game over! No more valid moves.\n");
            break;
        }

        spawnTile(board, size);
        displayBoard(board, size);
    }
}
