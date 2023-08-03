/*
	멀티맵 사용해서 데이터 지우려고 하니까 문제 발생
	ex 특정 이름 갖고있는 친구의 index를 사용해서 그 친구들의 다른 데이터 삭제하려고 하니,
	다른 해쉬 맵에서 그 속성이 중복될 경우 삭제할 때 귀찮아짐. 굳이 멀티맵 사용해야하나 싶음.

	Uncomplete Quit.
*/



/*
#include<iostream>
#include<cstring>
#include<string>
#include<unordered_map>
using namespace std;
#define MAXN 1000000
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

typedef unordered_multimap<string, int> hashMap;
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

	nameMap.insert(make_pair(name, contactCnt));
	numberMap.insert(make_pair(number, contactCnt));
	birthdayMap.insert(make_pair(birthday, contactCnt));
	emailMap.insert(make_pair(email, contactCnt));
	memoMap.insert(make_pair(memo, contactCnt));
	contactCnt++;
}

int Delete(FIELD field, char* str)
{
	int cnt;
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
		cnt = (*fieldMap).count(str);
		auto range = fieldMap->equal_range(str);

		for (auto it = range.first; it != range.second;) {
			//nameMap.erase(contacts[*it].name);

			cout << "delete";
			auto tempIt = it; // Store the iterator before erasing the element
			++it; // Move the iterator before erasing the element

			nameMap.erase(tempIt);
			numberMap.erase(tempIt);
			birthdayMap.erase(tempIt);
			emailMap.erase(tempIt);
			memoMap.erase(tempIt);
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
		auto range = fieldMap->equal_range(str);
		for (auto it = range.first; it != range.second; ++it) {
			cout << "change";
			switch (changefield) {
			case NAME:
				strcpy(contacts[it->second].name, changestr);
				break;
			case NUMBER:
				strcpy(contacts[it->second].number, changestr);
				break;
			case BIRTHDAY:
				strcpy(contacts[it->second].birthday, changestr);
				break;
			case EMAIL:
				strcpy(contacts[it->second].email, changestr);
				break;
			case MEMO:
				strcpy(contacts[it->second].memo, changestr);
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
		auto range = fieldHash->equal_range(str);
		for (auto it = range.first; it != range.second; ++it) {
			cnt++;
			cout << "result";
			if (cnt == 1) {
				switch (ret_field) {
				case NAME:
					strcpy(result.str, contacts[it->second].name);
					break;
				case NUMBER:
					strcpy(result.str, contacts[it->second].number);
					break;
				case BIRTHDAY:
					strcpy(result.str, contacts[it->second].birthday);
					break;
				case EMAIL:
					strcpy(result.str, contacts[it->second].email);
					break;
				case MEMO:
					strcpy(result.str, contacts[it->second].memo);
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