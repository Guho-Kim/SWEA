#include<queue>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct Post {
	int pID;
	int uID;
	int like;
	int timestamp;
};

struct cmp1 {
	bool operator()(const Post& p1, const Post& p2) {
        // return a < b : 큰 값이 우선순위. 일단 외우자. 내림차순
        return p1.like<p2.like;
		if (p1.like < p2.like) {
			return true;
		}
		else if (p1.like == p2.like) {
			return p1.timestamp < p2.timestamp;
		}
		else {
			return false;
		}
	}
};
struct cmp2 {
	bool operator()(const Post& p1, const Post& p2) {
		return p1.timestamp < p2.timestamp;
	}
};

// index == pID
Post postPool[10000];
int pCnt=0;
void makePost(int uID, int pID, int timestamp)
{
	postPool[pID].pID = pID;
	postPool[pID].uID = uID;
	postPool[pID].like = 0;
	postPool[pID].timestamp = timestamp;
    pCnt++;
}

int main(){
    priority_queue<Post, vector<Post>, cmp1> pq;
    int j=1;
    for(int i=1; i<=50; i++){
        makePost(1,i,j);
        j+=i*i;
    }
    for(int i=1; i<pCnt; i=i+2){
        postPool[i].like++;
    }

    for(int i=1; i<pCnt; i++){
        pq.push(postPool[i]);
    }


    while(!pq.empty()){
        Post curr = pq.top(); pq.pop();
        cout<<"pID: "<<curr.pID<<" like: "<<curr.like<<" timestaml: "<<curr.timestamp<<endl;
    }



    return 0;
}