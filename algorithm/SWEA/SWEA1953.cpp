#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
 
using namespace std;
 
int N,M,T,R,C,L;
// 상 하 좌 우
int dy[5] = { 0,-1,1,0,0 };
int dx[5] = { 0,0,0,-1,1 };
int Map[51][51], vst[51][51];
 
int canGo[8][5] = {
    {0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1},
    {0, 1, 1, 0, 0},
    {0, 0, 0, 1, 1},
    {0, 1, 0, 0, 1},
    {0, 0, 1, 0, 1},
    {0, 0, 1, 1, 0},
    {0, 1, 0, 1, 0} 
};
int reflect[5] = { 0,2,1,4,3 };
 
struct coor {
    int y, x;
};
 
void input() {
    cin >> N >> M >> R >> C >> L;
    memset(vst, 0, sizeof(vst));
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
            cin >> Map[y][x];
        }
    }
}
 
int bfs() {
    queue<coor> q; 
    q.push({ R,C });
    vst[R][C] = 1;
    int cnt = 1;
    L--;
    while (L--) {
        int sz = q.size();
        for (int i = 0; i < sz; i++) {
            coor now = q.front(); q.pop();
            for (int j = 1; j <= 4; j++) {
                int ny = now.y + dy[j]; int nx = now.x + dx[j];
 
                // 범위 밖이면 빠이
                if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue;
                // 내가 현재위치가 다음으로 안이어지면 빠이
                if (!canGo[Map[now.y][now.x]][j]) continue;
                // 내가 가려고하는 위치가 현재위치로 안이어지면 빠이
                if (!canGo[Map[ny][nx]][reflect[j]]) continue;
                // 갔던곳이면 빠이
                if (vst[ny][nx] == 1) continue;
 
                q.push({ ny,nx });
                vst[ny][nx] = 1;
                cnt++;
            }
        }
    }
    return cnt;
}
 
 
int main()
{
    cin >> T;
    for (int t = 0; t < T; t++) {
        input();
        cout << "#" << t + 1 << " " << bfs() << endl;
        int de = 0;
    }
    return 0; 
}