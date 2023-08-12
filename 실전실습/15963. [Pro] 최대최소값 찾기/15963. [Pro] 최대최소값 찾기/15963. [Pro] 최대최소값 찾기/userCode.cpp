#include<iostream>
#include<list>
#define INT_MAX 1000000000
using namespace std;
struct Bucket {
	int max;
	int min;
	int size;
	list<int> List;
	Bucket* next;
	Bucket* prev;
}bucket[3000];

int buckCnt;
Bucket* head;
Bucket* tail;

void init(int N, int mValue[]) {
	buckCnt = 0;
	head = &bucket[buckCnt];
	tail = &bucket[buckCnt];

	for (int i = 0; i < 3000; i++) {
		bucket[i].List.clear();
		bucket[i].next = nullptr;
		bucket[i].prev = nullptr;
	}

	int max = 0;
	int min = INT_MAX;

	for (int i = 0; i < N; i++) {
		if (mValue[i] < min) min = mValue[i];
		if (mValue[i] > max) max = mValue[i];
		bucket[0].List.push_back(mValue[i]);
	}

	bucket[buckCnt].max = max;
	bucket[buckCnt].min = min;
	bucket[buckCnt].size = N;
	buckCnt++;
}


void add(int M, int mValue[]) {
	tail->next = &bucket[buckCnt];
	bucket[buckCnt].prev=tail;
	bucket[buckCnt].next = nullptr;
	tail = tail->next;

	int max = 0;
	int min = INT_MAX;
	for (int i = 0; i < M; i++) {
		if (mValue[i] < min) min = mValue[i];
		if (mValue[i] > max) max = mValue[i];
		bucket[buckCnt].List.push_back(mValue[i]);
	}
	bucket[buckCnt].max = max;
	bucket[buckCnt].min = min;
	bucket[buckCnt].size = M;
	buckCnt++;
}

void erase(int mFrom, int mTo) {
	Bucket* node = head;
	Bucket* startBucket;
	Bucket* endBucket;
	int startIdx;
	int endIdx;
	
	int start = 0;
	while (start + node->size < mFrom) {
		start += node->size;
		node = node->next;
	}
	startBucket = node;
	startIdx = mFrom - start-1;		// 0부터 카운트 한다는 가정


	int end = start;
	while (end + node->size < mTo) {
		end += node->size;
		node = node->next;
	}
	endBucket = node;
	endIdx = mTo- end-1;

	//한 버킷에서 모두 끝나는 경우
	if (startBucket == endBucket) {
		auto it = startBucket->List.begin();
		for (int i = 0; i < startIdx; i++) it++;
		for (int i = 0; i < mTo - mFrom + 1; i++) {
			it = startBucket->List.erase(it);
			startBucket->size--;
		}
		int max = 0;
		int min = INT_MAX;
		for (auto it = startBucket->List.begin(); it != startBucket->List.end(); it++) {
			if (max < *it) max = *it;
			if (min > *it) min = *it;
		}
		startBucket->max = max;
		startBucket->min = min;


		return;
	}



	// 가운데 날리고 연결
	startBucket->next = endBucket;
	endBucket->prev = startBucket;

	// 각 버킷에서 idx 기준으로 날리기
	int List_size = startBucket->List.size();
	for (int i = startIdx; i < List_size; i++) {
		startBucket->List.pop_back();
		startBucket->size--;
	}
	
	for (int i = 0; i <= endIdx; i++) {
		endBucket->List.pop_front();
		endBucket->size--;
	}

	// max, min 갱신
	int max = 0;
	int min = INT_MAX;
	for (auto it = startBucket->List.begin(); it != startBucket->List.end(); it++) {
		if (max < *it) max = *it;
		if (min > *it) min = *it;
	}
	startBucket->max = max;
	startBucket->min = min;
	
	max = 0;
	min = INT_MAX;
	for (auto it = endBucket->List.begin(); it != endBucket->List.end(); it++) {
		if (max < *it) max = *it;
		if (min > *it) min = *it;
	}
	endBucket->max = max;
	endBucket->min = min;

}


int find(int K) {
	int cnt = K;
	int max = 0;
	int min = INT_MAX;
	Bucket* node = tail;
	while (node != nullptr) {
		if (node->size <= cnt) {
			if (max < node->max) max = node->max;
			if (min > node->min) min = node->min;
			cnt -= node->size;
		}
		else {
			auto it = node->List.end();
			it--;
			for (int i = 0; i < cnt; i++) {
				if (max < *it) max = *it;
				if (min > *it) min = *it;
				it--;
			}
			break;
		}
		node = node->prev;
	}
	return max-min;
}