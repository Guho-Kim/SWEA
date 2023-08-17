/*

    1. 원형 큐를 일반 큐로 바꿔보기
    속도 체크
    2. 리스트로 바꿔보기
    속도 체크 및 원래 코드랑 비교






*/
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <string>
#include <queue>
#include <algorithm>
#include <unordered_map>
#define MAX_CHAR_SIZE 11   // 파일명, 브랜치명 최대 길이
#define MAX_FILES_SIZE 50  // 브랜치 하나가 가질 수 있는 최대 파일 개수
#define MAX_API_CALL 10000 // 최대 API 호출 횟수

using namespace std;

struct File {
    short createdTime; // 생성 시각
    short editedTime;  // 수정 시각
    string name, data; // 파일명, 파일내용
};

struct Branch {
    bool isValid; // 브랜치의 유효여부 (부모로 merge되면 false)
    string name;   // 브랜치명
    short files_begin_pos, files_length; // 저장된 파일들을 원형 큐의 위치 정보
    File files[MAX_FILES_SIZE];          // 저장된 파일들을 담고 있는 원형 큐(배열)

    Branch* parentBranch;        // 부모 브랜치
    queue<Branch*> childBranchs; // 자식 브랜치들을 담고 있는 큐

    // 원형 큐에서 맨 앞의 파일을 pop
    void pop_file_front() {
        File* file = &files[files_begin_pos];
        files_begin_pos = (files_begin_pos + 1) % MAX_FILES_SIZE;
        files_length -= 1;
    }

    // 원형 큐의 맨 뒤에 새로운 파일을 push
    // 만약, 원형 큐가 가득차(SIZE >= 50) push가 불가능 하다면, pop(가장 오래된 파일 제거) 후 push
    void push_file_back(File _file) {
        if (files_length >= MAX_FILES_SIZE) pop_file_front();
        File* file = &files[(files_begin_pos + files_length) % MAX_FILES_SIZE];
        files_length += 1;
        *file = _file;

    }
};






Branch branch_pool[MAX_API_CALL + 1];            
short branch_cnt;                      

unordered_map<string, Branch*> branchMap;                     // 브랜치 이름을 키로, 해당 브랜치의 주소를 값으로 가지는 해시맵


// 브랜치 이름과 부모 브랜치 주소가 주어지면, 새로운 브랜치를 생성하고 그 브랜치의 주소를 반환
Branch* create_branch(const char* branch_name, Branch* parentBranch) {
    Branch* branch = &branch_pool[branch_cnt++];

    // 새로운 브랜치의 각 변수들을 초기화
    branch->isValid = true;
    branch->name = branch_name;
    branch->files_length = 0;
    branch->parentBranch = parentBranch;
    while (!branch->childBranchs.empty()) branch->childBranchs.pop();

    // `branchMap` 해시맵에 새로 생성된 브랜치를 맵핑
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
    // 모든 전역 변수들을 초기화
    branchMap.clear();
    branch_cnt = 0;

    // `root` 브랜치 생성
    create_branch("root", nullptr);
}

void create(int mTime, char branch_name[], char file_name[], char data[]) {
    // 브랜치에 저장된 파일을 관리하는 원형 큐에 새 파일을 추가
    branchMap[branch_name]->push_file_back({
        (short)mTime,
        (short)mTime,
        file_name,
        data
        });
    
}

void edit(int mTime, char branch_name[], char file_name[], char data[]) {
    File* file = find_file(branch_name, file_name);
    file->editedTime = mTime;      // 파일의 최근 수정 시각 업데이트
    file->data = data; // 파일의 내용 수정
    
}

void branch(int mTime, char parent_branch_name[], char child_branch_name[]) {
    Branch* parent_branch = branchMap[parent_branch_name];

    // 새로운 브랜치 생성
    Branch* child_branch = create_branch(child_branch_name, parent_branch);

    // 부모 브랜치의 자식 목록에 새 브랜치 추가
    parent_branch->childBranchs.push(child_branch);

    // 부모 브랜치의 모든 파일을 하나씩 자식 브랜치에 복사
    for (short i = 0; i < parent_branch->files_length; i++) {
        short pos = (parent_branch->files_begin_pos + i) % MAX_FILES_SIZE;
        child_branch->push_file_back(parent_branch->files[pos]);
    }
    
}

queue<File> q1, q2;
unordered_map<string, File*> check_duplicated_filename;

void merge(Branch* branch) {
    Branch* parentBranch = branch->parentBranch;

    // 재귀적으로, branch 의 자식 가지들을 분기된 순으로 병합
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
            // 자식 브랜치와 부모 브랜치 둘 다 동일한 이름의 파일을 가지고 있을 경우, 생성 시간이 동일하고 자식 브랜치의 수정 시간이 더 최신일 때만 부모 브랜치의 파일이 업데이트됩니다.
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
