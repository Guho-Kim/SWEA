#define MAX_N 100010

using namespace std;

struct userData {
	int ID, income;
};

userData map[MAX_N];

int mapCount;

void init()
{
	mapCount = 0;
}

void addUser(int uID, int height)
{
	map[mapCount].ID = uID;
	map[mapCount].income = height;
	mapCount++;
}

void swap(userData* a, userData* b) {
	int temp1, temp2;
	temp1 = a->ID;
	temp2 = a->income;
	a->ID = b->ID;
	a->income = b->income;
	b->ID = temp1;
	b->income = temp2;

}

int getTop10(int result[10])
{
	int maxIndex;
	int size = mapCount;
	if (size > 10) size = 10;


	for (int i = 0; i < size; i++) {
		maxIndex = i;
		for (int j = i+1; j < mapCount; j++) {
			if (map[j].income > map[maxIndex].income) {
				maxIndex = j;
			}
			else if (map[j].income == map[maxIndex].income) {
				if (map[j].ID < map[maxIndex].ID) {
					maxIndex = j;
				}
			}
		}
		swap(&map[i], &map[maxIndex]);



	}

	for (int i = 0; i < size; i++) {
		result[i] = map[i].ID;
	}
	
	return size;
}
