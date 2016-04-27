
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


string dp[51][26][18][3][3];
bool vis[51][26][18][3][3];
string ans;
int n;
int A,B,C;
bool isOk(string s){
    int sz = s.size();
    int i;
    forl(i,0,sz){
        if(s[i] == 'D')
            return false;
    }
    return true;
}
string doit(int prev1, int prev2, int a, int b, int c){
    if(a+b+c == n){
        return "";
    }
    if(vis[a][b][c][prev1][prev2]){
        return dp[a][b][c][prev1][prev2];
    }
    
    vis[a][b][c][prev1][prev2] = true;
    string &s = dp[a][b][c][prev1][prev2];
    s = "D";
    string tmp;
    if(a+1<=A){
        tmp = 'A'+doit(prev2,0,a+1,b,c);
        if(isOk(tmp) && tmp.compare(s)<0)
            s = tmp;
    }
    if(b+1<=B && prev2 != 1){
        tmp = 'B' + doit(prev2,1,a,b+1,c);
        if(isOk(tmp) && tmp.compare(s)<0)
            s = tmp;
    }
    if(c+1<=C && prev1 != 2 && prev2 != 2){
        tmp = 'C' + doit(prev2,2,a,b,c+1);
        if(isOk(tmp) && tmp.compare(s)<0)
            s = tmp;
    }
    
    dp[a][b][c][prev1][prev2] = s;
    return s;
    
}


class ThreeProgrammers {
    public:
    string validCodeHistory(string code) {
        n = code.size();
        if(n==1)
            return code;
        ms(vis,false);
        A = B = C = 0;
        int i;
        forl(i,0,n){
            if(code[i]=='A'){
                A++;
            }
            else if(code[i] == 'B'){
                B++;
            }else{
                C++;
            }
        }
        string s = "D";
        string tmp;
        if(A>=2){
            tmp = "AA"+ doit(0,0,2,0,0);
            if(isOk(tmp) && tmp.compare(s)<0)
            s = tmp;
        }
        if(A>=1 && B>=1){
            tmp = "AB"+ doit(0,1,1,1,0);
            if(isOk(tmp) && tmp.compare(s)<0)
            s = tmp;
            tmp = "BA"+ doit(1,0,1,1,0);
            if(isOk(tmp) && tmp.compare(s)<0)
            s = tmp;
        }
        if(A>=1 && C>=1){
            tmp = "AC"+ doit(0,2,1,0,1);
            if(isOk(tmp) && tmp.compare(s)<0)
            s = tmp;
            tmp = "CA"+ doit(2,0,1,0,1);
            if(isOk(tmp) && tmp.compare(s)<0)
            s = tmp;
        }
        if(B>=1 && C >= 1){
            tmp = "BC"+ doit(1,2,0,1,1);
            if(isOk(tmp) && tmp.compare(s)<0)
            s = tmp;
            tmp = "CB"+ doit(2,1,0,1,1);
            if(isOk(tmp) && tmp.compare(s)<0)
            s = tmp;
        }
        
        if(!isOk(s))
            return "impossible";
        return s;
    }
};



// CUT begin
ifstream data("ThreeProgrammers.sample");

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

bool do_test(string code, string __expected) {
    time_t startClock = clock();
    ThreeProgrammers *instance = new ThreeProgrammers();
    string __result = instance->validCodeHistory(code);
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
        string code;
        from_stream(code);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(code, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1461788943;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "ThreeProgrammers (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
