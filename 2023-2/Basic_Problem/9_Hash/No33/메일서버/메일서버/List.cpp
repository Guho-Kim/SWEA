#include <string>
#include <sstream>
#include <unordered_map>
#include <list>

using namespace std;
#define MAX_USER    1001
#define MAX_MAIL    10001
#define MAX_TEXT    10

list<int> mailbox[MAX_USER];
unordered_map<string, int> titleHash;
unordered_map<string, int> textHash;

struct Mail {
    int text[MAX_TEXT];
    int cnt;
}mail[MAX_MAIL];

int title_idx;
int text_idx;
int _K;
int _N;

void init(int N, int K) {
    title_idx = text_idx = 0;
    _K = K;

    for (int i = 0; i < _N; i++)
        mailbox[i].clear();

    titleHash.clear();
    textHash.clear();
    _N = N;
}

int getCount(int uID) {
    return mailbox[uID].size();
}

void sendMail(char subject[], int uID, int cnt, int rIDs[]) {
    if (titleHash[subject] == 0) {
        int idx = titleHash[subject] = ++title_idx;
        mail[idx].cnt = 0;
        string s(subject); istringstream iss(s); string str;
        while (iss >> str) {
            if (textHash[str] == 0) textHash[str] = ++text_idx;
            mail[idx].text[mail[idx].cnt++] = textHash[str];
        }
    }
    
    int hashValue = titleHash[subject];
    for (int i = 0; i < cnt; i++) {
        if (getCount(rIDs[i]) == _K) {
            mailbox[rIDs[i]].pop_front();
        }
        mailbox[rIDs[i]].push_back(hashValue);
    }
}

int deleteMail(int uID, char subject[]) {
    int cnt = 0;
    int target = titleHash[subject];

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
    int target = textHash[text];
    for (int idx : mailbox[uID]) {
        for (int i = 0; i < mail[idx].cnt; i++) {
            if (mail[idx].text[i] == target) {
                ++cnt;
                break;
            }
        }
    }
    return cnt;
    
}
