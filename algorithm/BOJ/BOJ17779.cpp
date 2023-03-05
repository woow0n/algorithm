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
int Map[22][22];
int mark[22][22];

int dy[] = { -1,1,1,-1 };
int dx[] = { 1,1,-1,-1 };
int ddy[] = { -1,0,1,0 };
int ddx[] = { 0,1,0,-1 };
void input() {
    cin >> n ;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <n ; j++) {
            cin >> Map[i][j];
        }
    }
}

void floodfill(pii initP, int name) {
    queue<pii> q;
    q.push(initP);
    mark[initP.Y][initP.X] = name;
    while (!q.empty()){
        pii now = q.front(); q.pop();
        for (int i = 0; i < 4; i++) {
            int ny = now.Y + ddy[i]; int nx = now.X + ddx[i];
            if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
            if (mark[ny][nx]!=0) continue;
            mark[ny][nx] = name;
            q.push({ ny,nx });
        }
    }
}


void devide(int initY, int initX, int d1, int d2) {
    int y = initY; int x = initX; mark[y][x] = 5;
    for (int i = 0; i < 4; i++) {
        int rep = 0; if (i % 2) rep = d2; else rep = d1;
        for (int j = 0; j < rep; j++) {
            y += dy[i]; x += dx[i];        
            mark[y][x] = 5;
        }
        int cpy = y; int cpx = x;
        while (1) {
            int ny = cpy + ddy[i]; int nx = cpx + ddx[i];
            if (ny < 0 || nx < 0 || ny >= n || nx >= n) break;
            mark[ny][nx] = i + 1;
            cpy=ny; cpx = nx;
        }
    }
    pii floodfillPoint[5] = { {0,0},{0,0},{0,n - 1},{n - 1,n - 1},{n - 1,0}};
    for (int i = 1; i <= 4; i++) {
        floodfill(floodfillPoint[i], i);
    }
}

int calScore() {
    int scores[6] = {0,};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scores[mark[i][j]]+=Map[i][j];
        }
    }
    scores[5] += scores[0];
    scores[0] = 0;
    sort(scores, scores + 6);
    return scores[5] - scores[1];
}

int main() {
    input();

    for (int x = 1; x <= n - 2; x++) {
        for (int y = 2; y <= n - 1; y++) {
            for (int d1 = 1; d1 <= y - 1 && d1 <= n - x - 1; d1++) {
                for (int d2 = 1; d2 <= n - y && d2 <= n - x - 1; d2++) {
                    memset(mark, 0, sizeof(mark));
                    devide(y-1, x-1, d1, d2);
                    int sc = calScore();
                    mn = min(sc, mn);
                }
            }
        }
    }

    cout << mn;

    int de = 2;
    return 0;
}
