#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <cstring>

#define Y first
#define X second
using namespace std;
using pic = pair<int, char>;
using pii = pair<int, int>;
using ll = long long;

int N, L, R;
int Map[55][55];
int vst[55][55];
int beforeVst[55][55];

int dy[] = { -1,1,0,0 };
int dx[] = { 0,0,-1,1 };

void input() {
    cin >> N >> L >> R;
    int a = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> Map[i][j];
            beforeVst[i][j] = a++;
        }
    }
}
// 같은 나라가 될 수 있나 확인을 bfs로하자 
int bfs(int sy, int sx, int name) {
    queue<pii> q; vector<pii> nations;
    q.push({ sy,sx });
    nations.push_back({ sy, sx });
    vst[sy][sx] = name;
    int sum = Map[sy][sx]; int cnt = 1;
    while (!q.empty()){
        pii now = q.front(); q.pop();
        for (int i = 0; i < 4; i++) {
            int ny = now.Y + dy[i];
            int nx = now.X + dx[i];
            if (nx < 0 || ny < 0 || ny >= N || nx >= N) continue;
            if (vst[ny][nx] != 0) continue;
            int diff = abs(Map[ny][nx] - Map[now.Y][now.X]);
            if ( diff < L || diff > R) continue;
            if (beforeVst[ny][nx] == beforeVst[now.Y][now.X]) continue;
            q.push({ ny, nx });
            nations.push_back({ ny, nx });
            vst[ny][nx] = name;
            sum += Map[ny][nx];
            cnt++;
        }
    }
    int val = sum / cnt;
    for (int i = 0; i < nations.size(); i++) {
        Map[nations[i].Y][nations[i].X] = val;
    }
    if (cnt == 1) return 0;
    return 1;
}



int main() {
    input();
    int year = 0; int flag = 1; int nation = 1;
    while (flag) {
        year++;
        int check = 0;  
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (vst[i][j] == 0) {
                    check += bfs(i, j, nation++);
                }
            }
        }
        for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) 
            beforeVst[i][j] = vst[i][j];
        memset(vst, 0, sizeof(vst));
        if (check == 0) flag = 0;
    }
    cout << year-1;

    int de = 123;
    return 0;
}
