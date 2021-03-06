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
int dp[505][51][51];
vector<int> v;
int n;
int avg, med;

int doit(int csum, int ind, int lessthan){
    if(ind == n){
        if(csum >= n*avg and lessthan <= (n-1)/2){
            return 0;
        }else{
            return INT_MAX;
        }
    }
    int remaining = n-ind;
    if(csum + remaining*10 < avg*n){
        return INT_MAX;
    }
    if(lessthan > (n-1)/2)
        return INT_MAX;
    if (dp[csum][ind][lessthan] != -1){
        return dp[csum][ind][lessthan];
    }
    int ans = INT_MAX;
    int i;
    forl(i,0,11){
        int tmp = doit(csum + i, ind+1, lessthan+(i<med));
        if(tmp != INT_MAX){
            ans = min(ans, v[ind]*i + tmp);
        }
    }
    dp[csum][ind][lessthan] = ans;
    return ans;
}
class MeanMedian {
    public:
    int minEffort(int needMean, int needMedian, vector<int> d) {
        ms(dp, -1); 
        n = d.size();
        v = d;
        avg = needMean;
        //cout << dp[0][0][0] << endl;
        med = needMedian;
        return doit(0, 0, 0); 
    }
};

// CUT begin
ifstream data("MeanMedian.sample");

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

bool do_test(int needMean, int needMedian, vector<int> d, int __expected) {
    time_t startClock = clock();
    MeanMedian *instance = new MeanMedian();
    int __result = instance->minEffort(needMean, needMedian, d);
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
        int needMean;
        from_stream(needMean);
        int needMedian;
        from_stream(needMedian);
        vector<int> d;
        from_stream(d);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(needMean, needMedian, d, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1614577518;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "MeanMedian (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
