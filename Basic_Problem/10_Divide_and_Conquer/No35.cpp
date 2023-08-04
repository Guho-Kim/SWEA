// [SWEA] No 7701. 염라대왕의 이름 정렬


#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
#define MAXN 20000

string name[MAXN+1];
int idx[MAXN+1];

bool cmp(int l, int r) {
    if (name[l].length() == name[r].length())
        return (name[l].compare(name[r]) < 0);
    else return (name[l].length() < name[r].length());
}
void solve(){
    int N; cin>>N;
    for (int i = 0; i < N; i++) {cin>> name[i]; idx[i] = i;}
    sort(idx, idx + N, cmp);
    string before="";
    for (int i = 0; i < N; i++) {
        if (before != name[idx[i]]) {
            cout<< name[idx[i]]<<"\n";
            before = name[idx[i]];
        }
    }
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(0);cin.tie(NULL);
	int T; cin>>T;

	for(int tc=1; tc<=T; ++tc){cout<<"#"<<tc<<"\n";solve();}
	return 0;
}