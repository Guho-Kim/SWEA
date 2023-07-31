/*
    No. 16 파핑파핑 지뢰찾기
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define MAX_N 300

int clickZero;

void viewGrid(int N, vector<vector<int>>& grid){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cout<<grid[i][j] << " ";
        }
        cout<<endl;
    }
}
const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

vector<vector<bool>> visited(MAX_N, vector<bool>(MAX_N, false));

void makeZero(int x, int y, int N, vector<vector<char>>& grid){
    queue<pair<int, int>> q;
    bool firstCheck = true;
    q.push({x, y});
    visited[x][y] = true;
    int isZero=0;
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            int cx = q.front().first;
            int cy = q.front().second;
            q.pop();

            if (grid[cx][cy] == '*') continue;
            
            int mine_count = 0;
            for (int j = 0; j < 8; j++) {
                int nx = cx + dx[j];
                int ny = cy + dy[j];
                if (nx >= 0 && nx < N && ny >= 0 && ny < N && grid[nx][ny] == '*') {
                    mine_count++;
                }
            }

            if (firstCheck && mine_count > 0) continue;
            firstCheck = false;
            


            if (mine_count == 0) {
                for (int j = 0; j < 8; j++) {
                    int nx = cx + dx[j];
                    int ny = cy + dy[j];
                    if (nx >= 0 && nx < N && ny >= 0 && ny < N && !visited[nx][ny]) {
                        q.push({nx, ny});
                        visited[nx][ny] = true;
                    }
                }
            }
            grid[cx][cy] = static_cast<char>(mine_count+'0');
            if(grid[cx][cy]=='0') isZero++;

        }
    }
    if(isZero) clickZero++;

}


int main() {
    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++) {
        int N;
        cin >> N;
        vector<vector<char>> grid(N, vector<char>(N));

        int totalClick = 0;
        
        // make grid
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> grid[i][j];
                visited[i][j]=false;
            }
        }

        clickZero=0;
        //make zero and count
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == '.') {
                    makeZero(i, j, N, grid);
                    if(grid[i][j]=='.') visited[i][j]=false;
                }
            }
        }

        totalClick+=clickZero;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == '.') {
                    totalClick++;
                }
            }
        }

        cout << "#" << tc << " " << totalClick << endl;
    }

    return 0;
}
