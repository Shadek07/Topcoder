#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>

using namespace std;
int grid[51][51];
int n,m;
int dx[] = {0, -1, -1, -1, 0, 1, 1, 1};
int dy[] = {1, 1, 0, -1, -1, -1, 0, 1};
int cnt = 0;
class IslandInALake {
    public:
    bool adjacent(int a, int b){
        int i,x,y;
        for(i=0;i<8;i+=1){
            x = a+dx[i];
            y = b+dy[i];
            if(x >=0 and x<n and y >= 0 and y < m){
                if(grid[x][y] == 1){
                    return true;
                }
            }
        }
        return false;
    }
    void watercnt(int a, int b){
        cnt += 1;
        grid[a][b] = 2;
        int i,x,y;
        for(i=0;i<8;i++){
            x = a+dx[i];
            y = b+dy[i];
            if(x>=0 and x<n and y>=0 and y<m and grid[x][y] == 0 and !adjacent(x,y)){
                watercnt(x,y);
            }
        }
    }
    void makeInvalid(int a, int b){
        int i,j,x,y;
        grid[a][b] = 2;
        for(i=0;i<8;i+=2){
            x = a + dx[i];
            y = b+ dy[i];
            if (x >= 0 and x < n and y >=0 and y<m){
                if(grid[x][y] == 0){
                    makeInvalid(x,y);
                }
            }
        }
    }
    int build(vector<string> country) {
	n = country.size();
	m = country[0].size();
	if(n == 1 or m == 1){
		return 0;
    }
    int i,j,k;
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            if (country[i][j] == '.')
                grid[i][j] = 0;
            else
                grid[i][j]=1;
        }
    }
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            if(i==0 or i==n-1 or j==0 or j==m-1){
                makeInvalid(i,j);
            }
        }
    }
    int ans = 0;

    for(i = 1;i<n-1;i++){
        for(j=1;j<m-1;j++){
            if(grid[i][j] == 0 and !adjacent(i,j)){
                cnt = 0;
                watercnt(i,j);
                ans = max(ans, cnt);
            }
        }
    }
    return ans;
  }
};

// CUT begin
ifstream data("IslandInALake.sample");

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

bool do_test(vector<string> country, int __expected) {
    time_t startClock = clock();
    IslandInALake *instance = new IslandInALake();
    int __result = instance->build(country);
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
        vector<string> country;
        from_stream(country);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(country, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1607162353;
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
        cout << "IslandInALake (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
