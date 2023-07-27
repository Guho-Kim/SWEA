#include<iostream>
using namespace std;
#define MAX_POWER 100

struct Node{
	int power;
	Node* next;
};
Node* graph[MAX_POWER];

Node nodePool[10000];
int nodeCount;

Node* getNode(int power) {
	nodePool[nodeCount].power = power;
	nodePool[nodeCount].next = nullptr;
	return &nodePool[nodeCount++];
}

void addNode(int parent, int child) {
	Node* tempNode = graph[parent]->next;
	graph[parent]->next = getNode(child);
	graph[parent]->next->next = tempNode;

}


void dfs_init(int N, int path[100][2])
{
	nodeCount = 0;
	for (int i = 0; i < MAX_POWER; i++) {
		graph[i] = getNode(i);
	}

	for (int i = 0; i < N - 1; i++) {

		addNode(path[i][0], path[i][1]);
//		cout << path[i][0] << "->" << path[i][1] << endl;
	}

}


int dfs(int n) {
	bool visited[MAX_POWER] = { false };
	int king = n;
	int Stack[MAX_POWER];
	int top = -1;
	Node* nextNode;
	Node* currNode;

	Stack[++top] = n;

	while (top != -1) {
		int curr = Stack[top--];
		if (!visited[curr]) {
			visited[curr] = true;
			if (curr > king) {
				return curr;
			}
			currNode = graph[curr];
			
			while (currNode->next != nullptr) {;
				nextNode = currNode->next;

				if (!visited[nextNode->power]) {
					Stack[++top] = nextNode->power;
				}
				currNode = nextNode;

			}

		}
	}
	return -1;
}