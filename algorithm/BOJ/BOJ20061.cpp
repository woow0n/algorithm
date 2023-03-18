#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>
#include <cmath>
#include <deque>

#define R first
#define C second

using namespace std;
using pii = pair<int, int>;
using ll = long long;
struct blockInfo { int t, r, c; };
int n, ans;
int dr[] = { 0,-1,1,0,0 };
int dc[] = { 0,0,0,-1,1 };

deque<blockInfo> infos;
deque<int> blueBlockCoor[4] = { {-1}, {0,},{0,4},{0,2} };
deque<int> greenBlockCoor[4] = { {-1}, {0,},{0,2},{0,4} };
deque<deque<int>> blue;
deque<deque<int>> green;

void input() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int t, c, r; cin >> t >> r >> c;
        infos.push_back({ t,r,c });
    }
    for (int i = 0; i < 4; ++i) {
        deque<int> tmp;
        for (int j = 0; j < 10; ++j) {
            tmp.push_back(0);
        }
        blue.push_back(tmp);
        green.push_back(tmp);
    }
}

void gravity(deque<deque<int>>& board, int line, int stPos) {
    int flag;
    for (int i = stPos; i >= 0; --i) {
        if (board[line][i] == 0) {
            flag = 0;
            for (int t = i - 1; t >= 0; --t) {
                if (board[line][t] != 0) {
                    board[line][i] = board[line][t];
                    board[line][t] = 0; flag = 1; break;
                }
            }
            if (flag == 0) break;
        }
    }
}

// type = 0 / blue
void inpBlock(deque<deque<int>> & board, blockInfo block, int type) {
    deque<int> check;
    if (type == 0) {
        for (int i = 0; i < blueBlockCoor[block.t].size(); ++i) {
            int posR = block.r + dr[blueBlockCoor[block.t][i]];
            int posC = block.c + dc[blueBlockCoor[block.t][i]];
            blue[posR][posC] = 1;
            check.push_back(posR);
        }
    }
    if (type == 1) {
        for (int i = 0; i < greenBlockCoor[block.t].size(); ++i) {
            int posR = block.r + dc[greenBlockCoor[block.t][i]];
            int posC = block.c + dr[greenBlockCoor[block.t][i]];
            green[posC][posR] = 1;
            check.push_back(posC);
        }
    }
    int dropPos = 21e8;
    for (int i = 0; i < check.size(); ++i) {
        int tmpIdx = check[i];
        int zeroPos = -1;
        for (int j = 4; j <= 9; ++j) {
            if (board[tmpIdx][j] != 0) { zeroPos = j-1; break; }
            if (j == 9) zeroPos = 9;
        }
        dropPos = min(dropPos, zeroPos);
    }
    for (int i = 0; i < check.size(); ++i) {
        int tmpIdx = check[i];
        gravity(board, tmpIdx, dropPos);
    }
    // 점수얻는다 얻을 때 터진애들 만큼만 내려갑니다 근데 중력이 아니라 그냥 단순 이동이네요 
    deque<int> score;
    for (int i = 9; i >= 0; --i) {
        int cnt = 0;
        for (int j = 0; j < 4; ++j) {
            cnt += board[j][i];
        }
        if (cnt == 4) score.push_front(i);
    }
    ans += score.size();
    // 땡기기 
    for (int endP = 0; endP < score.size(); ++endP) {
        for (int row = 0; row < 4; ++row) {
            for (int pullIdx = score[endP]; pullIdx >=1; --pullIdx) {
                board[row][pullIdx] = board[row][pullIdx - 1];
            }
        }
    }
    // 0,1 에 뭔가 있으면 제끼기
    int pullrep = 0;
    for (int i = 5; i >= 4; --i) {
        for (int j = 0; j < 4; ++j) {
            if (board[j][i]) { pullrep++; break; }
        }
    }
    while(pullrep--){
        for (int j = 0; j < 4; ++j) {
            board[j].pop_back();
            board[j].push_front(0);
        }
    }
}


int main(){
    input();
    for (int i = 0; i < infos.size(); ++i) {
        inpBlock(blue, infos[i], 0);
        inpBlock(green, infos[i], 1);   
    }
    int cnt = 0;
    for (int i = 9; i >= 0; --i) {
        for (int j = 0; j < 4; ++j) {
            cnt += blue[j][i];
            cnt += green[j][i];
        }
    }
    cout << ans << "\n" << cnt;
    int de = 1;
    return 0;
}