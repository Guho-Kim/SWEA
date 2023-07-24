#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_NODES 400
#define MAX_INT 2147483647

typedef struct Node {
    int dest;
    int weight;
    struct Node* next;
} Node;

typedef struct LinkedList {
    Node* head;
} LinkedList;

typedef struct {
    LinkedList* List;
    int inDegree[MAX_NODES + 1];
    int numNode;
    int numPath;
} Graph;

bool visited[MAX_NODES + 1];
int minWeight;

void resetGraph(Graph* graph) {
    for (int i = 1; i <= graph->numNode; i++) {
        graph->List[i].head = NULL;
        graph->inDegree[i] = 0;
    }
}

void freeLinkedLists(Graph* graph) {
    for (int i = 1; i <= graph->numNode; i++) {
        Node* current = graph->List[i].head;
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->List);
}

void resetVisited() {
    for (int i = 1; i <= MAX_NODES; i++) {
        visited[i] = false;
    }
}

void setGraph(Graph* graph) {
    int x, y, c;

    for (int i = 0; i < graph->numPath; i++) {
        scanf("%d %d %d", &x, &y, &c);

        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->dest = y;
        newNode->weight = c;
        newNode->next = NULL;

        graph->inDegree[y]++;

        if (graph->List[x].head == NULL) {
            graph->List[x].head = newNode;
        } 
        else {
            Node* current = graph->List[x].head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }
    }
}

void dfs(Graph* graph, int currentNode, int startNode, int currentWeight) {
    if (graph->inDegree[startNode] == 0) return;

    visited[currentNode] = true;

    Node* current = graph->List[currentNode].head;
    while (current != NULL) {
        int nextNode = current->dest;
        if (!visited[nextNode] || nextNode == startNode) {
            int nextWeight = currentWeight + current->weight;

            if (nextNode == startNode) {
                if (minWeight > nextWeight) minWeight = nextWeight;
            }
            else {
                dfs(graph, nextNode, startNode, nextWeight);
            }
        }
        current = current->next;
    }

    visited[currentNode] = false;
}

int main() {
    int test_case;
    int T;
    setbuf(stdout, NULL);
    scanf("%d", &T);

    Graph graph;
    resetVisited();

    for (test_case = 1; test_case <= T; ++test_case)
    {
        scanf("%d %d", &graph.numNode, &graph.numPath);

        // Allocate memory for LinkedLists
        graph.List = (LinkedList*)malloc((graph.numNode + 1) * sizeof(LinkedList));

        // Reset the graph
        resetGraph(&graph);


        // Set the graph
        minWeight = MAX_INT;
        setGraph(&graph);

        // Find the cycle
        for (int i = 1; i <= graph.numNode; i++) {
            dfs(&graph, i, i, 0);
        }

        if (minWeight == MAX_INT)
            minWeight = -1;
        printf("#%d %d\n", test_case, minWeight);

        freeLinkedLists(&graph);
    }

    return 0;
}
