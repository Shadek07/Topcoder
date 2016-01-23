
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
#include<climits>
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
typedef vector<string> vs;
typedef pair<int,int> pii;
typedef vector<pii> vpii;

typedef pair<int, string> pis;

string to_string(long long x) { stringstream ss; ss << x; return ss.str(); }
long long to_int(const string &s) { stringstream ss; ss << s; long long x; ss >> x; return x; }

#define MAX 100005
#define INF 9999999

string getName(string s){
    string s1 = "";
    int i;
    i = 0;
    while(s[i] != ' '){
        s1 += s[i];
        i++;
    }
    return s1;
}
pii getPair(string s, int start, int en){
    int sc = 0;
    int t=0;
    int i = 0;
    forl(i,start,en){
        if(s[i] == '/'){
            i++;
            break;
        }
        sc = sc*10 + (s[i]-'0');
    }
    for(;i<=en;i++){
        t = t*10 + (s[i]-'0');
    }
    return make_pair(sc,t);
}
int getIndex(string names[101], int sz, string name){
    int i;
    forl(i,0,sz){
        if(names[i] == name)
            return i;
    }
}
int comp(pis p1, pis p2){
    if(p1.first > p2.first)
        return 1;
    else if(p1.first == p2.first && p1.second.compare(p2.second) < 0)
        return 1;
    return 0;
}
class ContestScoreboard {
    public:
    vector<int> findWinner(vector<string> scores) 
    {
        string names[101];
        int sz = scores.size();
        vector< vector< pii> > sc(sz);
        vector<int> ans(sz,0);
        int i,j,k;
        vector<int> all_times;
        forl(i,0,sz){
            names[i] = getName(scores[i]);
            forl(j,3,scores[i].size()){
                if(scores[i][j] == ' '){
                    j++;
                    break;
                }
            }
            k = j;
            pii p1;
            int stringsz = scores[i].size();
            int start = k;
            while(true){
                if(j == stringsz || scores[i][j] == ' '){
                    p1 = getPair(scores[i], start, j-1);
                    all_times.pb(p1.second+1);
                    sc[i].pb(p1);
                    start = j+1;
                    if(j == stringsz)
                        break;
                    j = j+1;
                }else{
                    j++;
                }
            }
        }
        all_times.pb(1);
        sort(all(all_times));
       
        int timesz = all_times.size();
        forl(i,0,sz){
            sort(all(sc[i]));
        }
        forl(j,0,timesz){
            vector<pis> vpis;
            //cout << timesz[j] << endl;
            forl(i,0,sz){
                int val = 0;
                int tolSZ = sc[i].size();
                k=0;
                while(k<tolSZ){
                    if(sc[i][k].second < all_times[j]){
                        val += sc[i][k].first;
                    }
                    k++;
                }
                vpis.pb(make_pair(val, names[i]));
            }
            sort(all(vpis), comp);
            int ind = getIndex(names, sz, vpis[0].second);
            ans[ind] = 1; 
        }
        return ans;
    }
};

// CUT begin
ifstream data("ContestScoreboard.sample");

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

template <typename T> string to_string(vector<T> ts) {
    stringstream s;
    s << "[ ";
    for (int i = 0; i < ts.size(); ++i) {
        if (i > 0) s << ", ";
        s << to_string(ts[i]);
    }
    s << " ]";
    return s.str();
}

bool do_test(vector<string> scores, vector<int> __expected) {
    time_t startClock = clock();
    ContestScoreboard *instance = new ContestScoreboard();
    vector<int> __result = instance->findWinner(scores);
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
        vector<string> scores;
        from_stream(scores);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(scores, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1453292615;
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
        cout << "ContestScoreboard (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
