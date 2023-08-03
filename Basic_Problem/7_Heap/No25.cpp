// [SWEA] No 3000. 중간값 구하기

#include<iostream>
#include<queue>
using namespace std;

int main(int argc, char** argv){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int tc ,T;
    cin >> T;
    
    for(tc=1; tc<=T; tc++){
        priority_queue<int, vector<int>, less<int>> maxHeap;
        priority_queue<int, vector<int>, greater<int>> minHeap;
        int N, smaller, bigger, mid, result;
        cin >> N >> mid;

        result = 0;
        for(int i=0; i<N; i++){
            cin >> smaller >> bigger;
            if(smaller > bigger){
                int temp = smaller;
                smaller = bigger;
                bigger=temp;
            }

            if(mid < smaller){
                minHeap.push(bigger);
                minHeap.push(smaller);
                maxHeap.push(mid);
                mid = minHeap.top();
                minHeap.pop();
            }
            else if(bigger < mid){
                maxHeap.push(bigger);
                maxHeap.push(smaller);
                minHeap.push(mid);
                mid = maxHeap.top();
                maxHeap.pop();
            }
            else {
                maxHeap.push(smaller);
                minHeap.push(bigger);
            }

            result = (result + mid)%20171109;
        }
        cout<<"#"<<tc<<" "<<result<<endl;
    }

    return 0;
}