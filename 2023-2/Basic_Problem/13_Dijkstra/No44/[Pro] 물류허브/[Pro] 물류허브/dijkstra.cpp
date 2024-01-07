/*

#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
using namespace std;
typedef unsigned long long ull;
#define MAX_N 701
#define INF 1000000000

int arr[MAX_N][MAX_N];
int dist[MAX_N][MAX_N];
int cnt;

unordered_map<ull, int> hashMap;

void dijkstra(int start) {
    priority_queue< pair< int, int>> pq;
    for (int i = 1; i <= cnt; i++) {
        dist[start][i] = INF;
    }

    dist[start][start] = 0;
    pq.push({ 0,start }); // {dist, destination}
    while (!pq.empty()) {
        int cur_dist = -pq.top().first;
        int cur_node = pq.top().second;
        pq.pop();
        for (int i = 1; i <= cnt; i++) {
            int nxt_dist = cur_dist + arr[cur_node][i];
            if (nxt_dist < dist[start][i])
            {
                dist[start][i] = nxt_dist;
                pq.push({ -nxt_dist,i });
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

    for (int i = 1; i <= cnt; i++) for (int j = 1; j <= cnt; j++) arr[i][j] = INF;
    for (int i = 0; i < N; i++) arr[hashMap[sCity[i]]][hashMap[eCity[i]]] = mCost[i];
    for (int i = 1; i <= cnt; i++) dijkstra(i);
    return cnt;
}

void add(int sCity, int eCity, int mCost) {
    arr[hashMap[sCity]][hashMap[eCity]] = mCost;
    for (int i = 1; i <= cnt; i++) dijkstra(i);
	return;
}
void view() {for (int i = 1; i <= cnt; i++) {for (int j = 1; j <= cnt; j++) {cout << dist[i][j] << " ";}cout << "\n";}}

int cost(int mHub) {
    
    int sum = 0;
    for (int i = 1; i <= cnt; i++) sum += dist[hashMap[mHub]][i] + dist[i][hashMap[mHub]];

	return sum;
}

*/