#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<unordered_map>
using namespace std;
#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999
#define MAX_DIR 100000
#define MAX_CHILD 50

struct Node {
	string name;
	string path;
	Node* parent;
	Node* child[MAX_CHILD];
};

unordered_map<string, Node*> hashMap;		// path에 해당하는 노드의 주소 반환

Node nodes[MAX_DIR];
Node* root;
int nodeCnt;


Node* getNode(string name) {
	nodes[nodeCnt].name = name;
	for (int i = 0; i < MAX_CHILD; i++) {
		nodes[nodeCnt].child[i] = nullptr;
	}
	return &nodes[nodeCnt++];
}
string getNewPath(string path, string name) {
	string newPath(path);
	newPath += name + "/";
	return newPath;
}


void init(int n) {
	nodeCnt = 0;
	root = getNode("/");
	hashMap.clear();
	hashMap["/"] = root;
}


void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
	Node* node = hashMap[path];
	Node* newNode = getNode(name);
	newNode->parent = node;
	for (int i = 0; i < MAX_CHILD; i++) {
		if (node->child[i] == nullptr) {
			node->child[i] = newNode;
			break;
		}
	}
	string newPath = getNewPath(path, name);
	newNode->path = newPath;
	hashMap[newPath] = newNode;
}
void removeNodeFromHashMap(Node* node){
	for (int i = 0; i < MAX_CHILD; i++) {
		if (node->child[i] != nullptr) {
			hashMap.erase(node->child[i]->path);
			removeNodeFromHashMap(node->child[i]);
		}
	}
}

void cmd_rm(char path[PATH_MAXLEN + 1]) {
	Node* node = hashMap[path];
	Node* parent = node->parent;
	for (int i = 0; i < MAX_CHILD; i++) {
		if (parent->child[i] == node) {
			parent->child[i] = nullptr;
			break;
		}
	}
	hashMap.erase(node->path);
	removeNodeFromHashMap(node);
}



void recursiveCopy(Node* src, Node* dest, string path) {
	Node* newNode = getNode(src->name);
	newNode->parent = dest;
	for (int i = 0; i < MAX_CHILD; i++) {
		if (dest->child[i] == nullptr) {
			dest->child[i] = newNode;
			break;
		}
	}
	string newPath = getNewPath(path, newNode->name);
	hashMap[newPath] = newNode;
	for (int i = 0; i < MAX_CHILD; i++) {
		if (src->child[i] != nullptr) {
			recursiveCopy(src->child[i], newNode, newPath);
		}
	}
}

void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	Node* src = hashMap[srcPath];
	Node* dest = hashMap[dstPath];
	recursiveCopy(src, dest, dstPath);
}

void addNodeFromHashMap(Node* node, string path) {
	for (int i = 0; i < MAX_CHILD; i++) {
		if (node->child[i] != nullptr) {
			string newPath = getNewPath(path, node->child[i]->name);
			hashMap[newPath] = node->child[i];
			addNodeFromHashMap(node->child[i], newPath);
		}
	}
}

void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	Node* node = hashMap[srcPath];
	Node* parent = node->parent;
	for (int i = 0; i < MAX_CHILD; i++) {
		if (parent->child[i] == node) {
			parent->child[i] = nullptr;
			break;
		}
	}
	Node* dstNode = hashMap[dstPath];
	node->parent = dstNode;
	for (int i = 0; i < MAX_CHILD; i++) {
		if (dstNode->child[i] == nullptr) {
			dstNode->child[i] = node;
			break;
		}
	}
	removeNodeFromHashMap(node);

	string newPath = getNewPath(dstPath, node->name);
	node->path = newPath;
	hashMap[newPath] = node;
	addNodeFromHashMap(node, newPath);
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
	Node* node = hashMap[path];
	int count = recursiveCount(node);
	return count;
}



