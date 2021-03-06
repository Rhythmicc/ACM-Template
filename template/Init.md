# 初始设置

- 扩展工具
    - **CLion项目扩展工具:** [Qpro](https://pypi.org/project/Qpro/)

## 头文件及宏

```c++
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


typedef long long                               LL;
typedef unsigned long long                     ULL;
#define pi                            pair<int,int>
#define lowbit(x)                        (x)&(-(x))
#define mp                                make_pair
#define irange(i, arr)              for(auto&i:arr)
#define range(i, a, b)       for(auto i=a;i<=b;++i)
#define itrange(i, a, b)     for(auto i=a;i!=b;++i)
#define rerange(i, a, b)     for(auto i=a;i>=b;--i)
#define IOS ios::sync_with_stdio(false), cin.tie(0)
#define fill(arr, tmp)  memset(arr,tmp,sizeof(arr))
using namespace std;
/// here to write const value like: const int mod = 1e9+7


/// __TEMPLATE__
/// here to write data structure


void init() { /// here to write init function

}

void solve() { /// here to write main algorithm

}

int main(int argc, char**args) {
    IOS;
    init();
    solve();
    return 0;
}
```

## 读入挂

```c++
template <class T>
inline bool Read(T &ret) {
    char c;
    int sgn;
    if (c = getchar(), c == EOF) return 0; //EOF
    while (c != '-' && (c < '0' || c > '9')) c = getchar();
    sgn = (c == '-') ? -1 : 1;
    ret = (c == '-') ? 0 : (c - '0');
    while (c = getchar(), c >= '0' && c <= '9')
        ret = ret * 10 + (c - '0');
    ret *= sgn;
    return 1;
}
```

## 输出挂

```c++
void Out(int a){
    if(a < 0){
        putchar('-');
        a = -a;
    }
    if(a >= 10)Out(a / 10);
    putchar(a % 10 + '0');
}
```

## 超强输入输出挂!

```c++
namespace IO {
    using namespace std;
    typedef long long ll;
    class endln {
    };

    class iofstream {
    private:
        int idx;
        bool eof;
        char buf[100005], *ps, *pe;
        char bufout[100005], outtmp[50], *pout, *pend;

        inline void rnext() {
            if (++ps == pe)
                pe = (ps = buf) + fread(buf, sizeof(char), sizeof(buf) / sizeof(char), stdin), eof = true;
            eof = ps != pe;
        }

        inline void write() {
            fwrite(bufout, sizeof(char), pout - bufout, stdout);
            pout = bufout;
        }

    public:
        iofstream() : idx(-1), eof(true) {
            pe = (ps = buf) + 1;
            pend = (pout = bufout) + 100005;
        }

        ~iofstream() {
            write();
        }

        template<class T>
        inline bool fin(T &ans) {
#ifdef ONLINE_JUDGE
            ans = 0;
            T f = 1;
            if (ps == pe) {
                return eof = false;
            }
            do {
                rnext();
                if ('-' == *ps) f = -1;
            } while (!isdigit(*ps) && ps != pe);
            if (ps == pe) {
                return eof = false;
            }
            do {
                ans = (ans << 1) + (ans << 3) + *ps - 48;
                rnext();
            } while (isdigit(*ps) && ps != pe);
            ans *= f;
#else
            cin >> ans;
#endif
            return true;
        }

        template<class T>
        inline bool fdb(T &ans) {
#ifdef ONLINE_JUDGE
            ans = 0;
            T f = 1;
            if (ps == pe) return false;//EOF
            do {
                rnext();
                if ('-' == *ps) f = -1;
            } while (!isdigit(*ps) && ps != pe);
            if (ps == pe) return false;//EOF
            do {
                ans = ans * 10 + *ps - 48;
                rnext();
            } while (isdigit(*ps) && ps != pe);
            ans *= f;
            if (*ps == '.') {
                rnext();
                T small = 0;
                do {
                    small = small * 10 + *ps - 48;
                    rnext();
                } while (isdigit(*ps) && ps != pe);
                while (small >= 1) {
                    small /= 10;
                }
                ans += small;
            }
#else
            cin >> ans;
#endif
            return true;
        }


        inline bool out_char(const char c) {
#ifdef ONLINE_JUDGE
            *(pout++) = c;
            if (pout == pend) write();
#else
            cout << c;
#endif
            return true;
        }

        inline bool out_str(const char *s) {
#ifdef ONLINE_JUDGE
            while (*s) {
                *(pout++) = *(s++);
                if (pout == pend) write();
            }
#else
            cout << s;
#endif
            return true;
        }

        template<class T>
        inline bool out_double(T x, int idx) {
            char str[50];
            string format = "%";
            if (~idx) {
                format += '.';
                format += (char) (idx + '0');
            }
            format += "f";
            sprintf(str, format.c_str(), x);
            out_str(str);
            return true;
        }

        template<class T>
        inline bool out_int(T x) {
#ifdef ONLINE_JUDGE
            if (!x) {
                out_char('0');
                return true;
            }
            if (x < 0) x = -x, out_char('-');
            int len = 0;
            while (x) {
                outtmp[len++] = x % 10 + 48;
                x /= 10;
            }
            outtmp[len] = 0;
            for (int i = 0, j = len - 1; i < j; ++i, --j) swap(outtmp[i], outtmp[j]);
            out_str(outtmp);
#else
            cout << x;
#endif
            return true;
        }


        inline iofstream &operator<<(const double &x) {
            out_double(x, idx);
            return *this;
        }

        inline iofstream &operator<<(const int &x) {
            out_int(x);
            return *this;
        }

        inline iofstream &operator<<(const unsigned long long &x) {
            out_int(x);
            return *this;
        }

        inline iofstream &operator<<(const unsigned &x) {
            out_int(x);
            return *this;
        }

        inline iofstream &operator<<(const long &x) {
            out_int(x);
            return *this;
        }

        inline iofstream &operator<<(const ll &x) {
            out_int(x);
            return *this;
        }

        inline iofstream &operator<<(const endln &x) {
            out_char('\n');
            return *this;
        }


        inline iofstream &operator<<(const char *x) {
            out_str(x);
            return *this;
        }

        inline iofstream &operator<<(const string &x) {
            out_str(x.c_str());
            return *this;
        }

        inline iofstream &operator<<(const char &x) {
            out_char(x);
            return *this;
        }

        inline bool setw(int x) {
            if (x >= 0) {
                idx = x;
                return true;
            }
            return false;
        }

        inline iofstream &operator>>(int &x) {
            if (!fin(x))eof = false;
            return *this;
        }

        inline iofstream &operator>>(ll &x) {
            if (!fin(x))eof = false;
            return *this;
        }

        inline iofstream &operator>>(double &x) {
            if (!fdb(x))eof = false;
            return *this;
        }

        inline iofstream &operator>>(float &x) {
            if (!fdb(x))eof = false;
            return *this;
        }

        inline iofstream &operator>>(unsigned &x) {
            if (!fin(x))eof = false;
            return *this;
        }

        inline iofstream &operator>>(unsigned long long &x) {
            if (!fin(x))eof = false;
            return *this;
        }

        inline explicit operator bool() {
            return eof;
        }

        inline char getchar() {
#ifdef ONLINE_JUDGE
            if (ps == pe) {
                return eof = false;
            }
            rnext();
            if (ps + 1 == pe)
                eof = false;
            return *ps;
#else
            return std::getchar();
#endif
        }

        inline iofstream &operator>>(char *str) {
#ifdef ONLINE_JUDGE
            if (ps == pe) {
                eof = false;//EOF
                return *this;
            }
            do {
                rnext();
            } while (isspace(*ps) && iscntrl(*ps) && ps != pe);
            if (ps == pe) {
                eof = false;//EOF
                return *this;
            }
            do {
                *str = *ps;
                ++str;
                rnext();
            } while (!(isspace(*ps) || iscntrl(*ps)) && ps != pe);
            *str = '\0';
            return *this;
#else
            cin >> str;
            return *this;
#endif
        }

        inline iofstream &operator>>(string &str) {
#ifdef ONLINE_JUDGE
            str.clear();
            if (ps == pe) {
                eof = false;//EOF
                return *this;
            }
            do {
                rnext();
            } while (isspace(*ps) && iscntrl(*ps) && ps != pe);
            if (ps == pe) {
                eof = false;//EOF
                return *this;
            }
            do {
                str += *ps;
                rnext();
            } while (!(isspace(*ps) || iscntrl(*ps)) && ps != pe);
            return *this;
#else
            cin >> str;
            return *this;
#endif
        }
    };

    static iofstream fin;
    static endln ln;
}
```
## 大数阶乘

```c++
char a[50000];
void big_fact(int n){
    int temp,digit,i,j=0;
        a[0]=1;digit=1;
        for(i=2;i<=n;i++){
            int num=0;
            for(j=0;j<digit;j++){
                temp=a[j]*i+num;
                a[j]=temp%10;
                num=temp/10;
            }
            while(num){
                a[digit]=num%10;
                num=num/10;
                digit++;
            }
        for(i=digit-1;i>=0;i--)cout<<a[i];
        cout<<'\n';
    }
}
```
