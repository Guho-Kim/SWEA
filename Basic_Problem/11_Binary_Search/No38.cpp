// [SWEA] No 9843. 촛불 이벤트
#include<iostream>
#include<cmath>
using namespace std;
typedef unsigned long long ull;


void solve(){
    ull n; cin>>n;
    ull left=1;
    ull right =sqrt(2*n);
    ull k;
    while(left<=right){
        ull mid = left + (right - left)/2;
        if(mid*(mid+1) == n*2){
            cout<<mid;
            return;
        }
        else if(mid*(mid+1) < n*2){
            left = mid+1;
        }else{
            right = mid-1;
        }
    }
    cout<<"-1";
}
int main(int argc, char** argv)
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int T;cin>>T;
	for(int tc = 1; tc <= T; ++tc){cout<<'#'<<tc<<' ';solve();cout<<'\n';}
	return 0;
}