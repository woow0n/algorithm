#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

int T, N, M, MIN;
int mat[22][22];
int vst[22];
vector<int> teamA, teamB;

void input() {
    cin >> N;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            cin >> mat[y][x];
        }
    }
    M = N / 2;
    MIN = 21E8;
}

int calScore() {
    int scoreA = 0, scoreB = 0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            if (i == j) continue;
            scoreA += mat[teamA[i]][teamA[j]];
            scoreB += mat[teamB[i]][teamB[j]];
        }
    }
    return abs(scoreA - scoreB);
}

void dfs(int startIdx, int level) {
    if (level == M) {
        teamB.clear();
        for (int i = 0; i < N; i++) {
            if (vst[i] == 0) teamB.push_back(i);
        }
        int sc = calScore();
        if (MIN > sc) MIN = sc;
        return;
    }
    for (int i = startIdx; i < N; i++) {
        if (vst[i] == 1) continue;
        vst[i] = 1;
        teamA.push_back(i);
        dfs(i + 1, level + 1);
        vst[i] = 0;
        teamA.pop_back();
    }
}

int main()
{
    input();
    dfs(0, 0);
    cout << MIN;
    return 0;
}