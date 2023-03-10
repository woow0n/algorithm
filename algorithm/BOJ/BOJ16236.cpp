#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

#define R first
#define C second

using namespace std;
using pii = pair<int, int>;

int Map[25][25];
int n;
int sz = 2;
int cnt;
int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };
int costs[25][25];

pii babyShark;
vector<pii> fishs[7];

void input() {
    cin >> n;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            cin >> Map[r][c];
            if (Map[r][c] == 9) { Map[r][c] = 0; babyShark = { r,c }; continue; }
            if (Map[r][c] >= 1) fishs[Map[r][c]].push_back({ r,c });
        }
    }
    fishs[0].push_back({ 0, 0 });
}

void bfs() {
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            costs[r][c] = 21e8;
        }
    }
    queue<pii> q;
    q.push({ babyShark.R,babyShark.C });
    costs[babyShark.R][babyShark.C] = 0;

    while (!q.empty()) {
        pii now = q.front(); q.pop();
        for (int i = 0; i < 4; i++) {
            int nr = now.R + dr[i];
            int nc = now.C + dc[i];
            if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
            if (Map[nr][nc] > sz) continue;
            int cost = costs[now.R][now.C] + 1;
            if (costs[nr][nc] <= cost) continue;
            costs[nr][nc] = cost;
            q.push({ nr,nc });
        }
    }
}

int main()
{
    int ret = 0;  int flag = 1;
    input();
    while (flag) {
        bfs();
        pii eatIdx = { 0,0 }; int eatCost = 21e8;
        for (int i = 1; i < min(sz,7); i++) {
            for (int j = 0; j < fishs[i].size(); j++) {
                auto tmpfish = fishs[i][j];
                auto eatfish = fishs[eatIdx.first][eatIdx.second];
                int tmpCost = costs[tmpfish.R][tmpfish.C];
                if (tmpCost == 21e8) continue;
                if (tmpCost > eatCost) continue;
                else if (tmpCost == eatCost) {
                    if (eatfish.R > tmpfish.R) {
                        eatIdx = { i,j }; eatCost = tmpCost; continue;
                    }
                    if (eatfish.R == tmpfish.R && eatfish.C > tmpfish.C) {
                        eatIdx = { i,j }; eatCost = tmpCost; continue;
                    }
                }
                else if (tmpCost < eatCost) {
                    eatIdx = { i,j }; eatCost = tmpCost;
                }
            }
        }
        if (eatIdx.R == 0 && eatIdx.C == 0) { flag = 0; break; }
        else {
            cnt++;
            if (cnt == sz) { sz++; cnt = 0; }
            babyShark = fishs[eatIdx.first][eatIdx.second];
            ret += eatCost;
            Map[babyShark.first][babyShark.second] = 0;
            fishs[eatIdx.first].erase(fishs[eatIdx.first].begin() + eatIdx.second);
        }
    }
    cout << ret;
    return 0;
}