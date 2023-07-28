#include <iostream>
#include <unordered_map>
#include <algorithm>

#define MAX_ID 100000
#define MAX_TEAM 5
using namespace std;

int ct = 0;

struct Soldier {
    int team;
    int score;
};

unordered_map<int, Soldier> soldiers[MAX_TEAM + 1];

int teams[MAX_ID + 1] = { 0 };

void viewTeam(int team) {
    for (auto& soldier : soldiers[team]) {
        cout << "Team: " << team << ", ID: " << soldier.first << ", score: " << soldier.second.score << endl;
    }
    cout << endl;
}

void init() {
    for (int i = 1; i <= MAX_TEAM; i++) {
        soldiers[i].clear();
        soldiers[i].reserve(MAX_ID);
    }
    for (int i = 1; i <= MAX_ID; i++)
        teams[i] = 0;
}

void hire(int mID, int mTeam, int mScore) {
    soldiers[mTeam].insert({mID,{mTeam, mScore}});
    teams[mID] = mTeam;
}

void fire(int mID) {
    soldiers[teams[mID]].erase(mID);
}

void updateSoldier(int mID, int mScore) {
    soldiers[teams[mID]][mID].score = mScore;
}

void updateTeam(int mTeam, int mChangeScore) {
    for (auto& soldier : soldiers[mTeam]) {
        int newScore = mChangeScore + soldier.second.score;
        soldier.second.score = max(1, min(5, newScore));
    }
}
int bestSoldier(int mTeam) {
    int maxScore = 0;
    int bestID = -1;
    int id, score;

    for (auto& soldier : soldiers[mTeam]) {
        id = soldier.first;
        score = soldier.second.score;
        if (score > maxScore || (score == maxScore && id > bestID)) {
            maxScore = score;
            bestID = id;
        }
    }

    return bestID;
}