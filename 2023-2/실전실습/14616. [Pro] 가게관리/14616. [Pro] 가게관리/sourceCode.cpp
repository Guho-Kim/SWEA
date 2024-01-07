#include <unordered_map>
#include <list>
#include <queue>

using namespace std;
using pii = pair<int, int>;
struct Buy {int product, price, quantity, rest;};
struct Sell {bool isSold; int product; list<pii>::iterator itBegin, itEnd;};

unordered_map<int, Buy> buys;
unordered_map<int, int> stock;      // 마켓에 상품 재고

int pqCnt;
unordered_map<int, int> qIndex;
priority_queue<pii, vector<pii>, greater<> > pq[601];

unordered_map<int, Sell> sells;
list<pii> sellHistory;

void init() {
    buys.clear();
    stock.clear();
    qIndex.clear();
    sellHistory.clear();
    for (int i = 1; i <= pqCnt; i++) while (!pq[i].empty()) pq[i].pop();
    pqCnt = 0;
}

int buy(int bId, int mProduct, int mPrice, int mQuantity) {
    buys[bId] = { mProduct, mPrice, mQuantity, mQuantity };

    // 마켓 재고
    stock[mProduct] += mQuantity;

    // 마켓 상품에 대한 구매 가격. 싸게 산 것부터 판매 예정
    if (qIndex[mProduct] == 0) qIndex[mProduct] = ++pqCnt;
    pq[qIndex[mProduct]].push({ mPrice, bId });

    // 가게가 보유 중인 mProduct 상품의 총 개수를 반환
    return stock[mProduct];
}

int cancel(int bId) {
    auto it = buys.find(bId);
    if (it == buys.end() || it->second.quantity != it->second.rest) return -1;

    stock[it->second.product] -= it->second.rest;
    it->second.rest = 0;

    return  stock[it->second.product];
}

int sell(int sId, int mProduct, int mPrice, int mQuantity) {
    if (stock[mProduct] < mQuantity) return -1;

    stock[mProduct] -= mQuantity;

    sells[sId].isSold = true;
    sells[sId].product = mProduct;
    sells[sId].itEnd = sellHistory.begin();

    int qindex = qIndex[mProduct];
    int profit = 0;
    while (mQuantity > 0) {
        int bId = pq[qindex].top().second;
        int cnt = buys[bId].rest < mQuantity ? buys[bId].rest : mQuantity;
        buys[bId].rest -= cnt;
        mQuantity -= cnt;
        profit += (mPrice - buys[bId].price) * cnt;
        sellHistory.push_front({ bId, cnt });
        if (buys[bId].rest <= 0) pq[qindex].pop();
    }
    sells[sId].itBegin = sellHistory.begin();

    return profit;
}

int refund(int sId) {
    if (!sells[sId].isSold) return -1;

    int cnt = 0;
    int qindex = qIndex[sells[sId].product];
    sells[sId].isSold = false;
    for (auto it = sells[sId].itBegin; it != sells[sId].itEnd; it++) {
        int bId = it->first;
        if (buys[bId].rest == 0) {
            pq[qindex].push({ buys[bId].price, bId });
        }
        buys[bId].rest += it->second;
        cnt += it->second;
    }

    stock[sells[sId].product] += cnt;

    return cnt;
}