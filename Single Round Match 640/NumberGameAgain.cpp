
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


long long int ans;
vector<long long> tab;
set<long long> st;
int k1;
bool deduc[22];
void doit(long long int node, int level)
{
	if(st.find(node) != st.end())
	    return;
	if(level > k1)
	   return;
	ans++;
	doit(2*node, level+1);
	doit(2*node+1, level+1);
}

class NumberGameAgain 
{
    public:
    long long solve(int k, vector<long long> table) 
    {
    	ans = pow(2.0,k) - 2 ;
    	k1 = k;
    	memset(deduc, true, sizeof(deduc));
    	
    	tab = table;
    	int sz,i,j;
    	st.clear();
    	sz = table.size();
    	sort(all(table));
    	reverse(all(table));
    	forl(i,0,sz)
    	{
    		if(deduc[i] == true)
    		{
    			long long int tmp = table[i]/2;
    			
    			while(tmp != 1)
    			{
    				forl(j,i+1,sz)
    				{
    					if(table[j] == tmp && deduc[j] == true)
    					{
    						deduc[i] = false;
    						break;
    					}
    				}
    				
    				tmp /= 2;
    			}
    		}
    	}
    	
    	tab.clear();
    	forl(i,0,sz)
    	{
    		if(deduc[i] == true)
    		{
    			tab.pb(table[i]);
    		}
    	}
    	
    	/*forl(i,0,sz)
    	{
    		st.insert(table[i]);
    	}
    	
    	doit(1, 1);
    	ans--;*/
    	sz = tab.size();
    	forl(i,0,sz)
    	{
    		long long int value = tab[i];
    		int level=1;
    		while(value != 1)
    		{
    			level++;
    			value/=2;
    		}
    		int h = k - level + 1;
    		ans -= pow(2.0,h) - 1;
    	}
    	
        return ans;
    }
};

// CUT begin
ifstream data("NumberGameAgain.sample");

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

bool do_test(int k, vector<long long> table, long long __expected) {
    time_t startClock = clock();
    NumberGameAgain *instance = new NumberGameAgain();
    long long __result = instance->solve(k, table);
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
        int k;
        from_stream(k);
        vector<long long> table;
        from_stream(table);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(k, table, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1418148411;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 600 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "NumberGameAgain (600 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
