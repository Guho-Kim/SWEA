// [SWEA] No 11446. 사탕 가방
#include<iostream>
#include<algorithm>
using namespace std;
typedef unsigned long long ull;
constexpr int MAXN=200;
ull N, M; 
ull candys[MAXN];

void solve(){
    cin>>N>>M;
    ull right;
    for(int i=1; i<=N; i++) {
        cin>>candys[i];
        right = max(right, candys[i]);
    }
    ull left=1; 
    ull maxBags=0;

    while(left<=right){
        ull numBags=0;
        ull mid = left + (right-left)/2;
        for(int i=1; i<=N; i++){numBags+=candys[i]/mid;}
        if(numBags < M){
            right=mid-1;
        }
        else{
            // 찾았을 때도 계속 오른쪽으로 이동해서 최댓값 찾기
            maxBags = mid;
            left=mid+1;
        }
    }
    cout<<maxBags;
    
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T; cin>>T;
    for(int tc=1; tc<=T; ++tc){
        cout<<'#'<<tc<<' ';
        solve();
        cout<<'\n';
    }
    return 0;
}