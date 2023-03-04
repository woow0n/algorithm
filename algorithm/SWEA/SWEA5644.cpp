#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
#include<functional>
 
using namespace std;
int T, M, A, score;
int moveA[101], moveB[101];
 
int dy[5] = { 0,-1,0,1,0 };
int dx[5] = { 0,0,1,0,-1 };
struct coor { int y, x; };
struct charger { int name, power; };
// 맵을 채우는데 일반 어레이보다는 기본 channel이 1이지만 모든 좌표에서 channel이 커지지 않게 벡터로만
vector<charger> chargerMAP[11][11];
// 얘는 floodfill에서 원래간데 또 안가기위해서 
int mapVst[11][11];
 
// floodfill 알고리즘응용해서 맵채우기 
void fillMap(int initY, int initX, int range, charger c) {
    score = 0;
    memset(mapVst, 0, sizeof(mapVst));
    queue<coor> q;
    q.push({ initY, initX });
    chargerMAP[initY][initX].push_back(c);
    mapVst[initY][initX] = 1;
    int r = range;
    while (r--)
    {
        int sz = q.size();
        while (sz--) {
            coor now = q.front(); q.pop();
            for (int i = 1; i <= 4; i++) {
                int ny = now.y + dy[i];
                int nx = now.x + dx[i];
                if (ny < 0 || nx < 0 || ny >= 11 || nx >= 11) continue;
                if (mapVst[ny][nx] == 1) continue;
                mapVst[ny][nx] = 1;
                q.push({ ny,nx });
                chargerMAP[ny][nx].push_back({c});
            }
        }
    }
}
// 구조체 정렬법
bool cmp(const charger& a, const charger& b) {
    // 큰게 앞으로 간다는 뜻 (즉 내림차순정렬 -> 파워가 큰놈이 앞에가게)
    if (a.power > b.power) return true;
    // 파워가 같으면 네임으로 정렬
    else if (a.power == b.power) {
        if (a.name > b.name) return true;
    }
    return false;
}
 
void input() {
    cin >> M >> A;
    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 11; x++) {
            chargerMAP[y][x].clear();
        }
    }
    for (int m = 0; m < M; m++) cin >> moveA[m];
    for (int m = 0; m < M; m++) cin >> moveB[m];
    for (int name = 1; name <= A; name++) {
        int apY, apX, c, p;
        cin >> apX >> apY >> c >> p;
        fillMap(apY, apX, c, { name,p });
    }
    for (int y = 1; y < 11; y++) {
        for (int x = 1; x < 11; x++) {
            int sz = chargerMAP[y][x].size();
            // 이따 사이즈 체크하기 귀찮으니깐 0인놈들도 다 초기화
            if (sz == 0) chargerMAP[y][x].push_back({ 0,0 });
            // 큰거를 우선적으로 보니깐은 내림차순으로 정렬
            if (sz > 1) sort(chargerMAP[y][x].begin(), chargerMAP[y][x].end(), cmp);
        }
    }
 
}
 
 
void move() {
    // 초기좌표들
    int ay = 1, ax = 1, by = 10, bx = 10;
    // 초기값을 더한다
    score += chargerMAP[ay][ax].front().power; score += chargerMAP[by][bx].front().power;
 
    for (int i = 0; i < M; i++) {
        int aDir = moveA[i]; int bDir = moveB[i];
        int nay = ay + dy[aDir], nby = by + dy[bDir], nax = ax + dx[aDir], nbx = bx + dx[bDir];
        vector<charger> tmpA = chargerMAP[nay][nax]; vector<charger> tmpB = chargerMAP[nby][nbx];
        // 충전기가 안겹치면 각자 알아서 해라
        if (tmpA.front().name != tmpB.front().name) {
            score += tmpA.front().power;  score += tmpB.front().power;
        }
        // 둘이 같은충전기고 하나만 할당되어 있으면 한놈만 올린다 (나눠먹는다)
        else if (tmpA.front().name == tmpB.front().name && tmpA.size() == 1 && tmpB.size() == 1) {
            score += tmpA.front().power;
        }
        // 나머지 경우 이름이 같다면 둘이 공통 최댓값도 같을테니깐 일단은 최댓값을 더하고
        else if (tmpA.front().name == tmpB.front().name && tmpA.size() >= 1 && tmpB.size() >= 1) {
            score += tmpA.front().power;
            // 두번째로 큰놈을 비교하는데 더 큰놈을 넣는다 (어차피 공통최댓값은 같다/)
            if (tmpA.size() >= 2 && tmpB.size() >= 2) score += max(tmpA[1].power, tmpB[1].power);
            // 공통최댓값이 유일한 원소인 경우가 있다면 다른놈의 2등을 넣어준다
            if (tmpA.size() >= 2 && tmpB.size() == 1) score += tmpA[1].power;
            if (tmpA.size() == 1 && tmpB.size() >= 2) score += tmpB[1].power;
        }
        ay = nay; by = nby; ax = nax; bx = nbx;
    }
}
 
 
int main()
{
    cin >> T;
    for (int t = 0; t < T; t++) {
        input();
        move();
        cout << "#" << t + 1 << " " << score << endl;
 
    }
    return 0;
}