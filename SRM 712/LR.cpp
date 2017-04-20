#include <cstdio>
#include <cmath>
#include <cstring>

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

bool isEqual(vector<long long> a, vector<long long> b){
    int i;
    int n = a.size();
    forl(i,0,n){
        if(a[i] != b[i])
            return false;
    }
    return true;
}

class LR {
    public:
    string construct(vector<long long> s, vector<long long> t)
    {
        string no = "No solution";
        if(isEqual(s,t)){
            return "";
        }
        bool allZero = true;
        int i,j,k,n;
        n = s.size();
        long long int z = 0;
        forl(i,0,n){
            if(s[i] != z){
                allZero = false;
                break;
            }
        }
        if(allZero)
            return no;
        forl(i,0,n){
            if(s[i] > t[i])
                return no;
        }
        int step = 0;
        int l,r;
        for(step = 1;step <= 100; step++){
            for(l=0;l<=step;l++){
                r = step-l;
                vector<long long> v = s;
                vector<long long> tmp = s;
                bool ok=true;
                for(j=0;j<l;j++){
                    forl(i,0,n){
                        if(i==0)
                            tmp[i] = v[i] + v[n-1];
                        else
                            tmp[i] = v[i] + v[i-1];
                        if(tmp[i] > t[i]){
                            ok=false;
                            j=l;
                            break;
                        }
                   }
                   v = tmp;
                }
                for(j=0;j<r;j++){
                    forl(i,0,n){
                        if(i==n-1)
                            tmp[i] = v[i] + v[0];
                        else
                            tmp[i] = v[i] + v[i+1];
                        if(tmp[i] > t[i]){
                            ok=false;
                            j=r;
                            break;
                        }
                   }
                   v = tmp;
                }
                if(ok && isEqual(v,t))
                {
                    string ans = "";
                    forl(i,0,l)
                    ans = ans + 'L';
                    forl(i,0,r)
                    ans = ans+'R';
                    return ans;
                }
            }
        }
        return no;
    }
};

// CUT begin
ifstream data("LR.sample");

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

bool do_test(vector<long long> s, vector<long long> t, string __expected) {
    time_t startClock = clock();
    LR *instance = new LR();
    string __result = instance->construct(s, t);
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
        vector<long long> s;
        from_stream(s);
        vector<long long> t;
        from_stream(t);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s, t, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1492521071;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 300 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "LR (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
