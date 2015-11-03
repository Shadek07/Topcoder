
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

int num_cut(int sz, int make)
{
    if(make > sz)
        return -1;
    if(sz == make)
        return 0;
    int cnt=0;
    while(true)
    {
        if(sz == make)
            return cnt;
        if(sz < make)
            return -1;
        int sz1 = (sz+1)/2;
        
        if(make >= sz1)
        {
            cnt++;
            return cnt;
        }
        else
            cnt++;
        if(sz%2)
            sz = (sz+1)/2;
        else
        sz /= 2;     
    }
}

class FoldingPaper2 {
    public:
    int solve(int W, int H, int A)
    {
        unsigned long long int a,b,c,area;
        a =W;
        b = H;
        c = a*b;
        area = A;
        if(area > c)
            return -1;
        int i,j;
        int ans = 99999999;
        for(i = 1;i*i <= A;i++)
        {
            if(A%i == 0)
            {
                a = i;
                b = A/i;
                int a1,b1;
                a1 = num_cut(W,a);
                b1 = num_cut(H,b);
                int prev = ans;
                if(a1 != -1 && b1 != -1)
                {
                    ans = min(ans,a1+b1);
                }
                if(prev != ans && ans == 7)
                {
                    cout << W << " " << a << " " << a1 << endl;
                    cout << H << " " << b << " " << b1 << endl;
                }
                a1 = num_cut(H,a);
                b1 = num_cut(W,b);
                prev = ans;
                if(a1 != -1 && b1 != -1)
                {
                    ans = min(ans,a1+b1);
                }
                if(prev != ans && ans == 7)
                {
                    cout << "-" << H << " " << a << " " << a1 << endl;
                    cout << "-" << W << " " << b << " " << b1 << endl;
                }
            }
        }
        
        if(ans == 99999999)
            return -1;
        return ans;
    }
};

// CUT begin
ifstream data("FoldingPaper2.sample");

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

bool do_test(int W, int H, int A, int __expected) {
    time_t startClock = clock();
    FoldingPaper2 *instance = new FoldingPaper2();
    int __result = instance->solve(W, H, A);
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
        int W;
        from_stream(W);
        int H;
        from_stream(H);
        int A;
        from_stream(A);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(W, H, A, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1428592633;
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
        cout << "FoldingPaper2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
