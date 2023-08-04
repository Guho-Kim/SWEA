/*
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;
#define MAXN 30000

unordered_map<int, vector<int>> mailbox;		// <ID, subject_Index>
string subject_list[MAXN];

int subjectCnt;
int max_box;

void init(int N, int K) {
	subjectCnt = 0;
	max_box = K;
	mailbox.clear();
}

int getCount(int uID) {
	return mailbox[uID].size();
}

void sendMail(char subject[], int uID, int cnt, int rIDs[]) {
	subject_list[subjectCnt] = subject;
	for (int i = 0; i < cnt; i++) {
		if (getCount(rIDs[i]) == max_box) {
			mailbox[rIDs[i]].erase(mailbox[rIDs[i]].begin());
		}
		mailbox[rIDs[i]].push_back(subjectCnt);
	}
	subjectCnt++;
}

int deleteMail(int uID, char subject[]) {
	int cnt = 0;
	if (!mailbox[uID].empty()) {
		vector<int> vec = mailbox[uID];
		for (auto it = vec.begin(); it != vec.end(); it++) {
			int idx = *it;
			if (subject_list[idx] == subject) {
				mailbox[uID].erase(remove(mailbox[uID].begin(), mailbox[uID].end(), idx), mailbox[uID].end());
				cnt++;
			}
		}
	}
	return cnt;
}

int searchMail(int uID, char text[]) {
	int cnt = 0;
	for (int i : mailbox[uID]) {
		string s = subject_list[i];
		istringstream iss(s);
		string str;
		while (iss >> str) {
			if (str == text) {
				cnt++;
				break;
			}
		}
	}

	return cnt;
}
*/