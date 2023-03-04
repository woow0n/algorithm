#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
#include<functional>
 
using namespace std;
 
int k, n, Max, T, y,x, flagK, maxLen;
int dy[5] = { 0,-1,1,0,0 };
int dx[5] = { 0,0,0,-1,1 };
int Map[9][9], vst[9][9];
 
vector<int> path;
vector<int> maxY;
vector<int> maxX;
 
 
 
void input() {
    Max = -21E8;  maxLen = -21E8; maxY.clear(); maxX.clear();
    cin >> n >> k;
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            cin >> Map[y][x];
            if (Map[y][x] > Max) Max = Map[y][x];
        }
    }
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            if (Map[y][x] == Max) { maxY.push_back(y); maxX.push_back(x);}
        }
    }
}
 
void init() {
    flagK = 1;
    memset(vst, 0, sizeof(vst));
}
 
void dfs(int y, int x) {
    if (vst[y][x] > maxLen) maxLen = vst[y][x];
    for (int i = 1; i < 5; i++) {
        int ny = y + dy[i];
        int nx = x + dx[i];
 
        if (vst[ny][nx] != 0) continue;
        if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
 
        // 다음거가 크고 (못가고) 플래그가 0이면 그냥 넘어간다
        if (Map[ny][nx] >= Map[y][x] && !flagK) continue;
        // 다음거가 크고 (못가고) 플래그가 1이면 공사 할까 말까
        if (Map[ny][nx] >= Map[y][x] && flagK) {
            //공사 하는데 어느정도할까
            for (int sizeofK = 1; sizeofK <= k; sizeofK++) {
                Map[ny][nx] -= sizeofK;
                if (Map[ny][nx] >= Map[y][x]) { Map[ny][nx] += sizeofK; continue; }
                vst[ny][nx] = vst[y][x] + 1;
                flagK = 0;
                dfs(ny, nx);
                Map[ny][nx] += sizeofK;
                flagK = 1;
                vst[ny][nx] = 0;
            }
            // 공사안해
            if (Map[ny][nx] >= Map[y][x]) continue;
            vst[ny][nx] = vst[y][x] + 1;
            dfs(ny, nx);
            vst[ny][nx] = 0;
        }
        if (Map[ny][nx] >= Map[y][x]) continue;
        // 여기는 공사 못한다
        vst[ny][nx] = vst[y][x] + 1;
        dfs(ny, nx);
        vst[ny][nx] = 0;
    }
}
 
int main()
{
    cin >> T;
    for (int t = 0; t < T; t++) {
        input();
        for (int i = 0; i<maxY.size(); i++) {
            init();
            vst[maxY[i]][maxX[i]] = 1;
            dfs(maxY[i], maxX[i]);
        }
        cout << "#" << t + 1 << " " << maxLen << endl;
    }
    return 0; 
}