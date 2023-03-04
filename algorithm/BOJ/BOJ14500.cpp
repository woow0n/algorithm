#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

int N, M, sum, mx;
int map[550][550];
int vst[550][550];
int dy[] = {0,-1,1,0,0};
int dx[] = {0, 0,0,-1,1 };


void input() {
	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> map[y][x];
		}
	}
	mx = -21e8;
}

void dfs(int y, int x, int level) {
	if (level == 3) {
		mx = max(mx, sum); return;
	}

	for (int i = 1; i <= 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny <0 || ny >= N || nx < 0 || nx >= M) continue;
		if (vst[ny][nx] == 1) continue;
		vst[ny][nx] = 1;
		sum += map[ny][nx];
		dfs(ny, nx, level + 1);
		vst[ny][nx] = 0;
		sum -= map[ny][nx];	
	}
}

int plusCase(int y, int x) {
	int mx = 0;
	for (int j = 1; j <= 4; j++) {
		int sum = 0;
		for (int i = 1; i <= 4; i++) {
			if (i == j) continue;
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (ny < 0 || ny >= N || nx < 0 || nx >= M) break;
			if (vst[ny][nx] == 1) continue;
			sum += map[ny][nx];
		}
		mx = max(mx, sum);
	}
	return mx;
}

int main(){
	input();
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			vst[y][x] = 1;
			sum = map[y][x];
			dfs(y, x, 0);
			mx = max(sum + plusCase(y, x), mx);
			vst[y][x] = 0;
		}
	}
	cout << mx;
}


