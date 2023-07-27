/*
No. 17 영준이의 진짜 BFS
시간 : 61개 테스트케이스를 합쳐서 C/C++의 경우 4초 / Java의 경우 8초
메모리 : 힙, 정적 메모리 합쳐서 256MB 이내, 스택 메모리 1MB 이내
※ SW Expert 아카데미의 문제를 무단 복제하는 것을 금지합니다.

영준이는 루트가 있는 트리에서 BFS(Breadth First Search)를 하려고 한다.

트리는 1에서 N까지의 번호가 붙은 N개의 노드로 이루어져 있으며, 1이 루트이자 동시에 탐색 시작점이다.

BFS는 큐를 이용하여 탐색을 하는데, 큐의 가장 앞에 있는 노드를 뽑아 탐색을 하고, 탐색을 하는 노드의 자식들을 작은 번호부터 순서대로 큐의 뒤쪽에 넣는 방식으로 탐색이 진행된다.

이것은 컴퓨터에서 실제로 진행되는 방식이 아니고 영준이가 직접 노드를 방문해야 하기 때문에, BFS를 한다면 노드를 방문하는 순서가 정해질 것이고 영준이는 그 순서를 따라 최단거리로 트리를 이동하여 모든 노드를 탐색한다.

영준이는 과연 몇 개의 간선을 지나고 나서야 탐색을 끝 마칠 수 있을까?


[입력]

첫 번째 줄에 테스트 케이스의 수 T가 주어진다.

각 테스트 케이스의 첫 번째 줄에는 자연수 N(1 ≤ N ≤ 105)이 주어진다.

두 번째 줄에는 각 노드의 부모정점을 의미하는 N-1개의 자연수가 공백으로 구분되어 주어진다. 1번 노드는 루트이므로 부모가 없어 생략된다.

i-1(2 ≤ i ≤ N)번째로 주어지는 수는 i번 노드의 부모 pi (1 ≤ pi < i)이다. 즉 i번 노드의 부모의 번호는 i보다 작다.


[출력]

각 테스트 케이스마다 ‘#x ’(x는 테스트케이스 번호를 의미하며 1부터 시작한다)를 출력하고,

직접 BFS를 하였을 때 지나게 되는 총 간선의 개수를 출력한다.


[예제 풀이]

아래 그림은 첫 번째 테스트 케이스에서 각 노드를 BFS로 방문할 때의 이동 거리를 나타낸다.
*/

#include <iostream>
#include <vector>
#include <queue>
#define MAX_N 100001
#define LOG_N 17    // 2^17(131,072) > MAX_N

using namespace std;

vector<int> vec[MAX_N];
int Parent[MAX_N][LOG_N+1];
int depth[MAX_N];

void makeParent(int N){
    for(int i=1; i<LOG_N; i++){
        for(int j=1; j<=N; j++){
            Parent[j][i] = Parent[Parent[j][i-1]][i-1];
        }
    }
}

void makeDepth(int N)
{
    depth[1] = 0;
    for (int i = 2; i <= N; i++)
    {
        depth[i] = depth[Parent[i][0]] + 1;
    }
}

int diff(int a, int b){
    int temp = a-b;
    if (temp > 0) return temp;
    else{
        temp*= -1;
        return temp;
    }
}

// 공통 조상 찾기
int LCA(int a, int b){
    // 항상 b가 더 큼
    if(depth[a] > depth[b]){
        int temp =a;
        a=b;
        b=a;
    }

    // 깊이 맞추기
    for(int i=LOG_N; i>=0; i--){
        if(diff(depth[b],depth[a]) >= (1<<i)){
            b = Parent[b][i];
        }
    }
    if(a==b) {
        return b;
    }

    for(int i=LOG_N; i>=0; i--){
        if(Parent[a][i] != Parent[b][i]){
            a=Parent[a][i];
            b=Parent[b][i];
        }
    }
    return Parent[b][0];

}


long long bfs(int N)
{
    long long count = 0;
    int currDepth = 1;
    int curr, prev, lca;
    queue<int> q;
    prev = 1;
    for (auto iter = vec[1].begin(); iter != vec[1].end(); iter++) q.push(*iter);
    while (!q.empty())
    {
        curr = q.front();
        q.pop();

        lca= LCA(prev, curr);
        count += (depth[curr]+depth[prev]-2*depth[lca]);

        for (auto iter = vec[curr].begin(); iter != vec[curr].end(); iter++)
        {
            q.push(*iter);
        }
        prev = curr;

    }
    return count;
}

int main()
{

    int T;
    long long totalCount;
    cin >> T;
    for (int test_case = 1; test_case <= T; test_case++)
    {
        int N;
        cin >> N;


        for (int i = 2; i <= N; i++)
        {
            cin >> Parent[i][0];            // i 의 부모
            vec[Parent[i][0]].push_back(i); // parent[i][0]의 자식 i
        }

        // make 2^ith parent
        makeParent(N);
        makeDepth(N);

        totalCount = bfs(N);
        for (int i = 1; i < N; i++)
            vec[i].clear();

        cout << "#" << test_case << " " << totalCount << endl;
    }

    return 0;
}