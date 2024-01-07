

// [SWEA] No 6134. 연락처 DataBase
/*
	정답 코드
	이것 저것 많이 시도해봤는데 이게 제일 빠르다.
	
	map에 vector를 넣는 형태의 문제.
	데이터 삭제 툴은 외우면 좋을 듯.
	nameMap[contacts[idx].name].erase(remove(nameMap[contacts[idx].name].begin(), nameMap[contacts[idx].name].end(), idx), nameMap[contacts[idx].name].end());

*/



#include<vector>
#include<iostream>
#include<cstring>
#include<string>
#include<unordered_map>
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
typedef unordered_map<string, vector<int>> hashMap;
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
		vector<int> vec = (*fieldMap)[str];
		for (auto it = vec.begin(); it != vec.end(); it++) {
			int idx = *it;
			nameMap[contacts[idx].name].erase(remove(nameMap[contacts[idx].name].begin(), nameMap[contacts[idx].name].end(), idx), nameMap[contacts[idx].name].end());
			numberMap[contacts[idx].number].erase(remove(numberMap[contacts[idx].number].begin(), numberMap[contacts[idx].number].end(), idx), numberMap[contacts[idx].number].end());
			birthdayMap[contacts[idx].birthday].erase(remove(birthdayMap[contacts[idx].birthday].begin(), birthdayMap[contacts[idx].birthday].end(), idx), birthdayMap[contacts[idx].birthday].end());
			emailMap[contacts[idx].email].erase(remove(emailMap[contacts[idx].email].begin(), emailMap[contacts[idx].email].end(), idx), emailMap[contacts[idx].email].end());
			memoMap[contacts[idx].memo].erase(remove(memoMap[contacts[idx].memo].begin(), memoMap[contacts[idx].memo].end(), idx), memoMap[contacts[idx].memo].end());
			cnt++;
		}
	}


	return cnt;
}

int Change(FIELD field, char* str, FIELD changefield, char* changestr)
{
	int cnt = 0;

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
		vector<int> vec = (*fieldMap)[str];
		for (auto it = vec.begin(); it != vec.end(); it++) {
			int idx = *it;
			switch (changefield) {
			case NAME:
				nameMap[contacts[idx].name].erase(remove(nameMap[contacts[idx].name].begin(), nameMap[contacts[idx].name].end(), idx), nameMap[contacts[idx].name].end());
				nameMap[changestr].push_back(idx);
				strcpy(contacts[idx].name, changestr);
				break;
			case NUMBER:
				numberMap[contacts[idx].number].erase(remove(numberMap[contacts[idx].number].begin(), numberMap[contacts[idx].number].end(), idx), numberMap[contacts[idx].number].end());
				numberMap[changestr].push_back(idx);
				strcpy(contacts[idx].number, changestr);
				break;
			case BIRTHDAY:
				birthdayMap[contacts[idx].birthday].erase(remove(birthdayMap[contacts[idx].birthday].begin(), birthdayMap[contacts[idx].birthday].end(), idx), birthdayMap[contacts[idx].birthday].end());
				birthdayMap[changestr].push_back(idx);
				strcpy(contacts[idx].birthday, changestr);
				break;
			case EMAIL:
				emailMap[contacts[idx].email].erase(remove(emailMap[contacts[idx].email].begin(), emailMap[contacts[idx].email].end(), idx), emailMap[contacts[idx].email].end());
				emailMap[changestr].push_back(idx);
				strcpy(contacts[idx].email, changestr);
				break;
			case MEMO:
				memoMap[contacts[idx].memo].erase(remove(memoMap[contacts[idx].memo].begin(), memoMap[contacts[idx].memo].end(), idx), memoMap[contacts[idx].memo].end());
				memoMap[changestr].push_back(idx);
				strcpy(contacts[idx].memo, changestr);
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
		vector<int> vec = (*fieldHash)[str];
		for (auto it = vec.begin(); it != vec.end(); it++) {
			cnt++;
			if (cnt == 1) {
				int idx = *it;
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
	result.count = cnt;
	return result;
}
