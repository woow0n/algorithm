#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
#include<vector>
 
using namespace std;
 
int T, n, m;
int Map[21][21], vst[21][21];
vector<int> idxY, idxX;
 
 
void input() {
    cin >> n >> m ;
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            cin >> Map[y][x];
            if (Map[y][x] == 1) { idxY.push_back(y); idxX.push_back(x); }
        }
    }
}
 
int countHouse(int y,int x) {
    int Max = 0;
    vector<int> distance;
    for (int i = 0; i < idxY.size(); i++) {
        distance.push_back(abs(idxY[i] - y) + abs(idxX[i] - x));
    }
    for (int d = 0; d < n*2; d++) {
        int cnt = 0;
        for (int i = 0; i < idxY.size(); i++) {
            if (d >= distance[i]) cnt++;
        }
        int outcome = (d+1) * (d+1) + d*d;
        int income = cnt * m;
        if (income - outcome < 0) continue;
        if( Max < cnt) Max = cnt;
    }   
    return Max;
}
 
int main()
{
    cin >> T;
    for (int t = 0; t < T; t++) {
        idxY.clear(); idxX.clear();
        input();
        int Max = 0;
        for (int y = 0; y < n; y++) {
            for (int x = 0; x < n; x++) {
                int tmp = countHouse(y, x);
                if (tmp > Max) Max = tmp;
            }
        }
        cout << "#" << t + 1 << " " << Max << endl;
    }
    return 0;
}