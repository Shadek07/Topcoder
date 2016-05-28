
#pragma comment(linker,"/STACK:16777216")
#pragma  warning ( disable: 4786)
#include <bits/stdc++.h>
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

#define MAX 100005
#define INF 9999999

int ncr[51][51];

int pwMod(int a){
    int value=1;
    int i;
    forl(i,0,a){
        value = (value*10)%9;
    }
    return value; //it is always 1
}

int two_power(int n){
    int v = 1;
    int i;
    forl(i,0,n){
        v = (v*2)%9;
    }
    return v;
}
class LuckyRemainder {
    public:
    int getLuckyRemainder(string X) 
    {
        int n = X.size();
        int i,j,k;
        ncr[0][0] = 1;
        for(i=1;i<=50;i++){
            ncr[i][0] = 1;
            ncr[0][i] = 0;
        }
        for(i=1;i<=50;i++){
            for(j=1;j<=50;j++){
                if(j>i){
                    ncr[i][j] = 0;
                }
                else{
                    ncr[i][j] = (ncr[i-1][j] + ncr[i-1][j-1])%9;
                }
            }
        }
        long long int ans=0;
        for(i=0;i<n;i++){
            int value = X[i]-'0';
            long long int t = value;
            //total number of digits after digit at position i is (n-i-1)
            for(j=0;j<=n-i-1;j++){
                //remove total j digits out of (n-i-1)
                //number of ways to remove j digits is ncr[n-i-1][j]
                t = value*pwMod(n-i-1-j); //10^x, x=n-i-1-j
                t = (t*ncr[n-i-1][j])%9;
                //in the left side of position i, we can remove any number of digits
                //here total ways: iC0+iC1+iC2+....+iCi = 2^i
                t = (t*two_power(i))%9; //2^i
                ans = (ans+t)%9;
            }
        }
        return ans;
    }
};

// CUT begin
ifstream data("LuckyRemainder.sample");

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

bool do_test(string X, int __expected) {
    time_t startClock = clock();
    LuckyRemainder *instance = new LuckyRemainder();
    int __result = instance->getLuckyRemainder(X);
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
        string X;
        from_stream(X);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(X, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1464436825;
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
        cout << "LuckyRemainder (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
