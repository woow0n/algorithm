#include <iostream>
#include <vector>
#include <queue>

using namespace std;
using pic = pair<int, char>;
using pii = pair<int, int>;

int N, K, L;
int dir, y, x;
int map[110][110];
int dy[] = { -1,1,0,0 };
int dx[] = { 0,0,-1,1 };
vector<pic> cmds;
queue<pii> snake;
// 먼저 간애가 front임
void input() {
	cin >> N >> K;
	for (int k = 0; k < K; k++) {
		int y, x;
		cin >> y >> x;
		map[y][x] = 'a';
	}
	cin >> L;
	for (int l = 0; l < L; l++) {
		int x; char r;
		cin >> x >> r;
		cmds.push_back({x,r});
	}
	dir = 3; y = 1; x = 1; snake.push({ 1,1 });
}

int rotateHead(int dir, char lr) {
	int dR[] = {3,2,0,1};
	int dL[] = {2,3,1,0};
	if (lr == 'L') return dL[dir];
	if (lr == 'D') return dR[dir];
}

int move() {
	y += dy[dir]; x += dx[dir];
	int sz = snake.size();
	if (y<1 || x < 1 || y>N || x>N) return 0;
	for (int i = 0; i < sz; i++) {
		auto now = snake.front(); snake.pop();
		if (y == now.first && x == now.second) return 0;
		snake.push(now);
	}
	snake.push({ y,x });
	if (map[y][x] != 'a')  snake.pop();
	if (map[y][x] == 'a')  map[y][x] = 0;
	return 1;
}

int main(){
	input();
	int time = 0; int flag = 1; int cmdPointer = 0;
	while (flag) {
		time++;
		flag = move();
		// 시간이 맞으면은 회전하기 
		if (cmdPointer < cmds.size() && cmds[cmdPointer].first == time) {
			dir = rotateHead(dir, cmds[cmdPointer].second);
			cmdPointer++;
		}
	}
	cout << time;
	int de = 1;
	return 0;
}