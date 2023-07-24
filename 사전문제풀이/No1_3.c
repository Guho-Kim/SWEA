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

typedef struct {
    Node* head;
} LinkedList;

typedef struct {
    LinkedList List[MAX_NODES + 1];
    int inDegree[MAX_NODES + 1];
    int numNode;
    int numPath;
} Graph;

bool visited[MAX_NODES + 1];
int minWeight;

void resetGraph(Graph* graph) {
    for (int i = 1; i <= graph->numNode; i++) {
        graph->List[i].head = NULL;
        graph->inDegree[i]=0;
    }
    
}
void freeLinkedList(Graph* graph) {
    for(int i=1; i<=graph->numNode; i++){
        Node* current = graph->List[i].head;
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }

    }
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
        newNode->next = graph->List[x].head;
        graph->List[x].head = newNode;

        graph->inDegree[y]++;

    }
}



void dfs(Graph* graph, int currentNode, int startNode, int currentWeight) {
    if(graph->inDegree[startNode]==0) return;
    visited[currentNode] = true;

    Node* current = graph->List[currentNode].head;

    while (current != NULL) {
        int nextNode = current->dest;
        int nextWeight = currentWeight + current->weight;

        if ((!visited[nextNode] || nextNode == startNode) && (minWeight > nextWeight)) {
            if (nextNode == startNode) {
                if(minWeight > nextWeight) minWeight = nextWeight;
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
    // init_Graph(&graph);
    resetVisited();

    for (test_case = 1; test_case <= T; ++test_case)
	{
        scanf("%d %d", &graph.numNode, &graph.numPath);
        
        // Reset the graph
        resetGraph(&graph);
        
        // Set the graph
        minWeight = MAX_INT;
        setGraph(&graph);

        // Find the cycle
        for (int i = 1; i <= graph.numNode; i++) {
            if(graph.inDegree[i]!=0)
                dfs(&graph, i, i, 0);
        }

        if (minWeight == MAX_INT)
            minWeight = -1;
        printf("#%d %d\n", test_case, minWeight);
        
        freeLinkedList(&graph);
    }

    return 0;
}
