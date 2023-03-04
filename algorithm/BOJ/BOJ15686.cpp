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

int N, M, MIN = 21e8;

int Map[55][55];
int vst[15];
int dist[110][14];
vector<int> path;
vector<pii> chickens;
vector<pii> houses;

void input() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> Map[i][j];
            if (Map[i][j] == 2)chickens.push_back({ i,j });
            if (Map[i][j] == 1)houses.push_back({ i,j });
        }
    }
}
// 거리를 다 구해놓고 dfs로 확인할 것 
int calDist(pii h, pii c) {
    return abs(h.Y - c.Y) + abs(h.X - c.X);
}

void dfs(int level, int startIdx) {
    if (level == M) {
        int sum = 0;
        for (int i = 0; i < houses.size(); i++) {
            int mn = 21e8;
            for (int j = 0; j < path.size(); j++) {
                int chIdx = path[j];
                mn = min(mn, dist[i][chIdx]);
            }
            sum += mn;
        }
        MIN = min(MIN, sum);
        return;
    }
    for (int i = startIdx; i < chickens.size(); i++) {
        if (vst[i] == 1)continue;
        vst[i] = 1;
        path.push_back(i);
        dfs(level + 1, i+1);
        vst[i] = 0;
        path.pop_back();
    }
}

int main() {
    input();
    for (int i = 0; i < houses.size(); i++) {
        auto house = houses[i];
        for (int j = 0; j < chickens.size(); j++) {
            auto chicken = chickens[j];
            dist[i][j] = calDist(house, chicken);
        }
    }
    dfs(0,0);
    cout << MIN;
    int de = 123;

    return 0;
}
