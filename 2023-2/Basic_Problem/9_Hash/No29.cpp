// [SWEA] No 2948. 문자열 교집합
#include<iostream>
#include<map>
#include<unordered_set>
using namespace std;


int solve(){
    unordered_set<string> Set;
    int N, M; cin>>N>>M;
    int cnt =0;
    for(int i=0; i<N; ++i){
        string str; cin>>str;
        Set.insert(str);
    } 
    for(int i=0; i<M; ++i){
        string str; cin>>str;
        if(Set.find(str)!=Set.end()) cnt++;
    }

    return cnt;
}


int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T; cin>>T;
    for(int tc=1; tc<=T; ++tc) cout<<"#"<<tc<<" "<<solve()<<endl;
    return 0;
}