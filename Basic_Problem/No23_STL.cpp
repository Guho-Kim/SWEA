#include<iostream>
#include<queue>
using namespace std;
priority_queue<int> pq;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int test_case;
	int T;
    cin >> T;
	for(test_case = 1; test_case <= T; ++test_case)
	{
        cout << "#"<<test_case<<" ";
        int N;
        cin >> N;
        for(int i=0; i<N; i++){
            int a, b, c;
            cin>>a;
            if(a==1){
                cin>>b;
                pq.push(b);
            }
            else if(a==2){
                if(pq.empty()) cout<<"-1 ";
                else{
                    c=pq.top();
                    pq.pop();
                    cout<<c<<" ";
                }

            }
        }
        while(!pq.empty()) pq.pop();
        cout<<endl;
	}


    return 0;
}