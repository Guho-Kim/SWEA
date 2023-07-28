/*

#include <iostream>
#include <map>
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
        return mID < other.mID; // Score가 더 큰 것이 우선순위가 높음 (내림차순)
    }
};

map<int, Member, greater<int>> members[MAX_TEAM + 1];
int teams[MAX_ID + 1];

void viewTeam(int mTeam) {
    for (auto& member : members[mTeam]) {
        cout  << "Team: " << mTeam << ", ID : " << member.first << ", Score : " << member.second.mScore << endl;
    }
    cout << endl;
}

void init() {
    for (int i = 1; i <= MAX_TEAM; i++) {
        members[i].clear();
    }
    for (int i = 1; i <= MAX_ID; i++) {
        teams[i] = 0;
    }
}

void hire(int mID, int mTeam, int mScore) {
    //members[mTeam][mID] = {mID, mTeam, mScore };
    members[mTeam].insert({ mID, { mID, mTeam, mScore } });
    teams[mID] = mTeam;
    cout << "This is hire!\n";
//    cout <<"Team: "<< mTeam<<" " << members[mTeam].begin()->first << ", " << members[mTeam].begin()->second.mScore << endl;
    viewTeam(mTeam);
}

void fire(int mID) {
    int team = teams[mID];

    cout << "This is fire!\n";
    members[team].erase(mID);
    viewTeam(team);

}

void updateSoldier(int mID, int mScore) {
    int team = teams[mID];

    cout << "This is updateSoldier!\n";
    cout << members[team][mID].mScore << endl;
    members[team][mID].mScore = mScore;
    cout << members[team][mID].mScore << endl;
    viewTeam(team);
}

void updateTeam(int mTeam, int mChangeScore) {
    cout << "This is updateTeam of team " << mTeam << endl;

    for (auto& member : members[mTeam]) {
        if (member.second.mScore + mChangeScore > 5) {
            member.second.mScore = 5;
        }
        else if (member.second.mScore + mChangeScore < 1) {
            member.second.mScore = 1;
        }
        else {
            member.second.mScore += mChangeScore;
        }
    }

    viewTeam(mTeam);
}

int bestSoldier(int mTeam) {
    cout << "bestSoldier\n";
    cout <<"Team: "<< mTeam<<" " << members[mTeam].begin()->first << endl<<endl;
    return members[mTeam].begin()->first;
}
*/