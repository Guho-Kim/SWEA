/*
No. 17 영준이의 진짜 BFS
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