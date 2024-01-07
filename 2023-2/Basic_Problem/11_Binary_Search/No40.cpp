// [SWEA] No 9999. 광고 시간 정하기
#include<iostream>
#include<algorithm>
using namespace std;
constexpr int MAXN=100000;
int s[MAXN+1], e[MAXN+1], accumulated[MAXN+1];
int N, L; 
int getIndex(int target){

    int start=1, end=N;
    if(target>e[end]) return end;
    int mid;
    while(end!=start){
        mid=start+(end-start)/2;
        if(e[mid]>target){
            end=mid;
        }else{
            start=mid+1;
        }
    }
    return end-1;
}
int solve(){
    cin>>L>>N;
    int result, sum, start, end, idx;
    accumulated[0]=0;
    for(int i=1; i<=N; i++) {
        cin>>s[i]>>e[i];
        accumulated[i]=accumulated[i-1]+e[i]-s[i];
    }
    result=0;
    for(int i=1; i<=N; i++){
        start = s[i];
        end = start+L;
        idx = getIndex(end);        // target 직전의 idx 리턴.
        if(idx == N){
            sum = accumulated[idx] - accumulated[i-1];
        }else if(end<s[idx+1]){
            sum = accumulated[idx] - accumulated[i-1];
        }else{
            sum = accumulated[idx] - accumulated[i-1] + end - s[idx+1];
        }
        result = result > sum ? result : sum;
    }

    return result;    
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T; cin>>T;
    for(int tc=1; tc<=T; ++tc){
        cout<<'#'<<tc<<' '<<solve()<<'\n';
    }
    return 0;
}