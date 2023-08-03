#include<iostream>
#include<vector>
#include<unordered_map>
#include<set>
#include<sstream>
using namespace std;
#define MAXN 3000
unordered_map<string, set<int>> hashMapTitle[MAXN];
unordered_map<string, set<int>> hashMapWord[MAXN];

int mailCnt;
int id_Cnt[MAXN];
int limit;
void init(int N, int K) 
{	
	limit = K;
	mailCnt = 0;
	for (int i = 0; i < MAXN; i++) {
		id_Cnt[i] = 0;
		hashMapTitle[i].clear();
		hashMapWord[i].clear();
	}
}


void sendMail(char subject[], int uID, int cnt, int rIDs[]) 
{
	string inputString(subject);
	vector<string> tokens;
	string token;
	istringstream iss(inputString);

	while (iss >> token) {
		tokens.push_back(token);
	}

	for (int i = 0; i < cnt; i++) {
		if (getCount(rIDs[i]) == limit) {
			// 오래된 메일 삭제. set을 value로 했을 때, 제목을 알아야 정렬됨. 다른 방법으로 해할 듯.
		}
		hashMapTitle[rIDs[i]][inputString].insert(mailCnt);
		for (int j = 0; j < tokens.size(); j++) {
			hashMapWord[rIDs[i]][tokens[j]].insert(mailCnt);	
		}
		mailCnt++;
		id_Cnt[uID]++;
		
	}

}
int getCount(int uID) 
{
	/*
	int cnt = 0;
	for (auto it = hashMapTitle[uID].begin(); it != hashMapTitle[uID].end(); it++) {
		cnt += it->second.size();
	}
	return cnt;
	*/
	return id_Cnt[uID];
}
int deleteMail(int uID, char subject[]) 
{
	string str(subject);
	vector<string> tokens;
	string token;
	istringstream iss(str);
	int cnt = 0;
	auto it = hashMapTitle[uID].find(str);
	if (it != hashMapTitle[uID].end()) {
		set<int> indices = it->second;
		for (int idx : indices) {
			hashMapTitle[uID][str].erase(idx);
			for (int i = 0; i < tokens.size(); i++) {
				hashMapWord[uID][tokens[i]].erase(idx);
			}
			cnt++;
			id_Cnt[uID]--;
		}
	}
	return cnt;
}


int searchMail(int uID, char text[]) 
{
	int cnt = 0;
	string str(text);

	auto it = hashMapWord[uID].find(str);
	if (it != hashMapWord[uID].end()) {
		set<int> indices = it->second;
		for (int idx : indices) {
			cnt++;
		}
	}
	return cnt;
}