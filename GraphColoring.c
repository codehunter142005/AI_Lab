#include <stdio.h>
#include <stdbool.h>

int graph[100][100];
int color[100];
int V; 

bool isSafe(int v, int c) {
    for (int i = 0; i < V; i++) {
        if (graph[v][i] && color[i] == c) {
            return false;
        }
    }
    return true;
}

bool graphColoring(int v, int m) {
    if (v == V) {
        return true; 
    }

    for (int c = 1; c <= m; c++) {
        if (isSafe(v, c)) {
            color[v] = c;

            if (graphColoring(v + 1, m)) {
                return true;
            }

            color[v] = 0; 
        }
    }

    return false;
}

void printSolution() {
    printf("Vertex Color Assignment:\n");
    for (int i = 0; i < V; i++) {
        printf("Vertex %d -> Color %d\n", i, color[i]);
    }
}

int main() {
    int m;
    
    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter the number of colors: ");
    scanf("%d", &m);

    for (int i = 0; i < V; i++) {
        color[i] = 0;
    }

    if (graphColoring(0, m)) {
        printSolution();
    } else {
        printf("Solution does not exist with %d colors.\n", m);
    }

    return 0;
}
