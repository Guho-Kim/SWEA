// [SWEA] No 8935. 스팟마트
#include<iostream>
#include<algorithm>
using namespace std;
#define MAXN 3000
#define MAXM 100
#define FOR(i, n) for(int (i)=0; (i)<(n); ++(i))
#define FOR1(i, n) for(int (i)=1; (i)<=(n); ++(i))
int A[MAXN+1], B[MAXM+1];
int dp[MAXN+1][MAXM+1];

int solve(){
    int N; cin >> N; for(int i=0; i<N; ++i) cin >> A[i];
    int M; cin >> M; for(int i=0; i<M; ++i) cin >> B[i];
    dp[0][0]=0;
    for(int i=0; i<=MAXN; ++i) for(int j=0; j<=MAXM; ++j) dp[i][j]=0;
    
    for(int i=1; i<=N; ++i){
        for(int j=1; j<=M; ++j){
            for(int k=1; k<=j; k++){
                /*
                    j개 B 과자를 넣을 때, max를 찾기 위해 for loop을 돌아야 함.
                */
                dp[i][j]=max(dp[i-1][j], A[i]+dp[i-1][j]);

            }
        }
    }
    



}






int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int tc, T; cin>>T;
    FOR1(tc, T) cout<<"#"<<tc<<" "<<solve()<<endl;
    return 0;
}