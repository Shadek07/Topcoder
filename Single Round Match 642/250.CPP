
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




class ForgetfulAddition {
    public:
    int minNumber(string expression) 
    {
    	int sz,i,j,a,b;
    	a= 0;
    	b = 0;
    	sz = expression.size();
    	int mn = 99999999;
    	forl(i,0,sz-1)
    	{
    		a = 0;
    		b = 0;
    		forl(j,0,i+1)
    		{
    			a = a*10 + (expression[j] - '0');
    		}
    		forl(j,i+1,sz)
    		{
    			b = b*10 + (expression[j] - '0');
    		}
    		mn = min(mn,a+b);
    	}
        return mn;
    }
};

class ForgetfulAddition1 {
    public:
    int minNumber(string expression) 
    {
    	int sz,i,j,a,b;
    	a= 0;
    	b = 0;
    	sz = expression.size();
    	int mn = 99999999;
    	forl(i,0,sz-1)
    	{
    		a = 0;
    		b = 0;
    		forl(j,0,i+1)
    		{
    			a = a*10 + (expression[j] - '0');
    		}
    		forl(j,i+1,sz)
    		{
    			b = b*10 + (expression[j] - '0');
    		}
    		mn = min(mn,a+b);
    	}
        return mn;
    }
};

int main(void)
{
	ForgetfulAddition fr;
	int a = 99999999;
	//cout << a << endl;
	cout << fr.minNumber("9999999") << endl;
}
