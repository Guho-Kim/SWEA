// [SWEA] No 7091. 은기의 아주 큰 그림
#include<iostream>
#define MAXN 2010
#define DIV ((1<<30)-(1))
typedef unsigned long long ull;
using namespace std;

int myPic[MAXN][MAXN], tPic[MAXN][MAXN], hashTable[MAXN][MAXN], Trans[MAXN][MAXN];
int H, W, N, M; 

int getHash(int *ptr, int n, int shift){
    ull hash = 0;
    for(int i=0; i<n; i++) hash=(hash<<shift)+hash+ptr[i];
    return (int) (hash & DIV);
}
int CalcMul(int num, int shift) {
    ull hash = 1;
    for(int i = 1; i < num; i++) hash = (hash << shift) + hash;
    return (int) (hash & DIV);
}

/*
    info_getNextHash
    prevHash = 33^5*a + 33^4*b + 33^3*c + 33^2+d + 33^1*e + f
    nextHash = prevHash - 33^5*a
    nextHash = nextHash*33 + addHash
*/
int getNextHash(int prevHash, int subHash, int mul, int addHash, int shift) {
    ull hash = prevHash - (subHash * mul);
    hash = (hash << shift) + hash + addHash;
    return (int) (hash & DIV);
}

int solve(){
    cin>>H>>W>>N>>M;
    int rowShift = 5, colShift = 4;
    int rowMul = CalcMul(W, rowShift), colMul = CalcMul(H, colShift);
    for(int i=0; i<H; i++){for(int j=0; j<W; j++){char c; cin>>c; myPic[i][j]=c;}}
    for(int i=0; i<N; i++){for(int j=0; j<M; j++){char c; cin>>c; tPic[i][j]=c;}}
    
    int targetHash=0;
    for(int i=0; i<H; i++) {Trans[0][i] = getHash(myPic[i], W, rowShift);}
    targetHash = getHash(&Trans[0][0], H, colShift);

    for(int i=0; i<N; i++){
        Trans[0][i]=getHash(&tPic[i][0], W, rowShift);
        for(int j=1; j<M-W+1; j++){
            Trans[j][i]=getNextHash(Trans[j-1][i], tPic[i][j-1],rowMul, tPic[i][j+W-1], rowShift);
        }
    }

    for(int j=0; j<M-W+1; j++){
        hashTable[0][j]=getHash(&Trans[j][0], H, colShift);
        for(int i=1; i<N-H+1; i++){
            hashTable[i][j]=getNextHash(hashTable[i-1][j], Trans[j][i-1], colMul, Trans[j][i+H-1], colShift);
        }
    }

    int cnt=0;
    for(int i=0; i<N-H+1; i++){for(int j=0; j<M-W+1; j++){if(hashTable[i][j] == targetHash) {cnt++;}}}
    return cnt;
}

int main(){
    ios::sync_with_stdio(false);cin.tie(NULL);
    int T; cin>>T;
    for(int tc=1; tc<=T; ++tc) cout<<"#"<<tc<<" "<<solve()<<endl;
    return 0;
}