
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
typedef pair<int,string> pis;
typedef vector<pii> vpii;

string to_string(long long x) { stringstream ss; ss << x; return ss.str(); }
long long to_int(const string &s) { stringstream ss; ss << s; long long x; ss >> x; return x; }

#define MAX 100005
#define INF 9999999
map<pis, int> mp;
vector<int> adj[25];
map<pii, char> mpc;
struct state{
    int node;
    string s;
};

bool isPal(string s){
    string res = s;
    reverse(all(s));
    return s == res;
}
class PalindromePath {
    public:
    int shortestLength(int n, vector<int> a, vector<int> b, string c) 
    {
        int n1 = a.size();
        int i,j,k,x,y;
        mpc.clear();
        mp.clear();
        forl(i,0,n1){
            adj[a[i]].pb(b[i]);
            adj[b[i]].pb(a[i]);
            mpc[make_pair(a[i],b[i])] = c[i];
            mpc[make_pair(b[i],a[i])] = c[i];
        }
        queue<state> pq;
        state st;
        st.node = 0;
        st.s = "";
        pq.push(st);
        int ans = -1;
        while(!pq.empty()){
            state cur = pq.front();
            int c = cur.node;
            string s = cur.s;
            if(isPal(s) && c == 1){
                ans = s.size();
                break;
            }
            pq.pop();
            forl(i,0,adj[c].size()){
                int n = adj[c][i];
                pii pi = make_pair(c, n);
                string ns = s + mpc[pi];
                if(!mp[make_pair(n,ns)]){
                   state stn;
                   stn.node = n;
                   stn.s = ns;
                   pq.push(stn);
                   mp[make_pair(n,ns)] = 1;
               }
                
            }
        }
        return ans;
    }
};

// CUT begin
ifstream data("PalindromePath.sample");

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

bool do_test(int n, vector<int> a, vector<int> b, string c, int __expected) {
    time_t startClock = clock();
    PalindromePath *instance = new PalindromePath();
    int __result = instance->shortestLength(n, a, b, c);
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
        vector<int> a;
        from_stream(a);
        vector<int> b;
        from_stream(b);
        string c;
        from_stream(c);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, a, b, c, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1451151619;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "PalindromePath (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
