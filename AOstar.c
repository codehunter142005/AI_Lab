#include <stdio.h>
#include <stdlib.h>

#define N 4  

int cost[N][N] = {
    {-1, 3, 2, -1},
    {-1, -1, -1, 4},
    {-1, -1, -1, 1},
    {-1, -1, -1, -1}
};

int heuristic[N] = {4, 2, 1, 0};  

void aoStar(int current, int solved[]) {
    if (solved[current]) return;
 
    int minCost = heuristic[current], bestNode = -1;
    
    for (int i = 0; i < N; i++) {
        if (cost[current][i] != -1) {
            int totalCost = cost[current][i] + heuristic[i];
            if (totalCost < minCost) {
                minCost = totalCost;
                bestNode = i;
            }
        }
    }

    if (bestNode != -1) {
        heuristic[current] = minCost;
        aoStar(bestNode, solved);
    }

    solved[current] = 1;
}

int main() {
    int solved[N] = {0};
    aoStar(0, solved);
    printf("AO* Path Cost: %d\n", heuristic[0]);
    return 0;
}
