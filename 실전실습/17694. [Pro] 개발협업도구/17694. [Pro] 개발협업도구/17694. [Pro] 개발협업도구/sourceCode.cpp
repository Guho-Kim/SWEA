/*

    1. ���� ť�� �Ϲ� ť�� �ٲ㺸��
    �ӵ� üũ
    2. ����Ʈ�� �ٲ㺸��
    �ӵ� üũ �� ���� �ڵ�� ��






*/
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <string>
#include <queue>
#include <algorithm>
#include <unordered_map>
#define MAX_CHAR_SIZE 11   // ���ϸ�, �귣ġ�� �ִ� ����
#define MAX_FILES_SIZE 50  // �귣ġ �ϳ��� ���� �� �ִ� �ִ� ���� ����
#define MAX_API_CALL 10000 // �ִ� API ȣ�� Ƚ��

using namespace std;

struct File {
    short createdTime; // ���� �ð�
    short editedTime;  // ���� �ð�
    string name, data; // ���ϸ�, ���ϳ���
};

struct Branch {
    bool isValid; // �귣ġ�� ��ȿ���� (�θ�� merge�Ǹ� false)
    string name;   // �귣ġ��
    short files_begin_pos, files_length; // ����� ���ϵ��� ���� ť�� ��ġ ����
    File files[MAX_FILES_SIZE];          // ����� ���ϵ��� ��� �ִ� ���� ť(�迭)

    Branch* parentBranch;        // �θ� �귣ġ
    queue<Branch*> childBranchs; // �ڽ� �귣ġ���� ��� �ִ� ť

    // ���� ť���� �� ���� ������ pop
    void pop_file_front() {
        File* file = &files[files_begin_pos];
        files_begin_pos = (files_begin_pos + 1) % MAX_FILES_SIZE;
        files_length -= 1;
    }

    // ���� ť�� �� �ڿ� ���ο� ������ push
    // ����, ���� ť�� ������(SIZE >= 50) push�� �Ұ��� �ϴٸ�, pop(���� ������ ���� ����) �� push
    void push_file_back(File _file) {
        if (files_length >= MAX_FILES_SIZE) pop_file_front();
        File* file = &files[(files_begin_pos + files_length) % MAX_FILES_SIZE];
        files_length += 1;
        *file = _file;

    }
};






Branch branch_pool[MAX_API_CALL + 1];            
short branch_cnt;                      

unordered_map<string, Branch*> branchMap;                     // �귣ġ �̸��� Ű��, �ش� �귣ġ�� �ּҸ� ������ ������ �ؽø�


// �귣ġ �̸��� �θ� �귣ġ �ּҰ� �־�����, ���ο� �귣ġ�� �����ϰ� �� �귣ġ�� �ּҸ� ��ȯ
Branch* create_branch(const char* branch_name, Branch* parentBranch) {
    Branch* branch = &branch_pool[branch_cnt++];

    // ���ο� �귣ġ�� �� �������� �ʱ�ȭ
    branch->isValid = true;
    branch->name = branch_name;
    branch->files_length = 0;
    branch->parentBranch = parentBranch;
    while (!branch->childBranchs.empty()) branch->childBranchs.pop();

    // `branchMap` �ؽøʿ� ���� ������ �귣ġ�� ����
    branchMap[branch_name] = branch;
    return branch;
}

File* find_file(const char* branch_name, const char* file_name) {
    Branch* branch = branchMap[branch_name];
    for (short i = 0; i < branch->files_length; i++) {
        File* file = &branch->files[(branch->files_begin_pos + i) % MAX_FILES_SIZE];
        if (file->name == file_name) return file;
    }
    return nullptr;
}


void init() {
    // ��� ���� �������� �ʱ�ȭ
    branchMap.clear();
    branch_cnt = 0;

    // `root` �귣ġ ����
    create_branch("root", nullptr);
}

void create(int mTime, char branch_name[], char file_name[], char data[]) {
    // �귣ġ�� ����� ������ �����ϴ� ���� ť�� �� ������ �߰�
    branchMap[branch_name]->push_file_back({
        (short)mTime,
        (short)mTime,
        file_name,
        data
        });
    
}

void edit(int mTime, char branch_name[], char file_name[], char data[]) {
    File* file = find_file(branch_name, file_name);
    file->editedTime = mTime;      // ������ �ֱ� ���� �ð� ������Ʈ
    file->data = data; // ������ ���� ����
    
}

void branch(int mTime, char parent_branch_name[], char child_branch_name[]) {
    Branch* parent_branch = branchMap[parent_branch_name];

    // ���ο� �귣ġ ����
    Branch* child_branch = create_branch(child_branch_name, parent_branch);

    // �θ� �귣ġ�� �ڽ� ��Ͽ� �� �귣ġ �߰�
    parent_branch->childBranchs.push(child_branch);

    // �θ� �귣ġ�� ��� ������ �ϳ��� �ڽ� �귣ġ�� ����
    for (short i = 0; i < parent_branch->files_length; i++) {
        short pos = (parent_branch->files_begin_pos + i) % MAX_FILES_SIZE;
        child_branch->push_file_back(parent_branch->files[pos]);
    }
    
}

queue<File> q1, q2;
unordered_map<string, File*> check_duplicated_filename;

void merge(Branch* branch) {
    Branch* parentBranch = branch->parentBranch;

    // ���������, branch �� �ڽ� �������� �б�� ������ ����
    while (!branch->childBranchs.empty()) {
        Branch* child = branch->childBranchs.front();
        if (child->isValid) merge(child);
        branch->childBranchs.pop();
    }

    check_duplicated_filename.clear();
    for (short i = 0; i < parentBranch->files_length; i++) {
        File* file = &parentBranch->files[(parentBranch->files_begin_pos + i) % MAX_FILES_SIZE];
        check_duplicated_filename[file->name] = file;
    }
    for (short i = 0; i < branch->files_length; i++) {
        File* file = &branch->files[(branch->files_begin_pos + i) % MAX_FILES_SIZE];
        auto it = check_duplicated_filename.find(file->name);
        if (it != check_duplicated_filename.end()) {
            // �ڽ� �귣ġ�� �θ� �귣ġ �� �� ������ �̸��� ������ ������ ���� ���, ���� �ð��� �����ϰ� �ڽ� �귣ġ�� ���� �ð��� �� �ֽ��� ���� �θ� �귣ġ�� ������ ������Ʈ�˴ϴ�.
            if (file->createdTime == it->second->createdTime && file->editedTime > it->second->editedTime) {
                *(it->second) = *file;
            }
        }
        else {
            q2.push(*file);
        }
    }
    for (short i = 0; i < parentBranch->files_length; i++) {
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
