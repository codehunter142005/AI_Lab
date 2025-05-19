//A Star Code

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define N 5 

int graph[N][N] = {
    {0, 10, 3, 0, 0},
    {0, 0, 1, 2, 0},
    {0, 4, 0, 8, 2},
    {0, 0, 0, 0, 7},
    {0, 0, 0, 9, 0}
};

int heuristic[N] = {7, 6, 2, 1, 0};  

int minDistance(int dist[], int visited[]) {
    int min = INT_MAX, index = -1;
    for (int i = 0; i < N; i++) {
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            index = i;
        }
    }
    return index;
}

void aStar(int start, int goal) {
    int g[N], f[N], visited[N] = {0};

    for (int i = 0; i < N; i++) {
        g[i] = INT_MAX;
        f[i] = INT_MAX;
    }

    g[start] = 0;
    f[start] = heuristic[start];

    while (1) {
        int current = minDistance(f, visited);
        if (current == -1 || current == goal) break;

        visited[current] = 1;

        for (int i = 0; i < N; i++) {
            if (graph[current][i] && !visited[i]) {
                int tempG = g[current] + graph[current][i];

                if (tempG < g[i]) {
                    g[i] = tempG;
                    f[i] = g[i] + heuristic[i];
                }
            }
        }
    }

    printf("A* Path Cost: %d\n", g[goal]);
}

int main() {
    int start = 0, goal = 4;
    aStar(start, goal);
    return 0;
}

// A* Algorithm Dry Run (Concise)
// Setup

// Graph: 5×5 adjacency matrix with weighted edges
// Heuristic values: [7, 6, 2, 1, 0]
// Start: Node 0, Goal: Node 4

// Step-by-Step Execution
// Initialization

// g = [0, ∞, ∞, ∞, ∞]
// f = [7, ∞, ∞, ∞, ∞]
// visited = [0, 0, 0, 0, 0]

// Iteration 1: Node 0

// Select node 0 (lowest f-value = 7)
// Mark visited: [1, 0, 0, 0, 0]
// Process neighbors:

// Node 1: g=10, f=16
// Node 2: g=3, f=5

// Updated state:

// g = [0, 10, 3, ∞, ∞]
// f = [7, 16, 5, ∞, ∞]

// Iteration 2: Node 2

// Select node 2 (lowest f-value = 5)
// Mark visited: [1, 0, 1, 0, 0]
// Process neighbors:

// Node 1: g=7, f=13 (improved)
// Node 3: g=11, f=12
// Node 4: g=5, f=5

// Updated state:

// g = [0, 7, 3, 11, 5]
// f = [7, 13, 5, 12, 5]

// Iteration 3: Node 4

// Select node 4 (lowest f-value = 5)
// Goal reached! Exit loop

// Result

// Shortest path cost: 5
// Path: 0 → 2 → 4
// Path breakdown:

// 0→2: cost 3
// 2→4: cost 2
// Total: 5

// The A* algorithm efficiently found the optimal path by using the heuristic to guide its search directly toward the goal.
