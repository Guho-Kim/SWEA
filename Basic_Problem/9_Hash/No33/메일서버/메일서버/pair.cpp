/*
#include<string>
#include<list>
#include<sstream>

using namespace std;

#define MAX_TITLE 30002
#define MAX_USER 1001
#define MAX_HASH ((1<<30)-1)

struct Mail {
	int cnt; 
	list<int> mailList;
};	//mailList는 mail 제목의 해시값
Mail mailbox[MAX_USER];

int userCnt = 0;

pair<string, int> title[MAX_TITLE];

int titleCnt;
int max_box;

int makeHash(char* str, int power) {
	unsigned long long hash = 0;
	while (*str) {
		hash = (hash << power) + hash + *str;
		str++;
	}

	return (int) (hash & MAX_HASH);
}


void init(int N, int K) {
	max_box = K;
	titleCnt = 0;
	for (int i = 0; i < userCnt; i++) {
		mailbox[i].cnt = 0;
		mailbox[i].mailList.clear();
	}
	userCnt = N;
}

int getCount(int uID) {
	return mailbox[uID].cnt;
}

void sendMail(char subject[], int uID, int cnt, int rIDs[]) {
	for (int i = 0; i < cnt; i++) {
		if (getCount(rIDs[i]) == max_box) {
			mailbox[rIDs[i]].mailList.pop_front();
			mailbox[rIDs[i]].cnt--;
		}
		mailbox[rIDs[i]].cnt++;
		mailbox[rIDs[i]].mailList.push_back(titleCnt);
	}
	title[titleCnt++] = { subject, makeHash(subject, 5) };
}

int deleteMail(int uID, char subject[]) {
	int howmanydel = 0;
	int hash = makeHash(subject, 5);
	if (!mailbox[uID].mailList.empty()) {
		for (auto itt = mailbox[uID].mailList.begin(); itt != mailbox[uID].mailList.end(); ) {
			int target_hash = title[*itt].second;

			if (hash == target_hash ) {
				howmanydel++;
				itt = mailbox[uID].mailList.erase(itt);
				mailbox[uID].cnt--;
			}
			else {
				itt++;
			}
		}
	}

	return howmanydel;
}

int searchMail(int uID, char text[]) {
	int howmany = 0;

	for (int num : mailbox[uID].mailList) {
		string& s = title[num].first;
		istringstream changestr(s);
		string ttmp;

		while (changestr >> ttmp) {
			if (ttmp == text) {
				++howmany;
				break;
			}
		}
	}

	return howmany;
}

*/