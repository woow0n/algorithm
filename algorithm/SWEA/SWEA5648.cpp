#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>
#include <set>
#include <cmath>
#define Y first
#define X second
 
using namespace std;
using pii = pair<int, int>;
 
int T, N, ret;
struct atom
{
    int name, y, x, dir, power;
};
int Map[2001][2001];
vector<atom> atoms;
int dy[] = { 1,-1,0,0 };
int dx[] = { 0,0,-1,1 };
int diagY[] = { 1,1,-1,-1 };
int diagX[] = { -1,1,-1,1 };
int diagDir[][2] = {{0,1}, {2,3}, {0,2},{1,3}};
int reverseDir[] = { 1,0,3,2 };
int reverseDiagDir[][2] = { {3,2},{3,2},{1,0},{1,0} };
 
struct crush
{
    int a, b, power;
    float time;
};
vector<crush> crushs;
set<int> Set;
 
bool cmp(crush A, crush B) {
    if (A.time < B.time) return true;
    return false;
}
 
void input() {
    cin >> N;
    crushs.clear();
    atoms.clear(); 
    Set.clear();
    memset(Map, 0, sizeof(Map));
    atoms.push_back({ 0,0,0,0 });
    for (int i = 0; i < N; i++) {
        int x, y, dir, power;
        cin >> x >> y >> dir >> power;
        y += 1000; x += 1000;
        Map[y][x] = i + 1;
        atoms.push_back({ i + 1,y,x,dir,power });
    }
}
 
void checkColid(int i) {
    // 원자
    auto tmp = atoms[i];
    // 초기값은 모두 자기자신
    int ny = tmp.y, nx = tmp.x;
    int ndy1 = tmp.y, ndx1 = tmp.x;
    int ndy2 = tmp.y, ndx2 = tmp.x;
    vector<int> booms;
    int flag1 = 1; int flag2 = 1; int flag3 = 1;
    while (flag1 || flag2 || flag3) {
        if (flag1){ny += dy[tmp.dir]; nx += dx[tmp.dir];}
        if (flag1 && ny >= 0 && nx >= 0 && ny <= 2000 && nx <= 2000) {
            // 만약 0원자가 있고 그게 나한테오고있으면
            if (Map[ny][nx] != 0 && atoms[Map[ny][nx]].dir == reverseDir[tmp.dir])
                booms.push_back(Map[ny][nx]);
        }
        else flag1 = 0;
 
        if (flag2) { ndy1 += diagY[diagDir[tmp.dir][0]]; ndx1 += diagX[diagDir[tmp.dir][0]]; }
        if (flag2 && ndy1 >= 0 && ndx1 >= 0 && ndy1 <= 2000 && ndx1 <= 2000) {
            if (Map[ndy1][ndx1] != 0 && atoms[Map[ndy1][ndx1]].dir == reverseDiagDir[tmp.dir][0])
                booms.push_back(Map[ndy1][ndx1]);
        }
        else flag2 = 0;
 
        if (flag3) { ndy2 += diagY[diagDir[tmp.dir][1]]; ndx2 += diagX[diagDir[tmp.dir][1]]; }
        if (flag3 && ndy2 >= 0 && ndx2 >= 0 && ndy2 <= 2000 && ndx2 <= 2000) {
            if (Map[ndy2][ndx2] != 0 && atoms[Map[ndy2][ndx2]].dir == reverseDiagDir[tmp.dir][1])
                booms.push_back(Map[ndy2][ndx2]);
        }
        else flag3 = 0;
    }
    for (int i = 0; i < booms.size(); i++) {
        float time = (fabs(tmp.y - atoms[booms[i]].y) + fabs(tmp.x - atoms[booms[i]].x)) / 2;
        crushs.push_back({ booms[i], tmp.name, atoms[booms[i]].power,  time });
    }
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
 
    cin >> T;
    for (int t = 0; t < T; t++) {
        input();
        ret = 0;
        for (int i = 1; i <= N; i++) {
            checkColid(i);
        }
        sort(crushs.begin(), crushs.end(), cmp);
        float time = 0.5; int idx = 0;
        crushs.push_back({ 0,0,0,0 });
        vector<int>eraseVector;
        while (idx < crushs.size()) {
            auto tmp = crushs[idx];
            if (tmp.time != time) {
                time = tmp.time;
                for (int i = 0; i < eraseVector.size(); i++) { 
                    if (Set.find(eraseVector[i]) == Set.end()) ret += atoms[eraseVector[i]].power;
                    Set.insert(eraseVector[i]);
                }
                eraseVector.clear();
                continue;
            }
            if (Set.find(tmp.a) == Set.end() && Set.find(tmp.b) == Set.end())
                eraseVector.push_back(tmp.a);
            idx++;
        }
        cout << "#" << t + 1 << " " << ret << endl;
    }
    return 0;
}