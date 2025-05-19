//Depth Limited Search

#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100
#define TRUE 1
#define FALSE 0

// Adjacency matrix to represent the graph
int graph[MAX_NODES][MAX_NODES];
int visited[MAX_NODES];
int numNodes;

// Function prototype/declaration for DLS_Recursive
int DLS_Recursive(int current, int goal, int depth_limit);

// Depth-Limited Search function
int DLS(int start, int goal, int depth_limit) {
    // Initialize visited array
    for (int i = 0; i < numNodes; i++) {
        visited[i] = FALSE;
    }
    
    return DLS_Recursive(start, goal, depth_limit);
}

// Recursive helper function for DLS
int DLS_Recursive(int current, int goal, int depth_limit) {
    // Check if current node is the goal
    if (current == goal) {
        printf("Goal found: %d\n", current);
        return TRUE;
    }
    
    // If depth limit reached, stop exploring this path
    if (depth_limit <= 0) {
        return FALSE;
    }
    
    // Mark current node as visited
    visited[current] = TRUE;
    printf("Visiting node: %d (depth_limit: %d)\n", current, depth_limit);
    
    // Explore all adjacent nodes
    for (int i = 0; i < numNodes; i++) {
        if (graph[current][i] == 1 && !visited[i]) {
            // Recursive call with reduced depth limit
            if (DLS_Recursive(i, goal, depth_limit - 1)) {
                return TRUE; // Goal found in this path
            }
        }
    }
    
    return FALSE; // Goal not found in this path
}

int main() {
    int start, goal, depth_limit;
    int edges, u, v;
    
    // Input number of nodes
    printf("Enter number of nodes: ");
    scanf("%d", &numNodes);
    
    // Initialize graph
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            graph[i][j] = 0;
        }
    }
    
    // Input edges
    printf("Enter number of edges: ");
    scanf("%d", &edges);
    
    printf("Enter edges (u v):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1; // For undirected graph
    }
    
    // Input start node, goal node, and depth limit
    printf("Enter start node: ");
    scanf("%d", &start);
    
    printf("Enter goal node: ");
    scanf("%d", &goal);
    
    printf("Enter depth limit: ");
    scanf("%d", &depth_limit);
    
    // Perform Depth-Limited Search
    if (DLS(start, goal, depth_limit)) {
        printf("Path exists from %d to %d within depth limit %d\n", start, goal, depth_limit);
    } else {
        printf("No path exists from %d to %d within depth limit %d\n", start, goal, depth_limit);
    }
    
    return 0;
}

// Enter number of nodes: 5
// Enter number of edges: 5
// Enter edges (u v):
// 0 1
// 0 2
// 1 3
// 2 4
// 3 4
// Enter start node: 0
// Enter goal node: 4
// Enter depth limit: 2
// Visiting node: 0 (depth_limit: 2)
// Visiting node: 1 (depth_limit: 1)
// Visiting node: 3 (depth_limit: 0)
// Visiting node: 2 (depth_limit: 1)
// Visiting node: 4 (depth_limit: 0)
// Goal found: 4
// Path exists from 0 to 4 within depth limit 2
