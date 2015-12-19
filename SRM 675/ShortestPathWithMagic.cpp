
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


class ShortestPathWithMagic {
    public:
        struct state{
            int node;
            int potion;
            int dist;
            bool operator < ( const state& p ) const {
                return dist > p.dist;
            }
        };
        int dis[51][51];
    double getTime(vector<string> v, int k)
    {
        state st,tmp;
        st.node = 0;
        st.potion = k;
        st.dist = 0;
        priority_queue<state> pq;
        pq.push(st);
        int i,j,n;
        n = v.size();
        forl(i,0,51){
            forl(j,0,51)
           dis[i][j] = 999999;
        }
        dis[0][k] = 0;
        while(!pq.empty()){
            st = pq.top();
            pq.pop();
            int pot = st.potion;
            forl(i,0,n){
                if(i != st.node){
                    if(pot){
                        if(st.dist + (v[st.node][i]-'0') < dis[i][pot-1]){
                            dis[i][pot-1] = st.dist + (v[st.node][i]-'0');
                            tmp.dist = dis[i][pot-1];
                            tmp.node = i;
                            tmp.potion = pot-1;
                            pq.push(tmp);
                        }
                    }
                    if(st.dist + 2*(v[st.node][i]-'0') < dis[i][pot]){
                            dis[i][pot] = st.dist + 2*(v[st.node][i]-'0');
                            tmp.dist = dis[i][pot];
                            tmp.node = i;
                            tmp.potion = pot;
                            pq.push(tmp);
                    }
                    
                }
            }
        }
        int ans=999999;
        forl(i,0,k+1){
            ans = min(ans,dis[1][i]);
        }
        return ans/2.0;
        
    }
};

// CUT begin
ifstream data("ShortestPathWithMagic.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(vector<string> dist, int k, double __expected) {
    time_t startClock = clock();
    ShortestPathWithMagic *instance = new ShortestPathWithMagic();
    double __result = instance->getTime(dist, k);
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
        vector<string> dist;
        from_stream(dist);
        int k;
        from_stream(k);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(dist, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1450505948;
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
        cout << "ShortestPathWithMagic (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
