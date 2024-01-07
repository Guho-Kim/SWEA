#include <iostream>
using namespace std;
int dp[10001];
void makeDP(){
    int i=1;
    int j=1;
    for(int k=1; k<=10000; ++k){
        dp[k]=i*1000+j;
        if(i==j){
            i++;
            j=1;
        }
        else j++;
    }
}
int run(){
    int s, e, row_gap, col_gap;
    cin >> s >> e;
    if (e < s) swap(s, e);

    row_gap=dp[e]/1000 - dp[s]/1000;
    col_gap=dp[e]%1000 - dp[s]%1000;

    if(col_gap<0) return row_gap-col_gap;
    else if (col_gap>row_gap) return col_gap;
    return row_gap;
}
int main(){
    int t, T; cin>>T;
    makeDP();
    for(t=1; t<=T; ++t){
        cout<<"#"<<t<<" "<<run()<<"\n";
    }
    return 0;
}

