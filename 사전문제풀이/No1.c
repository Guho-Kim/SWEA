#include <stdio.h>
#define MAX_NODES 400
#define MAX_INT 2147483647

typedef struct {
    int cost[MAX_NODES+1][MAX_NODES+1];
    int numNode;
    int numPath;
} Graph;

int visited[MAX_NODES+1];
int minWeight;

void resetGraph(Graph* graph, int adjList[][MAX_NODES+1]){
    for(int i=0; i<=MAX_NODES; i++){
        for(int j=0; j<=MAX_NODES; j++){
            graph->cost[i][j]=0;
            adjList[i][j]=0;
        }
    }
}
void resetVisited(){
    for(int i=0; i<=MAX_NODES; i++){
        visited[i]=0;
    }
}

void setGraph(Graph* graph, int adjList[][MAX_NODES+1]){
    int x, y, c;
    int count;

    for(int i=0; i < graph->numPath; i++){
        scanf("%d %d %d", &x, &y, &c);
        graph->cost[x][0]++;    // number of outPath
        graph->cost[x][y]=c;
    }

    // Set the AdjList
    for(int i=1; i<=graph->numNode; i++){
        count=0;
        for(int j=1; j<=graph->numNode; j++){
            if(graph->cost[i][j]!=0){
                adjList[i][count++]=j;
            }
        }
    }
}

void dfs(Graph* graph, int currentNode, int startNode, int currentWeight, int adjList[][MAX_NODES+1]){    
    int nextNode;
    int nextWeight;
    visited[currentNode]=1;

    for(int i=0; i<graph->cost[currentNode][0]; i++){
        if(!visited[adjList[currentNode][i]] || adjList[currentNode][i] == startNode){
            nextNode=adjList[currentNode][i];
            nextWeight = currentWeight + graph->cost[currentNode][nextNode];

            if(nextNode==startNode && minWeight > nextWeight){
                minWeight = nextWeight;
            }

            else{
                dfs(graph, nextNode, startNode, nextWeight, adjList);
            }
        }
    }
    visited[currentNode]=0;

}
int main(void)
{
	int test_case;
	int T;
	Graph graph;
    int adjList[MAX_NODES+1][MAX_NODES+1];
    
    setbuf(stdout, NULL);
	scanf("%d", &T);

    for (test_case = 1; test_case <= T; ++test_case)
	{
        resetVisited();
        // Reset the graph
        resetGraph(&graph, adjList);
        minWeight=MAX_INT;

        // Set the graph
        scanf("%d %d", &graph.numNode, &graph.numPath);
        setGraph(&graph,adjList);

        for(int i=1; i<=graph.numNode; i++){
            dfs(&graph, i, i, 0, adjList);
        }

        if(minWeight==MAX_INT) minWeight=-1;
        printf("#%d %d\n", test_case, minWeight);
 
	}
    
	return 0; //정상종료시 반드시 0을 리턴해야 합니다.
}