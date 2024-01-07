// [SWEA] No 1249. [S/W 문제해결 응용] 4일차 - 보급로

#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;
#define MAX_N 110

int map[MAX_N][MAX_N];
int dp[MAX_N][MAX_N];
int N;

queue<pair<int,int>> q;

void init(){
    for(int i=0; i<MAX_N; i++){
        for(int j=0; j<MAX_N; j++){
            dp[i][j]=9999;
        }
    }
}

void bfs(){
    int x, y, nx, ny;
    int dx[4]={0, 0, 1, -1};
    int dy[4]={1, -1, 0, 0};
    
    q.push({0,0});
    dp[0][0]=0;

    while(!q.empty()){
        x = q.front().first;
        y = q.front().second;
        q.pop();

        for(int i=0; i<4; i++){
            nx=x+dx[i];
            ny=y+dy[i];
            if(nx<0 || ny <0 || nx>=N || ny>=N) continue;
            if(dp[nx][ny] > map[nx][ny]+dp[x][y]){
                dp[nx][ny]=map[nx][ny]+dp[x][y];
                q.push({nx,ny});
            }


        }

    }
    
}

void view(){
    cout<<"<<DP>>\n";
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cout<<dp[i][j];
        }
        cout<<endl;
    }

}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int tc, T;
    cin>>T;
    for(tc=1; tc<=T; tc++){
        init();
        cin >> N;

        for(int i=0; i<N; i++){
            string str;
            cin >> str;
            for(int j=0; j<N; j++){
                map[i][j] = str[j]-'0';
            }

        }
           
        bfs();
        //view();


        cout<<"#"<<tc<<" "<<dp[N-1][N-1]<<endl;
    }


    return 0;
}