#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
vector<int> idx;
int N, X, T, ret;
int Map[110][110], transposedMap[110][110];

void input() {
    cin >> N >> X;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            cin >> Map[y][x];
            transposedMap[x][y] = Map[y][x];
        }
    }
    if (X == 1) X = 0;
}

int canAppend(int x) {
    for (int i = 0; i < idx.size(); i++) {
        if (idx[i] == x) return 0;
    }
    return 1;
}

int makeAirstrip(int row, int Map[][110]) {
    idx.clear();  int flag = 0; int vst[110] = { 0, };
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
            if (X == 0) {
                if (vst[x-1] == 1) return 0;
                vst[x - 1] = 1;
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
            if (X == 0) vst[x] = 1;
            idx.clear();
            flag = 0;
        }
    }
    return 1;
}

int main()
{
    ret = 0;
    input();
    for (int i = 0; i < N; i++) {
        ret += makeAirstrip(i, Map);
        ret += makeAirstrip(i, transposedMap);
    }
    cout << ret;
    return 0;
}