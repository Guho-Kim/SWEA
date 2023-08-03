/*
#include<iostream>
#include<cstring>

using namespace std;
#define MAXN 100000
typedef enum
{
	NAME,
	NUMBER,
	BIRTHDAY,
	EMAIL,
	MEMO
} FIELD;
typedef struct
{
	int count;
	char str[20];
} RESULT;


typedef struct Node {
    char name[20];
    char number[20];
    char birthday[20];
    char email[20];
    char memo[20];
    struct Node* next;
} Node;

Node* head = nullptr;
Node nodePool[MAXN];
int nodeCnt;


void InitDB()
{
    nodeCnt = 0;
    head = nullptr;
}
Node* getNode() {
    return &nodePool[nodeCnt++];
}

void Add(char* name, char* number, char* birthday, char* email, char* memo)
{
    Node* newNode = getNode();

    strcpy(newNode->name, name);
    strcpy(newNode->number, number);
    strcpy(newNode->birthday, birthday);
    strcpy(newNode->email, email);
    strcpy(newNode->memo, memo);
    newNode->next = head;
    head = newNode;
}

int Delete(FIELD field, char* str)
{
    int cnt = 0;
    Node* prev = nullptr;
    Node* curr = head;
    while (curr != nullptr) {
        char* fieldValue = nullptr;
        switch (field) {
        case NAME:
            fieldValue = curr->name;
            break;
        case NUMBER:
            fieldValue = curr->number;
            break;
        case BIRTHDAY:
            fieldValue = curr->birthday;
            break;
        case EMAIL:
            fieldValue = curr->email;
            break;
        case MEMO:
            fieldValue = curr->memo;
            break;
        default:
            break;
        }
        if (strcmp(fieldValue, str) == 0 && fieldValue != nullptr) {
            if (prev == nullptr) {
                head = curr->next;
                //delete curr;
                curr = head;
            }
            else {
                prev->next = curr->next;
                //delete curr;
                curr = prev->next;
            }
            cnt++;
        }
        else {
            prev = curr;
            curr = curr->next;
        }
    }
    return cnt;
}

int Change(FIELD field, char* str, FIELD changefield, char* changestr)
{
    int cnt = 0;
    Node* curr = head;
    while (curr != nullptr) {
        char* fieldValue = nullptr;
        switch (field) {
        case NAME:
            fieldValue = curr->name;
            break;
        case NUMBER:
            fieldValue = curr->number;
            break;
        case BIRTHDAY:
            fieldValue = curr->birthday;
            break;
        case EMAIL:
            fieldValue = curr->email;
            break;
        case MEMO:
            fieldValue = curr->memo;
            break;
        default:
            break;
        }
        if (strcmp(fieldValue, str) == 0 && fieldValue != nullptr) {
            switch (changefield) {
            case NAME:
                strcpy(curr->name, changestr);
                break;
            case NUMBER:
                strcpy(curr->number, changestr);
                break;
            case BIRTHDAY:
                strcpy(curr->birthday, changestr);
                break;
            case EMAIL:
                strcpy(curr->email, changestr);
                break;
            case MEMO:
                strcpy(curr->memo, changestr);
                break;
            default:
                break;
            }
            cnt++;
        }
        curr = curr->next;
    }
    return cnt;
}


RESULT Search(FIELD field, char* str, FIELD ret_field)
{
    RESULT result;
    result.count = 0;
    int cnt = 0;
    Node* curr = head;
    while (curr != nullptr) {
        char* fieldValue = nullptr;
        switch (field) {
        case NAME:
            fieldValue = curr->name;
            break;
        case NUMBER:
            fieldValue = curr->number;
            break;
        case BIRTHDAY:
            fieldValue = curr->birthday;
            break;
        case EMAIL:
            fieldValue = curr->email;
            break;
        case MEMO:
            fieldValue = curr->memo;
            break;
        default:
            break;
        }

        if (fieldValue != nullptr && strcmp(fieldValue, str) == 0) {
            cnt++;
            if (cnt == 1) {
                switch (ret_field) {
                case NAME:
                    strcpy(result.str, curr->name);
                    break;
                case NUMBER:
                    strcpy(result.str, curr->number);
                    break;
                case BIRTHDAY:
                    strcpy(result.str, curr->birthday);
                    break;
                case EMAIL:
                    strcpy(result.str, curr->email);
                    break;
                case MEMO:
                    strcpy(result.str, curr->memo);
                    break;
                default:
                    break;
                }
            }
        }
        curr = curr->next;
    }
    result.count = cnt;
    return result;
}
*/