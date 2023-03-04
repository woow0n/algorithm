#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define Y first
#define X second

using namespace std;
using pic = pair<int, char>;
using pii = pair<int, int>;
using ll = long long;


int N, mx=-21e8, mn=21e8, tmp;
int numbers[13];
int opers[4];

void input() {
	cin >> N ;
	for (int i = 0; i < N; i++) cin >> numbers[i];
	for (int i = 0; i < 4; i++) cin >> opers[i];
	tmp = numbers[0];
}

void dfs(int level) {
	if (level == N - 1) {
		mx = max(mx, tmp);
		mn = min(mn, tmp);
		return;
	}
	for (int i = 0; i < 4; i++) {
		if (opers[i] == 0) continue;
		opers[i] --;
		int last = tmp;
		if (i == 0) tmp += numbers[level + 1];
		if (i == 1) tmp -= numbers[level + 1];
		if (i == 2) tmp *= numbers[level + 1];
		if (i == 3) tmp /= numbers[level + 1];
		dfs(level + 1);
		opers[i] ++;
		tmp = last;
	}
}

int main(){
	input();
	dfs(0);
	cout << mx << endl << mn;
	return 0;
}
