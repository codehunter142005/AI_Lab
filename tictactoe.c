#include <stdio.h>
#include<stdlib.h>

void constBoard(int board[]);
void user1Turn(int board[]);
void user2Turn(int board[]);
int analyzeBoard(int board[]);

int main() {
    int board[9] = {0};

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
