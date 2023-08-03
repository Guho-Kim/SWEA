// [SWEA] No 3316. 동아리실 관리하기

#include <iostream>
#include <cstring>
using namespace std;

const int MOD = 1000000007;
const int MAX_N = 10000;
const int MAX_STATE = 16;

int countClubActivities(int N, string str) {
    int dp[MAX_N][MAX_STATE]; // DP 배열
    memset(dp, 0, sizeof(dp));

    int key[MAX_N+1];

    for(int i=1; i<=N; i++){
        switch(str[i-1]){
            case 'A': key[i]=1; break;
            case 'B': key[i]=2; break;
            case 'C': key[i]=4; break;
            case 'D': key[i]=8; break;
        }
    }

    // 초기값 설정
    for(int i=1; i<MAX_STATE; i++){
        if(i & 1 && i & key[1]) dp[1][i] = 1;
    }

    // 2번째 날부터
    for(int i=2; i<=N; i++){
        for(int curr=1; curr< MAX_STATE; curr++){
            if(key[i] & curr){
                for(int prev = 1; prev < MAX_STATE; prev++){
                        if(key[i-1] & prev){
                            if(prev & curr){
                                dp[i][curr] = (dp[i][curr] + dp[i-1][prev]) % MOD;
                            }
                        }
                }
            }
        }
    }

    int totalCases = 0;
    for (int state = 1; state < MAX_STATE; ++state) {
        totalCases = (totalCases + dp[N][state]) % MOD;
    }

    return totalCases;
}

int main() {
    string str;
    cin >> str;

    int result = countClubActivities(str.length(), str);
    cout << result << endl;

    return 0;
}
