#include <iostream>
using namespace std;

int n, m, h;
int arr[32][12];
int cnt = 0;
int leadercnt;
int flag;

int check() {
	for (int i = 1; i <= n; i++) { //세로 
		int ii = i; //열
		for (int j = 1; j <= h; j++) {
			if (arr[j][ii] == 1)
				ii++;
			else if (arr[j][ii - 1] == 1) {
				ii--;
			}
		}
		if (ii != i)
			return 0;
	}
	return 1;
}

void dfs(int y, int cnt) {
	if (flag) return;
	if (cnt == leadercnt) { flag = check(); return; }
	for (int i = y; i <= h; i++) {
		for (int j = 1; j < n; j++) {
			if (arr[i][j] == 0 && arr[i][j - 1] == 0 && arr[i][j + 1] == 0){
				arr[i][j] = 1;
				dfs(i, cnt + 1);
				arr[i][j] = 0;
			}
		}
	}
	return;
}

int main() {
	int a = 0, b = 0;
	cin >> n >> m >> h;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		arr[a][b] = 1;
	}
	for (int i = 0; i <= 3; i++) {
		flag = 0;
		leadercnt = i;
		dfs(1, 0);
		if (flag) { cout << i << endl; return 0; }
	}
	cout << -1 << endl;
	return 0;
}