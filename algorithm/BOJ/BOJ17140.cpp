#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <cstring>

#define Y first
#define X second
using namespace std;
using pic = pair<int, char>;
using pii = pair<int, int>;
using ll = long long;
using piiWithVal = pair<pii,int>;

int r,c,k;
int mat[110][110];
int lenRow=3, lenCol=3;

void input() {
    cin >> r >> c >> k;
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <=3 ; j++) {
            cin >> mat[i][j];
        }
    }
}

bool cmp(pii a, pii b) {
    if (a.second < b.second) return true;
    if (a.second == b.second && a.first<b.first) return true;
    return false;
}

int rowSort(int rowIdx) {
    pii cnt[110] ;
    int mx = 0;
    for (int i = 1; i <= lenCol; i++) {
        cnt[mat[rowIdx][i]].first = mat[rowIdx][i];
        cnt[mat[rowIdx][i]].second++;
        mx = max(mx, mat[rowIdx][i]);
    }
    sort(cnt, cnt + mx+1, cmp);
    int j = 1;
    for (int i = 0; i < 110; i++) mat[rowIdx][i] = 0;
    for (int i = 0; i <= mx; i++) {
        if (cnt[i].first == 0 ) continue;
        mat[rowIdx][j++] = cnt[i].first;
        mat[rowIdx][j++] = cnt[i].second;
    }
    return --j;
}

int colSort(int colIdx) {
    pii cnt[110];
    int mx = 0;
    for (int i = 1; i <= lenCol; i++) {
        cnt[mat[i][colIdx]].first = mat[i][colIdx];
        cnt[mat[i][colIdx]].second++;
        mx = max(mx, mat[i][colIdx]);
    }
    sort(cnt, cnt + mx + 1, cmp);
    int j = 1;
    for (int i = 0; i < 110; i++) mat[i][colIdx] = 0;
    for (int i = 0; i <= mx; i++) {
        if (cnt[i].first == 0) continue;
        mat[j++][colIdx] = cnt[i].first;
        mat[j++][colIdx] = cnt[i].second;
    }
    return --j;
}


int main() {
    input();
    int rep = 0;

    while (mat[r][c] != k) {
        rep++;
        if (lenCol <= lenRow) {
            int mxlen = 0;
            for (int i = 1; i <= lenRow; i++) {
                int out = rowSort(i);
                mxlen = max(mxlen, out);
            }
            lenCol = mxlen;
        }
        else {
            int mxlen = 0;
            for (int i = 1; i <= lenCol; i++) {
                int out = colSort(i);
                mxlen = max(mxlen, out);
            }
            lenRow = mxlen;
        }
        if (rep > 100) break;
    }
    if (rep > 100) cout << -1;
    else cout << rep;
    int de = 123;
}
