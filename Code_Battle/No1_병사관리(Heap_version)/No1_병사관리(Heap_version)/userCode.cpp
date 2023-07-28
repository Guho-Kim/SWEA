/*
#include<queue>
#include<iostream>
#define MAX_ID 100000
#define MAX_TEAM 5
#define MAX_SCORE 5

using namespace std;

struct Member {
    int mID, mTeam, mScore;

    // 비교 연산자 정의: Score를 기준으로 내림차순, Score가 같으면 mID를 기준으로 내림차순으로 정렬
    bool operator<(const Member& other) const {
        if (mScore != other.mScore) {
            return mScore < other.mScore; // Score가 더 큰 것이 우선순위가 높음 (내림차순)
        }
        return mID < other.mID; // Score가 같으면 mID가 더 큰 것이 우선순위가 높음 (내림차순)
    }
};

priority_queue<Member> members[MAX_TEAM + 1];
int teams[MAX_ID + 1];

void init()
{
    for (int i = 1; i <= MAX_TEAM; i++) {
        while (!(members[i].empty())) {
            members[i].pop();
        }
    }
    for (int i = 1; i <= MAX_ID; i++) {
        teams[i] = 0;
    }
}

void hire(int mID, int mTeam, int mScore)
{
    members[mTeam].push({ mID, mTeam, mScore });
    teams[mID] = mTeam;
}

void fire(int mID)
{
    priority_queue<Member> tempMember;
    int team = teams[mID];

    // members[0] is temp;
    while (!members[team].empty()) {
        Member topMember = members[team].top();
        members[team].pop();
        if (!(topMember.mID == mID)) {
            tempMember.push(topMember);
        }
    }
    members[team] = tempMember;

}

void updateSoldier(int mID, int mScore)
{
    priority_queue<Member> tempMember;
    int team = teams[mID];
    while (!(members[team].empty())) {
        Member topMember = members[team].top();
        members[team].pop();

        if (topMember.mID == mID) {
            topMember.mScore = mScore;
        }
        tempMember.push(topMember);
    }
    members[team] = tempMember;
}

void updateTeam(int mTeam, int mChangeScore)
{
    priority_queue<Member> tempMember;
    while (!members[mTeam].empty()) {
        Member topMember = members[mTeam].top();
        members[mTeam].pop();

        if (topMember.mScore + mChangeScore > 5) {
            topMember.mScore = 5;
        }
        else if (topMember.mScore + mChangeScore < 1) {
            topMember.mScore = 1;
        }
        else {
            topMember.mScore += mChangeScore;
        }

        tempMember.push(topMember);
    }
    members[mTeam] = tempMember;
}

int bestSoldier(int mTeam)
{
    Member bestMember = members[mTeam].top();

    return bestMember.mID;
}

*/