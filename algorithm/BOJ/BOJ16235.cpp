#include <iostream>
#include <deque>
#include <algorithm>
#define Y first
#define X second
using namespace std;
using pii = pair<int, int >;

int n, m, k;
deque<int> Map[15][15];
int nutrient[15][15];
int tmpNutrient[15][15];

void input() {
    cin >> n >> m >> k;
    for (int y = 1; y <= n; y++) {
        for (int x = 1; x <= n; x++) {
            cin >> nutrient[y][x];
            tmpNutrient[y][x] = 5;
        }
    }
    for (int i = 0; i < m; i++) {
        int x, y, age;
        cin >> x >> y >> age;
        Map[x][y].push_back(age);
    }
}


void springsummer() {
    for (int y = 1; y <= n; y++) {
        for (int x = 1; x <= n; x++) {
            int sz = Map[y][x].size();
            if (sz == 0) continue;
            int j = 0;
            for (; j < sz; ++j) {
                if (Map[y][x][j] > tmpNutrient[y][x]) break;
                tmpNutrient[y][x] -= Map[y][x][j];
                Map[y][x][j]++; 
            }
            for (int k = sz-1; k >=j; k--) {
                tmpNutrient[y][x] += Map[y][x][k] / 2;
                Map[y][x].pop_back();
            }
        }
    } 
}

void fall() {
    int dy[] = { -1,-1,-1,0,0,1,1,1 };
    int dx[] = { -1,0,1,-1,1,-1,0,1 };
    for (int y = 1; y <= n; y++) {
        for (int x = 1; x <= n; x++) {
            int sz = Map[y][x].size();
            if (sz == 0) continue;
            for (int j = 0; j < sz; j++) {
                if (Map[y][x][j] % 5) continue;
                for (int d = 0; d < 8; d++) {
                    int ny = y + dy[d];
                    int nx = x + dx[d];
                    if (ny < 1 || nx<1 || ny>n || nx>n) continue;
                    Map[ny][nx].push_front(1);
                }
            }
        }
    }
}

void winter() {
    for (int y = 1; y <= n; y++) {
        for (int x = 1; x <= n; x++) {
            tmpNutrient[y][x] += nutrient[y][x];
        }
    }
}

int main() {
    input();
    while (k--) {
        springsummer();
        fall();
        winter();
    }
    int ret = 0;
    for (int y = 1; y <= n; y++) {
        for (int x = 1; x <= n; x++) {
            int sz = Map[y][x].size();
            ret += sz;
        }
    }
    cout << ret;
    return 0;
}