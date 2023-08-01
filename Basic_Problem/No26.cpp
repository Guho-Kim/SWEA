// [SWEA] No 10806. 수 만들기
/*
    For example
    k = 3 + a(5 + bc(2+d))
    3 is the remainder. It could be cnt by before value, and the quotient is next K.
    When I push it, it could be sorted by ascending with cnt.
*/
#include<iostream>
#include<queue>
using namespace std;
struct Node{
    int k, cnt;
};
struct cmp{
    bool operator()(const Node& n1, const Node& n2){
        return n1.cnt > n2.cnt;
    }
};
int N, K, A[11];
int solve(){
    cin >> N;
    for(int i=0; i<N; i++) cin >> A[i];
    cin >> K;
    priority_queue<Node, vector<Node>, cmp> pq;
    pq.push({K, 0});
    while(pq.top().k>0){
        Node curr = pq.top(); pq.pop();
        for(int i=0; i<N; i++){
            pq.push({curr.k/A[i], curr.cnt + curr.k%A[i]});
        }
    }
    return pq.top().cnt;
}
int main(){
    ios::sync_with_stdio(false); cin.tie(NULL);
    int T; cin >> T;
    for(int tc=1; tc<=T; ++tc){cout<<"#"<<tc<<" "<<solve()<<endl;}
    return 0;
}