#include<iostream>
#include<cstring>
#include<vector>
 
using namespace std;
 
int n, sum, cnt,nowDir, nowY, nowX, T;
int Map[105][105];
 
// 방향이야 그쪽으로 이동할거라는 뜻이지
int dy[] = { 0,0,0 ,1,-1 };
int dx[] = { 0,1,-1,0,0 };
// 시작지점을 저장할 벡터
vector<int> idxY;
vector<int> idxX;
 
struct wormhole {
    vector<int> y, x;
};
 
wormhole wormholes[11];
 
//  데이터 받기 초기화도 한번에 
void input() {
    cin >> n;
    // 초기화
    memset(Map, 0, sizeof(Map)); 
    memset(wormholes, 0, sizeof(wormholes));
    idxY.clear(); idxX.clear();
 
    // 데이터 받기
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            cin >> Map[y][x];
            if (Map[y][x] >= 6) {
                wormholes[Map[y][x]].y.push_back(y);
                wormholes[Map[y][x]].x.push_back(x);
            }
            if (Map[y][x] == 0) {
                idxY.push_back(y);
                idxX.push_back(x);
            }
        }
    }
}
 
 
// 블록을 마주했을 때 방향 바꾸기 동 1 서2 남3 북4
void block(int blockNum) {
    if (blockNum == 1) {
        if (nowDir == 1) {nowDir = 2; return;}
        if (nowDir == 2) {nowDir = 4; return;}
        if (nowDir == 3) {nowDir = 1; return;}
        if (nowDir == 4) {nowDir = 3; return;}
    }
    if (blockNum == 2) {
        if (nowDir == 1) {nowDir = 2; return;}
        if (nowDir == 2) {nowDir = 3; return;}
        if (nowDir == 3) {nowDir = 4; return;}
        if (nowDir == 4) {nowDir = 1; return;}
    }
    if (blockNum == 3) {
        if (nowDir == 1) {nowDir = 3; return;}
        if (nowDir == 2) {nowDir = 1; return;}
        if (nowDir == 3) {nowDir = 4; return;}
        if (nowDir == 4) {nowDir = 2; return;}
    }
    if (blockNum == 4) {
        if (nowDir == 1) {nowDir = 4; return;}
        if (nowDir == 2) {nowDir = 1; return;}
        if (nowDir == 3) {nowDir = 2; return;}
        if (nowDir == 4) {nowDir = 3; return;}
    }
    if (blockNum == 5) { //이거는 벽이랑 같은 로직이니깐 다음에도 쓰자
        if (nowDir == 1) {nowDir = 2; return;}
        if (nowDir == 2) {nowDir = 1; return;}
        if (nowDir == 3) {nowDir = 4; return;}
        if (nowDir == 4) {nowDir = 3; return;}
    }
}
 
// 웜홀 부분코드 웜홀은 방향그대로 가져가는데 위치만 그대로 바뀌는 거임;
void inWormHole(int num) {
    wormhole wh = wormholes[num];
    if (wh.y[0] == nowY && wh.x[0] == nowX) { nowY = wh.y[1];  nowX = wh.x[1]; }
    else { nowY = wh.y[0];  nowX = wh.x[0]; }
}
 
 
// 각 시작 좌표에서 이동했을 때 카운트
int move(int startY,int startX, int startDir) {
    int cnt=0;
    nowY = startY; nowX = startX; nowDir = startDir;
    while (1) {
        int ny = nowY + dy[nowDir];
        int nx = nowX + dx[nowDir];
 
        // 범위를 벗어날 떄 = 벽에 튕길때 : 여기는 이동안하고 방향반대로전환
        if (ny < 0 || nx < 0 || ny >= n || nx >= n) {
            nowY = ny; nowX = nx;
            block(5); cnt++;
            continue;
        }
        // 블록에 부딪혔을 때 : 이동하고 방향전환
        if (1 <=Map[ny][nx] && Map[ny][nx]<=5) {
            nowY = ny; nowX = nx;
            block(Map[ny][nx]); cnt++;
        }
        // 웜홀로 갔을때 : 방향그대로 + 좌표만 이동
        if (Map[ny][nx] >= 6) {
            nowY = ny; nowX = nx;
            inWormHole(Map[ny][nx]);
        }
        // 아무것도 없는데일 떄 그냥 이동
        if (Map[ny][nx] == 0) {
            nowY = ny; nowX = nx;
        }
        // 블랙홀이나 스타트지점으로 다시 돌아올경우 멈춘다
        if (Map[ny][nx] == -1 || (ny == startY && nx == startX)) break;
    }
    return cnt;
}
 
int main()
{
    cin >> T;
    for (int t = 0; t < T; t++) {
        input();
        int max = 0;
        for (int i = 0; i < idxX.size(); i++) {
            for (int dir = 1; dir <= 4; dir++) {
                int tmp = move(idxY[i], idxX[i], dir);
                if (max < tmp) max = tmp;
            }
        }
        cout << "#" << t + 1 << " " << max << endl;
    }
 
    return 0;
}