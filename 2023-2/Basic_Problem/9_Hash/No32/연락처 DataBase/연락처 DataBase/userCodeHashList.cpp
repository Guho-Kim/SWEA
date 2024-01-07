/*
#include <iostream>
#include <cstring>
#include <string>
#include <unordered_map>
#include <list>
//#include<algorithm>
using namespace std;
constexpr auto MAXN = 100000;
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
typedef unordered_map<string, list<int>> hashMap;
hashMap nameMap, numberMap, birthdayMap, emailMap, memoMap;
int contactCnt;
Contact contacts[MAXN];

void InitDB()
{
	contactCnt = 0;

	nameMap.clear();
	numberMap.clear();
	birthdayMap.clear();
	emailMap.clear();
	memoMap.clear();
}

void Add(char* name, char* number, char* birthday, char* email, char* memo)
{
	strcpy(contacts[contactCnt].name, name);
	strcpy(contacts[contactCnt].number, number);
	strcpy(contacts[contactCnt].birthday, birthday);
	strcpy(contacts[contactCnt].email, email);
	strcpy(contacts[contactCnt].memo, memo);

	nameMap[name].push_back(contactCnt);
	numberMap[number].push_back(contactCnt);
	birthdayMap[birthday].push_back(contactCnt);
	emailMap[email].push_back(contactCnt);
	memoMap[memo].push_back(contactCnt);
	contactCnt++;

}

int Delete(FIELD field, char* str)
{
	int cnt = 0;
	string fieldValue(str);

	hashMap* fieldMap = nullptr;
	switch (field) {
	case NAME:
		fieldMap = &nameMap;
		break;
	case NUMBER:
		fieldMap = &numberMap;
		break;
	case BIRTHDAY:
		fieldMap = &birthdayMap;
		break;
	case EMAIL:
		fieldMap = &emailMap;
		break;
	case MEMO:
		fieldMap = &memoMap;
		break;
	default:
		break;
	}
	if (fieldMap != nullptr) {
		list<int> lst = (*fieldMap)[str];
		for (auto it = lst.begin(); it != lst.end();) {
			nameMap[contacts[*it].name].remove(*it);
			numberMap[contacts[*it].number].remove(*it);
			birthdayMap[contacts[*it].birthday].remove(*it);
			emailMap[contacts[*it].email].remove(*it);
			memoMap[contacts[*it].memo].remove(*it);
			it = lst.erase(it);
			cnt++;
		}
	}

	return cnt;
}

int Change(FIELD field, char* str, FIELD changefield, char* changestr)
{
	int cnt = 0;
	string fieldValue(str);
	string changefieldValue(changestr);

	hashMap* fieldMap = nullptr;
	switch (field) {
	case NAME:
		fieldMap = &nameMap;
		break;
	case NUMBER:
		fieldMap = &numberMap;
		break;
	case BIRTHDAY:
		fieldMap = &birthdayMap;
		break;
	case EMAIL:
		fieldMap = &emailMap;
		break;
	case MEMO:
		fieldMap = &memoMap;
		break;
	default:
		break;
	}
	if (fieldMap != nullptr) {
		list<int> lst = (*fieldMap)[str];
		for (auto it = lst.begin(); it != lst.end(); ++it) {
			switch (changefield) {
			case NAME:
				strcpy(contacts[*it].name, changestr);
				nameMap[contacts[*it].name].push_back(*it);
				nameMap[fieldValue].remove(*it);
				break;
			case NUMBER:
				strcpy(contacts[*it].number, changestr);
				numberMap[contacts[*it].number].push_back(*it);
				numberMap[fieldValue].remove(*it);
				break;
			case BIRTHDAY:
				strcpy(contacts[*it].birthday, changestr);
				birthdayMap[contacts[*it].birthday].push_back(*it);
				birthdayMap[fieldValue].remove(*it);
				break;
			case EMAIL:
				strcpy(contacts[*it].email, changestr);
				emailMap[contacts[*it].email].push_back(*it);
				emailMap[fieldValue].remove(*it);
				break;
			case MEMO:
				strcpy(contacts[*it].memo, changestr);
				memoMap[contacts[*it].memo].push_back(*it);
				memoMap[fieldValue].remove(*it);
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
	int cnt = 0;
	string fieldValue(str);
	hashMap* fieldHash = nullptr;
	switch (field) {
	case NAME:
		fieldHash = &nameMap;
		break;
	case NUMBER:
		fieldHash = &numberMap;
		break;
	case BIRTHDAY:
		fieldHash = &birthdayMap;
		break;
	case EMAIL:
		fieldHash = &emailMap;
		break;
	case MEMO:
		fieldHash = &memoMap;
		break;
	default:
		break;
	}
	if (fieldHash != nullptr) {
		list<int> lst = (*fieldHash)[str];
		for (auto it = lst.begin(); it != lst.end(); ++it) {
			cnt++;
			if (cnt == 1) {
				switch (ret_field) {
				case NAME:
					strcpy(result.str, contacts[*it].name);
					break;
				case NUMBER:
					strcpy(result.str, contacts[*it].number);
					break;
				case BIRTHDAY:
					strcpy(result.str, contacts[*it].birthday);
					break;
				case EMAIL:
					strcpy(result.str, contacts[*it].email);
					break;
				case MEMO:
					strcpy(result.str, contacts[*it].memo);
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