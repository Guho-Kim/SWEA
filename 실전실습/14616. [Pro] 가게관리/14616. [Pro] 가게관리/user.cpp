/*
#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<vector>
#include<queue>
using namespace std;

struct Buy {
	int mProduct;
	int mPrice;
	int mQuantity;
	int mRest;
};
unordered_map<int, Buy> buys; 
unordered_map<int, int> productRest;	//상품별 남은 수량 <상품 번호, 수량>
int lastQIndex;
unordered_map<int, int> qIndex;
priority_queue < pair<int, int>, vector<pair<int, int>>, greater< pair<int, int>> q[601];

struct Node {
	int ID;
	int product;
	int price;
	int quantity;
	bool buy;
	bool sell;
};
vector<Node> buysellList;

unordered_map<int, int> um;	// product, quantity

void init() {
	buysellList.clear();
	return;
}

int buy(int bId, int mProduct, int mPrice, int mQuantity) {
	buysellList.push_back({ bId, mProduct, mPrice, mQuantity, true });
	if (um.find(mProduct) != um.end()) {
		um[mProduct] += mQuantity;
	}
	else {
		um.insert({mProduct, mQuantity});
	}
	
	return um[mProduct];
}

int cancel(int bId) {
	int result = 0;
	for (auto it = buysellList.begin(); it != buysellList.end();) {
		if ((*it).ID == bId && (*it).buy && um[(*it).product] >= (*it).quantity) {
			um[(*it).product] -= (*it).quantity;
			result = um[(*it).product];
			(*it).buy = false;
			it = buysellList.erase(it);
		}
		else {
			++it;
		}
	}
	if (result == 0) return -1;
	return result;
}

int sell(int sId, int mProduct, int mPrice, int mQuantity) {
	int result=0;
	buysellList.push_back({ sId, mProduct, mPrice, mQuantity, false });
	for (auto it = buysellList.begin(); it != buysellList.end(); it++) {
		if ((*it).ID == sId && (*it).sell) {
			result += (*it).price * (*it).quantity;
		}
	}
	return 0;
}

int refund(int sId) {
	int result = 0;
	for (auto it = buysellList.begin(); it != buysellList.end();) {
		if ((*it).ID == sId && (*it).sell) {
			(*it).sell = false;
			result += (*it).quantity;
			it = buysellList.erase(it);
		}
		else {
			++it;
		}
	}
	if (result == 0) return -1;
	return result;
}*/