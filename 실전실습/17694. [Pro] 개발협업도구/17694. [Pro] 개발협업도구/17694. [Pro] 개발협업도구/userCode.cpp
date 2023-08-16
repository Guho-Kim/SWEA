/*
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<iostream>
#include<list>
#include<string>
#include<unordered_map>
#include<cstring>
#define MAX_FILE	50
#define MAX_BRANCH	10000
#define MAX_CHILD	100
using namespace std;

struct File {
	string name, data;
	int make_time, update_time;
};

struct Branch {
	bool isMerged;
	list<File> file;
	int childCnt;
	Branch* parent;
	Branch* child[MAX_CHILD];
}branchs[MAX_BRANCH];

unordered_map<string, int> branchHash;
int branchCnt;

void init() {
	branchHash.clear();
	
	for (int i = 1; i <= branchCnt; i++) {
		branchs[i].file.clear();
		branchs[i].childCnt = 0;
	}
	
	branchCnt = 0;
	branchHash["root"] = ++branchCnt;
}

void create(int mTime, char mBranch[], char mFile[], char mData[]) {
	Branch* branch = &branchs[branchHash[mBranch]];

	if (branch->file.size() == MAX_FILE) branch->file.pop_front();
	branch->file.push_back({ mFile, mData, mTime, mTime });
	
}

void edit(int mTime, char mBranch[], char mFile[], char mData[]) {
	Branch* branch = &branchs[branchHash[mBranch]];
	for (auto it = branch->file.begin(); it != branch->file.end(); it++) {
		if (it->name == mFile) {
			it->data = mData;
			it->update_time = mTime;
			break;
		}
	}
}

void branch(int mTime, char mBranch[], char mChild[]) {
	branchHash[mChild] = ++branchCnt;
	Branch* branch = &branchs[branchHash[mBranch]];
	Branch* child = &branchs[branchHash[mChild]];

	for (auto it = branch->file.begin(); it != branch->file.end(); it++) {
		child->file.push_back({ it->name ,it->data ,it->make_time ,it->update_time });
	}

	child->isMerged = false;
	// 연결
	child->parent = branch;
	branch->child[branch->childCnt++] = child;
}

void merge(Branch* branch) {
	Branch* parent = branch->parent;

	for (int i = 0; i < branch->childCnt; i++) {
		Branch* child = branch->child[i];
		if(!child->isMerged) merge(child);
	}
	for (auto it = branch->file.begin(); it != branch->file.end(); it++) {
		bool isNew = true;
		for (auto pit = parent->file.begin(); pit != parent->file.end(); pit++) {
			if (pit->name == it->name) {
				isNew = false;
				if (pit->make_time == it->make_time && pit->update_time < it->update_time) {
					pit->update_time = it->update_time;
					pit->data = it->data;
				}
				break;
			}
		}
		if (isNew) {
			auto pit = parent->file.begin();
			for (; pit != parent->file.end(); pit++) {
				if (pit->make_time > it->make_time)
					break;
			}
			parent->file.insert(pit, { it->name ,it->data ,it->make_time ,it->update_time });
		}
	}
	// 머지 후 50개 초과시 50개로 맞추기
	int fileSize = parent->file.size();
	while (fileSize > MAX_FILE) {
		parent->file.pop_front();
		fileSize--;
	}
	branch->isMerged = true;
}

void merge(int mTime, char mBranch[]) {
	merge(&branchs[branchHash[mBranch]]);
	
	Branch* branch = &branchs[branchHash[mBranch]];
	Branch* parent = branch->parent;
	
	for (int i = 0; i < parent->childCnt; i++) {
		if (parent->child[i] == branch) {
			parent->child[i] = parent->child[parent->childCnt - 1];
			break;
		}
	}
	parent->childCnt--;

	// 머지 후 50개 초과시 50개로 맞추기
	
	int fileSize = parent->file.size();
	while (fileSize > MAX_FILE) {
		parent->file.pop_front();
		fileSize--;
	}
}

int readfile(int mTime, char mBranch[], char mFile[], char retString[]) {
	Branch* branch = &branchs[branchHash[mBranch]];
	int len=0;
	for (auto it = branch->file.begin(); it != branch->file.end(); it++) {
		if (it->name == mFile) {
			strcpy(retString, (it->data).c_str());
			len = it->data.size();
			break;
		}
	}
	return len;
}


*/