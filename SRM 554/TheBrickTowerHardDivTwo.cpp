

#pragma comment(linker,"/STACK:16777216")
#pragma  warning ( disable: 4786)
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
#include<set>
#include<string>
#include<cmath>
#include<cstdlib>
#include<cctype>
#include<algorithm>
#include<queue>
#include<sstream>
#include<stack>
#include<list>
#include <bitset>
#include<iomanip>
#include <fstream>
#include<ctime>
#include<climits>
using namespace std;

#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))

#define forl(i,a,b) for ( i = a; i < b; i++)
#define fore(i,a,b) for ( i = a; i <= b; i++)
#define forrev(i,a,b) for ( i = a; i >= b; i--)
#define pb push_back
typedef long long  LL;
#define in(a,b,c) ((a) <= (b) && (b) <= (c))
#define ms(a,b) memset((a),(b),sizeof(a))

#define all(v) (v).begin(),(v).end()
#define pb push_back
#define ull unsigned long long int
typedef vector<int> vi;
typedef vector<string> vs;
typedef pair<int,int> pii;
typedef vector<pii> vpii;

string to_string(long long x) { stringstream ss; ss << x; return ss.str(); }
long long to_int(const string &s) { stringstream ss; ss << s; long long x; ss >> x; return x; }

#define MAX 100005
#define MOD 1234567891


class TheBrickTowerHardDivTwo {
    public:
    int find(int C, int K, int H) {
        
        long long ans = 0;
        int i,j,k,l,p;
        int i1,j1,k1,l1;
        int h;
        ans = 0;
        long long dp[48][8][5][5][5][5];
        ms(dp,0);
        
        dp[0][0][0][0][0][0] = 1;
        
        forl(h,0,H){
            for(i=0;i<=C;i++){
                for(j=0;j<=C;j++){
                    for(k=0;k<=C;k++){
                        for(l=0;l<=C;l++){
                            for(p=0;p<=K;p++){
                                if(dp[h][p][i][j][k][l] != 0)
                                {
                                    for(i1=1;i1<=C;i1++){
                                        for(j1=1;j1<=C;j1++){
                                            for(k1=1;k1<=C;k1++){
                                                for(l1=1;l1<=C;l1++){
                                                    int same_cnt = 0;
                                                    same_cnt += (i1==j1) + (i1==l1) + (k1==j1) + (k1==l1);
                                                    same_cnt += (i==i1) + (j==j1) + (k==k1) + (l==l1);
                                                    int q = p+same_cnt;
                                                    if(q <= K){
                                                        dp[h+1][q][i1][j1][k1][l1] = 
                                                        ((long long)(dp[h][p][i][j][k][l] + dp[h+1][q][i1][j1][k1][l1]))%MOD;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        forl(h,1,H+1){
            for(i=1;i<=C;i++){
                for(j=1;j<=C;j++){
                    for(k=1;k<=C;k++){
                        for(l=1;l<=C;l++){
                            for(p=0;p<=K;p++){
                                ans = (long long)(ans + dp[h][p][i][j][k][l])%MOD;
                            }
                        }
                    }
                }
            }
        }
        return ans;
    }
};

// CUT begin
ifstream data("TheBrickTowerHardDivTwo.sample");

string next_line() {
    string s;
    getline(data, s);
    return s;
}

template <typename T> void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
}

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(int C, int K, int H, int __expected) {
    time_t startClock = clock();
    TheBrickTowerHardDivTwo *instance = new TheBrickTowerHardDivTwo();
    int __result = instance->find(C, K, H);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
        cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
        return true;
    }
    else {
        cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
        cout << "           Expected: " << to_string(__expected) << endl;
        cout << "           Received: " << to_string(__result) << endl;
        return false;
    }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
    int cases = 0, passed = 0;
    while (true) {
        if (next_line().find("--") != 0)
            break;
        int C;
        from_stream(C);
        int K;
        from_stream(K);
        int H;
        from_stream(H);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(C, K, H, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1452177672;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i) {
        if ( string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "TheBrickTowerHardDivTwo (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
