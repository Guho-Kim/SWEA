#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN = 100010;
const int INF = 1e9 + 7;
int n, q;

int arr[MAXN];
int segTreeMin[4*MAXN], segTreeMax[4*MAXN];

void build() {
    for(int i=1; i<=n; i++){
        segTreeMax[i+n]=arr[i];
        segTreeMin[i+n]=arr[i];
    }
    for (int i = n; i > 0; --i) {
        segTreeMax[i] = max(segTreeMax[i << 1], segTreeMax[i << 1 | 1]);
        segTreeMin[i] = min(segTreeMin[i << 1], segTreeMin[i << 1 | 1]);
    }

}

int queryMin(int l, int r) {
    int res = INF;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = min(res, segTreeMin[l++]);
        if (r & 1) res = min(res, segTreeMin[--r]);
    }
    return res;
}

int queryMax(int l, int r) {
    int res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = max(res, segTreeMax[l++]);
        if (r & 1) res = max(res, segTreeMax[--r]);
    }
    return res;
}
void update(int i, int x) {
    i+=n;
    segTreeMax[i]=x;
    segTreeMin[i]=x;

    while(i>>=1){
        segTreeMax[i] = max(segTreeMax[i << 1], segTreeMax[i << 1 | 1]);
        segTreeMin[i] = min(segTreeMin[i << 1], segTreeMin[i << 1 | 1]);
    }
}

void solve(){
    cin >> n >> q;
    for(int i=1; i<=4*n; i++){
        segTreeMin[i]=INF;
        segTreeMax[i]=0;
    }
    for (int i = 1; i <= n; ++i) cin >> arr[i];

    build();
    while(q--){
        int cmd; cin >> cmd;

        if (cmd == 0) {
            int i, x; cin>>i>>x;
            i++;
            arr[i]=x;
            update(i, x);
        } else if (cmd == 1) {
            int l, r; cin>>l>>r;
            l++; r++;
            int result = queryMax(l, r) - queryMin(l, r);
            cout << result << " ";
        }
    }

    cout << endl;
}


int main() {
    int T;cin >> T;
    for(int tc=1; tc<=T; tc++){
        cout<<'#'<<tc<<' ';
        solve();
    }
    return 0;
}
