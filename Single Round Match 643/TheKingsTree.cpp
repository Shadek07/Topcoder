
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

typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<pii> vpii;

vector<int> adj[51];
int n;
int dp[51][2];
bool ch[51][2];
int mx_level;

vector<int> levels[51];

void dfs(int node, int level)
{
	levels[level].pb(node);
	if(level > mx_level)
	  mx_level = level;
	
	int sz = adj[node].size(),i,j;
	forl(i,0,sz)
	{
		dfs(adj[node][i],level+1);
	}
}

int doit(int node, int col)
{
	if(adj[node].size() == 0)
	     return 1;
	
	if(ch[node][col])
	    return dp[node][col];
	
	int sz = adj[node].size(),i,j;
	int cost = 99999999;
	int tmp;
	forl(i,0,sz)
	{
		
	}
}
class TheKingsTree {
    public:
    int getNumber(vector<int> parent) 
    {
    	int i,j,k;
    	n = parent.size();
    	int a,b;
    	forl(i,0,n)
    	{
    		a = i+1;
    		b = parent[i];
    		adj[b].pb(a);
    	}
    	
    	ms(ch,false);
    	ms(dp,0);
    	mx_level = -1;
    	dfs(0, 0);
    	forl(i,0,levels[mx_level].size())
    	{
    		dp[levels[mx_level][i]][0] = 1;
    		dp[levels[mx_level][i]][1] = 1;
    	}
    	
    	for(i=mx_level -1; i>=0; i--)
    	{
    		forl(j,0,levels[i].size())
    		{
    			int node = levels[i][j];
    			int t1,t2;
    			t1 = t2 = 0;
    			forl(k,0,adj[node].size())
    			{
    				b = adj[node][k];
    				t1 += dp[b][0];
    				t2 += dp[b][1];
    			}
    			dp[node][1] = t1+1;
    			dp[node][0] = t2+1;
    		}
    	}
    	if(dp[0][0] < dp[0][1])
        return dp[0][0];
        return dp[0][1];
    }
};

// CUT begin
ifstream data("TheKingsTree.sample");

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

bool do_test(vector<int> parent, int __expected) {
    time_t startClock = clock();
    TheKingsTree *instance = new TheKingsTree();
    int __result = instance->getNumber(parent);
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
        vector<int> parent;
        from_stream(parent);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(parent, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1419701449;
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
        cout << "TheKingsTree (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
