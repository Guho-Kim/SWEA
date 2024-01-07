// [SWEA] No 8898. 3차원 농부
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
#define INT_MAX 2147483647

constexpr int MAXN = 500000;
int N, M;
int cows[MAXN + 1];

void solve()
{
    int c1, c2;
    cin >> N >> M;
    cin >> c1 >> c2;
    int dx = abs(c1 - c2);
    for (int i = 0; i < N; i++) cin >> cows[i];
    sort(cows, cows + N);

    int min = INT_MAX;
    int cnt = 0;

    for (int i = 0; i < M; i++){
        int horse; cin >> horse;
        int cowIdx = lower_bound(cows, cows + N, horse) - cows;
        if (cows[cowIdx] == horse){
            if (min > 0){
                min = 0;
                cnt = 1;
            }else if (min == 0){
                cnt++;
            }
        }
        else{
            if (cowIdx < N){
                int dz = abs(horse - cows[cowIdx]);
                if (min > dz)
                    min = dz, cnt = 1;
                else if (min == dz)
                    cnt++;
            }
            if (cowIdx != 0){
                int dz = abs(horse - cows[cowIdx - 1]);
                if (min > dz)
                    min = dz, cnt = 1;
                else if (min == dz)
                    cnt++;
            }
        }
    }
    cout<<min+dx<<' '<<cnt;
}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc)
    {
        cout << '#' << tc << ' ';
        solve();
        cout << '\n';
    }
    return 0;
}