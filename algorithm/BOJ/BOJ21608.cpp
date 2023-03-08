#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <set>
#include <algorithm>

#define Y first
#define X second

using namespace std;
using pii = pair<int, int>;
using pis = pair<int, set<int>>;
using pII = pair<pii, pii>;
int n;
int Map[440][440];
vector<pis> favor;

int dy[] = { -1,1,0,0 };
int dx[] = { 0,0,-1,1 };
int score[] = { 0,1,10,100,1000 };
void input() {
    cin >> n ;
    for (int i = 0; i < n*n; i++) {
        pis tmp;
        cin >> tmp.first;
        for (int j = 0; j < 4; j++) {
            int a; cin >> a; tmp.second.insert(a);
        }
        favor.push_back(tmp);
    }
}

pii checkFavor(pis student, pii coor) {
    auto name = student.first;
    auto Set = student.second;
    int zeroCnt = 0; int favorCnt = 0;
    for (int i = 0; i < 4; i++) {
        int ny = coor.Y + dy[i];
        int nx = coor.X + dx[i];
        if (ny < 0 || nx < 0 || ny >= n || nx >= n)continue;
        int tmpVal = Map[ny][nx];
        if (tmpVal == 0) { zeroCnt++; continue; }
        if (Set.find(tmpVal) != Set.end())favorCnt++;
    }
    return { favorCnt, zeroCnt };
}

bool cmp(pII a, pII b) {
    if (a.second.first > b.second.first) return true;
    if (a.second.first == b.second.first) {
        if (a.second.second > b.second.second) return true;
        if (a.second.second == b.second.second) {
            if (a.first.Y < b.first.Y) return true;
            if (a.first.Y == b.first.Y) {
                if (a.first.X < b.first.X) return true;
            }
        }
    }
    return false;
}

bool cmpFavor(pis a, pis b) {
    if (a.first < b.first) return true;
    return false;
}

int main() {
    input();
    int ret = 0;
    for (int s = 0; s < favor.size(); s++) {
        auto student = favor[s];
        vector<pII> subs;
        for (int y = 0; y < n; y++) {
            for (int x = 0; x < n; x++) {
                if (Map[y][x] != 0) continue;
                subs.push_back({ {y,x}, checkFavor(student, {y,x}) });
            }
        }
        sort(subs.begin(), subs.end(), cmp);
        Map[subs[0].first.Y][subs[0].first.X] = student.first;
    }
    sort(favor.begin(), favor.end(), cmpFavor);

    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            int s = 0;
            int a = Map[y][x];
            set<int> Set = favor[a-1].second;
            for (int i = 0; i < 4; i++) {
                int ny = y + dy[i];
                int nx = x + dx[i];
                if (ny < 0 || nx < 0 || ny >= n || nx >= n)continue;
                int tmpVal = Map[ny][nx];
                if (Set.find(tmpVal) != Set.end())s++;
            }
            ret += score[s];
        }
    }
    cout << ret;
    return 0;
}