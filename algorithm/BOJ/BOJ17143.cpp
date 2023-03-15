#include <iostream>
#include <algorithm>
#include <cstring>
#include <deque>

#define R first
#define C second

using namespace std;
using pii = pair<int, int>;
using ll = long long;

int N, M, num, mx = 0;
struct shark {
    int idx, r, c, s, d, z;
};
deque<int> Map[110][110];
deque<int> MapCpy[110][110];

deque<shark> sharks;
int dr[] = { 0, -1,1,0,0 };
int dc[] = { 0, 0,0,1,-1 };
int reverseDir[] = { 0,2,1,4,3 };

bool cmp(int a, int b) {
    if (sharks[a].z < sharks[a].z) return true;
    return false;
}

void input() {
    sharks.push_back({ 0,0,0,0,0,0 });
    cin >> N >> M >> num;
    for (int i = 1; i <= num; ++i) {
        shark tmp; tmp.idx = i;
        cin >> tmp.r >> tmp.c >> tmp.s >> tmp.d >> tmp.z;
        if (tmp.d == 1 || tmp.d == 2) tmp.s %= ((N - 1) * 2);
        if (tmp.d == 3 || tmp.d == 4) tmp.s %= ((M - 1) * 2);
        sharks.push_back(tmp);
        Map[tmp.r][tmp.c].push_back(i);
    }
}

void move(shark& now) {
    if (now.z == 0) return;
    int rep = now.s;
    Map[now.r][now.c].clear();
    for (int k = 0; k < rep; ++k) {
        int nr = now.r + dr[now.d]; int nc = now.c + dc[now.d];
        if (nr < 1 || nc<1 || nr>N || nc>M) now.d = reverseDir[now.d];
        now.r += dr[now.d];
        now.c += dc[now.d];
    }
    if (MapCpy[now.r][now.c].empty()) MapCpy[now.r][now.c].push_front(now.idx);
    else {
        if (sharks[MapCpy[now.r][now.c].back()].z < now.z) MapCpy[now.r][now.c].push_back(now.idx);
        else MapCpy[now.r][now.c].push_front(now.idx);
    }
}

void eat() {
    for (int i = 1; i <= num; ++i) {
        auto now = sharks[i];
        if (now.z == 0) continue;
        int sz = MapCpy[now.r][now.c].size();
        if (sz == 0) continue;
        for (int k =0; k<sz-1; ++k){
            int idx = MapCpy[now.r][now.c].front();
            MapCpy[now.r][now.c].pop_front();
            sharks[idx].z = 0;
        }
        int idx = MapCpy[now.r][now.c].front();
        Map[now.r][now.c].push_back(idx);
        MapCpy[now.r][now.c].pop_front();
    }
}

int main() {
    input();
    ll ret = 0;
    for (int i = 1; i <= M; ++i) {
        for (int j = 1; j <= N; ++j) {
            if (!Map[j][i].empty()) {
                ret += sharks[Map[j][i].front()].z;
                sharks[Map[j][i].front()].z = 0;
                Map[j][i].clear();
                break;
            }
        }
        for (int k = 1; k <= num; ++k) {
            move(sharks[k]);
        }
        eat();
    }
    cout << ret;
    return 0;
}