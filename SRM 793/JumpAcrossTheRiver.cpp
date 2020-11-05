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

class JumpAcrossTheRiver {
    public:
    bool isPossible(long long int L, int N, int J, vector<int> points){
        int cnt = 0;
        long long int csum = 0;
        int i = 1;
        while (i<= N){
            long long int d = points[i] - points[i-1];
            if (csum + d > L){
                cnt += 1;
                if (cnt > J){
                    return false;
                }
                csum = d;
            }else
                csum += d;
            i += 1;
        }
        if(csum > 0)
            cnt += 1;
        if (cnt > J)
            return false;
        return true;
    }
    long long minLength(int N, int M, int J) {
        vector<int> points (N+1, 0);
        long long int low = 1;
        long long int high = pow(10, 16);
        int i;
        for (i = 1; i<=N;i++){
            long long int j = i-1;
            points[i] = points[i-1] + (1 + (j*j)%M );
            low = max(low, (1 + (j*j)%M));
        }
        long long int ans = 0;
        /*if(N <= 15){
            for(i = 0;i<=N;i++){
            cout << " " << points[i] << endl;
            }
        }*/

        while (low <= high){
            long long int mid = (low+high) / 2;
            if (isPossible(mid, N, J, points)){
                ans = mid;
                high = mid-1;
            }else{
                low = mid+1;
            }

        }
        return ans;
    }
};

// CUT begin
ifstream data("JumpAcrossTheRiver.sample");

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

bool do_test(int N, int M, int J, long long __expected) {
    time_t startClock = clock();
    JumpAcrossTheRiver *instance = new JumpAcrossTheRiver();
    long long __result = instance->minLength(N, M, J);
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
        int N;
        from_stream(N);
        int M;
        from_stream(M);
        int J;
        from_stream(J);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, M, J, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1604582177;
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
        cout << "JumpAcrossTheRiver (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
