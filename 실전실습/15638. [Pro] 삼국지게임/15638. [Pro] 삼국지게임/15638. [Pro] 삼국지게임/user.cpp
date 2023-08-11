#include <unordered_map>
#include <list>
#include <string>
#define M_ATTACK 8000
#define M_N 25

using namespace std;
int _N;


int parent[M_ATTACK + M_N * M_N];

list < int > UnionList[M_N * M_N];
list < int > EnemyList[M_N * M_N];


int Find(int x) {
	if (x == parent[x])
		return x;
	else
		return parent[x] = Find(parent[x]);
}


void Union(int x, int y) {
	x = Find(x);
	y = Find(y);
	if (x != y) {
		parent[y] = x;
		UnionList[x].splice(UnionList[x].end(), UnionList[y]);
		EnemyList[x].splice(EnemyList[x].end(), EnemyList[y]);
	}
}


bool IsSameUnion(int x, int y) {
	x = Find(x);
	y = Find(y);
	if (x == y)	return true;
	else return false;
}


bool IsEnemy(int x, int y) {
	x = Find(x);
	y = Find(y);
	for (auto enemy : EnemyList[x]) {
		if (Find(enemy) == y) return true;
	}
	return false;
}


void MakeEnemy(int x, int y) {
	x = Find(x);
	y = Find(y);
	if (x == y || IsEnemy(x, y)) return;
	EnemyList[x].push_back(y);
	EnemyList[y].push_back(x);
}


struct SNationInfo
{
	int x;
	int y;
	int soldier;
};

SNationInfo Nation[M_ATTACK + M_N * M_N];
int NationIndex[M_N][M_N];

unordered_map < string, int > NationMap;

int NationCount;


void init(int N, int mSoldier[25][25], char mMonarch[25][25][11])
{
	_N = N;
	int index = 0;
	NationMap.clear();
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			NationMap[mMonarch[j][i]] = index;

			NationIndex[j][i] = index;

			Nation[index].soldier = mSoldier[j][i];
			Nation[index].x = i;
			Nation[index].y = j;
			parent[index] = index;

			UnionList[index].clear();
			EnemyList[index].clear();

			UnionList[index].push_back(index);

			index++;
		}
	}
	NationCount = N * N;
}


void destroy()
{

}


int ally(char mMonarchA[11], char mMonarchB[11])
{
	int a = NationMap[mMonarchA];
	int b = NationMap[mMonarchB];


	if (IsSameUnion(a, b)) return -1;
	if (IsEnemy(a, b)) return -2;

	Union(a, b);
	return 1;
}


int attack(char mMonarchA[11], char mMonarchB[11], char mGeneral[11])
{
	int a = NationMap[mMonarchA];
	int b = NationMap[mMonarchB];

	int bossA = Find(a);
	int bossB = Find(b);

	if (bossA == bossB) return -1;

	int dx[2] = { Nation[b].x - 1, Nation[b].x + 1 };
	int dy[2] = { Nation[b].y - 1, Nation[b].y + 1 };

	if (dx[0] < 0) dx[0] = 0;
	if (dy[0] < 0) dy[0] = 0;
	if (dx[1] > _N - 1) dx[1] = _N - 1;
	if (dy[1] > _N - 1) dy[1] = _N - 1;


	bool isThereEnemy = false;
	for (int j = dy[0]; j <= dy[1]; j++) {
		for (int i = dx[0]; i <= dx[1]; i++) {
			if (bossA == Find(NationIndex[j][i])) {
				isThereEnemy = true;
				j = dy[1] + 1;
				break;
			}
		}
	}
	if (!isThereEnemy) return -2;

	MakeEnemy(bossA, bossB);

	int totalSolA = 0;
	int totalSolB = Nation[b].soldier;
	Nation[b].soldier = 0;
	int moveNum;


	for (int j = dy[0]; j <= dy[1]; j++) {
		for (int i = dx[0]; i <= dx[1]; i++) {
			if (bossA == Find(NationIndex[j][i])) {
				moveNum = Nation[NationIndex[j][i]].soldier / 2;
				Nation[NationIndex[j][i]].soldier -= moveNum;
				totalSolA += moveNum;
			}
			else if (bossB == Find(NationIndex[j][i])) {
				moveNum = Nation[NationIndex[j][i]].soldier / 2;
				Nation[NationIndex[j][i]].soldier -= moveNum;
				totalSolB += moveNum;
			}
		}
	}

	int remainSol = totalSolB - totalSolA;
	if (remainSol >= 0) {
		// 방어 성공
		Nation[b].soldier = remainSol;
		return 0;
	}

	// 공격 성공
	Nation[NationCount] = Nation[b];
	Nation[NationCount].soldier = -remainSol;

	UnionList[bossB].remove(b);

	NationIndex[Nation[NationCount].y][Nation[NationCount].x] = NationCount;

	NationMap[mGeneral] = NationCount;

	parent[NationCount] = bossA;
	UnionList[bossA].push_back(NationCount++);

	return 1;
}


int recruit(char mMonarch[11], int mNum, int mOption)
{
	if (mOption == 0) {
		Nation[NationMap[mMonarch]].soldier += mNum;
		return Nation[NationMap[mMonarch]].soldier;
	}
	else {
		int sum = 0;
		int boss = Find(NationMap[mMonarch]);
		for (auto nation : UnionList[boss]) {
			Nation[nation].soldier += mNum;
			sum += Nation[nation].soldier;
		}
		return sum;
	}
}