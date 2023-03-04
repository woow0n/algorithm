#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
 
vector<int> Map[13];
vector<int> cpyMap[13];
vector<int> check;
vector<int> bombPath;
int MIN = 21E8;
int N, W, H, T;
 
// 다음 테스트케이스가 오기전에 초기화
void init() {
    for (int x = 0; x < W; x++) {
        Map[x].clear();
        cpyMap[x].clear();
    }
    check.clear();
    MIN = 21E8;
}
 
// 인풋을 받는데 어레이 연산은 되게 복잡할거 같은니깐 벡터로 받기로하고 transpose한 상태로 받자
void input() {
    cin >> N >> W >> H;
    for (int y = 0; y < H; y++) {
        int oneCnt = 0;
        for (int x = 0; x < W; x++) {
            int block; cin >> block;
            Map[x].push_back(block);
            cpyMap[x].push_back(0);
            if (block == 0 || block == 1) oneCnt++;
        }
    }
    // 한줄이 전부 1이거나 0이면은 연쇄반응이 일어 나지 않으니깐 걔네는 눈길도 안줄거야
    for (int x = 0; x < W; x++) {
        for (int y = 0; y < Map[x].size(); y++) {
            if (Map[x][y] != 0 && Map[x][y] != 1) { check.push_back(x); break; }
        }
    }
}
// 벽돌을 깨는 함수 재귀이용 좌표에 있는 숫자 -1 만큼 퍼지게
void pop(int x, int y, int range) {
    cpyMap[x][y] = 0;
    if (range == 1 || range == 0) return;
    int dy[] = { -1,1,0,0 };
    int dx[] = { 0,0,-1,1 };
    for (int r = 1; r <= range -1; r++) {
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i] * r;
            int ny = y + dy[i] * r;
            if (ny < 0 || nx < 0 || nx >= W || ny >= H) continue;
            if (cpyMap[nx][ny] == 0) continue;
            pop(nx, ny, cpyMap[nx][ny]);
        }
    }
}
 
// 한 행(원래는 열)에 폭탄 떨어뜨리는놈
void dropBomb(int x) {
    for (int y = 0; y < H; y++) {
        if (cpyMap[x][y] != 0) { pop(x, y, cpyMap[x][y]); break; }
    }
}
// 0를 지우고 우측으로 붙이는 놈 (원래는 중력으로 블록이 떨어지는 경우)
void eraseZero() {
    for (int x = 0; x < W; x++) {
        int flag = 0;
        for (int y = 0; y < H; y++) {
            if (cpyMap[x][y] != 0) flag = 1;
            if (cpyMap[x][y] == 0 && flag) {
                // 0 인놈 지우고 앞에 0추가
                cpyMap[x].erase(cpyMap[x].begin() + y);
                cpyMap[x].insert(cpyMap[x].begin(), 0);
            }
        }
    }
}
 
// 만약 후보에 벽돌이 남아있는지 아닌지 체크
int checkCheck(){
    for (int i = 0; i < check.size(); i++) {
        int x = check[i];
        for (int y = 0; y < H; y++) {
            if (cpyMap[x][y] != 0) return 0;
        }
    }
    return 1;
}
// 모든 좌표가 0이라면 더이상 할 필요없으니깐 체크
int checkAll () {
    for (int x = 0; x < W; x++) {
        for (int y = 0; y < H; y++) {
            if (cpyMap[x][y] != 0) return 0;
        }
    }
    return 1;
}
// DFS로 어느곳에 폭탄을 떨어뜨릴것인가 찾고
void dfs(int level) {
    if (level == N) {
    // path 순으로 떨어뜨리고 갯수세기
        int cnt = 0, exit = 0;
        // 맵 복사
        for (int x = 0; x < W; x++) {
            copy(Map[x].begin(), Map[x].end(), cpyMap[x].begin());
        }
        for (int i = 0; i < bombPath.size(); i++) {
            dropBomb(bombPath[i]);
            eraseZero();
            // 만약 모든 좌표가 0이라면 이제 안해
            if (checkAll()) { MIN = 0; return;}
            // 만약 후보군이 모두 0이다 ->> 나머지는 전부 1아니면 0이라는 뜻 -> 남은 rep만큼 뺴주면된다는뜻
            if (checkCheck()) { exit = N - (i+1); break;}
             
        }
        // 남은 숫자세기
        for (int y = 0; y < H; y++) {
            for (int x = 0; x < W; x++) {
                if (cpyMap[x][y] != 0) cnt++;
            }
        }
        // 남은 rep을 빼는데 음수일수도 있으니깐 보정
        if (exit > 0) cnt = max(0, cnt - exit);
        if (cnt < MIN) MIN = cnt;
        return;
    }
    if (MIN == 0) return;
    // 어차피 많이 터트린최댓값 찾아야되니깐 가지치기는 없고 중복가능
    for (int i = 0; i < check.size(); i++) {
        // pop에서 좌표저장하게하고 복원하는식으로 하면 할수는 있겠지만 너무 코드가 드러워지니깐 이렇게만하자
        bombPath.push_back(check[i]);
        dfs(level + 1);
        bombPath.pop_back();
    }
}
 
 
int main()
{
    cin >> T;
    for (int t = 0; t < T; t++) {
        input();
        dfs(0);
        cout << "#" << t+1 << " " << MIN << endl;
        init();
    }
    return 0;
}