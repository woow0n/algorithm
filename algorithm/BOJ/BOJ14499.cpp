#include <iostream>
#include <vector>
#include <queue>

using namespace std;
using pic = pair<int, char>;
using pii = pair<int, int>;
using ll = long long;

int N, M, K, x, y;
int map[25][25];
vector<int> cmds;
pii floorPos;
int dy[] = { 0,0,0,-1,1 };
int dx[] = { 0,1,-1,0,0 };
vector<int> dice(7); 

void input() {
    cin >> N >> M >> y >> x >> K;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
            cin >> map[y][x];
        }
    }
    for (int i = 0; i < K; i++) {
        int c;
        cin >> c;
        cmds.push_back(c);
    }
    //dice[6] = map[y][x];
}

// 가장 처음에 주사위에는 모든 면에 0이 적혀져 있다.
// 주사위를 굴렸을 때, 이동한 칸에 쓰여 있는 수가 0이면, 주사위의 바닥면에 쓰여 있는 수가 칸에 복사된다. 
// 0이 아닌 경우에는 칸에 쓰여 있는 수가 주사위의 바닥면으로 복사되며, 칸에 쓰여 있는 수는 0이 된다.
// 주사위를 놓은 곳의 좌표와 이동시키는 명령이 주어졌을 때,
// 주사위가 이동했을 때 마다 상단에 쓰여 있는 값을 구하는 프로그램을 작성하시오.

void move(int dir) {
    int ny = y + dy[dir], nx = x + dx[dir];
    if (ny < 0 || ny >= N || nx < 0 || nx >= M) return;

    if (dir == 1) dice = { 0, dice[4], dice[2], dice[1], dice[6], dice[5], dice[3] };
    if (dir == 2) dice = { 0, dice[3], dice[2], dice[6], dice[1], dice[5], dice[4] };
    if (dir == 3) dice = { 0, dice[5], dice[1], dice[3], dice[4], dice[6], dice[2] };
    if (dir == 4) dice = { 0, dice[2], dice[6], dice[3], dice[4], dice[1], dice[5] };

    cout << dice[1] << endl;
    if (map[ny][nx] == 0) map[ny][nx] = dice[6];
    else{
        dice[6] = map[ny][nx];
        map[ny][nx] = 0;
    }
    y = ny; x = nx;
}

int main() {
    input();

    for (int i = 0; i < cmds.size(); i++) {
        move(cmds[i]);
    }
    return 0;
}
