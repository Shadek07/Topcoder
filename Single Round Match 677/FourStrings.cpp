
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
#define INF 9999999

int getCount(string a, string b){
    int n = a.size();
    int m = b.size();
    int mn = min(m,n);
    int i,j;
    for(i = n-mn; i<n;i++){
         bool ok=true;
         int k=0;
        for(j=i;j<n;j++){
            if(a[j] != b[k]){
                ok=false;
                break;
            }
            k++;
        }
        if(ok){
            return n-i;
        }
    }
    return 0;
}
class FourStrings {
    public:
    int shortestLength(string a, string b, string c, string d) {
        string s[4];
        s[0] = a;
        s[1] = b;
        s[2] = c;
        s[3] = d;
        int arr[4] = {0,1,2,3};
        int ans = 999999;
        int total = a.size() + b.size() + c.size() + d.size();
        size_t found;
        do{
            int cnt = 0;
            cnt = s[arr[0]].size();
            string str = s[arr[0]];
            int gt;
            if(str.find(s[arr[1]]) == string::npos){
                gt = getCount(str, s[arr[1]]);
                str += s[arr[1]].substr(gt,100);
            }
            if(str.find(s[arr[2]]) == string::npos){
                gt = getCount(str, s[arr[2]]);
                str += s[arr[2]].substr(gt,100);
            }
            if(str.find(s[arr[3]]) == string::npos){
                gt = getCount(str, s[arr[3]]);
                str += s[arr[3]].substr(gt,100);
            }
            ans = min(ans,str.size());
        }while(next_permutation(arr,arr+4));
        
        return ans;
    }
};

// CUT begin
ifstream data("FourStrings.sample");

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

bool do_test(string a, string b, string c, string d, int __expected) {
    time_t startClock = clock();
    FourStrings *instance = new FourStrings();
    int __result = instance->shortestLength(a, b, c, d);
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
        string a;
        from_stream(a);
        string b;
        from_stream(b);
        string c;
        from_stream(c);
        string d;
        from_stream(d);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(a, b, c, d, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1451149753;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 550 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "FourStrings (550 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
