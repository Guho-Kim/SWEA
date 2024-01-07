#include <iostream>
#include <algorithm>

using namespace std;
const int INF=1e9;
const int MAX_R=50;
const int MAX_C=3;
const int MAX_M=1<<3;

void run(){
    int n; cin>>n;
    int galaxy[MAX_R][MAX_C];
    int total=0;
    for (int i=0; i<n; ++i) {
        for (int j=0; j<MAX_C; ++j) {
            cin >> galaxy[i][j];
            total+=galaxy[i][j];
        }
    }
    if(n<3){
        cout<<-1<<"\n";
        return;
    }
    int dp[MAX_R+1][MAX_M];
    for (int i=0; i<=n; ++i) {
        for (int j=0; j<MAX_M; ++j) {
            dp[i][j]=-INF;
        }
    }
    dp[0][0]=0;
    for (int i=1; i<=n; ++i) {
        for (int mask=0; mask<MAX_M; ++mask) {
            for (int j=0; j<MAX_C; ++j) {
                int nextMask=mask | (1<<j);
                dp[i][nextMask]=max(dp[i][nextMask], dp[i-1][mask] + galaxy[i-1][j]);
            }
        }
    }
    int maxSum=dp[n][MAX_M - 1];

    cout<<total-maxSum<<"\n";
}

int main() {
    int t, T; cin>>T;
    for(t=1; t<=T; ++t){
        cout<<"#"<<t<<" ";
        run();
    }
    return 0;
}
