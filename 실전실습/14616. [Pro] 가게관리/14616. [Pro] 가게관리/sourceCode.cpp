#include <unordered_map>
#include <list>
#include <queue>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

struct Buy {
    int mProdcut;  // 상품 번호
    int mPrice;    // 구매 가격
    int mQuantity; // 구매 수량
    int mRest;     // 남은 수량
};
struct Sell {
    bool isValid; // 유효 여부
    int mProdcut; // 상품 번호
    list<pair<int, int> >::iterator itBegin, itEnd;
};

unordered_map<int, Buy> buys;
unordered_map<int, int> productRest;

int lastQIndex;
unordered_map<int, int> qIndex;
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q[601];

unordered_map<int, Sell> sells;
list<pair<int, int> > sellHistory;

void init() {
    // 모든 전역 변수를 초기화
    buys.clear();
    productRest.clear();
    qIndex.clear();
    sellHistory.clear();
    for (int i = 1; i <= lastQIndex; i++) {
        // priority_queue는 clear 함수가 없기 때문에, 비어있을 때까지 pop
        while (!q[i].empty()) q[i].pop();
    }
    lastQIndex = 0;
}

int buy(int bId, int mProduct, int mPrice, int mQuantity) {
    // 새로운 구매 정보 생성
    buys[bId] = (Buy){mProduct, mPrice, mQuantity, mQuantity};

    // 전체 상품 개수 변화
    productRest[mProduct] += mQuantity;

    // 메모리 풀을 이용한 우선순위 큐 인덱스 접근
    if (qIndex[mProduct] == 0) qIndex[mProduct] = ++lastQIndex;
    q[qIndex[mProduct]].push({ mPrice, bId });

    // 가게가 보유 중인 mProduct 상품의 총 개수를 반환
    return productRest[mProduct];
}

int cancel(int bId) {
    auto it = buys.find(bId);

    // bId로 구매했던 상품 수량이 모두 가게에 남아 있을 경우에만, 취소가 가능
    if (it == buys.end() || it->second.mQuantity != it->second.mRest) {
        return -1;
    }

    // 재고에서 bId로 구매했던 상품을 삭제
    productRest[it->second.mProdcut] -= it->second.mRest;
    it->second.mRest = 0;

    // 가게에 남아 있는 동일 상품의 개수를 반환
    return  productRest[it->second.mProdcut];
}

int sell(int sId, int mProduct, int mPrice, int mQuantity) {
    // mProduct 상품의 재고 수량이 mQuantity 보다 작다면, 판매에 실패
    if (productRest[mProduct] < mQuantity) return -1;

    // 전체 상품 개수 변화
    productRest[mProduct] -= mQuantity;

    // 새로운 판매 정보 생성
    sells[sId].isValid = true;
    sells[sId].mProdcut = mProduct;
    sells[sId].itEnd = sellHistory.begin();

    // 가장 싸게 구매한 상품, 구매 ID 값이 작은 상품부터 판매
    int index = qIndex[mProduct];
    int profit = 0;
    while (mQuantity > 0) {
        int bId = q[index].top().second;
        int cnt = min(buys[bId].mRest, mQuantity);
        buys[bId].mRest -= cnt;
        mQuantity -= cnt;
        profit += (mPrice - buys[bId].mPrice) * cnt;
        sellHistory.push_front({ bId, cnt });
        if (buys[bId].mRest <= 0) q[index].pop();
    }
    sells[sId].itBegin = sellHistory.begin();

    // 발생한 총 수익을 반환
    return profit;
}

int refund(int sId) {
    // sId로 판매한 내역이 없거나 이미 환불해준 판매 ID라면, 환불 실패
    if (!sells[sId].isValid) return -1;

    // sId로 판매한 상품에 대해 환불
    int cnt = 0;
    int index = qIndex[sells[sId].mProdcut];
    sells[sId].isValid = false;
    for (auto it = sells[sId].itBegin; it != sells[sId].itEnd; it++) {
        if (buys[it->first].mRest == 0) {
            q[index].push({ buys[it->first].mPrice, it->first });
        }
        buys[it->first].mRest += it->second;
        cnt += it->second;
    }

    // 전체 상품 개수 변화
    productRest[sells[sId].mProdcut] += cnt;

    // 환불해 준 상품의 총 개수를 반환
    return cnt;
}