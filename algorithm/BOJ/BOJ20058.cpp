#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

#define Y first
#define X second

using namespace std;
using pii = pair<int, int>;

int n, q;
int Map[129][129];
int vst[129][129];

int dy[] = { -1,1,0,0 };
int dx[] = { 0,0,-1,1 };
vector<int> qv;
int sz;
int rote[] = { 2,0,3,1 };
void input() {
    cin >> n >>q;
    sz = pow(2, n);
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            cin >> Map[i][j];
        }
    }
    for (int qq = 0; qq < q; qq++) {
        int a; cin >> a;
        qv.push_back(a);
    }
}

int checkIce(pii coor) {
    int cnt = 0;
    if (Map[coor.Y][coor.X] == 0) return 0;
    for (int i = 0; i < 4; i++) {
        int ny = coor.Y + dy[i];
        int nx = coor.X + dx[i];
        if (ny < 0 || nx < 0 || ny >= sz || nx >= sz) continue;
        if (Map[ny][nx] > 0) cnt++;
    }
    if (cnt < 3) return 1;
    return 0;
}

void rotate(int y, int x, int l) {
    int temp[65][65] = {0,};
    for (int i = 0; i < l; i++)
        for (int j = 0; j < l; j++) {
            temp[i][j] = Map[y + l - 1 - j][x + i];
        }

    for (int i = 0; i < l; i++)
        for (int j = 0; j < l; j++) {
            Map[y + i][x + j] = temp[i][j];
        }
}

void fireStorm(int L) {
    int flag = 1;
    if (L == 0 ) flag = 0;
    if (flag){
        int rotateSize = pow(2, L);
        for (int i = 0; i < sz; i += rotateSize) {
            for (int j = 0; j < sz; j += rotateSize) {
                rotate(i,j, rotateSize);
            }
        }
    }
    vector<pii> minusVect;
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            if (checkIce({ i,j })) minusVect.push_back({ i,j });
        }
    }

    for (int i = 0; i < minusVect.size(); i++) {
        auto now = minusVect[i];
        Map[now.Y][now.X]--;
    }
}

pii bfs(int y, int x) {
    queue<pii> q;
    q.push({ y,x });
    vst[y][x] = 1;
    int cnt = 1;
    int val = Map[y][x];
    while (!q.empty()) {
        auto now = q.front(); q.pop();
        for (int i = 0; i < 4; i++) {
            int ny = now.Y + dy[i];
            int nx = now.X + dx[i];
            if (ny < 0 || nx < 0 || ny >= sz || nx >= sz) continue;
            if (vst[ny][nx] == 1) continue;
            if (Map[ny][nx] < 1) continue;
            vst[ny][nx] = 1;
            q.push({ ny,nx });
            cnt++;
            val += Map[ny][nx];
        }
    }
    return {cnt, val};
}

int main() {
    input();

    for (int i = 0; i < qv.size(); i++) {
        fireStorm(qv[i]);
    }
    int ret = 0;
    int mx = 0;
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            if (Map[i][j] < 1) continue;
            if (vst[i][j] == 1) continue;
            pii res = bfs(i, j);
            ret += res.second;
            mx = max(mx, res.first);
        }
    }
    cout << ret << endl << mx;

    return 0;
}