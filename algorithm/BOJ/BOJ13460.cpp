#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>
#include <cmath>
#include <set>

#define R first
#define C second

using namespace std;
using pii = pair<int, int>;

int n, m, mn = 21e8;
string Map[12];
int dr[] = { -1,1,0,0 };
int dc[] = { 0,0, -1,1 };
vector<int> path;
vector<int> minpath;

int reverseDir[] = { 1,0,3,2 };
pii red, blue, hole;

void input() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> Map[i];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (Map[i][j] == 'R') red = { i,j };
            if (Map[i][j] == 'B') blue = { i,j };
            if (Map[i][j] == 'O') hole = { i,j };
        }
    }
}

int rollMarvel(int dir, pii& color, char mark) {
    int cnt = 0; int flag = 1;
    while (flag) {
        int nr = color.R + dr[dir];
        int nc = color.C + dc[dir];
        if (nr<1 || nc<1 || nc>m || nr>n) break;
        if (Map[nr][nc] == 'O') { flag = 0; }
        if (flag && Map[nr][nc] != '.') { break; }
        cnt++;
        Map[color.R][color.C] = '.';
        Map[nr][nc] = mark;
        if (!flag)Map[nr][nc] = 'O';
        color.R = nr;
        color.C = nc;
    }
    if (!cnt) return 0;
    return 1;
}
// 1 -> red 먼저 0->blue 먼저
int whoisFirst(int dir) {
    if (dir == 0) return red.R <= blue.R;
    if (dir == 1) return red.R >= blue.R;
    if (dir == 2) return red.C <= blue.C;
    if (dir == 3) return red.C >= blue.C;
}

void dfs(int level) {

    if (level > 10) return;
    int redFlag = red.R == hole.R && red.C == hole.C;
    if (redFlag ) {
        mn = min(mn, level);
        minpath = path;
        return;
    }
    if (level > mn) return;

    for (int i = 0; i < 4; ++i) {
        pii beforeRed = red; pii beforeBlue = blue; 
        int flagR , flagB;

        // 마지막에 했던 명령 한번더 하지않기
        path.push_back(i);
        // 오른쪽이면 오른쪽에 있는애 먼저 왼쪽이면 왼쪽있는애 먼저
        if (whoisFirst(i)) {
            flagR = rollMarvel(i, red, 'R');
            flagB = rollMarvel(i, blue, 'B');
        }
        else {
            flagB = rollMarvel(i, blue, 'B');
            flagR = rollMarvel(i, red, 'R');
        }
        int blueFlag = blue.R == hole.R && blue.C == hole.C;
        // 만약 두 구슬의 위치가 변함이 없거나 파란공이 들어감 -> 복원해주고 취소
        if (!flagR&&!flagB || blueFlag) {
            path.pop_back(); 
            Map[red.R][red.C] = '.'; Map[blue.R][blue.C] = '.';
            red = beforeRed; blue = beforeBlue;
            Map[blue.R][blue.C] = 'B'; Map[red.R][red.C] = 'R'; Map[hole.R][hole.C] = 'O';
            continue; 
        }
        dfs(level + 1);

        // 복원
        path.pop_back();
        Map[red.R][red.C] = '.'; Map[blue.R][blue.C] = '.'; Map[hole.R][hole.C] = 'O';
        red = beforeRed; blue = beforeBlue;
        Map[blue.R][blue.C] = 'B'; Map[red.R][red.C] = 'R';
    }
}


int main()
{
    input();
    dfs(0);
    if (mn == 21e8) cout << -1;
    else cout << mn;
    return 0;
}