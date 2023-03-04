#include<iostream>
#include<string>
#include<set>
 
using namespace std;
 
int T, N, K;
string treasure;
set<string,greater<string>> square;
 
void input() {
    square.clear();
    cin >> N >> K;
    cin >> treasure;
    treasure += treasure;
}
 
void appendRotate() {
    int width = N / 4;
    for (int i = 0; i < N; i++) {
        square.insert(treasure.substr(i, width));
    }
}
 
int main()
{
    cin >> T;
    for (int t = 0; t < T; t++) {
        input();
        appendRotate();
        auto pointer = square.begin();
        for (int i = 0; i < K-1; i++) pointer++;
        int ret = stoi(*pointer, nullptr,16);
        cout << "#" << t + 1 << " " << ret << endl;
    }
    return 0;
}