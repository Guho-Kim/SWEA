// [SWEA] No 4038. [Professional] 단어가 등장하는 횟수

#include<iostream>
#include<vector>
using namespace std;
vector<int> makeTable(string pattern){
    int patternSize = pattern.length();
    vector<int> table(patternSize, 0);
    table[0]=0;
    for(int i=1, j=0; i<patternSize; i++){
        while(j>0 && pattern[i] != pattern[j])
            j = table[j-1];
        if(pattern[j] == pattern[i])
            table[i]=++j;
    }
    return table;
}
int KMP(string parent, string pattern){
    vector<int> table = makeTable(pattern);
    int parentSize = parent.length();
    int patternSize = pattern.length();
    int cnt=0;
    for(int i=0, j=0; i<parentSize; i++){
        while(j>0 && parent[i]!= pattern[j])
            j = table[j-1];            
        if(parent[i] == pattern[j]){
            if(j == patternSize-1){
                cnt++;
                j=table[j];
            } else j++;
        }
    }
    return cnt;
}
int solve(){
    string parent; cin>>parent;
    string pattern; cin>>pattern;
    return KMP(parent, pattern);
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int T; cin>>T;
    for(int tc=1; tc<=T; ++tc) cout<<"#"<<tc<<" "<<solve()<<endl;
    return 0;
}