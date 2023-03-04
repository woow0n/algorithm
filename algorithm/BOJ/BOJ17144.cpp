#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <cstring>

#define Y first
#define X second
using namespace std;
using pic = pair<int, char>;
using pii = pair<int, int>;
using ll = long long;
using piiWithVal = pair<pii,int>;

int N, M, T;
int Map[55][55];
int vst[55][55];
int beforeVst[55][55];

int dy[] = { -1,1,0,0 };
int dx[] = { 0,0,-1,1 };
vector<pii> dusts;
pii airCleaner[2];

void input() {
    cin >> N >> M >> T;
    int a = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> Map[i][j];
            if (Map[i][j] > 0) dusts.push_back({ i,j });
            if (Map[i][j] == -1) airCleaner[a++] = { i,j };
        }
    }
}
// 1.
//(r, c)에 있는 미세먼지는 인접한 네 방향으로 확산된다.
//인접한 방향에 공기청정기가 있거나, 칸이 없으면 그 방향으로는 확산이 일어나지 않는다.
//확산되는 양은 Ar, c / 5이고 소수점은 버린다.
//(r, c)에 남은 미세먼지의 양은 Ar, c - (Ar, c / 5)×(확산된 방향의 개수) 이다.
// 2. 
//공기청정기에서는 바람이 나온다.
//위쪽 공기청정기의 바람은 반시계방향으로 순환하고, 아래쪽 공기청정기의 바람은 시계방향으로 순환한다.
//바람이 불면 미세먼지가 바람의 방향대로 모두 한 칸씩 이동한다.
//공기청정기에서 부는 바람은 미세먼지가 없는 바람이고, 공기청정기로 들어간 미세먼지는 모두 정화된다.

void spread() {
    int sz = dusts.size();
    vector<piiWithVal> spreadVector;
    for (int i = 0; i < sz; i++) {
        pii now = dusts[i]; int cnt=1;

        int val = Map[now.Y][now.X] / 5;
        if (val == 0) continue;
        for (int d = 0; d < 4; d++) {
            int ny = now.Y + dy[d]; int nx = now.X + dx[d];
            if (ny < 0 || nx < 0 || nx >= M || ny >= N)continue;
            if (Map[ny][nx] == -1) continue;
            cnt++;
            spreadVector.push_back({{ ny,nx }, val});
        }
        Map[now.Y][now.X] -= val * (cnt - 1);
    }
    for (int i = 0; i < spreadVector.size(); i++) {
        auto now = spreadVector[i];
        Map[now.first.Y][now.first.X] += now.second;
    }
}

void doAirCleanersJob(int num) {
    int airCleanersDir[2][4] = {{3,0,2,1}, {3,1,2,0}};
    pii now = { airCleaner[num].Y, airCleaner[num].X + 1 };
    int cnt = 1; int lastVal = 0;
    for (int dir = 0; dir < 4; dir++) {
        int readDir = airCleanersDir[num][dir]; int flag = 1;
        if (cnt == 1) lastVal = 0; 
        if (dir > 0) cnt = 0;
        while (flag) {
            int ny = now.Y + dy[readDir]; int nx = now.X + dx[readDir];
            if (ny < 0 || nx < 0 || nx >= M || ny >= N) flag = 0;
            if (Map[ny][nx] == -1) { flag = 0; }
            int tmp = Map[now.Y][now.X] ;
            if (cnt) { Map[now.Y][now.X] = lastVal; lastVal = tmp; }
            if (!flag) break;
            now = { ny,nx }; cnt++;
        }
    }
}

int main() {
    input();
    while (T--) {
        spread();
        doAirCleanersJob(0);
        doAirCleanersJob(1);
        dusts.clear();
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (Map[i][j] > 0) dusts.push_back({ i,j });
            }
        }
    }
    int ret = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            ret += Map[i][j];
        }
    }
    cout << ret + 2;
    //int de = 123;
}
