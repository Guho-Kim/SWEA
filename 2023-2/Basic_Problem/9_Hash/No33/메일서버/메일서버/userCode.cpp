/*
#include<iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <list>

using namespace std;
using ull = unsigned long long;
#define M_USER 1000
#define M_MAIL 10000
#define M_WORD 10

int _K;

struct Mail {
    ull word[M_WORD];
    int cnt;
} mail[M_MAIL];

struct User {
    list<Mail*> mailBox;
} user[M_USER];

unordered_map<string, int> hashMap;

int idx_hash, idx_mail;

void init(int N, int K) {
    idx_hash = idx_mail = 0;
    hashMap.clear();
    for (int i = 0; i < M_USER; i++) user[i].mailBox.clear();
    _K = K;
}

void sendMail(char subject[], int uID, int cnt, int rIDs[]) {
    Mail* newMail = &mail[idx_mail++];
    newMail->cnt = 0;
    string s(subject);
    istringstream iss(s);
    string str;
    while (iss >> str) {
        if (hashMap[str] == 0) hashMap[str] = ++idx_hash;
        newMail->word[newMail->cnt] = hashMap[str];
        ++newMail->cnt;
    }

    for (int i = 0; i < cnt; i++) {
        User* newID = &user[rIDs[i]];
        if (newID->mailBox.size() >= _K) {
            newID->mailBox.pop_front();
        }
        newID->mailBox.push_back(newMail);
    }
    return;
}

int getCount(int uID) {
    return user[uID].mailBox.size();
}

int deleteMail(int uID, char subject[]) {

    ull tmpWord[M_WORD] = { 0, };
    int tmpCnt = 0;
    string s(subject); istringstream iss(s); string str;
    while (iss >> str) {
        tmpWord[tmpCnt++] = hashMap[str];
    }

    int cnt = 0;
    for (auto it = user[uID].mailBox.begin(); it != user[uID].mailBox.end(); ) {
        bool valid = true;
        for (int i = 0; i < (*it)->cnt; i++) {
            if ((*it)->word[i] != tmpWord[i]) {
                valid = false;
                break;
            }
        }
        if (valid) {
            it = user[uID].mailBox.erase(it);
            cnt++;
        }
        else {
            ++it;
        }
    }
    return cnt;
}

int searchMail(int uID, char text[]) {
    ull tmpWord = hashMap[text];
    int cnt = 0;

    User* und = &user[uID];
    for (auto mail : und->mailBox) {
        for (int i = 0; i < mail->cnt; i++) {
            if (mail->word[i] == tmpWord) {
                cnt++;
                break;
            }
        }
    }
    return cnt;

}

*/