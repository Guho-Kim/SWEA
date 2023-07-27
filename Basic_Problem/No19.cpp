/*

    힙 강의 듣고 다시 풀어보기
    
*/

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#define MAX_N 50000



using namespace std;

struct Edge{
    int u, v;
    long cost;
};
vector<Edge> edges(MAX_N);

int parent[MAX_N+1];

bool compareEdges(const Edge& e1, const Edge& e2){
    return e1.cost < e2.cost;
}

int findParent(int u){
    if(parent[u]==u) return u;
    return parent[u] = findParent(parent[u]);
}

void unionIsland(int u, int v){
    u = findParent(u);
    v = findParent(v);
    if (u != v) parent[v] = u;

}

int main(int argc, char **argv)
{
    int test_case;
    int T;
    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case)
    {
        int N, M;
        int totalCost=0;
        //vector<Edge> edges;

        
        cin >> N;
        cin >> M;
        priority_queue<Edge> edges;

        for(int i=0; i<M; i++){
            edges
        }


        /*
        edges.clear();
        for(int i=0; i<M; i++){
            int u, v, c;
            cin >> u >> v >> c;
            edges.push_back({u, v, c});
        }

        // 오름차순으로 정렬
        sort(edges.begin(), edges.end(), compareEdges);
        */
        for (int i = 1; i <= N; i++) {
            parent[i] = i;
        }

        for(const auto edge : edges){
            if(findParent(edge.u) != findParent(edge.v)){
                unionIsland(edge.u, edge.v);
                totalCost += edge.cost;
            }
        }

        cout << "#" << test_case << " " << totalCost << endl;

    }
    return 0;
}