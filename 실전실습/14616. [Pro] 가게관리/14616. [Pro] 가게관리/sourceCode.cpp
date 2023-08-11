#include <unordered_map>
#include <list>
#include <queue>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

struct Buy {
    int mProdcut;
    int mPrice;
    int mQuantity;
    int mRest;
};
struct Sell {
    bool isValid;
    int mProdcut;
    list<pair<int, int> >::iterator itBegin, itEnd;
};

unordered_map<int, Buy> buys;
unordered_map<int, int> productRest;

int lastqidx;
unordered_map<int, int> qidx;
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq[601];

unordered_map<int, Sell> sells;
list<pair<int, int> > sellHistory;

void init() {
    buys.clear();
    productRest.clear();
    qidx.clear();
    sellHistory.clear();
    for (int i = 1; i <= lastqidx; i++) {
        while (!pq[i].empty()) pq[i].pop();
    }
    lastqidx = 0;
}

int buy(int bId, int mProduct, int mPrice, int mQuantity) {
    buys[bId] = (Buy){mProduct, mPrice, mQuantity, mQuantity};

    productRest[mProduct] += mQuantity;
    
    if (qidx[mProduct] == 0) qidx[mProduct] = ++lastqidx;
    pq[qidx[mProduct]].push({ mPrice, bId });
    return productRest[mProduct];
}

int cancel(int bId) {
    auto it = buys.find(bId);
    if (it == buys.end() || it->second.mQuantity != it->second.mRest) {
        return -1;
    }

    productRest[it->second.mProdcut] -= it->second.mRest;
    it->second.mRest = 0;
    return  productRest[it->second.mProdcut];
}

int sell(int sId, int mProduct, int mPrice, int mQuantity) {
    if (productRest[mProduct] < mQuantity) return -1;

    productRest[mProduct] -= mQuantity;

    sells[sId].isValid = true;
    sells[sId].mProdcut = mProduct;
    sells[sId].itEnd = sellHistory.begin();

    int idx = qidx[mProduct];
    int profit = 0;
    while (mQuantity > 0) {
        int bId = pq[idx].top().second;
        int cnt = min(buys[bId].mRest, mQuantity);
        buys[bId].mRest -= cnt;
        mQuantity -= cnt;
        profit += (mPrice - buys[bId].mPrice) * cnt;
        sellHistory.push_front({ bId, cnt });
        if (buys[bId].mRest <= 0) pq[idx].pop();
    }
    sells[sId].itBegin = sellHistory.begin();

    return profit;
}

int refund(int sId) {
    if (!sells[sId].isValid) return -1;

    int cnt = 0;
    int idx = qidx[sells[sId].mProdcut];
    sells[sId].isValid = false;
    for (auto it = sells[sId].itBegin; it != sells[sId].itEnd; it++) {
        if (buys[it->first].mRest == 0) {
            pq[idx].push({ buys[it->first].mPrice, it->first });
        }
        buys[it->first].mRest += it->second;
        cnt += it->second;
    }

    productRest[sells[sId].mProdcut] += cnt;

    return cnt;
}
