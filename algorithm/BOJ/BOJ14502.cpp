#include <iostream>
#include <vector>
#include <queue>

#define Y first
#define X second

using namespace std;
using pic = pair<int, char>;
using pii = pair<int, int>;
using ll = long long;


int N, M, mx, safeCnt;
int map[10][10];
int vst[10][10]; 
int vstcpy[10][10];

int dy[] = {0,0,0,-1,1};
int dx[] = {0,1,-1,0,0};
queue<pii> q;
vector<pii> wallSubs;
vector<pii> initPoints;

void input() {
	cin >> N >> M ;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> map[y][x];
			if (map[y][x] == 2) { 
				q.push({ y,x });
				initPoints.push_back({ y,x });
				vst[y][x] = 2;
			}
			// 이미벽은 3;
			if (map[y][x] == 1) vst[y][x] = 3;
			if (map[y][x] == 0) {
				wallSubs.push_back({ y,x }); safeCnt++;
			}
		}
	}
}

int bfs() {
	int cnt = 0;
	while (!q.empty()) {
		int sz = q.size();
		for (int i = 0; i < sz; i++) {
			auto now = q.front(); q.pop();
			for (int d = 1; d <= 4; d++) {
				int ny = now.Y + dy[d];
				int nx = now.X + dx[d];
				if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue;
				if (vstcpy[ny][nx] != 0) continue;
				vstcpy[ny][nx] = 9;
				cnt++;
				q.push({ ny,nx });
			}
		}
	}
	return cnt;
}

void dfs(int level) {
	if (level == 3) {
		// vst복사
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < M; x++) {
				vstcpy[y][x] = vst[y][x];
			}
		}
		for (int i = 0; i < initPoints.size(); i++) q.push(initPoints[i]);
		int nonSafeCnt = bfs();
		mx = max(mx, safeCnt - nonSafeCnt);
		return;
	}

	for (int i = 0; i < wallSubs.size(); i++) {
		auto now = wallSubs[i];
		if (vst[now.Y][now.X] != 0) continue;
		vst[now.Y][now.X] = 4;
		dfs(level + 1);
		vst[now.Y][now.X] = 0;
	}	

}

int main(){
	input();
	dfs(0);
	cout << mx-3;
	return 0;
}
