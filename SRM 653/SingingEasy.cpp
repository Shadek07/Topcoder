
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

#define MAX 2002
#define INF 9999999

int dp[MAX][MAX][2];
int n;
vector<int> v;
//far is the smallest index where a player's last number belongs
int doit(int ind, int far, int isSingle){
    if(ind==n){
        return 0;
    }
    if(dp[ind][far][isSingle] != -1){
        return dp[ind][far][isSingle];
    }
    int &res = dp[ind][far][isSingle];
    res = 1e9;
    int tmp;
    //two players initialized their first number earlier
    if(isSingle == 0){
        //number at 'ind' is gonna taken by player whose last index was at far
        //remember that largest indexed number that is taken by any player before index 'ind' is always 'ind-1'
        tmp = abs(v[far]-v[ind]);
        tmp += doit(ind+1,ind-1,isSingle);
        res = min(res,tmp);
        
        tmp = abs(v[ind-1]-v[ind]);
        tmp += doit(ind+1,far,isSingle);
        res = min(res,tmp);
    }
    else{
        //existing one player is continuing his streak
        tmp = abs(v[ind-1]-v[ind]);
        tmp += doit(ind+1,far,1);
        res = min(res,tmp); 
    
        //2nd player is in the game for the first time from index 'ind'
        tmp = 0;
        tmp += doit(ind+1,ind-1,0); //so now isSingle is false(0)
        res = min(res,tmp);
    }
    return res;
}

class SingingEasy {
    public:
    int solve(vector<int> pitch) {
        n = pitch.size();
        int i;
        ms(dp,-1);
        v = pitch;
        return doit(1,0,1);//number at index 1 is taken by only one player, so isSingle is true
    }
};

// CUT begin
ifstream data("SingingEasy.sample");

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

bool do_test(vector<int> pitch, int __expected) {
    time_t startClock = clock();
    SingingEasy *instance = new SingingEasy();
    int __result = instance->solve(pitch);
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
        vector<int> pitch;
        from_stream(pitch);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(pitch, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1460528160;
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
        cout << "SingingEasy (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
