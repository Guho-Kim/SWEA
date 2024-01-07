
#define QUEUE_SIZE 100

struct Point {
	int x;
	int y;
};

Point Queue[QUEUE_SIZE];
int Size = 0, front = -1, rear = -1;

int queueSize() {
	return Size;
}
void enqueue(Point point) {
	if (Size >= QUEUE_SIZE) return;
	else {
		Size++;
		rear = (rear + 1) % QUEUE_SIZE;
		Queue[rear].x = point.x;
		Queue[rear].y = point.y;
	}
}

Point dequeue() {
	Size--;
	front = (front + 1) % QUEUE_SIZE;
	return Queue[front];
}

bool isEmpty() {
	if (front == rear) return true;
	return false;
}

int graph[10][10];

const int dx[] = { 0, 0, -1, 1 };
const int dy[] = { -1, 1, 0, 0 };


void bfs_init(int map_size, int map[10][10]) {
	for (int i = 0; i < map_size; i++) {
		for (int j = 0; j < map_size; j++) {
			graph[i][j] = map[i][j];
		}
	}
}


int bfs(int x1, int y1, int x2, int y2) {
	Size = 0;
	front = rear = -1;
	bool visited[10][10] = { false };
	int rows = 10;
	int cols = 10;
	Point curr;
	Point next;
	curr.x = x1;
	curr.y = y1;

	enqueue(curr);

	visited[y1-1][x1-1] = true;
	int moves = 0;

	while (!isEmpty()) {
		int size = queueSize();
		moves++;

		for (int j=0; j < size; j++) {
			curr = dequeue();
			for (int i = 0; i < 4; i++) {
				int nx = curr.x + dx[i];
				int ny = curr.y + dy[i];

				if (visited[ny - 1][nx - 1] || graph[ny-1][nx-1]==1 || nx > cols || ny > rows || nx <1 || ny <1) {
					continue;
				}
				if (nx == x2 && ny == y2) {
					return moves;
				}
				next.x = nx;
				next.y = ny;
				enqueue(next);
				visited[ny - 1][nx - 1]=true;
			}
		}
	}
	return -1;
}
