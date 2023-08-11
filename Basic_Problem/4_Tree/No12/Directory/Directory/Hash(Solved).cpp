
#include<string>
#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
#define NAME_MAXLEN 6
#define PATH_MAXLEN 2000
#define MAX_DIR 50000
#define MAX_CHILD 30

int totalChild;


struct Node {
	int name;
	Node* parent;
	Node* child[MAX_CHILD];
	int childCnt;
	int totalCnt;
};
Node* root;
Node nodes[MAX_DIR];

int nodeCnt;
void view(Node* node, int depth);

int getNameHash(char* pName) {
	unsigned long long hash = 0;
	int c;
	while (c = *pName++) {
		hash = (hash << 5) + hash + c;
	}
	return hash;
}

int getNameHashStr(string name) {
	unsigned long long hash = 0;
	for (int i = 0; i < name.size(); i++) {
		hash = (hash << 5) + hash + name[i];
	}
	return hash;
}

Node* getNode(int name) {
	nodes[nodeCnt].name = name;
	nodes[nodeCnt].totalCnt = 0;
	nodes[nodeCnt].childCnt = 0;
	return &nodes[nodeCnt++];
}

Node* findNode(string path) {
	if (path.size() == 1) return root;

	Node* node = root;
	string dir = "";
	int len = 0;
	for (int i = 1; i < path.size(); i++) {
		if (path[i] != '/') {
			len++;
			dir += path[i];
		}
		
		else {
			for (int j = 0; j < node->childCnt; j++) {
				if (getNameHashStr(dir) == node->child[j]->name) {
					node = node->child[j];
					break;
				}
			}
			dir = "";
			len = 0;
		}
	}
	return node;
}


void init(int n) {
	for (int i = 0; i < n; i++) {
		nodes[i].parent = nullptr;
		for (int j = 0; j < MAX_CHILD; j++) {
			nodes[i].child[j] = nullptr;
		}
	}
	nodeCnt = 0;
	root = getNode(getNameHashStr("/"));
}
void updateCnt(Node* node, int x) {
	while (node != root) {
		node = node->parent;
		node->totalCnt += x;
	}

}

void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
	Node* node = findNode(path);
	Node* newNode = getNode(getNameHash(name));
	getNameHash(name);
	newNode->parent = node;
	node->child[node->childCnt++] = newNode;
	updateCnt(newNode, 1);
	
}

void cmd_rm(char path[PATH_MAXLEN + 1]) {
	Node* node = findNode(path);
	Node* parent = node->parent;
	int idx;
	for (int i = 0; i < parent->childCnt; i++) {
		if (parent->child[i] == node) {
			idx = i;
			break;
		}
	}

	parent->childCnt--;
	parent->child[idx] = parent->child[parent->childCnt];
	parent->totalCnt -= node->totalCnt + 1;
	updateCnt(parent, -(node->totalCnt + 1));
	
	
}

void recursiveCopy(Node* src, Node* dest) {
	Node* newNode = getNode(src->name);
	newNode->parent = dest;
	dest->child[dest->childCnt++] = newNode;
	dest->totalCnt++;
	updateCnt(dest, 1);

	for (int i = 0; i < src->childCnt; i++) {
		recursiveCopy(src->child[i], newNode);
	}
}

void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	Node* src = findNode(srcPath);
	Node* dest = findNode(dstPath);
	
	recursiveCopy(src, dest);
	
	
}

void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	Node* node = findNode(srcPath);
	Node* parent = node->parent;
	int idx;
	for (int i = 0; i < parent->childCnt; i++) {
		if (parent->child[i] == node) {
			idx = i;
			break;
		}
	}
	parent->childCnt--;
	parent->child[idx] = parent->child[parent->childCnt];

	parent->totalCnt -= (node->totalCnt + 1);
	updateCnt(parent, -(node->totalCnt + 1));

	Node* dstNode = findNode(dstPath);

	node->parent = dstNode;
	dstNode->child[dstNode->childCnt++] = node;
	dstNode->totalCnt += node->totalCnt + 1;
	updateCnt(dstNode, (node->totalCnt + 1));

	
}

int cmd_find(char path[PATH_MAXLEN + 1]) {
	Node* node = findNode(path);
	cout << "Count\n" << node->totalCnt << "\n";
	return node->totalCnt;
}


void view(Node* node, int depth = 0) {
	for (int i = 0; i < depth; i++) {
		cout << "  ";
	}
	cout << "|_" << node->name << endl;
	for (int i = 0; i < node->childCnt; i++) {
		view(node->child[i], depth + 1);
	}
}
