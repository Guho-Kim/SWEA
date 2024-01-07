#include <string>
#include <unordered_map>
#define MAX_PARENT_LENGTH 14
#define MAX_MDAY 1048576

using namespace std;
struct Node {
    short depth;
    Node* parent[MAX_PARENT_LENGTH];
};

unordered_map<string, Node> tree;
int power[MAX_PARENT_LENGTH];

int nn = 0;
int segTree[MAX_MDAY * 2];

// segTree의 [x, y] 범위에 1 증가
void segTreePush(int idx, int l, int r, int x, int y) {
    int mid = (l + r) / 2;
    if (r < x || y < l) return;
    if (x <= l && r <= y) {
        segTree[idx] += 1;
        return;
    }
    segTreePush(idx * 2, l, mid, x, y);
    segTreePush(idx * 2 + 1, mid + 1, r, x, y);
}

void init(char mAncestor[], int mDeathday) {
    tree.clear();

    power[0] = 1;
    for (short i = 1; i < MAX_PARENT_LENGTH; i++) {
        power[i] = power[i - 1] * 2;
    }
    for (int i = 0; i < MAX_MDAY * 2; i++) {
        segTree[i] = 0;
    }
    segTreePush(1, 0, MAX_MDAY - 1, 0, mDeathday);
}

int add(char mName[], char mParent[], int mBirthday, int mDeathday) {
    Node* node = &tree[mName];
    node->parent[0] = &tree[mParent];
    node->depth = node->parent[0]->depth + 1;
    for (short i = 1; i < MAX_PARENT_LENGTH; i++) {
        if (node->parent[i - 1] == NULL) break;
        node->parent[i] = node->parent[i - 1]->parent[i - 1];
    }
    segTreePush(1, 0, MAX_MDAY - 1, mBirthday, mDeathday);
    return node->depth;
}

int distance(char mName1[], char mName2[]) {
    short dist = 0;
    Node* node1 = &tree[mName1];
    Node* node2 = &tree[mName2];

    if (node1->depth < node2->depth) {
        Node* tmp = node1;
        node1 = node2;
        node2 = tmp;
    }
    for (short i = MAX_PARENT_LENGTH - 1; i >= 0; i--) {
        if (node1->depth - node2->depth >= power[i]) {
            dist += power[i];
            node1 = node1->parent[i];
        }
    }
    for (short i = MAX_PARENT_LENGTH - 1; i >= 0; i--) {
        if (node1->parent[i] != node2->parent[i]) {
            dist += power[i] * 2;
            node1 = node1->parent[i];
            node2 = node2->parent[i];
        }
    }
    return dist + (node1 != node2 ? 2 : 0);
}

int count(int mDay) {
    int idx = mDay + MAX_MDAY;
    int cnt = 0;
    while (idx > 0) {
        cnt += segTree[idx];
        idx /= 2;
    }
    return cnt;
}