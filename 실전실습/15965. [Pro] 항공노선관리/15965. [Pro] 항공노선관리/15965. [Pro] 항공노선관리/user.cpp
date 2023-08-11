#include<unordered_map>
#include<vector>
#include<list>
#include<queue>
#include<stack>
#include<array>
#define INT_MAX 1000000000
#define MAX_N 60
using namespace std;
//unordered_map<int, int> ;
int _N;
//int graph_time[60][60];
int graph_price[60][60];
struct Path {
	int endAirport;
	int startTime;
	int travelTime;
};
vector<Path> graph_time[60];



struct Path {
	int endAirport;
	int startTime;
	int travelTime;
	int mPrice;
};
struct Airport {
	int startAirport;
	int endAirport;
	list<Path> next;
}Airport[60];

void init(int N)
{
	_N = N;
	//AirPort.clear();
}

void add(int mStartAirport, int mEndAirport, int mStartTime, int mTravelTime, int mPrice)
{
	//Airport[mStartAirport].next.push_back({mEndAirport, mStartTime, mTravelTime, mPrice });
	graph_time[mStartAirport].push_back({ mEndAirport, mStartAirport, mTravelTime });
	
	if(graph_price[mStartAirport][mEndAirport]>mPrice)
		graph_price[mStartAirport][mEndAirport] = mPrice;
}

int minTravelTime(int mStartAirport, int mEndAirport, int mStartTime)
{
	priority_queue<array<int, 3>, vector<array<int, 3>>, greater<>> pq;
	pq.push({0, mStartTime, mStartAirport });
	int dist[MAX_N];
	for (int i = 0; i < _N; i++) dist[i] = INT_MAX;
	//dist[mStartAirport]=

	return 0;
}

int minPrice(int mStartAirport, int mEndAirport)
{
	priority_queue<array<int, 2>, vector<array<int, 2>>, greater<>> pq;
	pq.push({ 0, mStartAirport });
	int dist[60];
	for (int i = 0; i < _N; i++) dist[i] = INT_MAX;

	dist[mStartAirport] = 0;
	while (!pq.empty()) {
		auto cur = pq.top();
		pq.pop();
		if (cur[0] != dist[cur[1]]) {
			continue;
		}
		if (cur[1] == mEndAirport) {
			while (!pq.empty()) {
				pq.pop();
			}
			return cur[0];
		}
		for (int i = 0; i < _N; i++) {
			if (graph_price[cur[1]][i] == INT_MAX) {
				continue;
			}
			if (cur[0] + graph_price[cur[1]][i] < dist[i]) {
				dist[i] = cur[0] + graph_price[cur[1]][i];
				pq.push({ dist[i],i });
			}
		}
	}

	return -1;
}