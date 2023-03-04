#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#define Y first
#define X second
using namespace std;
using pic = pair<int, char>;
using pii = pair<int, int>;
using ll = long long;
using key = pair<pii, pii>;
int N, M, mx = -21e8, cnt, zeroCnt;
struct dragon {
    int y, x, dir, level;
};
vector<dragon> dragons;
int Map[101][101];
int dy[] = { 0,-1,0,1 };
int dx[] = { 1,0,-1,0 };

void input() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        dragon tmp;
        cin >> tmp.x >> tmp.y >> tmp.dir >> tmp.level;
        dragons.push_back(tmp);
    }
}

pii rotate90(pii r, pii spot) {
    int new_x = spot.X - (r.Y - spot.Y);
    int new_y = spot.Y + (r.X - spot.X);
    return { new_y, new_x };
}

void makeDragon(dragon nowDragon, int name) {
    vector<pii> coors;
    coors.push_back({ nowDragon.y, nowDragon.x });
    int ny = nowDragon.y + dy[nowDragon.dir];
    int nx = nowDragon.x + dx[nowDragon.dir];
    coors.push_back({ ny,nx });
    int level = 1; int flag = 1;
    if (nowDragon.level == 0) flag = 0;
    pii around = { 0,0 };
    pii nextAround = { 0,0 };

    while (flag) {
        int sz = coors.size();
        if (level == 1) around = coors[sz - 1];
        else around = nextAround;
        for (int i = 0; i < sz; i++) {
            auto tmp = coors[i];
            if (tmp.Y == around.Y && tmp.X == around.X) continue;
            auto rotate = rotate90(tmp, around);
            if (i == 0) nextAround = rotate;
            coors.push_back(rotate);
        }
        if (level == nowDragon.level) break;
        level++;
    }
    for (int i = 0; i < coors.size(); i++) {
        Map[coors[i].Y][coors[i].X] = 1;
    }
}


int main() {
    input();
    for (int i = 0; i < dragons.size(); i++) {
        makeDragon(dragons[i], i+1);
    }
    int ret = 0;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            int tmp = Map[i][j] + Map[i + 1][j] + Map[i][j + 1] + Map[i + 1][j + 1];
            if (tmp >= 4) ret++;
        }
    }
    cout << ret;
    return 0;
}
