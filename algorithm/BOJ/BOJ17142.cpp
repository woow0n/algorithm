#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <cstring>

#define Y first
#define X second
using namespace std;
using pii = pair<int, int>;
using ll = long long;

int n, m, zeroCnt, mn=21e8;
int Map[55][55];
int mapVst[55][55];
int vst[15];
vector<pii> viruses;
vector<int> path;
int dy[] = { -1,1,0,0 };
int dx[] = { 0,0,-1,1 };

void input() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <n ; j++) {
            cin >> Map[i][j];
            if (Map[i][j] == 2) viruses.push_back({ i,j });
            if (Map[i][j] == 0) zeroCnt++;
        }
    }
}

int bfs(vector<int>& path) {
    if (zeroCnt == 0) return 0;
    queue<pii> q;
    for (int i = 0; i < path.size(); i++) {
        pii now = viruses[path[i]];
        q.push(now);
        mapVst[now.Y][now.X] = -1;
    }
    int time = 0; int cnt = 0;
    while (!q.empty()) {
        time++;
        int sz = q.size(); 
        for (int i = 0; i < sz; i++) {
            pii now = q.front(); q.pop();
            for (int d = 0; d < 4; d++) {
                int ny = now.Y + dy[d];
                int nx = now.X + dx[d];
                if (ny < 0 || nx < 0 || nx >= n || ny >= n)continue;
                if (mapVst[ny][nx] != 0)continue;
                if (Map[ny][nx] == 1)continue;
                if (Map[ny][nx] == 2) { 
                    q.push({ ny,nx });
                    mapVst[ny][nx] = -2;
                    continue; 
                }
                q.push({ ny,nx });
                mapVst[ny][nx] = time;
                cnt++;
            }
        }
        if (cnt == zeroCnt) return time;
    }
    return -1;
}


void dfs(int level, int startIdx) {
    if (level == m){
        memset(mapVst, 0, sizeof(mapVst));
        int time = bfs(path);
        if (time == -1) return;
        mn = min(mn, time);
        return;
    }

    for (int i = startIdx; i < viruses.size(); i++) {
        if (vst[i] == 1) continue;
        vst[i] = 1;
        path.push_back(i);
        dfs(level + 1, i+1);
        vst[i] = 0;
        path.pop_back();
    }
}


int main() {
    input();
    dfs(0,0);
    if (mn == 21e8) cout << -1;
    else cout << mn;
    int de = 123;
}
