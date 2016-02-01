
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
#define MID(a, b) (a + ((b - a) >> 1))
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

#define MAX 18
#define INF 9999999

bool dp[MAX][MAX][MAX];
class BearFair2 {
    public:
    string isFair(int N, int B, vector<int> upTo, vector<int> quantity) {
        int n = N;
        int i,j,k,sz;
        vector<int> upTo1 = upTo;
        vector<int> quantity1 = quantity;
        upTo1.pb(B);
        quantity1.pb(N);
        sz = upTo1.size();
        //cout << "\n-----\n";
        for(i=0;i<sz;i++){
            for(j=0;j<sz-1-i;j++){
                if(upTo1[j] > upTo1[j+1]){
                    swap(upTo1[j], upTo1[j+1]);
                    /*if(quantity[j] < quantity[j+1]){
                        return "unfair";
                    }*/
                    swap(quantity1[j],quantity1[j+1]);
                }
            }
        }
        
        int prevUpto=0;
        int prevQuantity=0;
        for(i=0;i<=n/3;i++){
            for(j=0;j<=n/3;j++){
                for(k=0;k<=n/3;k++){
                    dp[i][j][k] = false;
                }
            }
        }
        dp[0][0][0] = true;
        int a,b,c,x,y,z;
        for(i=0;i<sz;i++){
            int upto = upTo1[i];
            int quan = quantity1[i]-prevQuantity;
            
            int limit[3] = {0};
            for(j=prevUpto+1;j<=upto;j++){
                limit[j%3]++;
            }
            if(quan < 0 || quan > upto-prevUpto){
                return "unfair";
            }
            for(a=0;a<=limit[0];a++){
                for(b=0;b<=limit[1];b++){
                    for(c=0;c<=limit[2];c++){
                        if(a+b+c == quan){
                            for(x=0;x<=n/3;x++){
                                for(y=0;y<=n/3;y++){
                                    for(z=0;z<=n/3;z++){
                                        if(x+y+z == prevQuantity && x+a <= n/3 && y+b<= n/3 && z+c <= n/3 && dp[x][y][z]){
                                            dp[x+a][y+b][z+c] = true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            prevUpto = upto;
            prevQuantity = quantity1[i];
        }
        if(dp[n/3][n/3][n/3])
            return "fair";
        return "unfair";
    }
};

// CUT begin
ifstream data("BearFair2.sample");

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

template <typename T> void from_stream(vector<T> &ts) {
    int len;
    from_stream(len);
    ts.clear();
    for (int i = 0; i < len; ++i) {
        T t;
        from_stream(t);
        ts.push_back(t);
    }
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

bool do_test(int n, int b, vector<int> upTo, vector<int> quantity, string __expected) {
    time_t startClock = clock();
    BearFair2 *instance = new BearFair2();
    string __result = instance->isFair(n, b, upTo, quantity);
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
        int n;
        from_stream(n);
        int b;
        from_stream(b);
        vector<int> upTo;
        from_stream(upTo);
        vector<int> quantity;
        from_stream(quantity);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, b, upTo, quantity, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1454010403;
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
        cout << "BearFair2 (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
