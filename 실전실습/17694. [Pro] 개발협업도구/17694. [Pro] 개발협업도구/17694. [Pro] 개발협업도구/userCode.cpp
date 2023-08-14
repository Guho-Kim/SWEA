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
	string name;
	string data;
	int make_time;
	int update_time;
}files[MAX_BRANCH * MAX_FILE];

struct Branch {
	//for view
	string name;
	bool isValid;
	list<File*> file;
	int childCnt;
	Branch* child[MAX_CHILD];
	Branch* parent;
}branchs[MAX_BRANCH];

unordered_map<string, int> branchHash;
int branchCnt = 0;
int fileCnt;

//test
int cnt;


void printBranch(Branch* branch, int depth) {
	string indent(depth * 2, ' ');  // �鿩���⸦ ���� ���� ����

	// ���� �귣ġ�� ���� ���� ���
	
	if (branch->name == "qbkiilucm") {
		for (auto file : branch->file) {
				cout << indent << "- " << file->name << " - " <<file->data<< " - " << file->make_time << " - " << file->update_time << endl;
		}
		return;
	}

	// ���� �귣ġ�� �ڽ� �귣ġ�� ��������� ���
	for (int i = 0; i < branch->childCnt; i++) {
		//cout <<endl<< indent <<"<" << branch->child[i]->name <<">" << endl;
		printBranch(branch->child[i], depth + 1);
	}
}

void view() {
	cout << "<root>" << endl;
	printBranch(&branchs[1], 1);
	cout << endl;
}



void init() {
	//test
	cnt = 0;

	fileCnt = 0;
	branchHash.clear();
	for (int i = 0; i < branchCnt; i++) {
		branchs[i].file.clear();
		branchs[i].childCnt = 0;
	}
	branchCnt = 0;
	branchHash["root"] = ++branchCnt;

	//test
	branchs[branchCnt].name = "root";
}

void create(int mTime, char mBranch[], char mFile[], char mData[]) {
	File* newFile = &files[fileCnt++];
	newFile->name = mFile;
	newFile->data = mData;
	newFile->make_time = newFile->update_time = mTime;

	if (branchHash[mBranch] == 0) branchHash[mBranch] = ++branchCnt;

	int branch_idx = branchHash[mBranch];
	if (branchs[branch_idx].file.size() == 50) branchs[branch_idx].file.pop_front();
	branchs[branch_idx].file.push_back(newFile);
	branchs[branch_idx].isValid = true;
	
	//test
	branchs[branch_idx].name = mBranch;
	//if(900<cnt++ && cnt <950) view();
}

void edit(int mTime, char mBranch[], char mFile[], char mData[]) {
	int branch_idx = branchHash[mBranch];
	for (auto it = branchs[branch_idx].file.begin(); it != branchs[branch_idx].file.end(); it++) {
		if ((*it)->name == mFile) {
			(*it)->data = mData;
			(*it)->update_time = mTime;
			break;
		}
	}
}

void branch(int mTime, char mBranch[], char mChild[]) {
	int branch_idx = branchHash[mBranch];
	if (branchHash[mChild] == 0) branchHash[mChild] = ++branchCnt;
	int child_idx = branchHash[mChild];

	// branch ī�� �ּҸ� �ְ� �޾Ƽ� �����ϰ� ��. �ڷᱸ���� �����ϰų� branch ����
	//branchs[child_idx].file = branchs[branch_idx].file;
	for (auto it = branchs[branch_idx].file.begin(); it != branchs[branch_idx].file.end(); it++) {
		File* newFile = &files[fileCnt++];
		newFile->name = (*it)->name;
		newFile->data = (*it)->data;
		newFile->make_time= (*it)->make_time;
		newFile->update_time = (*it)->update_time;
		branchs[child_idx].file.push_back(newFile);
	}
	branchs[child_idx].isValid = true;
	// ����
	branchs[child_idx].parent = &branchs[branch_idx];
	branchs[branch_idx].child[branchs[branch_idx].childCnt++] = &branchs[child_idx];
	//test
	branchs[child_idx].name = mChild;
	//if(900<cnt++ && cnt <950) view();
}

void merge(Branch* branch) {
	Branch* parent = branch->parent;

	for (int i = 0; i < branch->childCnt; i++) {
		Branch* child = branch->child[i];
		if (child->isValid) merge(child);
	}
	//cout << "Parent: " << parent->name << "\n";
	//cout << "Child: " << branch->name << "\n";
	bool isNew;
	for (auto cit = branch->file.begin(); cit != branch->file.end(); cit++) {
		isNew = true;
		for (auto pit = parent->file.begin(); pit != parent->file.end(); pit++) {
			if ((*pit)->name == (*cit)->name) {
				isNew = false;
				if ((*pit)->make_time != (*cit)->make_time) {
					break;
				}
				else if ((*pit)->update_time < (*cit)->update_time) {
					(*pit)->update_time = (*cit)->update_time;
					(*pit)->data = (*cit)->data;
				}
				break;
			}
		}
		if (isNew) {
			File* newFile = &files[fileCnt++];
			newFile->name = (*cit)->name;
			newFile->data = (*cit)->data;
			newFile->make_time = (*cit)->make_time;
			newFile->update_time = (*cit)->update_time;
			if (parent->file.size() == 50) {
				parent->file.pop_front();
			}
			bool isPush = false;
			for (auto it = parent->file.begin(); it != parent->file.end(); it++) {
				if ((*it)->make_time > newFile->make_time) {
					parent->file.insert(it, newFile);
					isPush = true;
					break;
				}
			}
			if(!isPush) parent->file.push_back(newFile);
		}
	}
}

void merge(int mTime, char mBranch[]) {
	merge(&branchs[branchHash[mBranch]]);
	
	Branch* branch = &branchs[branchHash[mBranch]];
	Branch* parent = branch->parent;
	for (int i = 0; i < parent->childCnt; i++) {
		if (parent->child[i] == branch) {
			parent->child[i] = parent->child[parent->childCnt - 1];
			parent->childCnt--;
			break;
		}
	}
	//if(900<cnt++ && cnt <950) view();
}

int readfile(int mTime, char mBranch[], char mFile[], char retString[]) {
	int branch_idx = branchHash[mBranch];
	int len=0;
	for (auto it = branchs[branch_idx].file.begin(); it != branchs[branch_idx].file.end(); it++) {
		if ((*it)->name == mFile) {
			strcpy(retString, ((*it)->data).c_str());
			len = (*it)->data.size();
			break;
		}
	}
	//if(900<cnt++ && cnt <950) view();
	return len;
}

