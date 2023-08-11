#include <iostream>
#include <algorithm>
#include <cmath>
#include <set>
using namespace std;
int Charge;
struct Result {int mPrice, mPerformance; };
struct Part {int type, price, performance, position; };

struct cmp{
    bool operator()(const Part& a, const Part& b)const{
        if(a.performance == b.performance)
            return a.price > b.price;
        return a.performance > b.performance;
    }
};
set<Part, cmp> warehouse[2][3];

void init(int mCharge) {
    Charge = mCharge;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            warehouse[i][j].clear();
        }
    }
}

int stock(int mType, int mPrice, int mPerformance, int mPosition) {
    warehouse[mPosition][mType].insert({ mType, mPrice, mPerformance, mPosition });
    return warehouse[mPosition][mType].size();
}


Result order(int mBudget) {
    Result result;
    result.mPrice = 0;
    result.mPerformance = 0;
    for (int i = 0; i < 2; i++) {for (int j = 0; j < 2; j++) {for (int k = 0; k < 2; k++) {
        for (auto& part0 : warehouse[i][0]) {
            if (part0.price > mBudget || part0.performance < result.mPerformance) continue;
            for (auto& part1 : warehouse[j][1]) {
                if (part0.price + part1.price > mBudget || part1.performance < result.mPerformance) continue;
                for (auto& part2 : warehouse[k][2]) {
                    if (part2.performance < result.mPerformance) continue;
                    int price = part0.price + part1.price + part2.price;
                    if (!(i == j && j == k)) price += Charge;
                    if (price <= mBudget) {
                        int performance = min(part0.performance, min(part1.performance, part2.performance));
                        if (performance > result.mPerformance) {
                            result.mPerformance = performance;
                            result.mPrice = price;
                        }
                        else if (performance == result.mPerformance) {
                            result.mPrice = min(result.mPrice, price);
                        }

                    }
                }
            }
        }
    }}}

    return result;
}