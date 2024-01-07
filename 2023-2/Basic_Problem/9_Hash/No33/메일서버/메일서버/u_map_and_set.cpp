/*
#include <iostream>
#include <unordered_map>
#include <string>
#include <list>
#include <sstream>
#include<set>
using namespace std;
#define MAXN 30000

unordered_map<int, set<int>> mailbox;
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
		mailbox[rIDs[i]].insert(subjectCnt);
	}
	subjectCnt++;
}

int deleteMail(int uID, char subject[]) {
	int cnt = 0;
	if (!mailbox[uID].empty()) {
		for (auto it = mailbox[uID].begin(); it != mailbox[uID].end(); ) {
			if (subject_list[*it] == subject) {
				cnt++;
				it = mailbox[uID].erase(it);
			}
			else {
				it++;
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
}*/