

#pragma comment(linker,"/STACK:16777216")
#pragma  warning ( disable: 4786)
#include <bits/stdc++.h>
using namespace std;

#define forl(i,a,b) for ( i = a; i < b; i++)
#define ms(a,b) memset((a),(b),sizeof(a))

int dp[(1<<13)+1][14][14];
int n;
vector<string> v;
int doit(int mask, int r, int g){ 
    //r is number of red edge taken, g is number of green edge taken
    //mask is vertices that are already taken in spanning tree
    int a = (1<<n)-1;
    if(mask == a){
        return r==n/3 && g == n/3;
    }
    if(dp[mask][r][g] != -1)
        return dp[mask][r][g];
    int i,j,k;
    bool ok=false;
    //prim spanning tree logic
    for(i=0;i<n;i++){
        if((mask&(1<<i))){ // a vertex that is already in spanning tree
            for(j=0;j<n;j++){
                if((mask&(1<<j)) == 0){ // a vertex that is not in spanning tree
                    if(v[i][j] != '.'){
                        int r1 = 0;
                        int g1 = 0;
                        r1 = v[i][j] == 'R';
                        g1 = v[i][j] == 'G';
                        ok |= doit(mask|(1<<j),r+r1,g+g1); //add this new vertex in spanning tree
                    }
                }
            }
        }
    }
    dp[mask][r][g] = ok;
    return ok;
}

class RGBTree {
    public:
    string exist(vector<string> G) {
        ms(dp,-1);
        n = G.size();
        v = G;
        if(doit(1,0,0)){
            return "Exist";
        }
        return "Does not exist";
    }
};

// CUT begin
ifstream data("RGBTree.sample");

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

bool do_test(vector<string> G, string __expected) {
    time_t startClock = clock();
    RGBTree *instance = new RGBTree();
    string __result = instance->exist(G);
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
        vector<string> G;
        from_stream(G);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(G, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1459136495;
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
        cout << "RGBTree (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
