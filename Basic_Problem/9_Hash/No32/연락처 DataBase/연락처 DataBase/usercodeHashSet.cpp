/*
#include<cstring>
#include<iostream>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>
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

typedef unordered_map<string, unordered_set<int>> hashMap;
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
	nameMap.reserve(MAXN);
	numberMap.reserve(MAXN);
	birthdayMap.reserve(MAXN);
	emailMap.reserve(MAXN);
	memoMap.reserve(MAXN);

}

void Add(char* name, char* number, char* birthday, char* email, char* memo)
{
	strcpy(contacts[contactCnt].name, name);
	strcpy(contacts[contactCnt].number, number);
	strcpy(contacts[contactCnt].birthday, birthday);
	strcpy(contacts[contactCnt].email, email);
	strcpy(contacts[contactCnt].memo, memo);

	nameMap[name].insert(contactCnt);
	numberMap[number].insert(contactCnt);
	birthdayMap[birthday].insert(contactCnt);
	emailMap[email].insert(contactCnt);
	memoMap[memo].insert(contactCnt);
	contactCnt++;
}



int Delete(FIELD field, char* str)
{
	int cnt = 0;
	hashMap* fieldMap = nullptr;
	switch (field) {
	case NAME: fieldMap = &nameMap; break;
	case NUMBER: fieldMap = &numberMap; break;
	case BIRTHDAY: fieldMap = &birthdayMap;    break;
	case EMAIL:    fieldMap = &emailMap; break;
	case MEMO: fieldMap = &memoMap;    break;
	default: break;
	}

	if (fieldMap != nullptr) {

		auto it = fieldMap->find(str);
		if (it != fieldMap->end()) {
			unordered_set<int> contactIndices = it->second;
			for (int idx : contactIndices) {
				nameMap[contacts[idx].name].erase(idx);
				numberMap[contacts[idx].number].erase(idx);
				birthdayMap[contacts[idx].birthday].erase(idx);
				emailMap[contacts[idx].email].erase(idx);
				memoMap[contacts[idx].memo].erase(idx);
				cnt++;
			}
		}
	}

	return cnt;
}

int Change(FIELD field, char* str, FIELD changefield, char* changestr)
{
	int cnt = 0;

	hashMap* fieldMap = nullptr;
	switch (field) {
		case NAME: fieldMap = &nameMap;	break;
		case NUMBER: fieldMap = &numberMap; break;
		case BIRTHDAY: fieldMap = &birthdayMap;	break;
		case EMAIL:	fieldMap = &emailMap; break;
		case MEMO: fieldMap = &memoMap;	break;
		default: break;
	}

	if (fieldMap != nullptr) {
		auto it = fieldMap->find(str);
		if (it != fieldMap->end()){
			unordered_set<int> contactIndices = it->second;
			for (int idx : contactIndices) {
				switch (changefield) {
				case NAME:
					strcpy(contacts[idx].name, changestr);
					nameMap[str].erase(idx);
					nameMap[changestr].insert(idx);
					break;
				case NUMBER:
					strcpy(contacts[idx].number, changestr);
					numberMap[str].erase(idx);
					numberMap[changestr].insert(idx);
					break;
				case BIRTHDAY:
					strcpy(contacts[idx].birthday, changestr);
					birthdayMap[str].erase(idx);
					birthdayMap[changestr].insert(idx);
					break;
				case EMAIL:
					strcpy(contacts[idx].email, changestr);
					emailMap[str].erase(idx);
					emailMap[changestr].insert(idx);
					break;
				case MEMO:
					strcpy(contacts[idx].memo, changestr);
					memoMap[str].erase(idx);
					memoMap[changestr].insert(idx);
					break;
				default:
					break;

				}
				cnt++;
			}
		}

	}
	return cnt;
}

RESULT Search(FIELD field, char* str, FIELD ret_field)
{
	RESULT result;
	result.count = 0;
	hashMap* fieldHash = nullptr;

	switch (field) {
	case NAME: fieldHash = &nameMap; break;
	case NUMBER: fieldHash = &numberMap; break;
	case BIRTHDAY: fieldHash = &birthdayMap; break;
	case EMAIL:	fieldHash = &emailMap; break;
	case MEMO: fieldHash = &memoMap; break;
	default: break;
	}

	if (fieldHash != nullptr) {
		unordered_set<int> contactIndices = (*fieldHash)[str];
		for (int idx : contactIndices) {
			result.count++;
			if (result.count == 1) {
				switch (ret_field) {
				case NAME:
					strcpy(result.str, contacts[idx].name);
					break;
				case NUMBER:
					strcpy(result.str, contacts[idx].number);
					break;
				case BIRTHDAY:
					strcpy(result.str, contacts[idx].birthday);
					break;
				case EMAIL:
					strcpy(result.str, contacts[idx].email);
					break;
				case MEMO:
					strcpy(result.str, contacts[idx].memo);
					break;
				default:
					break;
				}
			}
		}
	}
	
	return result;
}
*/