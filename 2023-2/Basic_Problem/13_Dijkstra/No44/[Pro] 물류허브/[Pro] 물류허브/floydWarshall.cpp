/*
#include<iostream>
#include<unordered_map>
using namespace std;
typedef unsigned long long ull;
#define MAX_N 1410
#define INF 1000000000

int dist[MAX_N][MAX_N];
int cnt;

unordered_map<ull, int> hashMap;

void floydWarshall() {
    for (int k = 1; k <= cnt; k++) {
        for (int i = 1; i <= cnt; i++) {
            for (int j = 1; j <= cnt; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
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

    for (int i = 1; i <= cnt; i++) for (int j = 1; j <= cnt; j++) dist[i][j] = INF;
    for (int i = 1; i <= cnt; i++) dist[i][i] = 0;
    for (int i = 0; i < N; i++) dist[hashMap[sCity[i]]][hashMap[eCity[i]]] = mCost[i];
    floydWarshall();
    return cnt;
}

void add(int sCity, int eCity, int mCost) {
    dist[hashMap[sCity]][hashMap[eCity]] = mCost;
    floydWarshall();
    
    for (int i = 1; i <= cnt; i++) {
        for (int j = 1; j <= cnt; j++) {
            if (dist[hashMap[sCity]][i] + dist[hashMap[i]][hashMap[sCity]] < dist[i][j]) {
                dist[i][j] = dist[i][hashMap[sCity]] + dist[hashMap[sCity]][j];
            }
        }
    }
    
    return;
}

int cost(int mHub) {
    //floydWarshall();
    int sum = 0;
    for (int i = 1; i <= cnt; i++) sum += dist[hashMap[mHub]][i] + dist[i][hashMap[mHub]];

    return sum;
}
*/