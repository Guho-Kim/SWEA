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
	Node* parent;
	Node* child[MAX_CHILD];
};

Node nodes[MAX_DIR];
int nodeCnt;

Node* getNode(string name);
Node* findNode(string path);


Node* root;
void init(int n) {
	nodeCnt = 0;
	root = getNode("/");
}


void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
	Node* node = findNode(path);
	Node* newNode = getNode(name);
	newNode->parent = node;
	for (int i = 0; i < MAX_CHILD; i++) {
		if (node->child[i] == nullptr) {
			node->child[i] = newNode;
			break;
		}
	}
}

void cmd_rm(char path[PATH_MAXLEN + 1]) {
	Node* node = findNode(path);
	Node* parent = node->parent;
	for (int i = 0; i < MAX_CHILD; i++) {
		if (parent->child[i] == node) {
			parent->child[i] = nullptr;
			break;
		}
	}
}

void recursiveCopy(Node* src, Node* dest) {
	Node* newNode = getNode(src->name);
	newNode->parent = dest;
	for (int i = 0; i < MAX_CHILD; i++) {
		if (dest->child[i] == nullptr) {
			dest->child[i] = newNode;
			break;
		}
	}
	for (int i = 0; i < MAX_CHILD; i++) {
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
	Node* parent = node->parent;
	for (int i = 0; i < MAX_CHILD; i++) {
		if (parent->child[i] == node) {
			parent->child[i] = nullptr;
			break;
		}
	}
	Node* dstNode = findNode(dstPath);
	node->parent = dstNode;
	for (int i = 0; i < MAX_CHILD; i++) {
		if (dstNode->child[i] == nullptr) {
			dstNode->child[i] = node;
			break;
		}
	}
}

int recursiveCount(Node* node) {
	int count = 0;
	for (int i = 0; i < MAX_CHILD; i++) {
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
		for (int j = 0; j < MAX_CHILD; j++) {
			if (node->child[j] != nullptr && vec[i] == node->child[j]->name) {
				node = node->child[j];
				break;
			}
		}
	}
	return node;
}

*/