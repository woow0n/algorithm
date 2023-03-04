#include <iostream>
#include <vector>
#include <queue>

#define Y first
#define X second

using namespace std;
using pic = pair<int, char>;
using pii = pair<int, int>;
using ll = long long;


int N, M, cnt, y, x, dir;
int map[55][55];
int vst[55][55];

int dy[] = {-1,0,1,0};
int dx[] = {0,1,0,-1};
//북0 동1 남2 서3
int turnLeft[] = { 3,0,1,2 };

void input() {
	cin >> N >> M >> y >> x >> dir;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> map[y][x];
		}
	}
}

int move() {
	int cleanedCnt = 0;
	if (map[y][x] != 2) { map[y][x] = 2; cnt++;}
	// 네방향 확인해야해
	for (int i = 0; i < 4; i++) {
		//북0 동1 남2 서3
		//int turnLeft[] = { 3,0,1,2 };
		dir = turnLeft[dir];
		int ny = y + dy[dir]; int nx = x + dx[dir];
		// 0이 아니면 -> 벽이거나 청소한 곳이면 넘어가
		if (map[ny][nx] != 0) { cleanedCnt++; continue; }
		y = ny; x = nx; return 1;
	}

	if (cleanedCnt == 4) {
		int ny = y - dy[dir]; int nx = x - dx[dir];
		if (map[ny][nx] == 1) return 0;
		y = ny; x = nx; return 1;
	}
}


int main(){
	input();
	int flag = 1;
	while (flag) {
		flag = move();
	}
	cout << cnt;
	return 0;
}
