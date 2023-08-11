/*
#include<string>
#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999
#define MAX_DIR 100000

int totalChild;

struct Node {
	Node* parent;
	string name;
	vector<Node*> child;
};

Node nodes[MAX_DIR];
int nodeCnt;

Node* getNode(string name);
Node* findNode(string path);
void clearChild(Node* node);
void view(Node* node, int depth);
Node* root = getNode("/");

void init(int n) {
	nodeCnt = 0;
	clearChild(root);
	root = getNode("/");
	root->parent=nullptr;
}


void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
	Node* node = findNode(path);
	Node* newNode = getNode(name);
	newNode->parent = node;
	node->child.push_back(newNode);
	
}

void cmd_rm(char path[PATH_MAXLEN + 1]) {
	Node* node = findNode(path);
	Node* parent = node->parent;
	for (auto it = parent->child.begin(); it != parent->child.end(); it++) {
		if (*it == node) {
			parent->child.erase(it);
			break;
		}
	}
	clearChild(node);
	
}

void recursiveCopy(Node* src, Node* dest) {
	Node* newNode = getNode(src->name);
	newNode->parent = dest;
	dest->child.push_back(newNode);

	for (Node* child : src->child) {
		recursiveCopy(child, newNode);
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

	for (auto it = parent->child.begin(); it != parent->child.end(); it++) {
		if (*it == node) {
			parent->child.erase(it);
			break;
		}
	}
	Node* dstNode = findNode(dstPath);
	dstNode->child.push_back(node);
	node->parent = dstNode;
	
}

int recursiveCount(Node* node) {
	int count = 0;
	for (Node* child : node->child) {
		count += 1 + recursiveCount(child);
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
	nodes[nodeCnt].child.clear();
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
		for (int j = 0; j < node->child.size(); j++) {
			if (vec[i] == node->child[j]->name) {
				node = node->child[j];
				break;
			}
		}
	}
	return node;
}

void clearChild(Node* node) {
	for (Node* child : node->child) {
		clearChild(child);
	}
	node->child.clear();
}


void view(Node* node, int depth = 0) {
	for (int i = 0; i < depth; i++) {
		cout << "  ";
	}
	cout << "|_" << node->name << endl;
	for (Node* child : node->child) {
		view(child, depth + 1);
	}
}
*/