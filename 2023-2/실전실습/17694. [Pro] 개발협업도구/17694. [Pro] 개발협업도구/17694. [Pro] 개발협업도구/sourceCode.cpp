#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <string>
#include <string.h>
#include <queue>
#include <algorithm>
#include <unordered_map>
#define MAX_CHAR_SIZE 11
#define MAX_FILES_SIZE 50
#define MAX_API_CALL 10000

using namespace std;

struct File {
    int createdTime;
    int editedTime;
    string name, data;
};

struct Branch {
    bool isValid;
    string name;
    int files_begin_pos, files_length;
    File files[MAX_FILES_SIZE];

    Branch* parentBranch;
    queue<Branch*> childBranchs;

    void pop_file_front() {
        File* file = &files[files_begin_pos];
        files_begin_pos = (files_begin_pos + 1) % MAX_FILES_SIZE;
        files_length -= 1;
    }

    void push_file_back(File _file) {
        if (files_length >= MAX_FILES_SIZE) pop_file_front();
        File* file = &files[(files_begin_pos + files_length) % MAX_FILES_SIZE];
        files_length += 1;
        *file = _file;

    }
};




Branch branch_pool[MAX_API_CALL + 1];            
int branch_pool_last_idx;                      

unordered_map<string, Branch*> branchMap;                     

Branch* create_branch(const char* branch_name, Branch* parentBranch) {
    Branch* branch = &branch_pool[branch_pool_last_idx++];

    branch->isValid = true;
    branch->name = branch_name;
    branch->files_length = 0;
    branch->parentBranch = parentBranch;
    while (!branch->childBranchs.empty()) branch->childBranchs.pop();

    branchMap[branch_name] = branch;
    return branch;
}

File* find_file(const char* branch_name, const char* file_name) {
    Branch* branch = branchMap[branch_name];
    for (int i = 0; i < branch->files_length; i++) {
        File* file = &branch->files[(branch->files_begin_pos + i) % MAX_FILES_SIZE];
        if (file->name == file_name) return file;
    }
    return nullptr;
}


void init() {
    branchMap.clear();
    for (int i = 0; i < branch_pool_last_idx; i++) {
        while (!branch_pool[i].childBranchs.empty()) branch_pool[i].childBranchs.pop();
    }
    branch_pool_last_idx = 0;

    create_branch("root", nullptr);
}

void create(int mTime, char branch_name[], char file_name[], char data[]) {
    branchMap[branch_name]->push_file_back({
        mTime,
        mTime,
        file_name,
        data
     });

}

void edit(int mTime, char branch_name[], char file_name[], char data[]) {
    File* file = find_file(branch_name, file_name);
    file->editedTime = mTime;
    file->data = data;

}

void branch(int mTime, char parent_branch_name[], char child_branch_name[]) {
    Branch* parent_branch = branchMap[parent_branch_name];

    Branch* child_branch = create_branch(child_branch_name, parent_branch);

    parent_branch->childBranchs.push(child_branch);

    for (int i = 0; i < parent_branch->files_length; i++) {
        int pos = (parent_branch->files_begin_pos + i) % MAX_FILES_SIZE;
        child_branch->push_file_back(parent_branch->files[pos]);
    }

}

queue<File> q1, q2;
unordered_map<string, File*> check_duplicated_filename;

void merge(Branch* branch) {
    Branch* parentBranch = branch->parentBranch;

    while (!branch->childBranchs.empty()) {
        Branch* child = branch->childBranchs.front();
        if (child->isValid) merge(child);
        branch->childBranchs.pop();
    }

    check_duplicated_filename.clear();
    for (int i = 0; i < parentBranch->files_length; i++) {
        File* file = &parentBranch->files[(parentBranch->files_begin_pos + i) % MAX_FILES_SIZE];
        check_duplicated_filename[file->name] = file;
    }
    for (int i = 0; i < branch->files_length; i++) {
        File* file = &branch->files[(branch->files_begin_pos + i) % MAX_FILES_SIZE];
        auto it = check_duplicated_filename.find(file->name);
        if (it != check_duplicated_filename.end()) {
            if (file->createdTime == it->second->createdTime && file->editedTime > it->second->editedTime) {
                *(it->second) = *file;
            }
        }
        else {
            q2.push(*file);
        }
    }
    for (int i = 0; i < parentBranch->files_length; i++) {
        File* file = &parentBranch->files[(parentBranch->files_begin_pos + i) % MAX_FILES_SIZE];
        q1.push(*file);
    }

    parentBranch->files_length = 0;
    while (!q1.empty() || !q2.empty()) {
        auto q = (q2.empty() || !q1.empty() && !q2.empty() && q1.front().createdTime < q2.front().createdTime) ? &q1 : &q2;
        parentBranch->push_file_back(q->front());
        q->pop();
    }
    branch->isValid = false;
}

void merge(int mTime, char branch_name[]) {
    merge(branchMap[branch_name]);
}

int readfile(int mTime, char branch_name[], char file_name[], char ret[]) {
    File* file = find_file(branch_name, file_name);
    strcpy(ret, file->data.c_str());

    return file->data.size();
}
