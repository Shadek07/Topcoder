
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

bool isXPair(char a, char b){
    if(a == 'E' && b == 'W')
        return true;
    if(a == 'W' && b == 'E')
        return true;
   
    return false;
}

bool isYPair(char a, char b){
    
   if(a == 'N' && b == 'S')
        return true;
    if(a == 'S' && b == 'W')
        return true;
    return false;
}

bool isOut[55];
class AntsMeet {
    public:
    int countAnts(vector<int> x, vector<int> y, string direction) {
        int n = x.size();
        int i,j,k;
        ms(isOut,false);
        // find directions dx,dy for each ant:
        map<char, int> chdy;
        chdy['N'] = 1;
        chdy['S'] = -1;
        map<char, int> chdx;
        chdx['E'] = 1;
        chdx['W'] = -1;
        int dx[n];
        int dy[n];
        for ( i=0; i<n; i++) {
            dx[i] = chdx[direction[i]];
            dy[i] = chdy[direction[i]];
        }
        forl(k,0,4001){
            
            forl(i,0,n){
                if(isOut[i])
                    continue;
                forl(j,i+1,n){
                    if(isOut[j])
                        continue;
                    if((2*x[i] + dx[i]*k == 2*x[j]+dx[j]*k) && (2*y[i]+dy[i]*k == 2*y[j]+dy[j]*k)){
                        isOut[i] = isOut[j] = true;
                    }
                }
            }
        }
        
        int cnt=0;
        forl(i,0,n){
            if(isOut[i]==false)
                cnt++;
        }
        return cnt;
    }
};

// CUT begin
ifstream data("AntsMeet.sample");

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

bool do_test(vector<int> x, vector<int> y, string direction, int __expected) {
    time_t startClock = clock();
    AntsMeet *instance = new AntsMeet();
    int __result = instance->countAnts(x, y, direction);
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
        vector<int> x;
        from_stream(x);
        vector<int> y;
        from_stream(y);
        string direction;
        from_stream(direction);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, y, direction, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1465620388;
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
        cout << "AntsMeet (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
