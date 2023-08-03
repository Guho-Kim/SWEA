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

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
struct Contact {
	char name[20];
	char number[20];
	char birthday[20];
	char email[20];
	char memo[20];
};
Contact contacts[MAXN];
int contactCnt;
void InitDB()
{
	contactCnt = 0;
}

void Add(char* name, char* number, char* birthday, char* email, char* memo)
{
	strcpy(contacts[contactCnt].name, name);
	strcpy(contacts[contactCnt].number, number);
	strcpy(contacts[contactCnt].birthday, birthday);
	strcpy(contacts[contactCnt].email, email);
	strcpy(contacts[contactCnt].memo, memo);
	contactCnt++;
}

int Delete(FIELD field, char* str)
{
	int cnt = 0;
	for (int i = 0; i < contactCnt; i++) {
		char* fieldValue = nullptr;
		switch (field) {
			case NAME: fieldValue = contacts[i].name; break;
			case NUMBER: fieldValue = contacts[i].number; break;
			case BIRTHDAY: fieldValue = contacts[i].birthday; break;
			case EMAIL:	fieldValue = contacts[i].email;	break;
			case MEMO: fieldValue = contacts[i].memo; break;
			default:break;
		}
		if (strcmp(fieldValue, str) == 0 && fieldValue != nullptr) {
			contacts[i] = contacts[contactCnt - 1];
			contactCnt--;
			cnt++;
			i--;
		}
	}
	return cnt;
}

int Change(FIELD field, char* str, FIELD changefield, char* changestr)
{
	int cnt = 0;
	for (int i = 0; i < contactCnt; i++) {
		char* fieldValue = nullptr;
		switch (field) {
			case NAME: fieldValue = contacts[i].name; break;
			case NUMBER: fieldValue = contacts[i].number; break;
			case BIRTHDAY: fieldValue = contacts[i].birthday; break;
			case EMAIL:	fieldValue = contacts[i].email;	break;
			case MEMO: fieldValue = contacts[i].memo; break;
			default: break;
		}

		if (strcmp(fieldValue, str) == 0 && fieldValue != nullptr) {
			switch (changefield) {
				case NAME:
					strcpy(contacts[i].name, changestr);
					break;
				case NUMBER:
					strcpy(contacts[i].number, changestr);
					break;
				case BIRTHDAY:
					strcpy(contacts[i].birthday, changestr);
					break;
				case EMAIL:
					strcpy(contacts[i].email, changestr);
					break;
				case MEMO:
					strcpy(contacts[i].memo, changestr);
					break;
				default:
					break;
			}
			cnt++;
		}
	}
	return cnt;
}

RESULT Search(FIELD field, char* str, FIELD ret_field)
{
	RESULT result;
	result.count = 0;
	int cnt = 0;
	for (int i = 0; i < contactCnt; i++) {
		char* fieldValue = nullptr;
		switch (field) {
			case NAME: fieldValue = contacts[i].name; break;
			case NUMBER: fieldValue = contacts[i].number; break;
			case BIRTHDAY: fieldValue = contacts[i].birthday; break;
			case EMAIL: fieldValue = contacts[i].email;	break;
			case MEMO: fieldValue = contacts[i].memo; break;
			default:break;
		}

		if (fieldValue != nullptr && strcmp(fieldValue, str) == 0) {
			cnt++;
			if (cnt == 1) {
				switch (ret_field) {
					case NAME:
						strcpy(result.str, contacts[i].name);
						break;
					case NUMBER:
						strcpy(result.str, contacts[i].number);
						break;
					case BIRTHDAY:
						strcpy(result.str, contacts[i].birthday);
						break;
					case EMAIL:
						strcpy(result.str, contacts[i].email);
						break;
					case MEMO:
						strcpy(result.str, contacts[i].memo);
						break;
					default:
						break;
				}
			}
		}
	}
	result.count = cnt;
	return result;
}


*/