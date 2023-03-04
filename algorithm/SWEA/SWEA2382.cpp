#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
 
vector<int> MAP[105][105];
int T, n, m, k;
 
struct worm {
    int name, y, x, cnt, dir;
};
worm worms[1010];
// 상 1 하 2 좌 3 우4
int dy[] = { 0,-1,1,0,0 };
int dx[] = { 0,0,0,-1,1 };
vector<int> vec;
 
 
// 인풋
void input() {
    memset(worms, 0, sizeof(worms));
    for (int y = 0; y < 105; y++) {
        for (int x = 0; x < 105; x++) {
            MAP[y][x].clear();
        }
    }
    cin >> n >> m >> k;
    int y, x, cnt, dir;
 
    for (int i = 1; i <= k; i++) {
        cin >> y >> x >> cnt >> dir;
        MAP[y][x].push_back(i);
        worms[i] = { i,y,x,cnt,dir };
    }
}
 
// 약품을 만나면 방향 빠꾸
int meetMed(int inpDir) {
    if (inpDir == 1) return 2;
    if (inpDir == 2) return 1;
    if (inpDir == 3) return 4;
    if (inpDir == 4) return 3;
}
int ny, nx;
void killworm() {
    for (int time = 1; time <= m; time++) {
        for (int w = 1; w <= k; w++) {
 
            worm nowWorm = worms[w];
            // 벌레가 죽었으면 넘어간다.
            if (nowWorm.name == 0 && nowWorm.y == 0 && nowWorm.x == 0 && nowWorm.cnt == 0 && nowWorm.dir == 0) continue;
 
            // 기존좌표를 초기화먼저하고 다음 놈을 확인하자
            MAP[nowWorm.y][nowWorm.x].erase(MAP[nowWorm.y][nowWorm.x].begin());
 
            // 상 1 하 2 좌 3 우4
            ny = nowWorm.y + dy[nowWorm.dir];
            nx = nowWorm.x + dx[nowWorm.dir];
 
            // 약품으로가면
            if (ny == n - 1 || nx == n - 1 || nx == 0 || ny == 0) {
                nowWorm.cnt = nowWorm.cnt / 2;
                nowWorm.dir = meetMed(nowWorm.dir);
                if (nowWorm.cnt == 0) { worms[w] = { 0,0,0,0,0 }; continue; }
            }
 
            MAP[ny][nx].push_back(w);
 
            // worms배열에다가 다시 새로운 벌레의 위치를 잡아주기위해서 nowworm 좌표 조정
            nowWorm.y = ny; nowWorm.x = nx;
 
            // MAP에 업데이트 / 배열 수정 name = 인덱스
            worms[w] = nowWorm;
        }
        // 벌레들의 좌표들 다시 channel0으로 병합하기 
        for (int w = 1; w <= k; w++) {
            worm nowWorm = worms[w];
            // 벌레가 죽은놈이면은 넘어가
            if (nowWorm.name == 0 && nowWorm.y == 0 && nowWorm.x == 0 && nowWorm.cnt == 0 && nowWorm.dir == 0) continue;
 
            // 벌레들 서로 잡아먹기위해서 확인할 놈들
            int maxName = 0;
            int maxDir = 0;
            int maxCnt = 0;
            int totalCnt = 0;
 
            // 채널들을 다 살펴본다
            for (int c = 0; c < MAP[nowWorm.y][nowWorm.x].size(); c++) {
                worm tmpWorm = worms[MAP[nowWorm.y][nowWorm.x][c]];
                if (tmpWorm.cnt > maxCnt) {
                    maxName = tmpWorm.name;
                    maxDir = tmpWorm.dir;
                    maxCnt = tmpWorm.cnt;
                }
                totalCnt += tmpWorm.cnt;
 
                // 같은 채널이었던 놈들 모두 죽이기 -> 제일 쏀놈은 다시 살릴거임 / 좌표도 0으로
                worms[tmpWorm.name] = { 0,0,0,0,0 };
            }
            MAP[nowWorm.y][nowWorm.x].clear();
            worms[maxName] = { maxName, nowWorm.y, nowWorm.x, totalCnt, maxDir };
            MAP[nowWorm.y][nowWorm.x].push_back(maxName);
        }
    }
}
 
int main()
{
    cin >> T;
    for (int t = 0; t < T; t++) {
        input();
        killworm();
        int ret = 0;
        for (int i = 1; i <= k; i++) {
            ret += worms[i].cnt;
        }
        cout << "#" << t + 1 << " " << ret << endl;
    }
    return 0;
}