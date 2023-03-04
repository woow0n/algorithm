#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
#include<vector>
 
using namespace std;
 
int T, n, m, c;
int Map[11][11], squereMap[11][11], vst[11][11];
int scores[11][11];
int vstHoney[6];
int honeySum, honeySquereSum, maxHoney;
int sum, Max;
 
struct honey {
    int y, x, score;
};
struct coor {
    int y, x;
};
vector<coor> tmpHoney;
 
void input() {
    sum = 0, Max = 0;
    cin >> n >> m >> c;
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            cin >> Map[y][x];
            squereMap[y][x] = Map[y][x] * Map[y][x];
        }
    }
}
// 어차피 최댓값 구하는 문제야 이말인 즉슨 모든 경우의 수를 구해봐야된다는 뜻
// 윈도우 사이즈만큼 모두 계산을 해두고 정렬해서 M만큼 앞에꺼를 고른다? 겹치는 녀석은 VST처리해서 안고르면 되지롱 {Y,X,MAXSCORE}로 형성해서
// MAXSCORE로 정렬후에 앞에서 M개 선택 하지만 Y,X가 범위안이라면 선택안되게 하자규
 
 
vector<int> path;
vector<int> pathS;
 
void calHoney(int level) {
    if (honeySum > c) {
        int tmpSum = 0;
        for (int p = 0; p<path.size() - 1; p++) tmpSum += pathS[p];
        if (tmpSum > maxHoney) maxHoney = tmpSum;
        return; }
    if (level == m) {
        int tmpSum = 0;
        for (int p = 0; p < path.size(); p++) tmpSum += pathS[p];
        if (tmpSum > maxHoney) maxHoney = tmpSum;
        return;
    }
    for (int i = 0; i < m; i++) {
        if (vstHoney[i] == 1)continue;
        vstHoney[i] = 1;
        int honey = Map[tmpHoney[i].y][tmpHoney[i].x];
        int squereHoney = squereMap[tmpHoney[i].y][tmpHoney[i].x];
        honeySum += honey;
        pathS.push_back(squereHoney);
        path.push_back(honey);
 
        calHoney(level+1);
        vstHoney[i] = 0;
        path.pop_back();
        pathS.pop_back();
        honeySum -= honey;
    }
}
 
void calScores() {
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n - m + 1; col++) {
            tmpHoney.clear();
            memset(vstHoney, 0, sizeof(vstHoney));  honeySum = 0; honeySquereSum = 0; maxHoney = 0;
            for (int wd = 0; wd < m; wd++) {
                tmpHoney.push_back({ row, col + wd });
            }
            calHoney(0);
            scores[row][col] = maxHoney ;
        }
    }
}
 
// 계산한 score를 기반으로 누구누구를 선택할 것인가 m개 선택이;ㅁ Y,X가 범위안이라면 선택안되게 하자규
void maxScoreComb(int level) {
    if (level == 2) {
        if (sum > Max) Max = sum;
        return;
    }
 
    for (int i = 0; i < (n - m + 1) * n; i++) {
        int y = i / (n - m + 1); int x = i % (n - m + 1);
        if (vst[y][x] == 1) continue;
        // 방문처리
        int skipFlag = 0;
        for (int wd = 0; wd < m; wd++) {
            if (vst[y][x + wd] == 1) { skipFlag = 1; break; }
        }
        if (skipFlag) continue;
        for (int wd = 0; wd < m; wd++) {
            vst[y][x + wd] = 1;
        }
        sum += scores[y][x];
        // 다음꺼 고르기 
        maxScoreComb(level + 1);
        sum -= scores[y][x];
        for (int wd = 0; wd < m; wd++) {
            vst[y][x + wd] = 0;
        }
    }
}
 
 
 
 
int main()
{
    cin >> T;
    for (int t = 0; t < T; t++) {
        input();
        calScores();
        maxScoreComb(0);
        cout << "#" << t + 1 << " " << Max << endl;
    }
 
    return 0;
}