#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define Y first
#define X second
using namespace std;
using pic = pair<int, char>;
using pii = pair<int, int>;
using ll = long long;

int N, M, mx = -21e8, cnt, zeroCnt;
int Map[10][10];
// 상 하 좌 우
int dy[] = { 0,-1,1,0,0 };
int dx[] = { 0,0,0,-1,1 };
// 왼쪽으로 도는 경우 
int turnLeft[] = {0, 3,4,2,1 };
// 0이 주방향

// 여기 방향만큼 왼쪽으로 돌아야한다는 뜻;
vector<int> cctvs[6] = {
	{},
	{0},
	{0,2},
	{0,1},
	{0,1,2},
	{0,1,2,3}, 
};
vector<pii> cctvCoors;

void input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> Map[i][j];
			if (Map[i][j] >= 1 && Map[i][j] <= 5) cctvCoors.push_back({ i,j });
			if (Map[i][j] == 0) zeroCnt++;
		}
	}
}

int turnDir(int dir, int rep) {
	while (rep--) dir = turnLeft[dir];
	return dir;
}

void dfs(int level) {
	if (level == cctvCoors.size()) {
		mx = max(mx, cnt);
		return;
	}

	auto tmpCctv = cctvCoors[level];
	int val = Map[tmpCctv.Y][tmpCctv.X]; int end = 4;
	if (val == 5) end = 1;
	for (int d = 1; d <= end;d++) {
		vector<pii> restoreCoor;
		for (int i = 0; i < cctvs[val].size(); i++) {
			int flag = 1;
			int l = 1;
			int turnRep = cctvs[val][i];
			int realDir = turnDir(d, turnRep);
			while (flag) {
				int ny = tmpCctv.Y + dy[realDir] * l;
				int nx = tmpCctv.X + dx[realDir] * l;
				if (ny < 0 || nx < 0 || ny >= N || nx >= M) { flag = 0; continue; }
				if ((Map[ny][nx] >= 1 && Map[ny][nx] <= 5) || Map[ny][nx] == 9) { l++; continue; }
				if (Map[ny][nx] == 6) { flag = 0; continue; }
				Map[ny][nx] = 9;
				cnt++;
				restoreCoor.push_back({ ny,nx });
				l++;
			}
		}
		dfs(level + 1);
		for (int i = 0; i < restoreCoor.size(); i++) {
			Map[restoreCoor[i].Y][restoreCoor[i].X] = 0;
			cnt--;
		}
	}
}

int main(){
	input();
	dfs(0);
	cout << zeroCnt - mx;
	return 0;
}
