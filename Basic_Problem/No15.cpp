/*
    No. 15 프로세서 연결하기

삼성에서 개발한 최신 모바일 프로세서 멕시노스는 가로 N개 x 세로 N개의 cell로 구성되어 있다.



1개의 cell에는 1개의 Core 혹은 1개의 전선이 올 수 있다.


멕시노스의 가장 자리에는 전원이 흐르고 있다.

Core와 전원을 연결하는 전선은 직선으로만 설치가 가능하며,


전선은 절대로 교차해서는 안 된다.

초기 상태로는 아래와 같이 전선을 연결하기 전 상태의 멕시노스 정보가 주어진다.


(멕시노스의 가장자리에 위치한 Core는 이미 전원이 연결된 것으로 간주한다.)






▶ 최대한 많은 Core에 전원을 연결하였을 경우, 전선 길이의 합을 구하고자 한다.

   단, 여러 방법이 있을 경우, 전선 길이의 합이 최소가 되는 값을 구하라.

위 예제의 정답은 12가 된다.



[제약 사항]

1. 7 ≤  N ≤ 12

2. Core의 개수는 최소 1개 이상 12개 이하이다.

3. 최대한 많은 Core에 전원을 연결해도, 전원이 연결되지 않는 Core가 존재할 수 있다.



[입력]

입력의 가장 첫 줄에는 총 테스트 케이스의 개수 T가 주어지며 그 다음 줄부터 각 테스트 케이스가 주어진다.

각 테스트 케이스의 첫 줄에는 N값이 주어지며, 다음 N줄에 걸쳐서 멕시노스의 초기 상태가 N x N 배열로 주어진다.

0은 빈 cell을 의미하며, 1은 core를 의미하고, 그 외의 숫자는 주어지지 않는다.



[출력]

각 테스트 케이스마다 '#X'를 찍고, 한 칸 띄고, 정답을 출력한다.

(X는 테스트 케이스의 번호를 의미하며 1부터 시작한다.)

 

입력
3  
7    
0 0 1 0 0 0 0
0 0 1 0 0 0 0
0 0 0 0 0 1 0
0 0 0 0 0 0 0
1 1 0 1 0 0 0
0 1 0 0 0 0 0
0 0 0 0 0 0 0
9  
0 0 0 0 0 0 0 0 0
0 0 1 0 0 0 0 0 1
1 0 0 0 0 0 0 0 0
0 0 0 1 0 0 0 0 0
0 1 0 0 0 0 0 0 0
0 0 0 0 0 0 1 0 0
0 0 0 1 0 0 0 0 0
0 0 0 0 0 0 0 1 0
0 0 0 0 0 0 0 0 1
11 
0 0 1 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 1
0 0 0 1 0 0 0 0 1 0 0
0 1 0 1 1 0 0 0 1 0 0
0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 1 0 0 0
0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 1 0 0
0 0 0 0 0 0 1 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0

출력
#1 12
#2 10 
#3 24 
*/


#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 12;
const int dx[] = {0, 0, -1, 1};
const int dy[] = {-1, 1, 0, 0};

int N;
int minWireLength; // 최소 전선 길이 합을 저장하는 변수
int maxCores;
vector<pair<int, int>> cores; // 코어의 좌표를 저장하는 벡터
int map[MAX_N][MAX_N]; // 멕시노스의 초기 상태를 저장하는 배열

// 전선을 연결하는 함수
void dfs(int idx, int wireLength, int connectedCores) {
    if (idx == cores.size()) {
        // 모든 코어에 대해 처리가 끝났을 때, 최소 전선 길이 합을 업데이트
        if (connectedCores > maxCores) {
            maxCores = connectedCores;
            minWireLength = wireLength;
        }
        else if(connectedCores == maxCores){
            // 전선과 코어의 개수가 같은 경우, 최소 길이 업데이트
            minWireLength = min(minWireLength, wireLength);
            }
        return;
    }

    // 현재 코어의 좌표
    int x = cores[idx].first;
    int y = cores[idx].second;
    // 해당 코어가 처음부터 연결되어 있는 경우
    if(x==0 || y==0 || x==cores.size()-1 || y == cores.size()-1) {
        dfs(idx+1, wireLength, connectedCores+1);
        return;
    }       


    // 현재 코어를 연결하는 경우 (4방향으로 전선 연결 시도)
    for (int dir = 0; dir < 4; dir++) {
        int nx = x;
        int ny = y;
        int length = 0;
        bool canConnect = true;

        // 해당 방향으로 전선을 연결할 수 있는지 확인
        while (true) {


            nx += dx[dir];
            ny += dy[dir];

            if (nx < 0 || nx >= N || ny < 0 || ny >= N) break; // 멕시노스 범위를 벗어남

            if (map[ny][nx] != 0) { // 전선이나 코어를 만남
                canConnect = false;
                break;
            }

            length++;
        }

        if (canConnect) {
            // 해당 방향으로 전선 연결
            nx = x;
            ny = y;
            while (true) {
                nx += dx[dir];
                ny += dy[dir];
                if (nx < 0 || nx >= N || ny < 0 || ny >= N) break;

                map[ny][nx] = 2; // 전선을 2로 표시
            }

            // 다음 코어 연결 시도
            dfs(idx + 1, wireLength + length, connectedCores + 1);

            // 연결했던 전선 원복
            nx = x;
            ny = y;
            while (true) {
                nx += dx[dir];
                ny += dy[dir];
                if (nx < 0 || nx >= N || ny < 0 || ny >= N) break;

                map[ny][nx] = 0; // 전선을 원래대로 복구
            }
        }
    }
    // 현재 코어를 연결하지 않는 경우
    dfs(idx + 1, wireLength, connectedCores);

}

int main() {
    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++) {
        cin >> N;
        cores.clear();
        minWireLength = MAX_N * MAX_N; // 초기값은 큰 값으로 설정
        maxCores = 0;

        // 멕시노스 초기 상태 입력
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> map[i][j];
                if (map[i][j] == 1) {
                    // 코어 좌표 저장
                    cores.push_back(make_pair(j, i));
                }
            }
        }

        dfs(0, 0, 0); // 전선 연결 시작
        cout << "#" << tc << " " << minWireLength << endl;
    }

    return 0;
}
