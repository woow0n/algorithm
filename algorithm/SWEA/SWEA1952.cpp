#include<iostream>
 
using namespace std;
 
int T, dayM, monthM, tripleM, yearM, SUM, MIN;
int vstDay[13];
 
void input() {
    cin >> dayM >> monthM >> tripleM >> yearM;
    for (int i = 0; i < 12; i++) {
        cin >> vstDay[i];
    }
    // 년간이용은 계산 없이 바로 가능
    MIN = yearM;
}
 
void dfs(int month) {
 
    if (month >= 12) {
        if (SUM < MIN) MIN = SUM;
        return;
    }
 
    if (SUM > MIN) return;
    //일간이용
    SUM += dayM * vstDay[month];
    dfs(month + 1);
    SUM -= dayM * vstDay[month];
 
    //월간이용
    SUM += monthM;
    dfs(month + 1);
    SUM -= monthM;
 
    //세달이용
    if (month <= 10){
        SUM += tripleM;
        dfs(month + 3);
        SUM -= tripleM;
    }
}
 
int main()
{
    cin >> T;
    for (int t = 0; t < T; t++) {
        input();
        dfs(0);
        cout << "#" << t + 1 << " " << MIN << endl;
    }
    return 0;
}