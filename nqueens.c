#include <stdio.h>
#define N 4 

int solutionCount = 0;  

void printSolution(int board[N][N]) {
    printf("Solution %d:\n", solutionCount);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%c ", board[i][j] ? 'Q' : '.');
        printf("\n");
    }
    printf("\n");
}

int isSafe(int board[N][N], int row, int col) {
    for (int i = 0; i < col; i++)  
        if (board[row][i]) return 0;

    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)  
        if (board[i][j]) return 0;

    for (int i = row, j = col; i < N && j >= 0; i++, j--)  
        if (board[i][j]) return 0;

    return 1;
}

int solveNQueens(int board[N][N], int col) {
    if (col >= N) {
        solutionCount++;
        printSolution(board);
        return solutionCount >= 10 ? 1 : 0;  
    }

    for (int i = 0; i < N; i++) {
        if (isSafe(board, i, col)) {
            board[i][col] = 1;
            if (solveNQueens(board, col + 1))  
                return 1;  
            board[i][col] = 0;
        }
    }

    return 0;
}

void nQueens() {
    int board[N][N] = {0};
    solveNQueens(board, 0);
    if (solutionCount == 0)
        printf("No solution exists.\n");
}

int main() {
    nQueens();
    return 0;
}
