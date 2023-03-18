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

deque<int> Map[22][22];
pii smells[22][22];
int n, m, k;
int dr[] = { 0,-1,1,0,0 }; int dc[] = { 0,0,0,-1,1 }; 
int sharkDir[401]; int sharkDirOrder[401][5][5]; pii sharkPos[401];
struct posd { int r, c, i,d; };

// 아무냄새가 없는 칸이 먼저 -> 없으면 내 냄새가 있는곳 
// 가능한 곳이 어려개면 특정한 우선순위를 따른다
// 한격자에 여러마리면 나머지는 쫒겨난다
// 1번만 남을 때는 몇조임?
// 냄새는 k초후에 사라짐
void input() {
    cin >> n >> m >> k;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            int a; cin >> a;
            if (a != 0) {
                Map[r][c].push_back(a);
                sharkPos[a] = { r,c };
            }
        }
    }
    for (int i = 1; i <= m; ++i) {
        cin >> sharkDir[i]; 
    }
    for (int i = 1; i <= m; ++i) {
        for (int r = 1; r <= 4; ++r) {
            for (int c = 1; c <= 4; ++c) {
                int a; cin >> a;
                sharkDirOrder[i][r][a] = c;
            }
        }
    }
}
// 정렬 우선순위
//bool scro(posd posA, posd posB) {
//    if (smells[posA.r][posA.c].first == 0 && smells[posB.r][posB.c].first != 0) return true;
//    if (smells[posA.r][posA.c].first == 0 && smells[posB.r][posB.c].first == 0) {
//        if (sharkDirOrder[posA.i][sharkDir[posA.i]][posA.d] < sharkDirOrder[posA.i][sharkDir[posA.i]][posB.d]) return true;
//        else return false;
//    }
//    if (smells[posA.r][posA.c].first == posA.i && smells[posB.r][posB.c].first != posA.i) return true;
//    if (smells[posA.r][posA.c].first == posA.i && smells[posB.r][posB.c].first == posA.i) {
//        if (sharkDirOrder[posA.i][sharkDir[posA.i]][posA.d] < sharkDirOrder[posA.i][sharkDir[posA.i]][posB.d]) return true;
//        else return false;
//    }
//    return false;
//}

int score(posd pos) {
    int ret = 0;
    if (smells[pos.r][pos.c].first == pos.i) ret += 10;
    else if (smells[pos.r][pos.c].first != 0) ret += 20;
    ret += sharkDirOrder[pos.i][sharkDir[pos.i]][pos.d];
    return ret;
}

int sharkMove(int time) {

    for (int i = 1; i <= m; ++i) {
        vector<posd> posibleSharkDir;
        pii now = sharkPos[i]; int dir = sharkDir[i];
        if (dir == -1) continue;
        for (int d = 1; d <= 4; ++d) {
            int nr = now.R + dr[d]; int nc = now.C + dc[d];
            if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
            posibleSharkDir.push_back({ nr,nc,i,d });
        }
        posd movePos = posibleSharkDir[0]; int min_val = score(movePos);
        for (int j = 1; j < posibleSharkDir.size(); ++j) {
            int sc = score(posibleSharkDir[j]);
            if (min_val > sc) {
                min_val = sc; movePos = posibleSharkDir[j];
            }
        }
        sharkDir[i] = movePos.d;
        sharkPos[i] = { movePos.r,movePos.c };
        // 확인할것.
        int idx = 0;
        for (int k = 0; k < Map[now.R][now.C].size(); ++k) {
            if (Map[now.R][now.C][k] == i) idx = k;
        }
        Map[now.R][now.C].erase(Map[now.R][now.C].begin() + idx);
        int sz = Map[movePos.r][movePos.c].size();
        if (!sz) Map[movePos.r][movePos.c].push_back(i);
        else {
            if (Map[movePos.r][movePos.c].back() > i) Map[movePos.r][movePos.c].push_back(i);
            else Map[movePos.r][movePos.c].push_front(i);
        }
    }
    int cnt = 0;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            int sz = Map[r][c].size();
            if (sz > 1) {
                sz--; cnt += 1;
                while (sz--){
                    int tmp = Map[r][c].front();
                    sharkDir[tmp] = -1;
                    Map[r][c].pop_front();
                }
            }
            else { cnt += sz; }
        }
    }

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (smells[r][c].first != 0 ) smells[r][c].second--;
            if (smells[r][c].first != 0 && smells[r][c].second ==0) smells[r][c] = { 0,0 };
        }
    }
    for (int i = 1; i <= m; ++i) {
        if (sharkDir[i] == -1) continue;
        pii now = sharkPos[i];
        smells[now.R][now.C] = { i, k };
    }
    if (cnt == 1) return 1;
    else return 0;
}

int main() {
    input();
    int time = 0;
    for (int i = 1; i <= m; ++i) {
        pii now = sharkPos[i];
        smells[now.R][now.C] = { i, k };
    }

    while (time <= 1000)
    {
        time++;
        int flag = sharkMove(time);
        if (flag) break;
    }
    if (time > 1000) cout << -1;
    else cout << time;

    return 0;
}