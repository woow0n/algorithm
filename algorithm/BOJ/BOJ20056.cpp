#include <iostream>
#include <vector>
#include <queue>

#define Y first
#define X second

using namespace std;
using pii = pair<int, int>;

int n, m, k, idx;
int dy[] = { -1, -1, 0, 1,1,1,0,-1, };
int dx[] = { 0,1,1,1,0,-1,-1,-1 };
int sameDir[] = { 0,2,4,6 };
int diffDir[] = { 1,3,5,7 };

struct fireBall {
    int idx, y, x, m, s, d, status;
};
vector<fireBall> fireBalls;
vector<int> Map[55][55];

void input() {
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        fireBall tmp; tmp.idx = idx++; tmp.status = 0;
        cin >> tmp.y >> tmp.x >> tmp.m >> tmp.s >> tmp.d;
        tmp.y--; tmp.x--;
        fireBalls.push_back(tmp);
    }
}

void moveFire(fireBall now) {
    now.y = ((now.y + dy[now.d]* now.s)+1000*n) % n;
    now.x = ((now.x + dx[now.d]* now.s)+1000*n) % n;
    fireBalls[now.idx] = now;
    Map[now.y][now.x].push_back(now.idx);
}


void moveUnion() {
    int sz = fireBalls.size();
    for (int i = 0; i < sz; i++) {
        auto now = fireBalls[i];
        if (now.status == 1) continue;
        moveFire(now);
    }

    sz = fireBalls.size();

    for (int i = 0; i < sz; i++) {
        auto now = fireBalls[i];
        if (Map[now.y][now.x].size() == 1) {
            Map[now.y][now.x].clear();
            continue;
        }
        if (now.status == 1) continue;
        int tmpSz = Map[now.y][now.x].size();
        auto tmpVect = Map[now.y][now.x];
        int massSum = 0, speedSum = 0, dirSum = 0;
        for (int j = 0; j < tmpSz; j++) {
            massSum += fireBalls[tmpVect[j]].m;
            speedSum += fireBalls[tmpVect[j]].s;
            dirSum += fireBalls[tmpVect[j]].d % 2;
            fireBalls[tmpVect[j]].status = 1;
        }
        Map[now.y][now.x].clear();
        if (massSum / 5 == 0) continue;
        if (dirSum == 0 || dirSum == tmpSz) {
            for (int k = 0; k < 4; k++) {
                int dir = sameDir[k];
                fireBalls.push_back({ idx++,now.y ,now.x,massSum / 5, speedSum / tmpSz,dir,0 });
            }
        }
        else {
            for (int k = 0; k < 4; k++) {
                int dir = diffDir[k];
                fireBalls.push_back({ idx++,now.y ,now.x,massSum / 5, speedSum / tmpSz,dir,0 });
            }
        }
    }
}


int main() {
    input();
    while (k--) {
        moveUnion();
    }
    int ans = 0;
    int sz = fireBalls.size();
    for (int i = 0; i < sz; i++) {
        auto now = fireBalls[i];
        if (now.status == 1) continue;
        ans += now.m;
    }
    cout << ans;
    return 0;
}
