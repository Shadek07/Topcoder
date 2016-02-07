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
#define MID(a, b) (a + ((b - a) >> 1))
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
 
string to_string(long long x) { stringstream ss; ss << x; return ss.str(); }
long long to_int(const string &s) { stringstream ss; ss << s; long long x; ss >> x; return x; }
 
#define MAX 100005
#define INF 9999999
 
class ExplodingRobots {
    public:
    string canExplode(int x1, int y1, int x2, int y2, string instructions) 
    {
        int i,j,k;
        int a,b;
        char c1,c2;
        string ans = "Explosion";
        bool found;
        int sz = instructions.size();
        int up=0,down=0,left=0,right=0;
        forl(i,0,sz){
            if(instructions[i] == 'U'){
                up++;
            }
            if(instructions[i] == 'D'){
                down++;
            }
            if(instructions[i] == 'L'){
                left++;
            }
            if(instructions[i] == 'R'){
                right++;
            }
        }
        for(a = -76;a<=76;a++){
            for(b=-76;b<=76;b++){
                found = false;
                int up_needed1 = 0;
                int down_needed1 = 0;
                int left_needed1 = 0;
                int right_needed1 = 0;
                
                int up_needed2 = 0;
                int down_needed2 = 0;
                int left_needed2 = 0;
                int right_needed2 = 0;
                if(a > x1){
                    right_needed1 = a-x1;
                }else{
                    left_needed1 = x1-a;
                }
                if(b > y1){
                    up_needed1 = b-y1;
                }else{
                    down_needed1 = y1-b;
                }
                
                if(a > x2){
                    right_needed2 = a-x2;
                }else{
                    left_needed2 = x2-a;
                }
                if(b > y2){
                    up_needed2 = b-y2;
                }else{
                    down_needed2 = y2-b;
                }
                bool f1 = (left_needed1 <= left) && (right_needed1 <= right) && (up_needed1 <= up) && (down_needed1 <= down);
                bool f2 = (left_needed2 <= left) && (right_needed2 <= right) && (up_needed2 <= up) && (down_needed2 <= down);
                
                if(f1 && f2){
                    return ans;
                }
            }
        }
        
        return "Safe";
    }
};
 
// Powered by Greed 2.0-RC
