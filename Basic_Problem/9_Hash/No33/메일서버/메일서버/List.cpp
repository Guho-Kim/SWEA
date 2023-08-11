#include <string>
#include <sstream>
#include <unordered_map>
#include <list>
#include <algorithm>

using namespace std;
#define MAXN 30010
#define MAX_USER 1002

list<int> mailbox[MAX_USER];
string IdxToStr[MAXN];
unordered_map<string, int> StrToIdx;

int subjectCnt;
int max_box;

void init(int N, int K) {
    subjectCnt = 0;
    max_box = K;
    for (int i = 0; i < MAX_USER; i++)
        mailbox[i].clear();
    StrToIdx.clear();
}

int getCount(int uID) {
    return mailbox[uID].size();
}

void sendMail(char subject[], int uID, int cnt, int rIDs[]) {
    int hashValue;
    if (StrToIdx.find(subject) != StrToIdx.end()) {        // 이미 해시 값이 존재하는 경우
        hashValue = StrToIdx[subject];
    }else {
        hashValue = subjectCnt++;
        StrToIdx[subject] = hashValue;
        IdxToStr[hashValue] = subject;
    }
    for (int i = 0; i < cnt; i++) {
        if (getCount(rIDs[i]) == max_box) {
            mailbox[rIDs[i]].pop_front();
        }
        mailbox[rIDs[i]].push_back(hashValue);
    }
}

int deleteMail(int uID, char subject[]) {
    int cnt = 0;
    int target = StrToIdx[subject];

    if (!mailbox[uID].empty()) {
        auto it = mailbox[uID].begin();
        while (it != mailbox[uID].end()) {
            if (*it == target) {
                it = mailbox[uID].erase(it);
                cnt++;
            }
            else {
                ++it;
            }
        }
    }
    return cnt;
}
int searchMail(int uID, char text[]) {
    int cnt = 0;
    for (int idx : mailbox[uID]) {
        string s = IdxToStr[idx];
        istringstream iss(s);
        string str;
        while (iss >> str) {
            if (str == text) {
                ++cnt;
                break;
            }
        }
    }
    return cnt;
}
