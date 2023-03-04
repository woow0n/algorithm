#include <iostream>
#include <vector>
#include <cstring>
 
 
using namespace std;
 
int D, W, K, ans, cnt;
 
int film[30][30];
int filmCpy[30][30];
 
void clear() {
    memset(film, 0, sizeof(int) * 30 * 30);
    memset(filmCpy, 0, sizeof(int) * 30 * 30);
    ans = 9999;
}
 
 
void input() {
    cin >> D >> W >> K;
    for (int d = 0; d < D; d++) {
        for (int w = 0; w < W; w++) {
            cin >> film[d][w];
            filmCpy[d][w] = film[d][w];
        }
    }
}
 
int checkcol(int col) {
    int cnt = 1;
    for (int d = 1; d < D; d++) {
        if (film[d][col] == film[d - 1][col]) cnt++;
        else cnt = 1;
 
        if (cnt >= K) return 1;
    }
    return 0;
}
 
int check() {
    for (int w = 0; w < W; w++) {
        if (checkcol(w)) continue;
        return 0;
    }
    return 1;
}
 
void inputMed(int d, int ab, int foward){
    if (foward) {
        for (int i = 0; i < W; i++) {
            film[d][i] = ab;
        }
    }
    else {
        for (int i = 0; i < W; i++) {
            film[d][i] = filmCpy[d][i];
        }
    }
}
 
void dfs(int level) {
    if (level == D) {
        if (check() == true) {
            if (cnt < ans)
                ans = cnt;
        }
        return;
    }
 
 
    if (cnt > ans)
        return;
 
    dfs(level + 1);
 
    cnt++;
    inputMed(level, 0, 1); // 얘복원을 어찌함?
    dfs(level + 1);
    inputMed(level, 0, 0);
    cnt--;
 
    cnt++;
    inputMed(level, 1, 1); // 얘복원을 어찌함?
    dfs(level + 1);
    inputMed(level, 1, 0);
    cnt--;
}
 
 
int main()
{
    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        clear();
        input();
        if (check()) cout << "#" << t + 1 << " " << 0 << endl;
        else {
            dfs(0);
            cout << "#" << t + 1 << " " << ans << endl;
        }
    }
 
    return 0;
}