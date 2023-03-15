#include <iostream>
#include <algorithm>
#include <cstring>
#include <deque>
#define R first
#define C second
using namespace std;
using pii = pair<int, int>;
using ll = long long;

int n, k;
int Map[15][15];
deque<int> board[15][15];
int dir[15];
pii pos[15];
int dr[] = { 0,0,0,-1,1 };
int dc[] = { 0,1,-1,0,0, };
int reverseDir[] = { 0,2,1,4,3 };

void input() {
    cin >> n >> k;
    for (int r = 1; r <= n; ++r) {
        for (int c = 1; c <= n; ++c) {
            cin >> Map[r][c];
        }
    }
    for (int i = 1; i <= k; ++i) {
        int r, c, d; cin >> r >> c >> d;
        board[r][c].push_back(i);
        dir[i] = d; pos[i] = { r,c };
    }
}

int move(int num) {
    int stR = pos[num].R;  int stC = pos[num].C;
    int nr = pos[num].R + dr[dir[num]];
    int nc = pos[num].C + dc[dir[num]];
    if (nr<1 || nc<1 || nr>n || nc>n || Map[nr][nc] == 2) {
        dir[num] = reverseDir[dir[num]];
        nr = pos[num].R + dr[dir[num]];
        nc = pos[num].C + dc[dir[num]];
        if (nr<1 || nc<1 || nr>n || nc>n || Map[nr][nc] == 2) return 0;
    }
    if (Map[nr][nc] == 0) {
        int flag = 0; int cnt = 0;
        for (int i = 0; i < board[stR][stC].size(); ++i) {
            int now = board[stR][stC][i];
            if (now == num) flag = 1;
            if (flag) {
                board[nr][nc].push_back(now);
                pos[now] = { nr,nc };
                cnt++;
            }
        }
        while (cnt--) board[stR][stC].pop_back();
    }
    else if (Map[nr][nc] == 1) {
        int flag = 0; int cnt = 0; int sz = board[stR][stC].size();
        for (int i = sz - 1; i >= 0; --i) {
            if (flag) break;
            int now = board[stR][stC][i];
            board[nr][nc].push_back(now);
            board[stR][stC].pop_back();
            pos[now] = { nr,nc };
            if (now == num) flag = 1;
        }
    }

    if (board[nr][nc].size() >= 4) return 1;
    else return 0;
}

int main() {
    input();
    int flag = 0;
    int cnt = 0;
    while (cnt <= 1000) {
        cnt++;
        for (int i = 1; i <= k; ++i) {
            flag = move(i);
            if (flag) break;
        }
        if (flag) break;
    }
    if (flag) cout << cnt;
    else cout << -1;

    int de = 2;
    return 0;
}