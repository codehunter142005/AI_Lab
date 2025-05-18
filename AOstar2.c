#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 100
#define MAX_CHILDREN 10
#define INF INT_MAX

typedef enum { OR_NODE, AND_NODE } NodeType;

typedef struct Node {
    int id;
    NodeType type;
    int heuristic; 
    int solved;    
    int cost;   
    int num_children;
    struct Node* children[MAX_CHILDREN];
} Node;

Node* create_node(int id, NodeType type, int heuristic);
void add_child(Node* parent, Node* child);
int ao_star(Node* node);
void print_solution(Node* node);

int main() {
    Node* n1 = create_node(1, OR_NODE, 5);
    Node* n2 = create_node(2, AND_NODE, 3);
    Node* n3 = create_node(3, OR_NODE, 4);
    Node* n4 = create_node(4, OR_NODE, 2);
    Node* n5 = create_node(5, OR_NODE, 6);
    Node* n6 = create_node(6, OR_NODE, 1);

    add_child(n1, n2);
    add_child(n1, n3);

    add_child(n2, n4);
    add_child(n2, n5);

    add_child(n3, n6);

    int cost = ao_star(n1);

    printf("Minimum cost solution graph has cost: %d\n", cost);
    printf("Solution graph nodes:\n");
    print_solution(n1);

    return 0;
}

Node* create_node(int id, NodeType type, int heuristic) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->id = id;
    node->type = type;
    node->heuristic = heuristic;
    node->solved = 0;
    node->cost = heuristic;
    node->num_children = 0;
    for (int i = 0; i < MAX_CHILDREN; i++) {
        node->children[i] = NULL;
    }
    return node;
}

void add_child(Node* parent, Node* child) {
    if (parent->num_children < MAX_CHILDREN) {
        parent->children[parent->num_children++] = child;
    } else {
        printf("Max children exceeded for node %d\n", parent->id);
    }
}

int ao_star(Node* node) {
    if (node->solved) {
        return node->cost;
    }

    if (node->num_children == 0) {
        node->solved = 1;
        return node->cost;
    }

    if (node->type == OR_NODE) {
        int min_cost = INF;
        Node* best_child = NULL;
        for (int i = 0; i < node->num_children; i++) {
            int child_cost = ao_star(node->children[i]);
            if (child_cost < min_cost) {
                min_cost = child_cost;
                best_child = node->children[i];
            }
        }
        node->cost = min_cost;
        node->solved = 1;
        return node->cost;
    } else if (node->type == AND_NODE) {
        int total_cost = 0;
        for (int i = 0; i < node->num_children; i++) {
            total_cost += ao_star(node->children[i]);
        }
        node->cost = total_cost;
        node->solved = 1;
        return node->cost;
    }

    return INF; 
}

void print_solution(Node* node) {
    if (node == NULL) return;
    printf("Node %d (Cost: %d, Type: %s)\n", node->id, node->cost,
           node->type == OR_NODE ? "OR" : "AND");
    for (int i = 0; i < node->num_children; i++) {
        print_solution(node->children[i]);
    }
}
