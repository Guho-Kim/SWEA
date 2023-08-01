// [SWEA] No 4006. [Professional] 고속도로 건설 2


#include <iostream>
#include <queue>
#define MAX_N 50000

using namespace std;
struct Node{
    int u, v, cost;
};

struct cmp{
    bool operator()(const Node& n1, const Node& n2){
        return n1.cost > n2.cost;
    }
};

priority_queue<Node, vector<Node>, cmp> pq;

int parent[MAX_N+1];

void init(int N){
    for(int i=1; i<=N; i++){
        parent[i]=i;
    }
}


int findParent(int node) {
    if (parent[node] == node)
        return node;
    return parent[node] = findParent(parent[node]);
}

void unionNodes(int a, int b) {
    a = findParent(a);
    b = findParent(b);
    if (a != b)
        parent[b] = a;
}


int main(int argc, char **argv)
{
    int test_case;
    int T;
    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case)
    {
        int N, M;
        int s, e, c;
        int totalCost=0;
        cin >> N;
        init(N);

        cin >> M;
        for(int i=0; i<M; i++){
            cin >> s >> e >> c;
            pq.push({s,e,c});
        }

        while(!pq.empty()){
            Node node = pq.top();
            pq.pop();
            if(findParent(node.u) != findParent(node.v)){
                unionNodes(node.u, node.v);
                totalCost+= node.cost;
            }
        }

        cout << "#" << test_case << " " << totalCost << endl;

    }
    return 0;
}