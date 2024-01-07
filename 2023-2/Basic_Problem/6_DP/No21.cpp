// [SWEA] No 3282. 0/1 Knapsack


#include<iostream>
#include<algorithm>
#define MAX_N 101
#define MAX_K 1001
using namespace std;

struct Node{
    int V, C;
};

Node Nodes[MAX_N];
int dp[MAX_N][MAX_K];

void makeDP(int N, int K){
    // init
    for(int i=0; i<N; i++){
        for(int j=0; j<K; j++){
            dp[i][j]=0;
        }
    }

    for(int i=1; i<=N; i++){
        for(int j=1; j<=K; j++){
            if(Nodes[i].V <= j){
                dp[i][j] = max(dp[i-1][j], dp[i-1][j-Nodes[i].V]+Nodes[i].C);
            } else{
                dp[i][j] = dp[i-1][j];
            }
        }
    }
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        int N, K;   // N: number of object, K: volume of bag
        int result;
        cin >> N >> K;
        for(int i=1; i<=N; i++){
            cin >> Nodes[i].V >> Nodes[i].C;
        }
        makeDP(N, K);
        result = dp[N][K];

        cout<<"#"<<test_case<<" "<<result<<endl;


	}
	return 0;
}