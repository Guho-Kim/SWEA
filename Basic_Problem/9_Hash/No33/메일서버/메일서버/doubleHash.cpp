/*
#include <unordered_map>
#include <string>
#include <list>
#include <sstream>
#include <vector>

using namespace std;
#define MAXID 1010
#define MAXMAIL 30010
list<int> mailbox[MAXID];
string subject_list[MAXMAIL];
unordered_multimap<string, int> subject_to_id;

int max_box;
int subjectCnt;

void init(int N, int K) {
    max_box = K;
    subjectCnt = 0;
    subject_to_id.clear();
    for (int i = 0; i < MAXID; i++) mailbox[i].clear();
}

int getCount(int uID) {
    return mailbox[uID].size();
}

void sendMail(char subject[], int uID, int cnt, int rIDs[]) {
    subject_list[subjectCnt] = subject;
    subject_to_id.insert({ subject, subjectCnt });
    for (int i = 0; i < cnt; i++) {
        if (getCount(rIDs[i]) == max_box) {
            mailbox[rIDs[i]].pop_front();
        }
        mailbox[rIDs[i]].push_back(subjectCnt);
    }
    subjectCnt++;
}



int deleteMail(int uID, char subject[]) {
    int cnt = 0;

    if (!mailbox[uID].empty()) {
        auto it = mailbox[uID].begin();
        while (it != mailbox[uID].end()) {
            auto range = subject_to_id.equal_range(subject);
            for (auto it2 = range.first; it2 != range.second; ++it2) {
                if (*it == it2->second) {
                    it = mailbox[uID].erase(it);
                    cnt++;
                }
                else {
                    it++;
                }
            
            }
        }
    }
    return cnt;
}

int searchMail(int uID, char text[]) {
    int cnt = 0;
    for (int subject_id : mailbox[uID]) {
        istringstream iss(subject_list[subject_id]);
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