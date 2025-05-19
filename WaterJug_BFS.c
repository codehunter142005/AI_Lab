//Water Jug BFS
#include <stdio.h>
#include <stdbool.h>

#define MAX_JUG1 4
#define MAX_JUG2 3
#define TARGET 2
#define MAX_STATES 100

typedef struct {
    int x, y;
    int parent;
} State;

typedef struct {
    State data[MAX_STATES];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = 0;
}

void enqueue(Queue *q, State s) {
    q->data[q->rear++] = s;
}

State dequeue(Queue *q) {
    return q->data[q->front++];
}

bool isEmpty(Queue *q) {
    return q->front == q->rear;
}

bool visited[MAX_JUG1+1][MAX_JUG2+1] = {false};

void printPath(State states[], int index) {
    if (index == -1) return;
    printPath(states, states[index].parent);
    printf("(%d, %d)\n", states[index].x, states[index].y);
}

void solveBFS() {
    Queue q;
    State states[MAX_STATES];
    int count = 0;
    
    initQueue(&q);
    
    // Start with empty jugs
    states[0].x = 0;
    states[0].y = 0;
    states[0].parent = -1;
    enqueue(&q, states[0]);
    visited[0][0] = true;
    count++;
    
    while (!isEmpty(&q)) {
        State current = dequeue(&q);
        
        // Check if target reached
        if (current.x == TARGET || current.y == TARGET) {
            printf("Solution found!\n");
            printPath(states, count-1);
            return;
        }
        
        // Try all possible moves
        int moves[6][2] = {
            {MAX_JUG1, current.y},  // Fill jug1
            {current.x, MAX_JUG2},  // Fill jug2
            {0, current.y},         // Empty jug1
            {current.x, 0},         // Empty jug2
            {current.x - min(current.x, MAX_JUG2 - current.y), 
             current.y + min(current.x, MAX_JUG2 - current.y)}, // Pour jug1 to jug2
            {current.x + min(current.y, MAX_JUG1 - current.x), 
             current.y - min(current.y, MAX_JUG1 - current.x)}  // Pour jug2 to jug1
        };
        
        for (int i = 0; i < 6; i++) {
            int newX = moves[i][0];
            int newY = moves[i][1];
            
            if (newX >= 0 && newX <= MAX_JUG1 && newY >= 0 && newY <= MAX_JUG2 
                && !visited[newX][newY]) {
                visited[newX][newY] = true;
                states[count].x = newX;
                states[count].y = newY;
                states[count].parent = count-1;
                enqueue(&q, states[count]);
                count++;
            }
        }
    }
    
    printf("No solution found!\n");
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    printf("Water Jug Problem (BFS)\n");
    printf("Jug capacities: %d and %d, Target: %d\n\n", MAX_JUG1, MAX_JUG2, TARGET);
    solveBFS();
    return 0;
}
