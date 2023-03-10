#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <deque>
#include <queue>

#define R first
#define C second

using namespace std;
using pii = pair<int, int>;
int n, m, t, ret;
deque<int> circle[55];
int rotate[55];
int vst[55][55];

struct cmd { int x, d, k; };
vector<cmd> cmds;
int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };

// 번호가 xi의 배수인 원판을 di방향으로 ki칸 회전시킨다. di가 0인 경우는 시계 방향, 1인 경우는 반시계 방향이다.
// 원판에 수가 남아 있으면, 인접하면서 수가 같은 것을 모두 찾는다.
// 그러한 수가 있는 경우에는 원판에서 인접하면서 같은 수를 모두 지운다.
// 없는 경우에는 원판에 적힌 수의 평균을 구하고, 평균보다 큰 수에서 1을 빼고, 작은 수에는 1을 더한다.

void input() {
    cin >> n >> m>>t;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int a; cin >> a;
            circle[i].push_back(a);
        }
    }
    for (int j = 0; j < t; ++j) {
        int x, d, k ;
        cin >> x >> d >> k;
        cmds.push_back({ x,d,k });
    }
}
// 방향벡터로 보면될듯?  별로 안크니깐 인덱스 말고 그냥 벡터로 봐도될거같아 원판은 다 1이상이니깐 그냥 x는 0으로 푷ㄴ하ㅏ자
void roll(cmd cmd) {
    // d =0 시계방형 d=1 반시계
    for (int i = cmd.x-1; i < n; i += cmd.x) {
        if (!cmd.d) {
            for (int j = 0; j < cmd.k; ++j) {
                int tmp = circle[i].back(); circle[i].pop_back();
                circle[i].push_front(tmp);
            }
        }
        else {
            for (int j = 0; j < cmd.k; ++j) {
                int tmp = circle[i].front(); circle[i].pop_front();
                circle[i].push_back(tmp);
            }
        }
    }
}

int pop(int r, int c) {
    if (circle[r][c] == 0) {return 0;}
    queue<pii> q;
    int val = circle[r][c];
    q.push({ r,c });
    vst[r][c] = 1;
    int cnt = 0;
    while (!q.empty()){
        pii now = q.front(); q.pop();
        for (int i = 0; i < 4; ++i) {
            int nr = now.R + dr[i];
            int nc = (now.C + dc[i] + 50 * m) % m;
            if (nr < 0 || nr >= n) continue;
            if (circle[nr][nc] != val) continue;
            if (vst[nr][nc] == 1) continue;
            vst[nr][nc] = 1;
            circle[nr][nc] = 0;
            q.push({ nr,nc });
            cnt++;
        }
    }
    if (cnt > 0)  circle[r][c] = 0;
    return cnt;
}


int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    input();
    int ret = 0;
    for (int i = 0; i < (int)cmds.size(); ++i) {
        memset(vst, 0, sizeof(vst));
        roll(cmds[i]); int avgFlag = 0;
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                avgFlag += pop(r, c);
            }
        }
        if (!avgFlag) {
            int sum = 0; int len = 0;
            for (int r = 0; r < n; ++r) {
                for (int c = 0; c < m; ++c) {
                    if (circle[r][c] > 0) {
                        sum += circle[r][c]; len++;
                    }
                }
            }
            float avg = (float)sum / (float)len;
            for (int r = 0; r < n; ++r) {
                for (int c = 0; c < m; ++c) {
                    if (circle[r][c] == 0) continue;
                    if (circle[r][c] > avg) { circle[r][c] --; continue;}
                    if (circle[r][c] < avg) { circle[r][c] ++; continue;}
                }
            }
        }
    }
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            ret += circle[r][c];
        }
    }

    cout << ret;
    return 0;
}
