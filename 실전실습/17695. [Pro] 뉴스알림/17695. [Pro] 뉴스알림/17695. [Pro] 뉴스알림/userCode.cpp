#include<iostream>
#include<queue>
#include<vector>
#include<unordered_map>
using namespace std;

#define MAX_USER	501
#define MAX_CHANNEL	501
int _N, _K;
struct News {
	int time;
	int news_id;
	int channel_idx;
	bool canceled;
	bool operator()(const News* a, const News* b)const{
		if (a->time == b->time) {
			return a->news_id > b->news_id;
		}
		return a->time > b->time;
	}
};
vector<News*> Users[MAX_USER];			//idx: 유저 idx, vector: news address
vector<int> Users_Channel_Info[MAX_USER];
vector<int> Channels_User_Info[MAX_CHANNEL];		//idx: 채널 idx, vector: 유저 idx	user_info
News news[30000];


unordered_map<int, int> channelMap;
unordered_map<int, int> userMap;
unordered_map<int, int> newsMap;

priority_queue<News*, vector<News*>, News> pq;	// 각 채널의 뉴스 정보

int channelCnt, userCnt, newsCnt;
void init(int N, int K)
{
	for (int i = 1; i <= userCnt; i++) {
		Users_Channel_Info[i].clear();
		Users[i].clear();
	}
	for (int i = 1; i <= channelCnt; i++) {
		Channels_User_Info[i].clear();
	}
	while (!pq.empty()) pq.pop();
	userMap.clear();
	channelMap.clear();
	newsMap.clear();

	newsCnt = userCnt = channelCnt = 0;
}

void registerUser(int mTime, int mUID, int mNum, int mChannelIDs[])
{
	while (!pq.empty()) {
		auto cur_news = pq.top();
		if (cur_news->time > mTime) {
			break;
		}
		pq.pop();
		if (cur_news->canceled) continue;

		for (auto idx : Channels_User_Info[cur_news->channel_idx]) {
			Users[idx].push_back(cur_news);
		}
	}

	if(!userMap[mUID]) userMap[mUID] = ++userCnt;
	int user_idx = userMap[mUID];
	
	for (int i = 0; i < mNum; i++) {
		if (!channelMap[mChannelIDs[i]])  channelMap[mChannelIDs[i]] = ++channelCnt;
		int channel_idx = channelMap[mChannelIDs[i]];
		Channels_User_Info[channel_idx].push_back(user_idx);
		Users_Channel_Info[user_idx].push_back(channel_idx);
	}
}

int offerNews(int mTime, int mNewsID, int mDelay, int mChannelID)
{
	if (!newsMap[mNewsID]) newsMap[mNewsID] = ++newsCnt;

	int news_id = newsMap[mNewsID];
	int channel_idx = channelMap[mChannelID];

	news[news_id] = { mTime + mDelay, mNewsID, channel_idx, false};

	pq.push(&news[news_id]);
	
	return Channels_User_Info[channel_idx].size();
}

void cancelNews(int mTime, int mNewsID)
{
	int news_id = newsMap[mNewsID];
	news[news_id].canceled = true;
}

int checkUser(int mTime, int mUID, int mRetIDs[])
{
	while (!pq.empty()) {
		auto cur_news = pq.top();
		if (cur_news->time > mTime) {
			break;
		}
		pq.pop();
		if (cur_news->canceled) continue;

		for (auto idx : Channels_User_Info[cur_news->channel_idx]) {
			Users[idx].push_back(cur_news);
		}
	}

	int user_idx = userMap[mUID];
	int cnt = 0;
	int cancleCnt = 0;
	int len = Users[user_idx].size();
	for (int i = len - 1; i >= 0; i--) {
		if (Users[user_idx][i]->canceled) {
			cancleCnt++;
			continue;
		}
		if (cnt < 3) {
			mRetIDs[cnt++] = Users[user_idx][i]->news_id;
		}
	}
	Users[user_idx].clear();



	return len - cancleCnt;
}