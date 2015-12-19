
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
typedef pair<int,int> pii;
typedef vector<pii> vpii;

string to_string(long long x) { stringstream ss; ss << x; return ss.str(); }
long long to_int(const string &s) { stringstream ss; ss << s; long long x; ss >> x; return x; }

#define MAX 100005

int n,m;
vector<string> v;
int dx[] = {0,1,0,-1};
int dy[] = {1,0,-1,0};
bool between(int x, int y){
    return (x>=0&&x<n && y >= 0 && y < m);
}
bool canExit(int a, int b){
    int i;
    forl(i,0,4){
        int x = a+dx[i];
        int y = b+dy[i];
        if(between(x,y) && v[x][y] =='E')
            return true;
    }
    return false;
}

bool canMove(int a, int b){
    int i;
    forl(i,0,4){
        int x = a+dx[i];
        int y = b+dy[i];
        if(between(x,y) && (v[x][y] =='.' || v[x][y] =='E'))
            return true;
    }
    return false;
}
bool canMove2(int a, int b){
    int i;
    forl(i,0,4){
        int x = a+dx[i];
        int y = b+dy[i];
        if(between(x,y) && (v[x][y] =='.'))
            return true;
    }
    return false;
}
class BoardEscapeDiv2 {
    public:
    string findWinner(vector<string> s, int k) {
        
        n = s.size();
        m = s[0].size();
        int tx,ty;
        int i,j;
        v = s;
        forl(i,0,n){
            forl(j,0,m){
                if(s[i][j] == 'T'){
                    tx = i;
                    ty = j;
                    i=n;
                    break;
                }
            }
        }
        if(!canMove(tx,ty)){
            return "Bob";
        }
        if(canExit(tx,ty)){
            return "Alice";
        }
        if(canMove2(tx,ty) && (k%2 == 0)){
            return "Bob";
        }
        
        return "Bob";
    }
};

// CUT begin
ifstream data("BoardEscapeDiv2.sample");

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

bool do_test(vector<string> s, int k, string __expected) {
    time_t startClock = clock();
    BoardEscapeDiv2 *instance = new BoardEscapeDiv2();
    string __result = instance->findWinner(s, k);
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
        vector<string> s;
        from_stream(s);
        int k;
        from_stream(k);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1450455663;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 550 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "BoardEscapeDiv2 (550 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
