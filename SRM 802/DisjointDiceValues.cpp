#include<bits/stdc++.h>
using namespace std;
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))

#define MX 1000000

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
typedef pair<int,int> pii;
typedef vector<pii> vpii;

string to_string(long long x) { stringstream ss; ss << x; return ss.str(); }
long long to_int(const string &s) { stringstream ss; ss << s; long long x; ss >> x; return x; }

#define MAX 100005
long long int dp[20][130][130];
int n,m;
bool iscommon(int m1, int m2){
    int i;
    forl(i,1,7){
        if((m1&(1<<i)) and (m2 &(1<<i)))
            return true;
    }
    return false;
}

long long int doit(int ind, int mask1, int mask2){
    if(ind == n+m){
        return iscommon(mask1, mask2);
    }
    if(dp[ind][mask1][mask2] != -1)
        return dp[ind][mask1][mask2];
    long long int ans = 0;
    //fill Alice's elements
    int i,j,k;
    if(ind <n){
        forl(i,1,7){
            ans += doit(ind+1, mask1|(1<<i), mask2);
        }
    }
    else{//fill Bob's elements
        forl(i,1,7){
            ans += doit(ind+1, mask1, mask2|(1<<i));
        }
    }
    
    dp[ind][mask1][mask2] = ans;
    return ans;
}
class DisjointDiceValues {
    public:
    double getProbability(int A, int B) {
        long long int total = pow(6, A+B);
        n = A;
        m = B;
        int i,j,k,a,b;
        forl(i,0,20){
            forl(k,0,130){
                forl(a,0,130){
                    dp[i][k][a] = -1;
                }
            }
        }

        long long int r = doit(0,0,0);
        double ans = r;
        ans /= total;
        return ans;
    }
};

// CUT begin
ifstream data("DisjointDiceValues.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(int A, int B, double __expected) {
    time_t startClock = clock();
    DisjointDiceValues *instance = new DisjointDiceValues();
    double __result = instance->getProbability(A, B);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (double_equal(__expected, __result)) {
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
        int A;
        from_stream(A);
        int B;
        from_stream(B);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, B, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1616154955;
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
        cout << "DisjointDiceValues (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
