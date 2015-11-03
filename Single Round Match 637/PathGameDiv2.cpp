
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

typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<pii> vpii;


class PathGameDiv2 {
    public:
    int calc(vector<string> board) 
    {
    	int i,j,m;
    	int mx = 0;
    	m = board[0].size();
    	if(m == 1)
    	{
    		if(board[0][0] == '#')
    		
			return 0;
			if(board[1][0] == '#')   		
			return 0;
			return 1;
    	}
    	
    	bool fnd = true;
    	int to=0;
    	if(board[0][0] != '#')
    	{
			i = 0;
			j = 0;
			
			while(true)
			{
				if(j == m-1)
				{
					board[i][j] = 'c';
					break;
				}
				
				if(board[i][j] == '#')
				{
					fnd = false;
					break;
				}
				board[i][j] = 'c';
				
				if(board[i][j+1] != '#')
				{
					//board[i][j+1] = 'c';
					j++;
				}
				else
				{
					if(i == 0)
					i = 1;
					else
					i = 0;
				}
			}
			
		    to=0;
			if(fnd)
			forl(i,0,2)
			{
				forl(j,0,m)
				{
					if(board[i][j] == '.')
					to++;
					if(board[i][j] == 'c')
					   board[i][j] = '.';
				}
			}
			
			mx = max(mx, to);
    	}
 
    	if(board[1][0] == '.')
    	{
    		fnd = true;
    		i = 1;
    		j = 0;
    		while(true)
			{
				if(j == m-1)
				{
					board[i][j] = 'c';
					break;
				}
				
				if(board[i][j] == '#')
				{
					fnd = false;
					break;
				}
				
				board[i][j] = 'c';
				
				if(board[i][j+1] != '#')
				{
					//board[i][j+1] = 'c';
					j++;
				}
				else
				{
					if(i == 0)
					i = 1;
					else
					i = 0;
				}
			}
			to=0;
			if(fnd)
			forl(i,0,2)
			{
				forl(j,0,m)
				{
					if(board[i][j] == '.')
					to++;
					if(board[i][j] == 'c')
					   board[i][j] = '.';
				}
			}
			mx = max(mx, to);
    	}
    	
        return mx;
    }
};

// CUT begin
ifstream data("PathGameDiv2.sample");

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

bool do_test(vector<string> board, int __expected) {
    time_t startClock = clock();
    PathGameDiv2 *instance = new PathGameDiv2();
    int __result = instance->calc(board);
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
        vector<string> board;
        from_stream(board);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(board, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1414076710;
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
        cout << "PathGameDiv2 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
