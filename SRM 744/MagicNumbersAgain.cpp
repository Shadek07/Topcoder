
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

bool checkValidity(long long int n){
    int i;
    int arr[20];
    long long int a = n;
    i=0;
    while(a){
        arr[i++] = int(a%10);
        a /= 10;
    }
    reverse(arr,arr+i);
    if(i==1)
        return true;
    int j;
    for(j=1;j<i;j++){
        if(j%2 == 0)
        {
            if(arr[j-1] <= arr[j])
                return false;
        }else{
             if(arr[j-1] >= arr[j])
                  return false;

            }
    }
    return true;

}

class MagicNumbersAgain {
    public:
    int count(long long A, long long B)
    {
        long long int a = sqrt(A*1.0);
        long long int b = sqrt(B*1.0);
        if(a*a < A){
            a++;
        }

        cout << a << " " << b << endl;
        long long int i;
        int cnt = 0;
        for(i=a;i<=b;i++){
            long long int c = i*i;
            /*if (c < A or c > B)
                continue;*/
            if(checkValidity(c)){
                cnt++;
                cout << c << endl;
            }
            //cnt += checkValidity(c);
        }
        return cnt;
    }
};

// CUT begin
ifstream data("MagicNumbersAgain.sample");

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

bool do_test(long long A, long long B, int __expected) {
    time_t startClock = clock();
    MagicNumbersAgain *instance = new MagicNumbersAgain();
    int __result = instance->count(A, B);
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
        long long A;
        from_stream(A);
        long long B;
        from_stream(B);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, B, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1546385218;
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
        cout << "MagicNumbersAgain (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
