//1257. [S/W 문제해결 응용] 6일차 - K번째 문자열

#include <iostream>
#include <cstring>
#include <vector>
#include<set>
using namespace std;

void solve() {
    int K;
    cin >> K;
    string str; cin >> str;

	set<string> Set;
	for(int i=0; i<str.size(); i++){
		for(int j=0; j<str.size()-1; j++){
			Set.insert(str.substr(i,j+1));
		}
	}
	if(Set.size() < K){
		cout<<"none\n";
		return;
	}
	auto it = Set.begin();
	advance(it,K-1);
	cout<<*it<<'\n';

}

int main(int argc, char** argv) {
    ios::sync_with_stdio(0);  cin.tie(); cout.tie();
    int test_case, T;
    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case) {
        cout << '#' << test_case << ' ';
        solve();
    }
    return 0;
}
