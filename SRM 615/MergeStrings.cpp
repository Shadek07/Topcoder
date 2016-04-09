
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

#define MAX 55
#define INF 9999999

string dp[MAX][MAX];
bool ch[MAX][MAX];
int n;
string S,A,B;
string doit(int a, int b){
    if(a+b==n){
        return "";
    }
    if(ch[a][b]){
        return dp[a][b];
    }
    string ans="[";
    string tmp;
    if(S[a+b] == '?'){
        if(a < A.size() && (doit(a+1,b).compare("[")) != 0){
            tmp = A[a] + doit(a+1,b);
            if(ans.compare(tmp)>0){
                ans = tmp;
            }
        }
        if(b < B.size() && (doit(a,b+1).compare("[")) != 0){
            tmp = B[b] + doit(a,b+1);
            if(ans.compare(tmp)>0){
                ans = tmp;
            }
        }
        
    }else{
        if(S[a+b] == A[a]){
            if(a < A.size() && (doit(a+1,b).compare("[")) != 0){
                tmp = A[a] + doit(a+1,b);
                if(ans.compare(tmp)>0){
                    ans = tmp;
                }
            }
        }
        if(S[a+b] == B[b]){
            if(b <B.size()&&  (doit(a,b+1).compare("[")) != 0){
                tmp = B[b] + doit(a,b+1);
                if(ans.compare(tmp)>0){
                    ans = tmp;
                }
            }
        }
    }
    //if(ans.compare("[") == 0)
        //ans = "";
    ch[a][b] = true;
    return dp[a][b] = ans;
    
}

class MergeStrings {
    public:
    string getmin(string s, string a, string b) {
        ms(ch,false);
        n = s.size();
        S = s,A=a,B=b;
        if((doit(0,0).compare("[")) != 0){
            return doit(0,0);
        }
        return "";
    }
};

// CUT begin
ifstream data("MergeStrings.sample");

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

bool do_test(string S, string A, string B, string __expected) {
    time_t startClock = clock();
    MergeStrings *instance = new MergeStrings();
    string __result = instance->getmin(S, A, B);
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
        string S;
        from_stream(S);
        string A;
        from_stream(A);
        string B;
        from_stream(B);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(S, A, B, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1460117002;
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
        cout << "MergeStrings (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
