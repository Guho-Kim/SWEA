
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;
typedef unsigned long long ull;
#define MAX_N 1410
#define INF 1000000000

int arr[MAX_N][MAX_N];
int dist[MAX_N][MAX_N];
int cnt;

unordered_map<ull, int> hashMap;

void dijkstra(int start, int target) {
    bool visited[MAX_N] = { false };
    for (int i = 1; i <= cnt; i++) {
        dist[start][i] = arr[start][i];
    }

    dist[start][start] = 0;
    for (int k = 0; k < cnt; k++) {
        int minDist = INF;
        int cur_node = -1;
        for (int i = 1; i <= cnt; i++) {
            if (!visited[i] && dist[start][i] < minDist) {
                minDist = dist[start][i];
                cur_node = i;
            }
        }

        if (cur_node == -1) break; // All nodes are visited
        if (cur_node == target && start != target) break;
        visited[cur_node] = true;

        for (int i = 1; i <= cnt; i++) {
            int nxt_dist = minDist + arr[cur_node][i];
            if (nxt_dist < dist[start][i]) {
                dist[start][i] = nxt_dist;
            }
        }
    }

}

int init(int N, int sCity[], int eCity[], int mCost[]) {
    cnt = 1;
    hashMap.clear();
    for (int i = 0; i < N; i++) {
        if (hashMap.insert({ sCity[i], cnt }).second) cnt++;
        if (hashMap.insert({ eCity[i], cnt }).second) cnt++;
    }
    --cnt;

    for (int i = 1; i <= cnt; i++)
        for (int j = 1; j <= cnt; j++)
            arr[i][j] = INF;
    for (int i = 0; i < N; i++)
        arr[hashMap[sCity[i]]][hashMap[eCity[i]]] = mCost[i];

    return cnt;
}

void add(int sCity, int eCity, int mCost) {
    arr[hashMap[sCity]][hashMap[eCity]] = mCost;
    return;
}
void view() { for (int i = 1; i <= cnt; i++) { for (int j = 1; j <= cnt; j++) { cout << dist[i][j] << " "; }cout << "\n"; } }

int cost(int mHub) {
    int sum = 0;
    for (int i = 1; i <= cnt; i++) {
        dijkstra(i, mHub);
    }
    for (int i = 1; i <= cnt; i++) sum += dist[hashMap[mHub]][i] + dist[i][hashMap[mHub]];

    return sum;
}
