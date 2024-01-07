#include <iostream>
#include <queue>

using namespace std;

constexpr int MAX_N = 1000;

int Graph[MAX_N][MAX_N];
bool visited[MAX_N];
typedef int dataType;
int N, E;

void bfs(int node)
{
    queue<dataType> Queue;
    Queue.push(node);

    while (!Queue.empty())
    {
        int curr = Queue.front();
        Queue.pop();

        if (!visited[curr])
        {
            // visited[curr] = true;
            /*
                Do something here with curr.
            */
            cout << curr << " ";
            for (int next = 0; next < N; ++next)
            {
                if (!visited[next] && Graph[curr][next])
                {
                    visited[next]=true;
                    Queue.push(next);
                }
            }
        }
    }
}

int main()
{
    freopen("graph_search_input.txt","r",stdin);   
    cin >> N >> E;
    for (int i = 0; i < N; i++)
    {
        visited[i] = false;
        for (int j = 0; j < N; j++)
        {
            Graph[i][j] = 0;
        }
    }
    for (int i = 0; i < E; i++)
    {
        int a, b;
        cin >> a >> b;
        Graph[a][b] = Graph[b][a] = 1;
    }
    bfs(0);
    return 0;
}
