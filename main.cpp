#include      <iostream>
#include       <iomanip>
#include        <string>
#include        <cstdio>
#include         <cmath>
#include       <cstring>
#include     <algorithm>
#include        <vector>
#include         <queue>
#include         <deque>
#include          <list>
#include           <map>
#include <unordered_map>
#include <unordered_set>
#include           <set>
#include        <bitset>
#include       <fstream>
#include         <ctime>
#include         <stack>
#include         <regex>
#include        <random>

#define P(n, f)               cout<<n<<(f?'\n':' ')
#define Po(n, f)               out<<n<<(f?'\n':' ')
#define pi                            pair<int,int>
#define LL                                long long
#define ULL                      unsigned long long
#define lowbit(x)                            x&(-x)
#define mp                                make_pair
#define elif                                else if
#define irange(i,arr)               for(auto&i:arr)
#define range(i, a, b)       for(auto i=a;i<=b;++i)
#define itrange(i, a, b)     for(auto i=a;i!=b;++i)
#define rerange(i, a, b)     for(auto i=a;i>=b;--i)
#define IOS ios::sync_with_stdio(false), cin.tie(0)
#define fill(arr, tmp)  memset(arr,tmp,sizeof(arr))
using namespace std;
int fail[int(1e6+5)],t;
int ex[int(1e6+5)];
string x;

void init() {
    cin>>t;
}

void getFail(string&p, int*f){
    int len = p.length(),i=0,j;
    f[0] = len;
    while(p[i]==p[i+1] and i+1 < len)++i;
    f[1] = i;
    int po=1;
    for(i=2; i < len; ++i){
        if(f[i-po]+i<f[po]+po)f[i] = f[i-po];
        else{
            j = max(0,f[po]+po-i);
            while(i+j < len and p[j] == p[j+i])++j;
            f[i] = j;
            po = i;
        }
    }
}

void exKMP(string T,string P){
    int i=0,j,po,len=T.length(),l2=P.length();
    getFail(P,fail);
    while(T[i]==P[i] and i<l2 and i<len)++i;
    ex[0] = i;
    po = 0;
    for(i=1;i<len;++i){
        if(fail[i-po]+i<ex[po]+po)ex[i]=fail[i-po];
        else{
            j=max(ex[po]+po-i,0);
            while(i+j<len and j<l2 and T[j+i]==P[j])++j;
            ex[i]=j;
            po=i;
        }
    }
}

void solve() {
    while (t--) {
        cin >> x;
        fill(fail, 0);
        fill(ex, 0);
        exKMP(x, x);
        LL ans = 0;
        range(i, 1ul, x.length() - 1) {
            if (!ex[i])++ans;
            else {
                if (i + ex[i] == x.length())ans += ex[i];
                else ans += ex[i] + 1;
            }
            //cout<<ex[i]<<(i==x.length()-1?'\n':' ');
        }
        cout << ans << '\n';
    }
}

int main() {
    IOS;
    init();
    solve();
    return 0;
}