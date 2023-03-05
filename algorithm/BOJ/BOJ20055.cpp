#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <cstring>

#define Y first
#define X second
using namespace std;
using pii = pair<int, int>;
using ll = long long;

int n, k, cnt;
int Map[210];
int nums[210];

void input() {
    cin >> n >> k ;
    for (int i = 0; i < 2*n; i++)  cin >> nums[i];
}

void beltMove() {
    int last = Map[0];
    int lastNum = nums[0];

    for (int i = 1; i < 2*n; i++) {
        int tmp = Map[i]; Map[i] = last; last = tmp;
        int tmpNum = nums[i]; nums[i] = lastNum; lastNum = tmpNum;
    }
    Map[0] = last;
    nums[0] = lastNum;

    Map[n - 1] = 0;
    
    for (int i = n - 1; i >= 0; i--) {
        if (Map[i] == 1 && Map[i + 1] == 0 && nums[i + 1] != 0) {
            Map[i] = 0; Map[i + 1] = 1; nums[i + 1]--;
            if (nums[i + 1] == 0) cnt++;
            if (i + 1 == n - 1) Map[i + 1] = 0;
        }
    }
    if (nums[0] > 0 && Map[0] != 1) {
        Map[0] = 1;
        nums[0]--;
        if (nums[0] == 0)cnt++;
    }
}


int main() {
    input();
    int time = 0;
    while (cnt < k) { 
        time++;  
        beltMove(); 
    }
    cout << time;
    return 0;
}
