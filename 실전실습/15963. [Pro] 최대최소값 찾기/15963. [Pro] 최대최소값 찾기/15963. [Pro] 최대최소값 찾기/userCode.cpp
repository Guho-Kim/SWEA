#include<list>
#define MAX_N 1000000000
#define INT_MAX 1000000000
using namespace std;
struct Bucket {
	int max, min;
	int size;
	list<int> list;
	Bucket* next;
	Bucket* prev;
}bucket[2000];

int buckCnt;
Bucket* head;
Bucket* tail;

void init(int N, int mValue[]) {
	buckCnt = 0;
	head->next = &bucket[buckCnt];
	tail->prev = &bucket[buckCnt];
	bucket[buckCnt].prev = nullptr;
	bucket[buckCnt].next = nullptr;

	int max = 0;
	int min = INT_MAX;

	for (int i = 0; i < N; i++) {
		if (mValue[i] < min) min = mValue[i];
		if (mValue[i] > max) max = mValue[i];
		bucket[0].list.push_back(mValue[i]);
	}
	bucket[buckCnt].max = max;
	bucket[buckCnt].min = min;
	bucket[buckCnt].size = N;
	buckCnt++;
}


void add(int M, int mValue[]) {
	tail->prev->next = &bucket[buckCnt];
	bucket[buckCnt].prev=tail->prev;
	bucket[buckCnt].next = nullptr;
	tail->prev = &bucket[buckCnt];

	int max = 0;
	int min = INT_MAX;
	for (int i = 0; i < M; i++) {
		if (mValue[i] < min) min = mValue[i];
		if (mValue[i] > max) max = mValue[i];
		bucket[buckCnt].list.push_back(mValue[i]);
	}
	bucket[buckCnt].max = max;
	bucket[buckCnt].min = min;
	bucket[buckCnt].size = M;
	buckCnt++;
}

void erase(int mFrom, int mTo) {
	Bucket* node = head;
	Bucket* prev;
	Bucket* next;
	int start = 1;
	int eraseNum = mTo - mFrom + 1;
	while (node != nullptr) {
		int end = start + node->size-1;
		node = node->next;

		if (mFrom <= end) {
			// 여기서 지울 게 있음
			if (end <= mTo) {
				//여기서 끝남
				int idx = mFrom - start;
				
				auto it = node->list.begin();
				advance(it, idx);
				node->list.erase(it, std::next(it, eraseNum));
				node->size -= eraseNum;
				// 버킷 내부 최대 최소 갱신
				node->max = 0;
				node->min = INT_MAX;
				for (auto it = node->list.begin(); it != node->list.end(); it++) {
					if (node->max < *it) node->max = *it;
					if (node->min > *it) node->min = *it;
				}
			}
			else {
				// 다음 버킷까지 계속 넘어가야함
				int idx = mFrom - start;
				auto it = node->list.begin();
				advance(it, idx);
				node->list.erase(it, node->list.end());
				eraseNum -= node->size - idx;
				node->size = idx;
				// 버킷 내부 최대 최소 갱신
				node->max = 0;
				node->min = INT_MAX;
				for (auto it = node->list.begin(); it != node->list.end(); it++) {
					if (node->max < *it) node->max = *it;
					if (node->min > *it) node->min = *it;
				}


			}
		}
		else if(mTo < start){
			return;
		}
		
		start = end + 1;
	}
}


int find(int K) {
	Bucket* node = tail;
	while (node != nullptr) {
		node = node->prev;



	}
	return 0;
}