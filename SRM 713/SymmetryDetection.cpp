
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

class SymmetryDetection {
    public:
    string detect(vector<string> board) {
        int n = board.size();
        int m = board[0].size();
        if (n==1 && m ==1)
            return "Both";
        //cout << m << endl;
        int i,j;
        bool b = true;
        bool h = true;
        int i1,j1,i2,j2;
        i1= 0;
        j2 = m-1;
        if((m&1) == 1){
            j1 = ((m-1)/2) - 1;
            i2 = ((m-1)/2) + 1;
            //cout << "here\n";
        }else{
            j1 = (m/2) - 1;
            i2 = (m/2);
        }
        //cout << j1 << endl;
        //if(i1 > j1)
        //    b = false;
        fore(i,i1,j1){
            bool ok=true;
            //cout << i << " " << j2-i << endl;
            for(j=0;j<n;j++){
                if(board[j][i] != board[j][j2-i]){
                    //cout << j << " " << i << " " << j2-i << " " << board[j][i]  << " " << board[j][j2-i] << endl;
                    ok=false;
                    break;
                }
            }
            if(ok==false){
                b = false;
                break;
            }
        }

        i1= 0;
        j2 = n-1;
        if((n&1) == 1){
            j1 = ((n-1)/2) - 1;
            i2 = ((n-1)/2) + 1;
        }else{
            j1 = (n/2) - 1;
            i2 = (n/2);
        }
        //if(i1 > j1)
        //    h = false;
        fore(i,i1,j1){
            bool ok=true;
            for(j=0;j<m;j++){
                if(board[i][j] != board[j2-i][j]){
                    ok=false;
                    break;
                }
            }
            if(ok==false){
                h = false;
                break;
            }
        }

        if(b && h)
        return "Both";
        if (b)
        return "Vertically symmetric";
        if (h)
            return "Horizontally symmetric";
        return "Neither";
    }
};

// CUT begin
ifstream data("SymmetryDetection.sample");

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

bool do_test(vector<string> board, string __expected) {
    time_t startClock = clock();
    SymmetryDetection *instance = new SymmetryDetection();
    string __result = instance->detect(board);
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
        vector<string> board;
        from_stream(board);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(board, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1494744742;
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
        cout << "SymmetryDetection (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
