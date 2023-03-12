#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <deque>
#include <queue>

#define R first
#define C second

using namespace std;
using pii = pair<int, int>;

int n, m, k, dir;
int Map[22][22];
int score[22][22];

int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };
// dice[3] -> 바닥면
vector<int> dice = {0,1,2,3,4,5,6};
pii dicePos = { 1,1 };
int diceDir = 3;
int reveseDir[] = {1,0,3,2};
int clockWise[] = {3,2,0,1};
int counterClockWise[] = { 2,3,1,0 };
// v플러드필로 맵채우고시작할 것
void input() {
    cin >> n >> m >>k; 
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> Map[i][j];
        }
    }
}

void diceMove() {
    int nr = dicePos.R + dr[diceDir];
    int nc = dicePos.C + dc[diceDir];
    if (nr < 1 || nc<1 || nr>n || nc>m) { 
        diceDir = reveseDir[diceDir];
        nr = dicePos.R + dr[diceDir];
        nc = dicePos.C + dc[diceDir];
    }
    int val = Map[nr][nc];
    
    if (diceDir == 0) dice = { 0, dice[5], dice[1], dice[3], dice[4], dice[6], dice[2] };
    if (diceDir == 1) dice = { 0, dice[2], dice[6], dice[3], dice[4], dice[1], dice[5] };
    if (diceDir == 2) dice = { 0, dice[3], dice[2], dice[6], dice[1], dice[5], dice[4] };
    if (diceDir == 3) dice = { 0, dice[4], dice[2], dice[1], dice[6], dice[5], dice[3] };

    if (dice[6] > val) diceDir = clockWise[diceDir];
    if (dice[6] < val) diceDir = counterClockWise[diceDir];

    dicePos.R = nr;
    dicePos.C = nc;
}

void bfs(int r, int c) {
    int val = Map[r][c];
    queue<pii> q;
    vector<pii> v;
    score[r][c] = 1;
    q.push({ r,c });
    v.push_back({ r,c });
    int sc = 1;
    int cnt = 1;
    while (!q.empty()) {
        sc++;
        int sz = q.size();
        for (int i = 0; i < sz; ++i) {
            pii now = q.front(); q.pop();
            for (int dir = 0; dir < 4; ++dir) {
                int nr = now.R + dr[dir];
                int nc = now.C + dc[dir];
                if (nr < 1 || nc<1 || nr>n || nc>m) continue;
                if (score[nr][nc]>0) continue;
                if (Map[nr][nc]!=val) continue;
                cnt++;
                q.push({ nr,nc });
                score[nr][nc] = sc;
                v.push_back({ nr,nc });
            }
        }
    }
    for (int i = 0; i < (int)v.size(); ++i) {
        auto now = v[i];
        score[now.R][now.C] = cnt;
    }
}


int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    input();
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (score[i][j] > 0) continue;
            bfs(i, j);
        }
    }
    int ans = 0;
    while (k--) {
        diceMove();
        ans += Map[dicePos.R][dicePos.C] * score[dicePos.R][dicePos.C];
    }
    cout << ans;
    return 0;
}
