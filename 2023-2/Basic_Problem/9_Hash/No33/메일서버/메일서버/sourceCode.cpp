/*
#include <stdio.h>
#include <memory.h>

#define R           register
#define M_USER      1000
#define M_MAIL      10000
#define M_WORD      10
#define M_BOX       5000
#define M_SUBJECT   120

int _N, _K;

struct t_mail
{
    long long word[M_WORD];
    int cnt;
}mail[M_MAIL];
int idx_mail;

struct t_user
{
    t_mail* box[M_BOX];
    int cnt;
    int start, end;
}user[M_USER];
int idx_user;

void init(int N, int K) {

    idx_user = idx_mail = 0;
    memset(mail, 0x00, sizeof(mail));
    memset(user, 0x00, sizeof(user));

    _N = N;
    _K = K;
}

void sendMail(char subject[], int uID, int cnt, int rIDs[]) {
    R t_mail* mnd = &mail[idx_mail++];
    mnd->cnt = 0;
    R int i = 0;
    while (1)
    {
        mnd->word[mnd->cnt] = 0;
        while (subject[i] != ' ' && subject[i] != '\0') {
            mnd->word[mnd->cnt] = (mnd->word[mnd->cnt] << 5) + (subject[i] - 'a' + 1);
            ++i;
        }
        ++mnd->cnt;
        if (subject[i++] == '\0') break;
    }

    for (R int k = 0; k < cnt; k++) {
        R t_user* und = &user[rIDs[k]];
        if (und->cnt >= _K) {
            R int b = 0;
            while (1)
            {
                if (und->box[b] != nullptr) {
                    und->box[b] = nullptr;
                    --und->cnt;
                    break;
                }
                ++b;
            }
        }
        und->box[und->end++] = mnd;
        ++und->cnt;

    }
    return;
}

int getCount(int uID) {
    return user[uID].cnt;
}

int deleteMail(int uID, char subject[]) {
    R long long tmpWord[M_WORD] = { 0, };
    R int tmpCnt = 0;

    R int i = 0;
    R int ret = 0;
    while (1) {
        tmpWord[tmpCnt] = 0;
        while (subject[i] != ' ' && subject[i] != '\0') {
            tmpWord[tmpCnt] = (tmpWord[tmpCnt] << 5) + (subject[i] - 'a' + 1);
            ++i;
        }
        ++tmpCnt;
        if (subject[i++] == '\0') break;
    }

    R t_user* und = &user[uID];
    R int boxCnt = 0;
    R int m = 0;
    while (und->cnt > boxCnt)
    {
        R t_mail* mnd = und->box[m];
        if (mnd == nullptr) {
            ++m;
            continue;
        }
        if (mnd->cnt == tmpCnt) {
            R int w = 0;
            while (w < mnd->cnt)
            {
                if (mnd->word[w] != tmpWord[w]) break;
                ++w;
            }
            if (w == mnd->cnt) {
                und->box[m] = nullptr;
                --und->cnt;
                ++ret;
            }
        }
        ++m;
        ++boxCnt;
    }
    return ret;
}

int searchMail(int uID, char text[]) {
    R long long tmpWord = 0;
    R int i = 0;
    R int ret = 0;

    while (text[i] != '\0') {
        tmpWord = (tmpWord << 5) + (text[i] - 'a' + 1);
        ++i;
    }

    R t_user* und = &user[uID];
    R int boxCnt = und->cnt - 1;
    R int m = 0;
    while (boxCnt >= 0) {
        R t_mail* mnd = und->box[m];
        if (mnd != nullptr) {
            for (R int w = 0; w < mnd->cnt; w++) {
                if (tmpWord == mnd->word[w]) {
                    ++ret;
                    break;
                }
            }
            --boxCnt;
        }
        ++m;
    }

    return ret;
}

*/