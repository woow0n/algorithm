#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
#include<functional>
 
using namespace std;
using pii = pair<int, int>;
 
int N, tryNum, T, cnt, retLine=0, maxCnt, stCnt;
int dy[5] = { 0,-1,1,0,0 };
int dx[5] = { 0,0,0,-1,1 };
int Map[13][13];
vector<pii> coor;
vector<int> path;
 
void input() {
    path.clear(); coor.clear();
    cnt = 0;
    cin >> N;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            cin >> Map[y][x];
            if ((x == N - 1 || y == N - 1 || y == 0 || x == 0) && Map[y][x] == 1) cnt++;
            if (!(x == N - 1 || y == N - 1 || y == 0 || x == 0) && Map[y][x] == 1) {
                coor.push_back({ y,x });
            }
        }
    }
    tryNum = coor.size();
    maxCnt = cnt;
    stCnt = cnt;
}
 
int countLine() {
    int c=0;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            if (Map[y][x] == 2) c++;
        }
    }
    return c;
}
 
void dfs(int level) {
    if (level == tryNum) { 
        int lineCnt = countLine();
        if (maxCnt < cnt) { maxCnt = cnt; retLine = lineCnt; }
        if (maxCnt <= cnt && retLine > lineCnt) { retLine = lineCnt; }
        return; }
    // 남은거 
    if (tryNum - level + cnt < maxCnt) return;
 
    for (int dir = 0; dir <= 4; dir++) {
        queue<pii> lastCoor;
        int ny = coor[level].first + dy[dir]; int nx = coor[level].second + dx[dir];
        int flag = 0; int cntFlag = 0;
         
        while (dir) {
            if (Map[ny][nx] != 0) { flag = 1; break; }
            Map[ny][nx] = 2;
            lastCoor.push({ ny ,nx });
            if (nx == N - 1 || ny == N - 1 || ny == 0 || nx == 0) { cntFlag = 1; cnt++; break; }
            ny += dy[dir];  nx += dx[dir];
 
        }
        while (!lastCoor.empty() && flag && dir) {
            auto now = lastCoor.front(); lastCoor.pop();
            if (Map[now.first][now.second] == 1) continue;
            Map[now.first][now.second] = 0;
        }
        if (flag) continue;
        path.push_back(dir);
        dfs(level + 1);
        path.pop_back();
        while (!lastCoor.empty()) {
            auto now = lastCoor.front(); lastCoor.pop();
            if (Map[now.first][now.second] == 1) continue;
            Map[now.first][now.second] = 0;
        }
        if (cntFlag)cnt--;
    }
}
 
 
int main()
{
    cin >> T;
    for (int t = 0; t < T; t++) {
        input();
        dfs(0);
        cout << "#" << t + 1 << " " << retLine<< endl;
    }
    return 0;
}