
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
map<string, int> mp;

int get_A(string s)
{
    int i = 0,sz;
    sz = s.size();
    int j = 0;
    forl(i,0,sz)
    {
        if(s[i] == 'A')
            j++;
    }
    return j;
}
int get_B(string s)
{
    int i = 0,sz;
    sz = s.size();
    int j = 0;
    forl(i,0,sz)
    {
        if(s[i] == 'B')
            j++;
    }
    return j;
}
string rev_s(string s)
{
    string s1 = "";
    int sz = s.size();
    int i;
    for(i=sz-1;i>=0;i--)
        s1 += s[i];
    return s1;
}
class ABBA {
    public:
    string canObtain(string initial, string target) 
    {
        queue<string> pq;
        mp.clear();
        int ind = 1;
        bool found = false;
        mp[initial] = ind++;
        pq.push(initial);
        int n = target.size();
        int i,j;
        int a = get_A(target);
        int b = get_B(target);
        while(!pq.empty())
        {
            string s = pq.front();
            pq.pop();
            int sz = s.size();
            if(s.compare(target) == 0)
            {
                found = true;
                break;
            }
            if(s.size() >= n)
                continue;
            string s1 = s + "A";
            int a1,b1;
            a1 = get_A(s1);
            b1 = get_B(s1);
            string rs = rev_s(s1);
            if(mp[s1] == 0 and a1 <= a and b1 <= b and (target.find(s1,0) != string::npos or target.find(rs,0) != string::npos) )
            {
                mp[s1] = ind++;
                pq.push(s1);
            }
            s1 = "";
            for(i=sz-1;i>=0;i--)
            {
                s1 += s[i];
            }
            s1 += "B";
            a1 = get_A(s1);
            b1 = get_B(s1);
            rs = rev_s(s1);
            if(mp[s1] == 0 and a1 <= a and b1 <= b and (target.find(s1,0) != string::npos or target.find(rs,0) != string::npos))
            {
                mp[s1] = ind++;
                pq.push(s1);
            }           
            
        }
        
        if(!found)
        return "Impossible";
        return "Possible";
    }
};

// CUT begin
ifstream data("ABBA.sample");

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

bool do_test(string initial, string target, string __expected) {
    time_t startClock = clock();
    ABBA *instance = new ABBA();
    string __result = instance->canObtain(initial, target);
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
        string initial;
        from_stream(initial);
        string target;
        from_stream(target);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(initial, target, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1437664807;
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
        cout << "ABBA (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
