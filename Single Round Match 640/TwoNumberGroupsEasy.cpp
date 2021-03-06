
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


class TwoNumberGroupsEasy {
    public:
    int solve(vector<int> A, vector<int> numA, vector<int> B, vector<int> numB) 
    {
    	vector<int> ch;
    	vector<int> tA,tB;
    	bool fir = true;
    	long long int dist;
    	set<int> st;
    	int sz,sz1,sz2,i,j,k;
    	sz = numA.size();
    	sz1 = sz;
    	forl(i,0,sz)
    	{
    		st.insert(A[i]);
    	}
    	sz = numB.size();
    	sz2 = sz;
    	forl(i,0,sz)
    	{
    		st.insert(B[i]);
    	}
    	
    	set<int>::iterator it;
    	for(it = st.begin(); it != st.end(); it++)
    	{
    		ch.pb(*it);
    	}
    	
    	sz = ch.size();
    	forl(i,0,sz)
    	{
    		int mod = ch[i];
    		if(mod<2)
    		continue;
    		tA = A;
    		tB = B;
    		forl(j,0,sz1)
    		{
    			tA[j] %= mod;
    		}
    		forl(j,0,sz2)
    		{
    			tB[j] %= mod;
    		}
    		
    		map<int, int> cntA;
			map<int, int> cntB;
			forl(j,0,sz1)
			{
				if(cntA[tA[j]])
				   cntA[tA[j]] += numA[j];
			    else
			       cntA[tA[j]] = numA[j];
			}
			
			forl(j,0,sz2)
			{
				if(cntB[tB[j]])
				   cntB[tB[j]] += numB[j];
			    else
			       cntB[tB[i]] = numB[j];
			}
			
			long long int tmp=0;
			set<int> st1;
			forl(j,0,sz1)
			{
				st1.insert(tA[j]);
			}
			
			forl(j,0,sz2)
			{
				st1.insert(tB[j]);
			}
			
			for(it = st1.begin(); it != st1.end(); it++)
			{
				tmp += abs(cntA[*it] - cntB[*it]);
			}
			if(fir)
			dist = tmp;
			else if(tmp < dist)
			dist = tmp;
    		
    	}
    	
        return dist;
    }
};

// CUT begin
ifstream data("TwoNumberGroupsEasy.sample");

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

bool do_test(vector<int> A, vector<int> numA, vector<int> B, vector<int> numB, int __expected) {
    time_t startClock = clock();
    TwoNumberGroupsEasy *instance = new TwoNumberGroupsEasy();
    int __result = instance->solve(A, numA, B, numB);
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
        vector<int> A;
        from_stream(A);
        vector<int> numA;
        from_stream(numA);
        vector<int> B;
        from_stream(B);
        vector<int> numB;
        from_stream(numB);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, numA, B, numB, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1418150829;
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
        cout << "TwoNumberGroupsEasy (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
