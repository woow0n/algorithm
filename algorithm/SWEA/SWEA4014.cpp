#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
 
using namespace std;
vector<int> idx;
int N, X, T, ret;
int Map[25][25], transposedMap[25][25];
 
void input() {
    cin >> N >> X;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            cin >> Map[y][x];
            transposedMap[x][y] = Map[y][x];
        }
    }
}
 
int canAppend(int x) {
    for (int i = 0; i < idx.size(); i++) {
        if (idx[i] == x) return 0;
    }
    return 1;
}
 
int makeAirstrip(int row, int Map[][25]) {
    idx.clear();  int flag = 0; int vst[25] = { 0, };
    for (int x = 1; x < N; x++) {
        int prevH = Map[row][x - 1]; int nowH = Map[row][x];
        if (abs(prevH - nowH) > 1) return 0;
        if (prevH == nowH) {
            if (canAppend(x - 1))idx.push_back(x - 1);
            if (canAppend(x))idx.push_back(x);
        }
        if (prevH < nowH) {
            if (flag) return 0;
            if (idx.size() < X) return 0;
            for (int i = 0; i < X; i++) {
                int last = idx.back(); idx.pop_back();
                if (vst[last] == 1) return 0;
                vst[last] = 1;
            }
            idx.clear();
            idx.push_back(x);
        }
        if (prevH > nowH && flag == 0) { flag = 1; idx.clear(); }
        if (flag > 1 && prevH != nowH) return 0;
        if (flag) flag++;
        if (flag && X - idx.size() > N - x) return 0;
        if (flag && idx.size() >= X) {
            for (int i = 0; i < X; i++) {
                int last = idx.back(); idx.pop_back();
                if (vst[last] == 1) return 0;
                vst[last] = 1;
            }
            idx.clear();
            flag = 0;
        }
    }
    return 1;
}
 
int main()
{
    //    freopen("input.txt", "r", stdin);
    cin >> T;
    for (int t = 0; t < T; t++) {
        ret = 0;
        input();
        for (int i = 0; i < N; i++) {
            ret += makeAirstrip(i, Map);
            ret += makeAirstrip(i, transposedMap);
        }
        cout << "#" << t + 1 << " " << ret << endl;
    }
    return 0;
}