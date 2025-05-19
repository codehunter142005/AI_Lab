#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_CAPACITY_JUG1 4
#define MAX_CAPACITY_JUG2 3
#define TARGET_AMOUNT 2
#define MAX_STATES 1000

// Structure to represent state of water jugs
typedef struct State {
    int jug1;
    int jug2;
    int parent;  // Index of parent state
} State;

// Stack implementation for DFS
typedef struct Stack {
    State states[MAX_STATES];
    int top;
} Stack;

// Initialize stack
void initStack(Stack *s) {
    s->top = -1;
}

// Push state onto stack
void push(Stack *s, State state) {
    if (s->top < MAX_STATES - 1) {
        s->states[++s->top] = state;
    }
}

// Pop state from stack
State pop(Stack *s) {
    return s->states[s->top--];
}

// Check if stack is empty
bool isStackEmpty(Stack *s) {
    return s->top == -1;
}

// Check if state has been visited
bool isVisited(State states[], int count, int jug1, int jug2) {
    for (int i = 0; i < count; i++) {
        if (states[i].jug1 == jug1 && states[i].jug2 == jug2) {
            return true;
        }
    }
    return false;
}

// Print solution path
void printPath(State states[], int index) {
    if (index == -1) {
        return;
    }
    
    printPath(states, states[index].parent);
    printf("(%d, %d)\n", states[index].jug1, states[index].jug2);
}

// Solve using DFS
void solveDFS() {
    Stack s;
    State states[MAX_STATES];
    int count = 0;
    bool found = false;
    bool visited[MAX_CAPACITY_JUG1+1][MAX_CAPACITY_JUG2+1] = {false};
    
    initStack(&s);
    
    // Add initial state (0,0)
    states[count].jug1 = 0;
    states[count].jug2 = 0;
    states[count].parent = -1;
    push(&s, states[count]);
    count++;
    visited[0][0] = true;
    
    while (!isStackEmpty(&s) && !found) {
        State current = pop(&s);
        
        // Check if target is reached
        if (current.jug1 == TARGET_AMOUNT || current.jug2 == TARGET_AMOUNT) {
            printf("Solution found using DFS!\n");
            printf("Path from initial state (0,0) to target:\n");
            int currentIndex = -1;
            
            // Find the index of the current state in the states array
            for (int i = 0; i < count; i++) {
                if (states[i].jug1 == current.jug1 && states[i].jug2 == current.jug2) {
                    currentIndex = i;
                    break;
                }
            }
            
            printPath(states, currentIndex);
            found = true;
            break;
        }
        
        // Store current state for reference
        int parentIndex = -1;
        for (int i = 0; i < count; i++) {
            if (states[i].jug1 == current.jug1 && states[i].jug2 == current.jug2) {
                parentIndex = i;
                break;
            }
        }
        
        // Fill jug1
        if (current.jug1 < MAX_CAPACITY_JUG1 && !visited[MAX_CAPACITY_JUG1][current.jug2]) {
            visited[MAX_CAPACITY_JUG1][current.jug2] = true;
            states[count].jug1 = MAX_CAPACITY_JUG1;
            states[count].jug2 = current.jug2;
            states[count].parent = parentIndex;
            push(&s, states[count]);
            count++;
        }
        
        // Fill jug2
        if (current.jug2 < MAX_CAPACITY_JUG2 && !visited[current.jug1][MAX_CAPACITY_JUG2]) {
            visited[current.jug1][MAX_CAPACITY_JUG2] = true;
            states[count].jug1 = current.jug1;
            states[count].jug2 = MAX_CAPACITY_JUG2;
            states[count].parent = parentIndex;
            push(&s, states[count]);
            count++;
        }
        
        // Empty jug1
        if (current.jug1 > 0 && !visited[0][current.jug2]) {
            visited[0][current.jug2] = true;
            states[count].jug1 = 0;
            states[count].jug2 = current.jug2;
            states[count].parent = parentIndex;
            push(&s, states[count]);
            count++;
        }
        
        // Empty jug2
        if (current.jug2 > 0 && !visited[current.jug1][0]) {
            visited[current.jug1][0] = true;
            states[count].jug1 = current.jug1;
            states[count].jug2 = 0;
            states[count].parent = parentIndex;
            push(&s, states[count]);
            count++;
        }
        
        // Pour jug1 to jug2
        if (current.jug1 > 0 && current.jug2 < MAX_CAPACITY_JUG2) {
            int pour = (current.jug1 + current.jug2 <= MAX_CAPACITY_JUG2) ? 
                        current.jug1 : MAX_CAPACITY_JUG2 - current.jug2;
            int newJug1 = current.jug1 - pour;
            int newJug2 = current.jug2 + pour;
            
            if (!visited[newJug1][newJug2]) {
                visited[newJug1][newJug2] = true;
                states[count].jug1 = newJug1;
                states[count].jug2 = newJug2;
                states[count].parent = parentIndex;
                push(&s, states[count]);
                count++;
            }
        }
        
        // Pour jug2 to jug1
        if (current.jug2 > 0 && current.jug1 < MAX_CAPACITY_JUG1) {
            int pour = (current.jug1 + current.jug2 <= MAX_CAPACITY_JUG1) ? 
                        current.jug2 : MAX_CAPACITY_JUG1 - current.jug1;
            int newJug1 = current.jug1 + pour;
            int newJug2 = current.jug2 - pour;
            
            if (!visited[newJug1][newJug2]) {
                visited[newJug1][newJug2] = true;
                states[count].jug1 = newJug1;
                states[count].jug2 = newJug2;
                states[count].parent = parentIndex;
                push(&s, states[count]);
                count++;
            }
        }
    }
    
    if (!found) {
        printf("No solution found using DFS!\n");
    }
}

int main() {
    printf("Water Jug Problem - DFS Solution\n");
    printf("Jug 1 capacity: %d, Jug 2 capacity: %d, Target: %d\n\n", 
           MAX_CAPACITY_JUG1, MAX_CAPACITY_JUG2, TARGET_AMOUNT);
    
    solveDFS();
    
    return 0;
}
