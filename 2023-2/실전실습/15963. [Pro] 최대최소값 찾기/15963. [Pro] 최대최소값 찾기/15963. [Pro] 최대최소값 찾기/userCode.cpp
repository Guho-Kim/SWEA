#include<list>
#define INT_MAX 1000000000
#define M_MAX 100
#define BUCKET_MAX 2300
using namespace std;
struct Bucket {
	int max;
	int min;
	int size;
	int List[M_MAX];
	Bucket* next;
	Bucket* prev;
}bucket[BUCKET_MAX];

int buckCnt;
Bucket* head;
Bucket* tail;

void add(int M, int mValue[]) {
	int j = 0;
	for (int i = 0; i < M; i++) {
		if (bucket[buckCnt].size >= M_MAX) {
			j = 0;
			buckCnt++;
			tail->next = &bucket[buckCnt];
			bucket[buckCnt].prev = tail;
			bucket[buckCnt].next = nullptr;
			tail = tail->next;
		}
		if (mValue[i] < bucket[buckCnt].min) bucket[buckCnt].min = mValue[i];
		if (mValue[i] > bucket[buckCnt].max) bucket[buckCnt].max = mValue[i];
		bucket[buckCnt].List[bucket[buckCnt].size++] = mValue[i];
	}
}

void init(int N, int mValue[]) {
	for (int i = 0; i < BUCKET_MAX; i++) {
		bucket[i].max = 0;
		bucket[i].min = INT_MAX;
		bucket[i].next = nullptr;
		bucket[i].prev = nullptr;
		bucket[i].size = 0;
	}

	buckCnt = 0;
	head = &bucket[buckCnt];
	tail = &bucket[buckCnt];

	add(N, mValue);
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
		int j = 0;
		for (int i = endIdx + 1; i < startBucket->size; i++) {
			startBucket->List[startIdx + j] = startBucket->List[i];;
			j++;
		}
		startBucket->size -= endIdx-startIdx+1;

		int max = 0;
		int min = INT_MAX;
		for (int i = 0; i < startBucket->size; i++) {
			int value = startBucket->List[i];
			if (max < value) max = value;
			if (min > value) min = value;
		}
		startBucket->max = max;
		startBucket->min = min;

		
		return;
	}



	// 가운데 날리고 연결
	startBucket->next = endBucket;
	endBucket->prev = startBucket;

	// 각 버킷에서 idx 기준으로 날리기
	startBucket->size = startIdx;

	int j = 0;
	for (int i = endIdx+1; i < endBucket->size; i++) {
		endBucket->List[j] = endBucket->List[i];
		j++;
	}
	endBucket->size = j;

	// max, min 갱신
	int max = 0;
	int min = INT_MAX;
	for (int i = 0; i < startBucket->size; i++) {
		int value = startBucket->List[i];
		if (max < value) max = value;
		if (min > value) min = value;
	}
	startBucket->max = max;
	startBucket->min = min;
	
	max = 0;
	min = INT_MAX;
	for (int i = 0; i < endBucket->size; i++) {
		int value = endBucket->List[i];
		if (max < value) max = value;
		if (min > value) min = value;
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
			int idx = node->size - 1;
			for (int i = 0; i < cnt; i++) {
				int value = node->List[idx];
				if (max < value) max = value;
				if (min > value) min = value;
				idx--;
			}
			break;
		}
		node = node->prev;
	}
	return max-min;
}