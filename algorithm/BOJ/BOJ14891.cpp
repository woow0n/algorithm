#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

string magnetics[5];
// 자석의 빨간쪽 인덱스 번호
int magIdx[5];
int T, K, tmpPole, tmpNum, tmpDir;
int scores[5] = { 0,1,2,4,8 };
int cnt[5];

struct rotation
{// 자석번호 || 방향 -1 :반시계 , 1:시계방향/
    int magNum, direction;
};
vector<rotation> rotateVec;
//인접한놈 확인하는 벡터 //나보다 작으면 작은놈의 우측, 크면 큰놈의 우측 봐야함
vector<int> adjMag[5] = { {},{2},{1,3},{2,4},{3} };

// 모든 회전이 끝나면 점수 산출
// 두번째 (0으로 시작)하는 놈의 값이 S면 1/2/4/8 점
// 그냥 벡터로구성하고 인덱스로 할까? 그러자
// 인풋이다름 확인할것
void input() {
    memset(magIdx, 0, sizeof(magIdx));
    for (int m = 1; m <= 4; m++) {
        cin >> magnetics[m];
    }
    cin >> K; // 회전수

    rotateVec.clear();
    for (int i = 0; i < K; i++) {
        cin >> tmpNum >> tmpDir;
        rotateVec.push_back({ tmpNum, tmpDir });
    }
}
// magnetics[i][rotateIdx(0, 2,  1)] i번째의 우측놈
// magnetics[i][rotateIdx(0, 2, -1)] i번째의 좌측놈
int rotateIdx(int inpIdx, int size, int dir) {
    return (inpIdx + (size * dir) + 800) % 8;
}


void rotateOneMag(int magNum, int dir) {
    // 좌우 체크하고 돌려
    if (cnt[magNum] == 1) return;

    int rIdx = rotateIdx(magIdx[magNum], 2, 1);
    int lIdx = rotateIdx(magIdx[magNum], 2, -1);
    int tmpIdx = rotateIdx(magIdx[magNum], 1, -1 * dir);
    magIdx[magNum] = tmpIdx;
    cnt[magNum] = 1;

    for (int i = 0; i < adjMag[magNum].size(); i++) {
        // 만약 왼쪽꺼면
        int targetMag = adjMag[magNum][i];
        if (targetMag < magNum) {
            // 타겟이랑 맞는지 확인
            int targetRIdx = rotateIdx(magIdx[targetMag], 2, 1);
            if (magnetics[targetMag][targetRIdx] == magnetics[magNum][lIdx]) continue;
            else {
                // 맞으면
                rotateOneMag(targetMag, dir * -1);
            }
        }
        if (targetMag > magNum) {
            int targetLIdx = rotateIdx(magIdx[targetMag], 2, -1);
            if (magnetics[targetMag][targetLIdx] == magnetics[magNum][rIdx]) continue;
            else {
                rotateOneMag(targetMag, dir * -1);
            }
        }
    }
}

int main()
{

    input();
    for (int i = 0; i < rotateVec.size(); i++) {
        memset(cnt, 0, sizeof(cnt));
        rotateOneMag(rotateVec[i].magNum, rotateVec[i].direction);
    }
    int ret = 0;
    for (int i = 1; i <= 4; i++) {
        ret += (magnetics[i][magIdx[i]]-'0') * scores[i];
    }
    cout << ret << endl;

    return 0;
}