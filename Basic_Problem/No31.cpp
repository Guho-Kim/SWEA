// [SWEA] No 7091. 은기의 아주 큰 그림
#include<iostream>
#include<vector>
#define MAXN 2010
#define DIV ((1<<25)-(1))
using namespace std;


int myPic[MAXN][MAXN];
int tPic[MAXN][MAXN];

int hashTable[MAXN][MAXN];
int Trans[MAXN][MAXN];

int H, W, N, M; 

int getHash(int *ptr, int n){
    int hash = 5381;
    for(int i=0; i<n; i++)
        hash=(hash<<5)+hash+ptr[i];
    return hash;
}
int getMul(int *ptr, int n){
    int hash = 5381;
    for(int i=0; i<n; i++)
        hash=(hash<<5)+hash+ptr[i];
    return hash;
}


int solve(){
    cin>>H>>W>>N>>M;
    int mul;
    // Input data
    for(int i=0; i<H; i++){for(int j=0; j<W; j++){char c; cin>>c; myPic[i][j]=c;}}
    for(int i=0; i<N; i++){for(int j=0; j<M; j++){char c; cin>>c; tPic[i][j]=c;}}
    
    // make target hash value
    int targetHash=0;
    for(int i=0; i<H; i++) {
        Trans[0][i] = getHash(myPic[i], W);
    }
    targetHash = getHash(&Trans[0][0], H);

    for(int i=0; i<N; i++){
        for(int j=0; j<M-W+1; j++){
            Trans[j][i]=getHash(&tPic[i][j], W);
        }
    }
    for(int i=0; i<N-H+1; i++){
        for(int j=0; j<M-W+1; j++){
            hashTable[i][j]=getHash(&Trans[j][i], H);
        }
    }


    int cnt=0;
    for(int i=0; i<N-H+1; i++){
        for(int j=0; j<M-W+1; j++){
            if(hashTable[i][j] == targetHash) {
                cnt++;
            }
        }
    }
    return cnt;
}

int main(){
    ios::sync_with_stdio(false);cin.tie(NULL);
    int T; cin>>T;
    for(int tc=1; tc<=T; ++tc) cout<<"#"<<tc<<" "<<solve()<<endl;
    return 0;
}