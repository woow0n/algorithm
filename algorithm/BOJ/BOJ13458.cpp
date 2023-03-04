#include <iostream>
#include <vector>
#include <queue>

using namespace std;
using pic = pair<int, char>;
using pii = pair<int, int>;
using ll = long long;
ll N, A;
ll inspector, subInspector;
ll classNum[1000100];

void input() {
	cin >> N ;
	for (int i = 0; i < N; i++) cin >> classNum[i];
	cin >> inspector >> subInspector;
}

int main(){
	input();
	ll cnt = 0;
	for (int i = 0; i < N; i++) {
		classNum[i] -= inspector;
		cnt++;
		if (classNum[i] <= 0) continue;
		ll share = classNum[i] / subInspector;
		ll remain = classNum[i] % subInspector;
		cnt += share;
		if (remain == 0) { continue; }
		cnt++;
	}
	cout << cnt;
	return 0;
}

// 10 9 10 9 10
// 3  2 3  2 3