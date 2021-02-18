#include <bits/stdc++.h>
using namespace std;

int dist[25][25][15];

class State{
  int cost;
  int x, y;

public:
  State()
  {
     cost = 0;
  }
  State( int r, int c, int cs)
  {
     cost = cs;
     x = r;
     y = c;
  }

  int getx(){
      return x;
  }
  int gety(){
      return y;
  }

  int getcost() const
  {
     return cost;
  }
};

// Determine priority.
bool operator<(const State &a, const State &b)
{
  return a.getcost() > b.getcost();
}

class PoisonedSwamp {
    public:
    string cross(vector<string> swamp) {
        int i,j,k;
        for(i = 0;i<=20;i++){
            for(j=0;j<=20;j++){
                for(k=0;k<=10;k++){
                    dist[i][j][k] = -1;
                }
            }
        }

       priority_queue<State> mypq;
       mypq.push(State(0,0,0));
       int n,m;
       n = swamp.size();
       m = swamp[0].length();

       int dx[] = {0, -1, 0, 1};
       int dy[] = {1, 0, -1, 0};

       State curr_state;

       while (!mypq.empty())
	  {
		 curr_state =  mypq.top();
		 mypq.pop();
		 int x,y;
		 x = curr_state.getx();
		 y = curr_state.gety();
		 int c = curr_state.getcost();
		 if(x == n-1 && y == m-1){
            return "possible";
		 }
		 for(k = 0;k<4;k++){
            int a,b;
            a = x+dx[k];
            b = y+dy[k];
            if (a < 0 || a >= n)
                continue;
            if(b < 0 || b>= m)
                continue;
            int v = 0;
            if (swamp[a][b] == '#')
                continue;
            if(swamp[a][b] >= '1' and swamp[a][b] <= '9'){
                v = swamp[a][b] - '0';
            }
            int newc = c+v;
            if(swamp[a][b] == 'S'){
                newc = 0;
            }
            if(newc >= 10)
                continue;
            if (dist[a][b][newc] != -1)
                continue;
            dist[a][b][newc] = 1;
            mypq.push(State(a,b,newc));
		 }
	  }
      return "impossible";
    }
};

// CUT begin
ifstream data("PoisonedSwamp.sample");

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

bool do_test(vector<string> swamp, string __expected) {
    time_t startClock = clock();
    PoisonedSwamp *instance = new PoisonedSwamp();
    string __result = instance->cross(swamp);
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
        vector<string> swamp;
        from_stream(swamp);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(swamp, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1613237598;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 750 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "PoisonedSwamp (750 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
