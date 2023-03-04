#include <iostream>
using namespace std;

int n;
int times[200];
int money[200];
int dp[200];

void input() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> times[i] >> money[i];
		if (i + times[i] > n)  money[i] = 0;
	}
}

int getMaxMoney(int level)
{
	if (level >= n) return 0;
	if (dp[level] != 0) return dp[level];

	int max = 0;
	for (int i = 0; i < times[level]; i++) {
		int now = level + i;
		int ret = getMaxMoney(now + times[now]) + money[now];
		if (ret > max) max = ret;
	}

	dp[level] = max;
	return dp[level];
}

int main()
{
	input();
	int ret = getMaxMoney(0);
	cout << ret << endl;

	return 0;
}