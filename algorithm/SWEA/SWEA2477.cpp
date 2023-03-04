#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
 
using namespace std;
 
int T, N, M, K, A, B;
 
struct user {
    int name, time;
};
 
int deskTm[11], repairTm[11];
user deskUsers[11], repairUsers[11];
int checkDATA[1010], checkDATB[1010];
 
 
queue<user> deskLine; // 줄서는 건 두개지
queue<user> repairLine;
 
// N 개 접수 (1~N) / M개 정비(1~M) / 고객명수 K (1~K) / 도착시간  tk
// A,B 각각 사용한 창구
// 정비 과정 : 접수창구에서 먼저 접수 -> 정비창구에서 정비시작
// 근데 직원들마다 접수/정비 속도가 달라
// 접수창구에서 걸리는 시간은 ai /정비창구에서 걸리는 시간은 bj 
// 도착시간 tk
// 도착하면 빈 접수 창구가서 접수하고 아니면 기다려
// 접수끝나면 정비로 가 똑
// 접수 1.고객번호가 낮은 순대로 우선접수 / 2. 빈창구가 많으면 앞에서 먼저 채움
// 이동시간은 무시 
// 정비끝나면 만족도조사를 해
// 지갑을 분실한 고객과 같은 접수창구/정비창구를 이용한 고객의 합을 출력/ 없으면  -1;
// 지금 어떤놈이 어떤 창구 썻는지 모르니깐 그거 구현하고 고객번호합하면됩니다.
 
void input() {
    // 인풋들
    int t;
    memset(checkDATA, 0, sizeof(checkDATA));
    memset(checkDATB, 0, sizeof(checkDATB));
 
    memset(deskUsers, 0, sizeof(deskUsers));
    memset(repairUsers, 0, sizeof(repairUsers));
    cin >> N >> M >> K >> A >> B;
    for (int i = 1; i <= N; i++) cin >> deskTm[i];
    for (int i = 1; i <= M; i++) cin >> repairTm[i];
    for (int i = 1; i <= K; i++) {
        cin >> t;
        deskLine.push({ i,t });
    }
 
}
// 도착 -> 접수 -> 정비
int deskUsersOk() {
    for (int i = 1; i <= N; i++) {
        if (deskUsers[i].name == 0) return i;
    }
    return -1;
}
int repairUsersOK() {
    for (int i = 1; i <= M; i++) {
        if (repairUsers[i].name == 0) return i;
    }
    return -1;
}
int checkDesk() {
    for (int i = 1; i <= N; i++) {
        if (deskUsers[i].name > 0) return 1;
    }
    return 0;
}
int checkRepair() {
    for (int i = 1; i <= M; i++) {
        if (repairUsers[i].name > 0) return 1;
    }
    return 0;
}
// queue가 empty인경우 잘보자
void solution() {
    // 두개의 줄이 없어지면 끝난다. 어차피 누가 누구한테 정비/접수햇는지만 알면되니깐은 
    // 끝날때까지는 안해도돼
    // 시간이 0인거도있다아
    int time = 0;
    while (!deskLine.empty() || !repairLine.empty() || checkDesk() || checkRepair()) {
        for (int i = 1; i <= N; i++) {
            if (deskUsers[i].name == 0) continue;
            deskUsers[i].time++;
            if (deskUsers[i].time >= deskTm[i]) {
                user outuser = deskUsers[i]; outuser.time = 0;
                repairLine.push(outuser);
                deskUsers[i] = { 0,0 };
            }
        }
 
        while (deskLine.size()>0 && deskLine.front().time <= time  && deskUsersOk() != -1) {
            user firstUser = deskLine.front();
            int check = deskUsersOk();
            deskLine.pop();
            deskUsers[check] = { firstUser.name, 0 };
            if (check == A)checkDATA[firstUser.name] = 1;
        }
 
        for (int i = 1; i <= M; i++) {
            if (repairUsers[i].name == 0) continue;
            repairUsers[i].time++;
            if (repairUsers[i].time >= repairTm[i]) {
                user outuser = repairUsers[i]; outuser.time = 0;
                repairUsers[i] = { 0,0 };
            }
        }
        while (repairLine.size()>0 && repairUsersOK() != -1) {
            user firstUser = repairLine.front();
            int check = repairUsersOK();
            repairLine.pop();
            repairUsers[check] = { firstUser.name, 0 };
            if (check == B)checkDATB[firstUser.name] = 1;
        }
        time++;
    }
}
 
 
int main()
{
    cin >> T;
    for (int t = 0; t < T; t++) {
        int ret = 0;
        input();
        solution();
        for (int i = 1; i <= K; i++) {
            if (checkDATA[i]+ checkDATB[i] == 2) ret += i;
        }
        if (ret == 0) ret--;
        cout << "#" << t + 1 << " " << ret << endl;
    }
    return 0;
}