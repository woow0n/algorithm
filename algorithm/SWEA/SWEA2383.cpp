#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
#include<functional>
 
 
using namespace std;
int Map[12][12];
int N,T,MIN;
 
struct coor
{
    int y, x;
};
 
struct stair
{
    int y, x, length;
};
vector<coor> persons;
vector<stair> stairs;
int path[12];
 
// 계단을 다 내려가려면 k분이 걸린다 / 계단은 최대 3명까지 서있을 수 있다.
// 이동은 유클리드거리다. -> 상하좌우 
// bfs로 계산해보자 -> 최소 이동거리 + 계단대기시간 + 계단의길이
// 계단은 최대가 두개 * 사람은 최대 10명 -> 경우의 수가 크지 않다.
// 이러면 dfs로 가능한가? 모든경우의 수를 계산해서 각각 시뮬레이션 후에 제일 낮은애를 셀렉?
 
 
void input() {
    cin >> N;
    persons.clear();    stairs.clear(); MIN = 21E8;
    stairs.push_back({ -1,-1,-1 });
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            cin >> Map[y][x];
            if (Map[y][x] == 1) {
                persons.push_back({ y,x });
            }
            if (Map[y][x] > 1) {
                stairs.push_back({ y,x,Map[y][x] });
            }
        }
    }
}
 
 
int calTime() {
    priority_queue<int, vector<int>, greater<int>> line1; 
    priority_queue<int, vector<int>, greater<int>> line2;
    queue<int> stair1; queue<int> stair2;
 
 
    for (int p = 0; p < persons.size(); p++) {
        int stairNum = path[p];
        int distance = abs(persons[p].y - stairs[stairNum].y) + abs(persons[p].x - stairs[stairNum].x);
        if (stairNum == 1) line1.push(distance);
        if (stairNum == 2) line2.push(distance);
    }
 
    for (int s = 0; s < stairs[1].length; s++) stair1.push(0);
    for (int s = 0; s < stairs[2].length; s++) stair2.push(0);
 
 
    int time1 = 0, time2 = 0; int tmp_num = 0;
 
    // 줄이 빌 때 까지
    while (!line1.empty()) {
        time1++;
        int tmp = 0;
        tmp_num -= stair1.front(); stair1.pop();
        while (tmp_num < 3 && !line1.empty() && time1 >= line1.top()) {
            line1.pop(); tmp++; tmp_num++;
        }
        stair1.push(tmp); 
    }
    time1 += stairs[1].length;
     
    tmp_num = 0;
 
    while (!line2.empty()) {
        time2++;
        int tmp = 0;
        tmp_num -= stair2.front(); stair2.pop();
        while (tmp_num < 3 && !line2.empty() && time2 >= line2.top()) {
            line2.pop(); tmp++; tmp_num++;
        }
        stair2.push(tmp);
    }
    time2 += stairs[2].length;
 
    return max(time2, time1);
}
 
void dfs(int level) {
    if (level == persons.size()) {
        int tmp = calTime();
        if (MIN > tmp)MIN = tmp;
        return;
    }
         
    //1번계단
    path[level] = 1;
    dfs(level + 1);
    path[level] = 0;
 
    //2번계단
    path[level] = 2;
    dfs(level + 1);
    path[level] = 0;
     
}
 
int main()
{
    cin >> T;
    for (int t = 0; t < T; t++) {
        input();
        dfs(0);
        cout << "#"<<t+1<<" " << MIN + 1 << endl;
    }
 
    return 0;
}