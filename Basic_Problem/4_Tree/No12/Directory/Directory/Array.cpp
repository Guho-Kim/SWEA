/*

#include<iostream>
#include<string>
#include<cstring>
#include<vector>
using namespace std;
#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999
#define MAX_DIR 50010
#define MAX_CHILD 50


struct Node {
	string name;
	Node* child[MAX_CHILD];
};

Node nodes[MAX_DIR];
int nodeCnt;

Node* getNode(string name);
Node* findNode(string path);
void clearChild(Node* node);

Node* root = getNode("/");
void init(int n) {
	nodeCnt = 0;
	clearChild(root);
	root = getNode("/");
}


void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
	Node* node = findNode(path);
	Node* newNode = getNode(name);
	
	for (int i = 0; i < MAX_CHILD; i++) { // 배열 초기화
		if (node->child[i] == nullptr) {
			node->child[i] = newNode;
			break;
		}
	}
	
}

void cmd_rm(char path[PATH_MAXLEN + 1]) {
	string pathStr(path);
	int idx = 0;
	for (int i = pathStr.size() - 2; i >= 0; i--) {
		if (pathStr[i] == '/') {
			idx = i;
			break;
		}
	}
	string ppath = pathStr.substr(0, idx + 1);

	Node* parent = findNode(ppath);
	Node* node = findNode(path);
	for (int i = 0; i < MAX_CHILD; i++) { // 배열에서 해당 노드 검색 후 삭제
		if (parent->child[i] == node) {
			parent->child[i] = nullptr; // 해당 위치의 노드를 삭제
			break;
		}
	}
	
}

void recursiveCopy(Node* src, Node* dest) {
	Node* newNode = getNode(src->name);
	for (int i = 0; i < MAX_CHILD; i++) { // 배열 초기화
		if (dest->child[i] == nullptr) {
			dest->child[i] = newNode;
			break;
		}
	}

	for (int i = 0; i < MAX_CHILD; i++) { // 자식 노드 재귀적으로 복사
		if (src->child[i] != nullptr) {
			recursiveCopy(src->child[i], newNode);
		}
	}
}

void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	Node* src = findNode(srcPath);
	Node* dest = findNode(dstPath);

	recursiveCopy(src, dest);
	
}

void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	Node* node = findNode(srcPath);
	string pathStr(srcPath);
	int idx = 0;
	for (int i = pathStr.size() - 2; i >= 0; i--) {
		if (pathStr[i] == '/') {
			idx = i;
			break;
		}
	}
	string ppath = pathStr.substr(0, idx + 1);
	Node* parent = findNode(ppath);

	for (int i = 0; i < MAX_CHILD; i++) { // 배열에서 해당 노드 검색 후 삭제
		if (parent->child[i] == node) {
			parent->child[i] = nullptr; // 해당 위치의 노드를 삭제
			break;
		}
	}

	Node* dstNode = findNode(dstPath);
	for (int i = 0; i < MAX_CHILD; i++) { // 배열에 노드 추가
		if (dstNode->child[i] == nullptr) {
			dstNode->child[i] = node;
			break;
		}
	}
	
}

int recursiveCount(Node* node) {
	int count = 0;
	for (int i = 0; i < MAX_CHILD; i++) { // 자식 노드 개수 재귀적으로 계산
		if (node->child[i] != nullptr) {
			count += 1 + recursiveCount(node->child[i]);
		}
	}
	return count;
}

int cmd_find(char path[PATH_MAXLEN + 1]) {
	Node* node = findNode(path);
	int count = recursiveCount(node);
	return count;
}

Node* getNode(string name) {
	nodes[nodeCnt].name = name;
	for (int i = 0; i < MAX_CHILD; i++) {
		nodes[nodeCnt].child[i] = nullptr;
	}
	return &nodes[nodeCnt++];
}

Node* findNode(string path) {
	vector<string> vec;
	if (path.size() == 1) return root;

	Node* node = root;
	string dir = "";
	for (int i = 1; i < path.size(); i++) {
		if (path[i] != '/')
			dir += path[i];
		else {
			vec.push_back(dir);
			dir = "";
		}
	}

	for (int i = 0; i < vec.size(); i++) {
		for (int j = 0; j < MAX_CHILD; j++) { // 배열에서 해당 노드 검색
			if (node->child[j] != nullptr && vec[i] == node->child[j]->name) {
				node = node->child[j];
				break;
			}
		}
	}
	return node;
}

void clearChild(Node* node) {
	for (int i = 0; i < MAX_CHILD; i++) { // 자식 노드 모두 삭제
		if (node->child[i] != nullptr) {
			clearChild(node->child[i]);
			node->child[i] = nullptr;
		}
	}
}

*/