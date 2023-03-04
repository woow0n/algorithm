#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
 
 
using namespace std;
using ll = long long;
 
int T, N, M, K;
int Map[900][900];
int dy[] = { -1,1,0,0 };
int dx[] = { 0,0,-1,1 };
struct cell
{
    int y, x, power, status, bornTime; //  비활성 = 0 / 활성 = 1 / 죽음 =2;
};
struct cmp {
    bool operator()(cell a, cell b) {
        if (a.power < b.power) return true;
        return false;
    }
};
vector<cell> cellsV;
// 생명력 쎈애가 먼저 자리차지하고 다음애들은 넘겨야니깐
priority_queue<cell, vector<cell>, cmp> cellsQ;
 
void input() {
    cellsV.clear();
    while (!cellsQ.empty()) {cellsQ.pop();}
    memset(Map, 0, sizeof(Map));
    cin >> N >> M >> K;
    for (int y = 350; y < 350+N; y++) {
        for (int x = 350; x < 350+M; x++) {
            cin >> Map[y][x];
            if (Map[y][x] > 0) cellsV.push_back({y,x,Map[y][x],0,0});
        }
    }
}
 
void timeRuner(int time) {
    for (int i = 0; i < cellsV.size(); i++) {
        auto nowCell = cellsV[i];
        // 죽었으면 넘어가
        if (nowCell.status >=2) continue;
        else {
            if (nowCell.bornTime + nowCell.power == time) nowCell.status = 1;
            if (nowCell.bornTime + nowCell.power*2 == time) nowCell.status = 2;      
        }
        cellsV[i] = nowCell;
        if (nowCell.status == 1)cellsQ.push(nowCell);
    }
}
 
void bfs() {
    for (int time=1; time<=K-1; time++){
        timeRuner(time);
        int sz = cellsQ.size();
        for (int s = 0; s < sz; s++) {
            auto now = cellsQ.top(); cellsQ.pop();
            // 아직 활성화 안된놈은 다시 줄서게
            for (int i = 0; i < 4; i++) {
                int ny = now.y + dy[i];
                int nx = now.x + dx[i];
                if (Map[ny][nx] != 0) continue;
                Map[ny][nx] = now.power;
                // 비활성 상태로 태어남
                cell nextCell = { ny,nx, now.power, 0, time+1};
                cellsV.push_back(nextCell);
            }
        }
    }
    timeRuner(K);
 
}
 
int main()
{
    cin >> T;
    for (int t = 0; t < T; t++) {
        int ret = 0;
        input();
        bfs();
        for (int i = 0; i < cellsV.size(); i++) {
            auto nowCell = cellsV[i];
            if (nowCell.status < 2) ret ++;           
        }
        cout << "#" << t + 1 << " " << ret << endl;
    }
    return 0;
}