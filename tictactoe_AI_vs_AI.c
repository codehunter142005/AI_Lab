//TicTactoe AI vs AI
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char grid[3][3];
const char AI1 = 'X';
const char AI2 = 'O';

void drawBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", grid[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---+---+---\n");
    }
    printf("\n");
}

bool isMovesLeft() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i][j] == ' ')
                return true;
    return false;
}

int evaluate() {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (grid[i][0] != ' ' && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2])
            return (grid[i][0] == AI1) ? 10 : -10;
    }
    
    // Check columns
    for (int i = 0; i < 3; i++) {
        if (grid[0][i] != ' ' && grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i])
            return (grid[0][i] == AI1) ? 10 : -10;
    }
    
    // Check diagonals
    if (grid[0][0] != ' ' && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2])
        return (grid[0][0] == AI1) ? 10 : -10;
    if (grid[0][2] != ' ' && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])
        return (grid[0][2] == AI1) ? 10 : -10;
    
    return 0;
}

int minimax(bool isMax) {
    int score = evaluate();
    
    if (score == 10 || score == -10)
        return score;
    
    if (!isMovesLeft())
        return 0;
    
    if (isMax) {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid[i][j] == ' ') {
                    grid[i][j] = AI1;
                    int val = minimax(false);
                    if (val > best)
                        best = val;
                    grid[i][j] = ' ';
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid[i][j] == ' ') {
                    grid[i][j] = AI2;
                    int val = minimax(true);
                    if (val < best)
                        best = val;
                    grid[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

void findBestMove(char player, int *row, int *col) {
    int bestVal = (player == AI1) ? -1000 : 1000;
    *row = -1;
    *col = -1;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i][j] == ' ') {
                grid[i][j] = player;
                int moveVal = minimax(player == AI2);
                grid[i][j] = ' ';
                
                if ((player == AI1 && moveVal > bestVal) ||
                    (player == AI2 && moveVal < bestVal)) {
                    bestVal = moveVal;
                    *row = i;
                    *col = j;
                }
            }
        }
    }
}

bool checkWinner(char *winner) {
    int score = evaluate();
    if (score == 10) {
        *winner = AI1;
        return true;
    }
    if (score == -10) {
        *winner = AI2;
        return true;
    }
    return false;
}

void resetGrid() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            grid[i][j] = ' ';
}

int main() {
    char winner = ' ';
    int moveCount = 1;
    int row, col;
    
    resetGrid();
    
    printf("AI vs AI Tic Tac Toe: AI1 = X, AI2 = O\n");
    
    while (true) {
        drawBoard();
        char currentPlayer = (moveCount % 2 == 1) ? AI1 : AI2;
        printf("Move %d: AI Player %d (%c)\n", 
               moveCount, 
               (currentPlayer == AI1) ? 1 : 2, 
               currentPlayer);
        
        findBestMove(currentPlayer, &row, &col);
        grid[row][col] = currentPlayer;
        
        if (checkWinner(&winner)) {
            drawBoard();
            printf("Winner: AI Player %d (%c)\n", 
                   (winner == AI1) ? 1 : 2, 
                   winner);
            break;
        }
        
        if (!isMovesLeft()) {
            drawBoard();
            printf("It's a draw!\n");
            break;
        }
        
        moveCount++;
    }
    
    return 0;
}