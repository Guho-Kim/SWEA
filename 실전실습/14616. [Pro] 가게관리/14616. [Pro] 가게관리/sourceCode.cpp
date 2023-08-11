#include <unordered_map>
#include <list>
#include <queue>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

struct Buy {
    int mProdcut;  // ��ǰ ��ȣ
    int mPrice;    // ���� ����
    int mQuantity; // ���� ����
    int mRest;     // ���� ����
};
struct Sell {
    bool isValid; // ��ȿ ����
    int mProdcut; // ��ǰ ��ȣ
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
    // ��� ���� ������ �ʱ�ȭ
    buys.clear();
    productRest.clear();
    qIndex.clear();
    sellHistory.clear();
    for (int i = 1; i <= lastQIndex; i++) {
        // priority_queue�� clear �Լ��� ���� ������, ������� ������ pop
        while (!q[i].empty()) q[i].pop();
    }
    lastQIndex = 0;
}

int buy(int bId, int mProduct, int mPrice, int mQuantity) {
    // ���ο� ���� ���� ����
    buys[bId] = (Buy){mProduct, mPrice, mQuantity, mQuantity};

    // ��ü ��ǰ ���� ��ȭ
    productRest[mProduct] += mQuantity;

    // �޸� Ǯ�� �̿��� �켱���� ť �ε��� ����
    if (qIndex[mProduct] == 0) qIndex[mProduct] = ++lastQIndex;
    q[qIndex[mProduct]].push({ mPrice, bId });

    // ���԰� ���� ���� mProduct ��ǰ�� �� ������ ��ȯ
    return productRest[mProduct];
}

int cancel(int bId) {
    auto it = buys.find(bId);

    // bId�� �����ߴ� ��ǰ ������ ��� ���Կ� ���� ���� ��쿡��, ��Ұ� ����
    if (it == buys.end() || it->second.mQuantity != it->second.mRest) {
        return -1;
    }

    // ����� bId�� �����ߴ� ��ǰ�� ����
    productRest[it->second.mProdcut] -= it->second.mRest;
    it->second.mRest = 0;

    // ���Կ� ���� �ִ� ���� ��ǰ�� ������ ��ȯ
    return  productRest[it->second.mProdcut];
}

int sell(int sId, int mProduct, int mPrice, int mQuantity) {
    // mProduct ��ǰ�� ��� ������ mQuantity ���� �۴ٸ�, �Ǹſ� ����
    if (productRest[mProduct] < mQuantity) return -1;

    // ��ü ��ǰ ���� ��ȭ
    productRest[mProduct] -= mQuantity;

    // ���ο� �Ǹ� ���� ����
    sells[sId].isValid = true;
    sells[sId].mProdcut = mProduct;
    sells[sId].itEnd = sellHistory.begin();

    // ���� �ΰ� ������ ��ǰ, ���� ID ���� ���� ��ǰ���� �Ǹ�
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

    // �߻��� �� ������ ��ȯ
    return profit;
}

int refund(int sId) {
    // sId�� �Ǹ��� ������ ���ų� �̹� ȯ������ �Ǹ� ID���, ȯ�� ����
    if (!sells[sId].isValid) return -1;

    // sId�� �Ǹ��� ��ǰ�� ���� ȯ��
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

    // ��ü ��ǰ ���� ��ȭ
    productRest[sells[sId].mProdcut] += cnt;

    // ȯ���� �� ��ǰ�� �� ������ ��ȯ
    return cnt;
}