#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

#define Y first
#define X second

using namespace std;
using pii = pair<int, int>;
using fish = pair<pii, int>;


int N,M, mn=21e8, zeroCnt;
int Map[55][55];
int vst[55][55];
int dy[] = { -1,1,0,0 };
int dx[] = { 0,0,-1,1 };

vector<pii> subs;
int subVst[11];

vector<int> path;
void input() {
    cin >> N >> M;
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            cin >> Map[r][c];
            if (Map[r][c] == 2) subs.push_back({ r,c });
            if (Map[r][c] == 0) zeroCnt++;
        }
    }
}

int bfs(vector<int>& path) {
    queue<pii> q; int cnt = 0;
    for (int i = 0; i < M; i++) {
        q.push(subs[path[i]]);
        vst[subs[path[i]].Y][subs[path[i]].X] = 1;
    }
    int time = 1;
    while (!q.empty()) {
        int sz = q.size(); time++;
        for (int rep = 0; rep < sz; rep++) {
            pii now = q.front(); q.pop();
            for (int i = 0; i < 4; i++) {
                int ny = now.Y + dy[i];
                int nx = now.X + dx[i];
                if (ny < 0 || nx < 0 || nx >= N || ny >= N) continue;
                if (Map[ny][nx] == 1) continue;
                if (vst[ny][nx] > 0) continue;
                q.push({ ny,nx });
                vst[ny][nx] = time;
                cnt++;
            }
        }
    }
    if (cnt != zeroCnt - M + subs.size()) return 21e8;
    return time-2;
}

void dfs(int level, int startIdx) {
    if (level == M) {
        memset(vst, 0, sizeof(vst));
        int time = bfs(path);
        mn = min(mn, time);
    }
    for (int i = startIdx; i < subs.size(); i++) {
        if (subVst[i] == 1) continue;
        subVst[i] = 1;
        path.push_back(i);
        dfs(level+1, i + 1);
        subVst[i] = 0;
        path.pop_back();
    }
}


int main() {
    input();
    dfs(0, 0);
    if (mn == 21e8) cout << -1;
    else cout << mn;
    return 0;
}
