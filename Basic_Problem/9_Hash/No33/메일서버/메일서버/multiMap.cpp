/*
#include <iostream>
#include <unordered_map>
#include <string>
#include <list>
#include <sstream>
using namespace std;
#define MAXN 30000

unordered_multimap<size_t, size_t> mailbox;
string subject_list[MAXN];

int subjectCnt;
int max_box;

void init(int N, int K) {
    subjectCnt = 0;
    max_box = K;
    mailbox.clear();
}

int getCount(int uID) {
    return mailbox.count(uID);
}

size_t getHash(const char* subject) {
    // 개선된 해시 함수
    size_t hash_val = 5381;
    int c;

    while ((c = *subject++)) {
        hash_val = ((hash_val << 5) + hash_val) + c;
    }

    return hash_val;
}

void sendMail(char subject[], int uID, int cnt, int rIDs[]) {
    size_t hash_val = getHash(subject);
    subject_list[subjectCnt] = subject;

    for (int i = 0; i < cnt; i++) {
        if (getCount(rIDs[i]) == max_box) {
            auto range = mailbox.equal_range(rIDs[i]);
            for (auto it = range.first; it != range.second; ) {
                if (it->second == hash_val) {
                    it = mailbox.erase(it);
                }
                else {
                    ++it;
                }
            }
        }
        mailbox.insert({ rIDs[i], hash_val });
    }
    subjectCnt++;
}

int deleteMail(int uID, char subject[]) {
    int cnt = 0;
    size_t hash_val = getHash(subject);

    auto range = mailbox.equal_range(uID);
    for (auto it = range.first; it != range.second; ) {
        if (it->second == hash_val) {
            it = mailbox.erase(it);
            cnt++;
        }
        else {
            ++it;
        }
    }
    return cnt;
}

int searchMail(int uID, char text[]) {
    int cnt = 0;
    size_t hash_val = getHash(text);

    auto range = mailbox.equal_range(uID);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second == hash_val) {
            cnt++;
        }
    }
    return cnt;
}
*/