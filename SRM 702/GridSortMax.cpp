
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

#define MAX 55

class GridSortMax {
    public:
    string findMax(int n, int m, vector<int> grid) {
        if(n == 1 or m == 1){
            string a(n*m,'1');
            return a;
        }
        bool rb[MAX];
        bool cb[MAX];
        pii pos[2505]; //pos[v] is position of value v
        ms(rb,false);
        ms(cb,false);
        int i,j,k,a;
        int ind;
        int arr[MAX][MAX];
        forl(i,0,n){
            forl(j,0,m){
                ind = i*m + j;
                pos[grid[ind]] = make_pair(i,j);
                arr[i][j] = grid[ind];
            }
        }
        fore(k,1,n*m){
            int dr = (k-1)/m;
            int dc = (k-1)%m;

            pii ps = pos[k];
            if(ps.first == dr && ps.second == dc){ //in place
                rb[dr] = true;
                cb[dc] = true;
                continue;
            }
            bool ok1 = false,ok2=false;
            if(dr == ps.first )
                ok1 = true;
            if(dc == ps.second)
                ok2 = true;
            if(dr != ps.first && rb[dr] == false && rb[ps.first] == false){ //change row
                forl(a,0,m){
                    int v1 = arr[dr][a];
                    int v2 = arr[ps.first][a];
                    pii ps1 = pos[v1],ps2 = pos[v2];
                    ps1.first = ps.first;
                    ps2.first = dr;
                    pos[v1] = ps1;
                    pos[v2] = ps2;
                    swap(arr[dr][a], arr[ps.first][a]);
                }
                ok1 = true;
            }
            if(dc != ps.second and cb[dc] == false and cb[ps.second] == false){ //change column
                forl(a,0,n){
                    int v1 = arr[a][dc];
                    int v2 = arr[a][ps.second];
                    pii ps1 = pos[v1],ps2 = pos[v2];
                    ps1.second = ps.second;
                    ps2.second = dc;
                    pos[v1] = ps1;
                    pos[v2] = ps2;
                    swap(arr[a][dc], arr[a][ps.second]);
                }
                ok2 = true;
            }
            if(ok1 && ok2){
                rb[dr] = true;
                cb[dc] = true;
            }

        }
        string ans = "";
        fore(k,1,n*m){
            int dr1 = (k-1)/m;
            int dc1 = (k-1)%m;

            pii pss = pos[k];
            if(pss.first == dr1 && pss.second == dc1){ //in place
                ans += "1";
            }else{
                ans += "0";
            }
        }
        return ans;
    }
};

// CUT begin
ifstream data("GridSortMax.sample");

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

bool do_test(int n, int m, vector<int> grid, string __expected) {
    time_t startClock = clock();
    GridSortMax *instance = new GridSortMax();
    string __result = instance->findMax(n, m, grid);
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
        int m;
        from_stream(m);
        vector<int> grid;
        from_stream(grid);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, m, grid, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1479187966;
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
        cout << "GridSortMax (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
