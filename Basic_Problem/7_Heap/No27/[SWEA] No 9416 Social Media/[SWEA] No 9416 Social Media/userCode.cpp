// [SWEA] No 9416. Social Media

#include<queue>
using namespace std;

#define MAXN 1000
#define MAXP 100000

// 게시글 노드
struct Post {
	int pID;
	int uID;
	int like;
	int timestamp;
};

struct cmp1 {
	bool operator()(const Post& p1, const Post& p2) {
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
Post postPool[MAXP];
int pCnt;

// Follow info
bool arr[MAXN + 1][MAXN + 1];


void init(int N)
{
	pCnt = 0;
	for (int i = 0; i <= MAXN; i++) {
		for (int j = 0; j <= MAXN; j++) {
			arr[i][j] = false;
		}
	}
	for (int i = 1; i <= MAXN; i++) arr[i][i] = true;
}

void follow(int uID1, int uID2, int timestamp)
{
	arr[uID1][uID2] = true;
}

void makePost(int uID, int pID, int timestamp)
{
	postPool[pID].pID = pID;
	postPool[pID].uID = uID;
	postPool[pID].like = 0;
	postPool[pID].timestamp = timestamp;
	pCnt++;
}

void like(int pID, int timestamp)
{
	postPool[pID].like++;
}

void getFeed(int uID, int timestamp, int pIDList[])
{
	priority_queue<Post, vector<Post>, cmp1> pq1;
	priority_queue<Post, vector<Post>, cmp2> pq2;
	for (int i = pCnt; i >= 1; i--) {
		int tID = postPool[i].uID;
		int tTime = postPool[i].timestamp;

		if (arr[uID][tID]) {
			if ((timestamp - tTime) <= 1000) {
				pq1.push(postPool[i]);
			}
			else {
				if (pq1.size() + pq2.size() >= 10) {
					break;
				}
				pq2.push(postPool[i]);
			}
		}
	}

	int i = 0;
	while (!pq1.empty()) {
		if (i == 10) break;
		pIDList[i++] = pq1.top().pID; pq1.pop();
	}
	while (!pq2.empty()) {
		if (i == 10) break;
		pIDList[i++] = pq2.top().pID; pq2.pop();
	}

	return;
}