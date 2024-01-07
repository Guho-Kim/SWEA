#include<unordered_map>
#include<vector>
#include<queue>
#define INT_MAX 2000000000
#define MAX_N 60
using namespace std;
using tiii = tuple<int, int, int>;
using pii = pair<int, int>;

int _N;
int graph_price[MAX_N][MAX_N];
int dist_price[MAX_N];		// dist[cur_node] : mStart부터 cur_node까지 최소 비용
vector<vector<tiii>> graph_time;
pii dist_time[MAX_N];

bool visited[MAX_N];

void init(int N)
{
	_N = N;
	graph_time.clear();
	graph_time.assign(N, vector<tiii>());
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			graph_price[i][j] = INT_MAX;
		}
		dist_price[i] = INT_MAX;
		dist_time[i] = {INT_MAX,INT_MAX};
	}
}

void add(int mStartAirport, int mEndAirport, int mStartTime, int mTravelTime, int mPrice)
{
	graph_time[mStartAirport].push_back({mEndAirport, mStartTime, mTravelTime});
	if(graph_price[mStartAirport][mEndAirport]>mPrice)
		graph_price[mStartAirport][mEndAirport] = mPrice;
}

int minTravelTime(int mStartAirport, int mEndAirport, int mStartTime)
{
	priority_queue<tiii, vector<tiii>, greater<>> pq;
	pq.push({0, mStartTime, mStartAirport });	// {date, time, node}
	for (int i = 0; i < _N; i++) {
		dist_time[i] = { INT_MAX,INT_MAX };
		visited[i] = false;
	}
	dist_time[mStartAirport] = {0, mStartTime};

	while (!pq.empty()) {
		auto cur = pq.top();
		int cur_date = get<0>(cur);
		int cur_start_time = get<1>(cur);
		int cur_node = get<2>(cur);


		pq.pop();
		if (visited[cur_node]) {
			continue;
		}
		visited[cur_node] = true;
		if (cur_node == mEndAirport) {
			while (!pq.empty()) {
				pq.pop();
			}
			return cur_date * 24 + cur_start_time - mStartTime;
		}


		for (auto next : graph_time[cur_node]) {
			int next_date = cur_date;
			int next_start_time = get<1>(next);
			if (cur_start_time > next_start_time) {
				next_date++;
			}
			int next_time = next_start_time + get<2>(next);
			if (next_time >= 24) {
				next_time -= 24;
				next_date++;
			}
			int next_node = get<0>(next);
			if ((next_date == dist_time[next_node].first && next_time < dist_time[next_node].second)
				|| next_date < dist_time[next_node].first) {
				dist_time[next_node] = { next_date, next_time };
				pq.push({ next_date, next_time, next_node });
			}
		}
	}
	return -1;
}

int minPrice(int mStartAirport, int mEndAirport)
{
	priority_queue<pii, vector<pii>, greater<>> pq;
	pq.push({ 0, mStartAirport });		// {dist_price, dest_node}

	for (int i = 0; i < _N; i++) {
		dist_price[i] = INT_MAX;
		visited[i] = false;
	}

	dist_price[mStartAirport] = 0;
	while (!pq.empty()) {
		int cur_price = pq.top().first;
		int cur_node = pq.top().second;
		pq.pop();
		if (visited[cur_node]) {
			continue;
		}
		visited[cur_node] = true;

		if (cur_node == mEndAirport) {
			while (!pq.empty()) {
				pq.pop();
			}
			return cur_price;
		}
		for (int i = 0; i < _N; i++) {
			if (graph_price[cur_node][i] == INT_MAX) {
				continue;
			}
			int next_price = cur_price + graph_price[cur_node][i];
			if (next_price < dist_price[i]) {
				dist_price[i] = next_price;
				pq.push({ dist_price[i],i });
			}
		}
	}

	return -1;
}