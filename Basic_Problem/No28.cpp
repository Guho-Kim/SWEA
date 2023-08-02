// [SWEA] No 8935. 스팟마트
/*
    dp[n][m][mp][take]
    n : 현재까지 take한 N과자 수
    m : 현재까지 take한 M과자 수
    mp : 현재까지 non take한 M과자 수
    take : 현재 과자를 take할지 말지
*/
#include<iostream>
#include<algorithm>
using namespace std;
#define MAXN 3000
#define MAXM 100
int A[MAXN+1], B[MAXM+1], dp[MAXN+1][MAXM+1][MAXM+1][2];
bool cmp(int a, int b) {return a > b;}
int solve(){
    int N; cin >> N; for(int i=1; i<=N; ++i) cin >> A[i];
    int M; cin >> M; for(int i=1; i<=M; ++i) cin >> B[i]; sort(&B[1],B+M+1, cmp);
    for(int i=0; i<=N; ++i) {
        for(int j=0; j<=M; ++j) {
            for(int k=0; k<=M; ++k){
                dp[i][j][k][0]=0;
                dp[i][j][j][1]=0;  
            } 
        }
    }
    int Max;
    for(int i=0; i<=N; ++i){
        for(int j=0; j<=M; ++j){
            for(int k=0; k<=M-j; ++k){
                Max=0;
                if(i) Max = max(dp[i-1][j][k][0], dp[i-1][j][k][1]);
                if(k) Max = max(Max, max(dp[i][j][k-1][0], dp[i][j][k-1][1]));
                dp[i][j][k][0] = Max;
                Max=0;
                if(i) Max=dp[i-1][j][k][0]+A[i];
                if(j) Max=max(Max, dp[i][j-1][k][0]+B[j]);
                dp[i][j][k][1] = Max;
            }
        }
    }
    int result=0;
    for(int j=0; j<=M; j++){
        result = max(result, max(dp[N][j][M-j][0], dp[N][j][M-j][1]));
    }
    return result;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int tc, T; cin>>T;
    for(tc=1; tc<=T; ++tc) cout<<"#"<<tc<<" "<<solve()<<endl;
    return 0;
}