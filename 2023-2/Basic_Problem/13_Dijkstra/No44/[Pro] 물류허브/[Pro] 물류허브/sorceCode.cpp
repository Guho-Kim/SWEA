/*
#include <unordered_map>
#include <cstring>
#include <queue>
using namespace std;
#define MAXC 610
constexpr auto INF = 999999;
#define rint register int
int c_idx;
using pii = pair<int, int>;

vector<pii>weight[MAXC];
vector<pii>rweight[MAXC];

priority_queue< pii, vector<pii>, greater<pii>> pq;
unordered_map <int, int > chash;

int dist[MAXC];
int visit[MAXC];
int dijkstra(vector<pii>map[MAXC], int start)
{
    for (rint i = 1; i <= c_idx; i++) {
        dist[i] = INF;
        visit[i] = 0;
    }
    dist[start] = 0;
    pq.push({ 0,start });
    while (!pq.empty())
    {
        auto it = pq.top(); pq.pop();

        int from = it.second;
        if (visit[from]) continue;
        visit[from] = 1;
        for (auto e : map[from])
        {
            int to = e.second;
            int cost = e.first;
            if (!visit[to] && dist[to] > dist[from] + cost)
            {
                dist[to] = dist[from] + cost;
                pq.push({ dist[to] ,to });

            }
        }
    }
    int sum = 0;
    for (rint i = 1; i <= c_idx; i++) sum += dist[i];
    return sum;
}


int init(int N, int sCity[], int eCity[], int mCost[]) {
    chash.clear();
    c_idx = 0;
    for (rint i = 0; i < MAXC; i++) {
        weight[i].clear();
        rweight[i].clear();
    }
    for (rint i = 0; i < N; i++)
    {
        int sid = chash[sCity[i]];
        if (sid == 0) sid = chash[sCity[i]] = ++c_idx;
        int eid = chash[eCity[i]];
        if (eid == 0) eid = chash[eCity[i]] = ++c_idx;
        weight[sid].push_back({ mCost[i],eid });
        rweight[eid].push_back({ mCost[i],sid });
    }
    return c_idx;
}
void add(int sCity, int eCity, int mCost) {
    int sid = chash[sCity];
    int eid = chash[eCity];
    weight[sid].push_back({ mCost,eid });
    rweight[eid].push_back({ mCost,sid });

}

int cost(int mHub) {
    int sum = 0;
    int hid = chash[mHub];
    return dijkstra(weight, hid) + dijkstra(rweight, hid);
}

*/