// [SWEA] No 10507. 영어 공부
#include <iostream>
#include<vector>
#define MAXN 200000

using namespace std;
int days[MAXN+1];
vector<int> blanks;
int n, p;

int last_true(int l, int r, int target) {
    while (l != r) {
        int m = r - (r - l) / 2;
        blanks[m] == target ? l = m : r = m - 1;
    }
    return l;
}

int binarySearch(int left, int target) {
    int right = n - 1;
    int closestIndex = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (blanks[mid] == target) {
            return last_true(mid, right, target);
        } else if (blanks[mid] < target) {
            closestIndex = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return closestIndex;
}

int solve() {
    cin>>n>>p;
    for (int i = 0; i < n; i++) cin >> days[i];
    blanks.clear();
    blanks.push_back(0);
    int temp=0;
    for (int i = 1; i < n; i++){
        temp+=days[i]-days[i-1]-1;
        blanks.push_back(temp);
    }

    int result = 1 + p;
    for(int left=0; left<n; left++){
        int newP = p + blanks[left];
        int idx = binarySearch(left, newP);
        int temp;
        if(idx==-1) continue;
        else{
            temp = days[idx] - days[left]+1;
            if(blanks[idx] < newP){
                temp+=newP-blanks[idx];
            }
        }
        result = result > temp ? result : temp;
    }
    return result;
}

int main(int argc, char** argv){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int T; cin>>T;

	for(int tc = 1; tc <= T; ++tc){cout<<'#'<<tc<<' '<<solve()<<'\n';}
	return 0;
}