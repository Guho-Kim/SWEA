// [SWEA] No 1251. [S/W 문제해결 응용] 4일차 - 하나로
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#define MAX_N 1000
using namespace std;

vector<pair<int, int>> islands;

struct Edge{
    int u, v;
    long long squreDistance;
};

int parent[MAX_N];


long long makeSqureDistance(int x1, int y1, int x2, int y2){
    long long dx = x1-x2;
    long long dy = y1-y2;
    long long squreDistance = dx*dx+dy*dy;
    return squreDistance;
}

bool compareEdges(const Edge& e1, const Edge& e2){
    return e1.squreDistance < e2.squreDistance;
}

int findParent(int u){
    if(parent[u]==u) return u;
    else return findParent(parent[u]);
}

void unionIsland(int u, int v){
    u = findParent(u);
    v = findParent(v);
    if (u != v) parent[v] = u;

}

int main(int argc, char **argv)
{
    int z=0;
    int test_case;
    int T;
    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case)
    {
        int N;
        double E;
        double totalCost=0;
        long long squreDistance;
        vector<Edge> edges;
        
        cin >> N;

        for (int i = 0; i < N; i++) {
            parent[i] = i;
        }
        for (int i = 0; i < N; i++)
        {
            int x;
            cin >> x;
            islands.push_back({x, 0});
        }
        for (int i = 0; i < N; i++)
        {
            int y;
            cin >> y;
            islands[i].second=y;
        }

        cin >> E;

        for(int u=0; u<N; u++){
            for(int v=u+1; v<N; v++){
                squreDistance = makeSqureDistance(islands[u].first, islands[u].second, islands[v].first, islands[v].second);
                edges.push_back({u, v, squreDistance});
            }
        }
        // 오름차순으로 정렬
        sort(edges.begin(), edges.end(), compareEdges);

        for(const auto edge : edges){
            if(findParent(edge.u) != findParent(edge.v)){
                unionIsland(edge.u, edge.v);
                totalCost += (double)edge.squreDistance*E;
            }
        }

        cout << "#" << test_case << " " << totalCost << endl;
        islands.clear();

    }
    return 0;
}