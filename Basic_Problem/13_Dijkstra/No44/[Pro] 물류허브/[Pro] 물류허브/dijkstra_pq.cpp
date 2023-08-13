#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;
using pii = pair<int, int>;

#define MAX_N 601
#define INT_MAX 1000000000

int arr[MAX_N][MAX_N];
int cityNum;
vector<pii> weight[MAX_N];
vector<pii> rweight[MAX_N];

unordered_map<int, int> hashMap;

int dist[MAX_N];
bool visited[MAX_N];

int dijkstra(int start, vector<pii> map[MAX_N]) {
    priority_queue< pii, vector<pii>, greater<>> pq;        //cost, next
    for (int i = 1; i <= cityNum; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }
    dist[start] = 0;
    pq.push({ 0, start });
    while (!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        int cur_dist = cur.first;
        int cur_node = cur.second;

        if (visited[cur_node]) continue;
        visited[cur_node] = true;

        for (auto next : map[cur_node]) {
            int next_dist = next.first;
            int next_node = next.second;
            if (dist[next_node] > dist[cur_node] + next_dist) {
                dist[next_node] = dist[cur_node] + next_dist;
                pq.push({ dist[next_node] , next_node });
            }
        }
    }
    int sum = 0;
    for (int i = 1; i <= cityNum; i++) sum += dist[i];
    return sum;
}

int init(int N, int sCity[], int eCity[], int mCost[]) {
    cityNum = 0;
    hashMap.clear();
    for (int i = 0; i < MAX_N; i++) {
        weight[i].clear();
        rweight[i].clear();
    }
    for (int i = 0; i < N; i++) {
        if (hashMap[sCity[i]] == 0) hashMap[sCity[i]] = ++cityNum;
        if (hashMap[eCity[i]] == 0) hashMap[eCity[i]] = ++cityNum;
        weight[hashMap[sCity[i]]].push_back({ mCost[i], hashMap[eCity[i]] });
        rweight[hashMap[eCity[i]]].push_back({ mCost[i], hashMap[sCity[i]] });
    }
    return cityNum;
}

void add(int sCity, int eCity, int mCost) {
    weight[hashMap[sCity]].push_back({ mCost, hashMap[eCity] });
    rweight[hashMap[eCity]].push_back({ mCost, hashMap[sCity] });
}

int cost(int mHub) {
    return dijkstra(hashMap[mHub], weight) + dijkstra(hashMap[mHub], rweight);
}
