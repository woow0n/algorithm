#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>
#include <cmath>
#include <deque>

#define R first
#define C second

using namespace std;
using pii = pair<int, int>;
using ll = long long;
int sum, mx = -21e8;
int dr[] = { 0, -1,-1,0,1,1,1,0,-1 };
int dc[] = { 0, 0,-1,-1,-1,0,1,1,1 };

struct fish { int idx, r, c, d, deadFlag; };
deque<fish> fishs;
deque<deque<int>> Map;
// 다음놈(방향)은 +1 %8 연산으로 찾을 수 있다
void Swap(fish& a, fish& b) {
    fish tmp = a;
    a = b;
    b = tmp;
}

void input() {
    for (int i = 0; i < 17; ++i) fishs.push_back({ 0,0,0,0 });
    for (int i = 0; i < 4; ++i) {
        deque<int> tmp;
        for (int j = 0; j < 4; ++j) {
            tmp.push_back(0);
        }
        Map.push_back(tmp);
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int idx, d;  cin >> idx >> d;
            fishs[idx] = { idx, i, j ,d,0 };
            Map[i][j] = idx;
        }
    }
    // 첫놈은 먹고시작;
    sum += Map[0][0];
    fishs[0].d = fishs[Map[0][0]].d;
    fishs[Map[0][0]].deadFlag = 1;
    Map[0][0] = 0;
}

int rotate(int num) {
    if (num == 8) return (num + 2) % 9;
    else return (num + 1) % 9;
}
// is shark 
int findNextDir(fish tmp, deque<deque<int>> Map, deque<fish> fishs) {
    int dir = tmp.d; int row = tmp.r; int col = tmp.c;
    int flag = 1;
    while (flag) {
        int nr = row + dr[dir]; int nc = col + dc[dir];
        if (nr < 0 || nc < 0 || nr >= 4 || nc >= 4) { dir = rotate(dir); continue; }
        if (nr == fishs[0].r && nc == fishs[0].c) { dir = rotate(dir); continue; }
        flag = 0;
    }
    return dir;
}

void timeRun(deque<deque<int>>& Map, deque<fish>& fishs) {
    for (int i = 1; i < 17; ++i) {
        if (fishs[i].deadFlag) continue;
        int row = fishs[i].r; int col = fishs[i].c;
        int nd = findNextDir(fishs[i],Map, fishs);
        fishs[i].d = nd;
        int nr = row + dr[nd]; int nc = col + dc[nd];
        int target = Map[nr][nc];
        swap(Map[row][col], Map[nr][nc]);
        if (target == 0) {
            fishs[i].r = nr;
            fishs[i].c = nc;
        }
        else {
            swap(fishs[i].r, fishs[target].r);
            swap(fishs[i].c, fishs[target].c);
        }
    }
}

void dfs(deque<deque<int>> Map, deque<fish> fishs, int sum) {
    timeRun(Map, fishs);
    deque<pii> sub;
    for (int i = 1; i <= 3; ++i) {
        int nsr = fishs[0].r + dr[fishs[0].d] * i;
        int nsc = fishs[0].c + dc[fishs[0].d] * i;
        if (nsr < 0 || nsc < 0 || nsr >= 4 || nsc >= 4) break;
        if (Map[nsr][nsc] == 0) continue;
        sub.push_back({ nsr,nsc });
    }
    if (sub.size() == 0) {
        mx = max(mx, sum);
        return;
    }

    for (int i = 0; i < sub.size(); ++i) {
        pii nCoor = sub[i];
        int val = Map[nCoor.R][nCoor.C];
        int lastSr = fishs[0].r; int lastSc = fishs[0].c; int lastDir = fishs[0].d;
        sum += val;
        fishs[val].deadFlag = 1;
        Map[nCoor.R][nCoor.C] = 0;
        fishs[0].r = nCoor.R; fishs[0].c = nCoor.C; fishs[0].d = fishs[val].d;
        dfs(Map, fishs, sum);
        fishs[0].r = lastSr; fishs[0].c = lastSc; fishs[0].d = lastDir;
        Map[nCoor.R][nCoor.C] = val;
        fishs[val].deadFlag = 0;
        sum -= val;
    }
}

int main() {
    input();
    dfs(Map, fishs, sum);
    cout << mx;
    int de = 1;
    return 0;
}