#include <unordered_map>
#include <list>
#include <string>
#define M_ATTACK 8000
#define M_N 25

using namespace std;

int _N;

list < int > UnionList[M_N * M_N];
list < int > EnemyList[M_N * M_N];

int parent[M_ATTACK+M_N * M_N];

unordered_map<string, int> MonarchMap;
struct Info {
	int x, y, soldier;
}NationInfo[M_ATTACK+M_N * M_N];
int NationIndex[M_N][M_N];

int Find(int x) {
	if (x == parent[x]) return x;
	return parent[x] = Find(parent[x]);
}

int monarchCnt;

void init(int N, int mSoldier[25][25], char mMonarch[25][25][11])
{
	_N = N;
	int cnt = 0;
	MonarchMap.clear();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			MonarchMap[mMonarch[i][j]] = cnt;
			NationInfo[cnt] = {i, j, mSoldier[i][j]};
			parent[cnt] = cnt;

			NationIndex[i][j] = cnt;

			UnionList[cnt].clear();
			EnemyList[cnt].clear();

			UnionList[cnt].push_back(cnt);

			cnt++;
		}
	}
	monarchCnt = N * N;
}


void destroy()
{

}


int ally(char mMonarchA[11], char mMonarchB[11])
{
	int a = Find(MonarchMap[mMonarchA]);
	int b = Find(MonarchMap[mMonarchB]);

	// 이미 동맹관계
	if (a == b) return -1;

	// 적대 관계
	for (auto enemy : EnemyList[a]) {
		if (Find(enemy) == b) {
			return -2;
		}
	}

	// 동맹 가능
	parent[b] = a;
	UnionList[a].splice(UnionList[a].end(), UnionList[b]);
	EnemyList[a].splice(EnemyList[a].end(), EnemyList[b]);
	return 1;
}


int attack(char mMonarchA[11], char mMonarchB[11], char mGeneral[11])
{
	int a = MonarchMap[mMonarchA];
	int b = MonarchMap[mMonarchB];
	int parentA = Find(a);
	int parentB = Find(b);
	
	// 동맹 관계
	if (parentA == parentB) return -1;

	// A의 동맹이 B에 인접하지 않음
	int dx[2] = { NationInfo[b].x - 1,NationInfo[b].x + 1 };
	int dy[2] = { NationInfo[b].y - 1,NationInfo[b].y + 1 };
	if (dx[0] < 0) dx[0] = 0;
	if (dy[0] < 0) dy[0] = 0;
	if (dx[1] > _N - 1) dx[1] = _N - 1;
	if (dy[1] > _N - 1) dy[1] = _N - 1;
	bool connected = false;
	for (int i = dx[0]; i <= dx[1]; i++) {
		for (int j = dy[0]; j <= dy[1]; j++) {
			if (parentA == Find(NationIndex[i][j])) {
				connected = true;
				i = dx[1] + 1;
				break;
			}
		}
	}
	if (!connected) return -2;

	// 적대관계 생성
	// 이미 적대관계인지 체크
	bool isEnemy = false;
	for (auto enemy : EnemyList[parentB]) {
		if (Find(enemy) == parentA) {
			isEnemy = true;
			break;
		}
	}
	if (!isEnemy) {
		EnemyList[parentA].push_back(parentB);
		EnemyList[parentB].push_back(parentA);
	}


	// 전투
	int totalSoldierA = 0;
	int totalSoldierB = NationInfo[b].soldier;
	NationInfo[b].soldier = 0;
	int veteran;

	for (int i = dx[0]; i <= dx[1]; i++) {
		for (int j = dy[0]; j <= dy[1]; j++) {
			int connectedNation = NationIndex[i][j];
			if (parentA == Find(connectedNation)) {
				veteran = NationInfo[connectedNation].soldier / 2;
				totalSoldierA += veteran;
				NationInfo[connectedNation].soldier -= veteran;
			}
			else if(parentB == Find(connectedNation)){
				veteran = NationInfo[connectedNation].soldier / 2;
				totalSoldierB += veteran;
				NationInfo[connectedNation].soldier -= veteran;
			}
		}
	}

	// 방어 성공
	if (totalSoldierB >= totalSoldierA) {
		NationInfo[b].soldier = totalSoldierB - totalSoldierA;
		return 0;
	}

	// 방어 실패
	MonarchMap[mGeneral]=monarchCnt;

	NationInfo[monarchCnt]=NationInfo[b];
	NationInfo[monarchCnt].soldier = totalSoldierA - totalSoldierB;
	UnionList[parentB].remove(b);
	
	NationIndex[NationInfo[monarchCnt].x][NationInfo[monarchCnt].y] = monarchCnt;
	
	parent[monarchCnt] = parentA;

	UnionList[parentA].push_back(monarchCnt);
	monarchCnt++;
	return 1;
}


int recruit(char mMonarch[11], int mNum, int mOption)
{
	int a = MonarchMap[mMonarch];
	if (mOption == 0) {
		NationInfo[a].soldier += mNum;
		return NationInfo[a].soldier;
	}
	else {
		int sum = 0;
		int parentA = Find(a);
		for (auto ally : UnionList[parentA]) {
			NationInfo[ally].soldier += mNum;
			sum += NationInfo[ally].soldier;
		}
		return sum;
	}
}
