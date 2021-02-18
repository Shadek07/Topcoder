//solved after contest

#include<bits/stdc++.h>
using namespace std;

class SlotMachineHacking {
    public:
    int win(vector<string> reels, vector<int> steps) {
        map<string, int> uniq_configs;
        string jackpot = ""; //jackpot string: all 'c'
        int i,j,k;
        for(i = 0;i<reels.size();i++)        
        {
            jackpot = jackpot + 'c';
        }
        int cnt = 0;
        int n = reels.size();
        int pos[n]; //indices of current display letters for all reel strings
        for(i=0;i<n;i++)
        {
            pos[i] = 0;
        }
	auto newpos = [&pos, &reels, &steps](int n){
	    int i;	
            for(i=0;i<n;i++){
                pos[i] = (pos[i]+ steps[i])%reels[i].size();
            } 
	};
        while (true){
            string curr_display = "";
	    newpos(n);
            for(i=0;i<n;i++)
            {
                curr_display += reels[i][pos[i]];
            }
            if(curr_display == jackpot)  //current display matches jackpot
                return cnt;
	    string curr_config= "";
	    for(i = 0;i<n;i++){
		curr_config = curr_config + char(('a'+pos[i]));	
	    }
	    if(uniq_configs[curr_config]) 
		 return -1;
            uniq_configs[curr_config] = 1;
            cnt += 1;
        }
        return -1;
    }
};

// CUT begin
ifstream data("SlotMachineHacking.sample");

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

bool do_test(vector<string> reels, vector<int> steps, int __expected) {
    time_t startClock = clock();
    SlotMachineHacking *instance = new SlotMachineHacking();
    int __result = instance->win(reels, steps);
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
        vector<string> reels;
        from_stream(reels);
        vector<int> steps;
        from_stream(steps);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(reels, steps, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1613240253;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 400 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "SlotMachineHacking (400 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
