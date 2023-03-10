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
using pII = pair<pii, pii>;
int n, m, f;
int Map[22][22];
int costs[22][22];

int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };
pii taxi;
pII passengers[420];
int passengersVst[420];

bool cmp(pII a, pII b) {
    if (a.first.R < b.first.R) return true;
    if (a.first.R == b.first.R) {
        if (a.first.C < b.first.C) return true;
    }
    return false;
}

void input() {
    cin >> n >> m >> f;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> Map[i][j];
        }
    }
    cin >> taxi.R >> taxi.C;
    for (int i = 0; i < m; ++i) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        passengers[i] = { { a,b }, { c,d } };
    }
    sort(passengers, passengers + m, cmp);
}

int bfs(int r, int c) {
    queue<pii> q;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            costs[i][j] = 21e8;
        }
    }
    int cost = 0;
    costs[r][c] = cost;
    q.push({ r,c });
    while (!q.empty()) {
        int sz = q.size();
        cost++;
        for (int j = 0; j < sz; ++j) {
            pii now = q.front(); q.pop();
            for (int i = 0; i < 4; ++i) {
                int nr = now.R + dr[i];
                int nc = now.C + dc[i];
                if (nc<1 || nr<1 || nc>n || nr>n) continue;
                if (Map[nr][nc] == 1) continue;
                if (costs[nr][nc] <= cost) continue;
                costs[nr][nc] = cost;
                q.push({ nr,nc });
            }
        }
    }
    return cost;
}

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    input();
    int flag = 0; int ret = 0; int fuel = f;
    for (int i = 0; i < m; ++i) {
        bfs(taxi.R, taxi.C);
        int mnVal = 21e8, mnIdx = -1;
        for (int i = 0; i < m; ++i) {
            pii now = passengers[i].first;
            int val = costs[now.R][now.C];
            if (passengersVst[i] != 1 && val < mnVal) {
                mnVal = val; mnIdx = i;
            }
        }
        if (mnIdx == -1) { flag = 1; break; }
        pII passenger = passengers[mnIdx];
        passengersVst[mnIdx] = 1;
        bfs(passenger.first.R, passenger.first.C);
        int toDCost = costs[passenger.second.R][passenger.second.C];
        int toPCost = costs[taxi.R][taxi.C];
        int totalFuel = toPCost + toDCost;
        if (totalFuel > fuel) { flag = 1; break; }
        fuel -= toPCost;
        fuel += toDCost;
        taxi = passenger.second;
    }

    if (flag) cout << -1;
    else cout << fuel;
    return 0;
}