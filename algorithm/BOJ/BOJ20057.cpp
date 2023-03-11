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

int n, out;
int Map[550][550];
int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };
int dirCycle[] = { 2,1,3,0 };
pii coor;

int sandR[4][10] = { {-2,-3, 0,-1,-2, 0,-1,-2, -1,-1}, 
                     { 2, 3, 0, 1, 2, 0, 1, 2,  1, 1},
                     { 0, 0, 1, 1, 1,-1,-1,-1,  2,-2},
                     { 0, 0, 1, 1, 1,-1,-1,-1,  2,-2}};
int sandC[4][10] = { { 0, 0,-1,-1,-1,1, 1, 1, -2, 2},
                     { 0, 0,-1,-1,-1,1, 1, 1, -2, 2},
                     {-2,-3, 0,-1,-2, 0,-1,-2, -1,-1},
                     { 2, 3, 0, 1, 2, 0, 1, 2,  1, 1}};
double rates[10] = {0.45,0.05,0.01,0.07,0.1,0.01,0.07,0.1 ,0.02,0.02 };

void input() {
    cin >> n; coor = { n / 2, n / 2 };
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> Map[i][j];
        }
    }
}

void move(int dir) {
    int flag = 1;
    int NR = coor.R + dr[dir];
    int NC = coor.C + dc[dir];
    if (Map[NR][NC] == 0) { flag = 0; }
    if (flag) {
        int sand = Map[NR][NC];
        int alphaSand = Map[NR][NC];
        for (int i = 1; i < 10; i++)
        {
            int nr = coor.R + sandR[dir][i];
            int nc = coor.C + sandC[dir][i];
            int plus = sand * rates[i];
            if (nr < 0 || nc < 0 || nr >= n || nc >= n) out += plus;
            else Map[nr][nc] += plus;
            alphaSand -= plus;
        }
        int nr = coor.R + sandR[dir][0];
        int nc = coor.C + sandC[dir][0];
        if (nr < 0 || nc < 0 || nr >= n || nc >= n) out += alphaSand;
        else Map[nr][nc] += alphaSand;
    }
    coor.R = NR; coor.C = NC;
    Map[coor.R][coor.C] = 0;
}

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    input();

    int cnt = 0; int len = 1; int totalCnt = 0; int flag = 1;

    while (flag) {
        cnt++;
        int dir = totalCnt % 4;
        for (int i = 0; i < len; ++i) {
            move(dirCycle[dir]);

            if (coor.R == 0 && coor.C == 0) { flag = 0; break; }
        }
        if (cnt == 2) { cnt = 0; len++; }
        totalCnt++;
    }

    cout << out;
    return 0;
}
