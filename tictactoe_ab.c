#include <stdio.h>
#include <stdlib.h>

void constBoard(int board[]);
void user1Turn(int board[]);
void user2Turn(int board[]);
int alphaBeta(int board[], int depth, int alpha, int beta, int player);
void compTurn(int board[]);
int analyzeBoard(int board[]);

int main() {
    int choice;
    printf("Enter 1 for single player, 2 for multiplayer: ");
    scanf("%d", &choice);
    int board[9] = {0};

    if (choice == 1) {
        printf("Computer : O Vs. You : X\n");
        printf("Enter to play 1(st) or 2(nd) : ");
        int player;
        scanf("%d", &player);
        for (int i = 0; i < 9; i++) {
            if (analyzeBoard(board) != 0) {
                break;
            }
            if ((i + player) % 2 == 0) {
                compTurn(board);
            } else {
                constBoard(board);
                user1Turn(board);
            }
        }
    } else {
        for (int i = 0; i < 9; i++) {
            if (analyzeBoard(board) != 0) {
                break;
            }
            if (i % 2 == 0) {
                constBoard(board);
                user1Turn(board);
            } else {
                constBoard(board);
                user2Turn(board);
            }
        }
    }

    int x = analyzeBoard(board);
    constBoard(board);
    if (x == 0) {
        printf("Draw!!!\n");
    } else if (x == -1) {
        printf("X Wins!!! Y Lose !!!\n");
    } else {
        printf("X Lose!!! O Wins !!!!\n");
    }
}

void constBoard(int board[]) {
    printf("Current State Of Board : \n\n");
    for (int i = 0; i < 9; i++) {
        if (i > 0 && i % 3 == 0) {
            printf("\n");
        }
        if (board[i] == 0) {
            printf("- ");
        } else if (board[i] == 1) {
            printf("O ");
        } else {
            printf("X ");
        }
    }
    printf("\n\n");
}

void user1Turn(int board[]) {
    printf("Enter X's position from [1...9]: ");
    int pos;
    scanf("%d", &pos);
    if (board[pos - 1] != 0) {
        printf("Wrong Move!!!\n");
        exit(0);
    }
    board[pos - 1] = -1;
}

void user2Turn(int board[]) {
    printf("Enter O's position from [1...9]: ");
    int pos;
    scanf("%d", &pos);
    if (board[pos - 1] != 0) {
        printf("Wrong Move!!!\n");
        exit(0);
    }
    board[pos - 1] = 1;
}

int alphaBeta(int board[], int depth, int alpha, int beta, int player) {
    int x = analyzeBoard(board);
    if (x != 0) {
        return x * player;
    }
    int pos = -1;
    int value = (player == 1) ? -2 : 2;
    for (int i = 0; i < 9; i++) {
        if (board[i] == 0) {
            board[i] = player;
            int score = -alphaBeta(board, depth + 1, -beta, -alpha, player * -1);
            board[i] = 0;
            if (score > value) {
                value = score;
                pos = i;
            }
            if (player == 1) {
                alpha = (alpha > value) ? alpha : value;
            } else {
                beta = (beta < value) ? beta : value;
            }
            if (alpha >= beta) {
                break;
            }
        }
    }
    return (pos == -1) ? 0 : value;
}

void compTurn(int board[]) {
    int pos = -1;
    int value = -2;
    for (int i = 0; i < 9; i++) {
        if (board[i] == 0) {
            board[i] = 1;
            int score = -alphaBeta(board, 0, -2, 2, -1);
            board[i] = 0;
            if (score > value) {
                value = score;
                pos = i;
            }
        }
    }
    board[pos] = 1;
}

int analyzeBoard(int board[]) {
    int cb[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };

    for (int i = 0; i < 8; i++) {
        if (board[cb[i][0]] != 0 &&
            board[cb[i][0]] == board[cb[i][1]] &&
            board[cb[i][0]] == board[cb[i][2]]) {
            return board[cb[i][2]];
        }
    }
    return 0;
}
