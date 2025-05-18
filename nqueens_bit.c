#include <stdio.h>

#define N 4

int solutionCount = 0;

void printSolution(int board[N]) {
    printf("Solution %d:\n", solutionCount);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i] == j) {
                printf("Q ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void solveNQueensUtil(int row, int cols, int diag1, int diag2, int board[N]) {
    if (row == N) {
        solutionCount++;
        printSolution(board);
        return;
    }

    // All possible column positions for current row
    for (int col = 0; col < N; col++) {
        int colMask = 1 << col;
        int diag1Mask = 1 << (row - col + N - 1);
        int diag2Mask = 1 << (row + col);

        // Check if current column or diagonals are occupied
        if (cols & colMask || diag1 & diag1Mask || diag2 & diag2Mask)
            continue;

        // Place the queen and mark the column and diagonals
        board[row] = col;
        solveNQueensUtil(row + 1, cols | colMask, diag1 | diag1Mask, diag2 | diag2Mask, board);
    }
}

void solveNQueens() {
    int board[N] = {-1};  // Array to hold the positions of queens
    solveNQueensUtil(0, 0, 0, 0, board);
    if (solutionCount == 0) {
        printf("No solution exists.\n");
    }
}

int main() {
    solveNQueens();
    return 0;
}
