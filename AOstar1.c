#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

typedef struct {
    char name;
    int heuristic;
    int solved;
    int numSets;
    int setSize[MAX];
    char children[MAX][MAX];
    int setCost[MAX];
    int chosenSet;
} Node;

Node graph[MAX];
int graphSize = 0;

int findIndex(char name) {
    for (int i = 0; i < graphSize; i++)
        if (graph[i].name == name)
            return i;
    return -1;
}

int getSetHeuristic(int index, int setIndex) {
    int cost = graph[index].setCost[setIndex];
    for (int j = 0; j < graph[index].setSize[setIndex]; j++) {
        int childIndex = findIndex(graph[index].children[setIndex][j]);
        cost += graph[childIndex].heuristic;
    }
    return cost;
}

void aoStar(int index) {
    if (graph[index].solved)
        return;

    for (int i = 0; i < graph[index].numSets; i++)
        for (int j = 0; j < graph[index].setSize[i]; j++)
            aoStar(findIndex(graph[index].children[i][j]));

    int min = 1e9, minSet = -1;
    for (int i = 0; i < graph[index].numSets; i++) {
        int cost = getSetHeuristic(index, i);
        if (cost < min) {
            min = cost;
            minSet = i;
        }
    }

    graph[index].heuristic = min;
    graph[index].chosenSet = minSet;

    int solved = 1;
    for (int j = 0; j < graph[index].setSize[minSet]; j++) {
        int childIndex = findIndex(graph[index].children[minSet][j]);
        if (!graph[childIndex].solved)
            solved = 0;
    }
    if (solved)
        graph[index].solved = 1;
}

void printPath(int index) {
    printf("%c ", graph[index].name);
    if (graph[index].numSets == 0)
        return;
    int set = graph[index].chosenSet;
    for (int i = 0; i < graph[index].setSize[set]; i++) {
        int childIndex = findIndex(graph[index].children[set][i]);
        printPath(childIndex);
    }
}

void printGraph() {
    for (int i = 0; i < graphSize; i++)
        printf("Node %c: Heuristic = %d, Solved = %d\n", graph[i].name, graph[i].heuristic, graph[i].solved);
}

int main() {
    graphSize = 5;

    graph[0].name = 'A';
    graph[0].heuristic = 999;
    graph[0].numSets = 2;
    graph[0].setSize[0] = 2;
    strcpy(graph[0].children[0], "BC");
    graph[0].setCost[0] = 1;
    graph[0].setSize[1] = 1;
    strcpy(graph[0].children[1], "D");
    graph[0].setCost[1] = 3;

    graph[1].name = 'B';
    graph[1].heuristic = 4;
    graph[1].numSets = 0;
    graph[1].solved = 1;

    graph[2].name = 'C';
    graph[2].heuristic = 2;
    graph[2].numSets = 0;
    graph[2].solved = 1;

    graph[3].name = 'D';
    graph[3].heuristic = 6;
    graph[3].numSets = 0;
    graph[3].solved = 1;

    graph[4].name = 'E';
    graph[4].heuristic = 5;
    graph[4].numSets = 0;
    graph[4].solved = 1;

    aoStar(0);
    printGraph();
    printf("Optimal Cost: %d\n", graph[0].heuristic);
    printf("Optimal Path: ");
    printPath(0);
    printf("\n");

    return 0;
}
