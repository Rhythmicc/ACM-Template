# 字符串

## KMP算法
```c++
void getFail(char *P, int *f) {
    int lenP = (int) strlen(P);
    f[0] = 0;
    f[1] = 0; //递推边界初值
    for (int i = 1; i < lenP; i++) {
        int j = f[i];
        while (j && P[i] != P[j]) j = f[j];
        f[i + 1] = (P[i] == P[j] ? j + 1 : 0);
    }
}

vector<int> KMP(char *T, char *P, int *f) {
    int lenT = strlen(T);
    int lenP = strlen(P);
    getFail(P, f);
    int j = 0;
    vector<int> ans;
    for (int i = 0; i < lenT; i++) {
        while (j && P[j] != T[i])
            j = f[j];
        if (P[j] == T[i])
            j++;
        if (j == lenP)
            ans.push_back(i - lenP + 1);
    }
    return ans;
}
```

## 扩展KMP

```c++
const int K=100005;
int nt[K],extand[K];
char S[K],T[K];
void Getnext(char *t, int *next) {
    int len = strlen(t), a = 0;
    next[0] = len;
    while (a < len - 1 && t[a] == t[a + 1]) a++;
    next[1] = a;
    a = 1;
    for (int k = 2; k < len; k++) {
        int p = a + next[a] - 1, L = next[k - a];
        if ((k - 1) + L >= p) {
            int j = (p - k + 1) > 0 ? (p - k + 1) : 0;
            while (k + j < len && t[k + j] == t[j]) j++;
            next[k] = j;
            a = k;
        } else next[k] = L;
    }
}
void GetExtand(char *s, char *t, int *next) {
    Getnext(t, next);
    int slen = strlen(s), tlen = strlen(t), a = 0;
    int MinLen = slen < tlen ? slen : tlen;
    while (a < MinLen && s[a] == t[a]) a++;
    extand[0] = a;
    a = 0;
    for (int k = 1; k < slen; k++) {
        int p = a + extand[a] - 1, L = next[k - a];
        if ((k - 1) + L >= p) {
            int j = (p - k + 1) > 0 ? (p - k + 1) : 0;
            while (k + j < slen && j < tlen && s[k + j] == t[j]) j++;
            extand[k] = j;
            a = k;
        } else
            extand[k] = L;
    }
}
```


## AC自动机

```c++
const int maxn=500010+5;
const int SIGMA_SIZE=26;
struct ACAutomata {
    int nxt[maxn][SIGMA_SIZE];//节点
    int fail[maxn]; //失配指针
    int end[maxn]; //end[i]记录以i结尾的字符串个数
    int root, L;
    int newnode() {
        for (int i = 0; i < SIGMA_SIZE; i++)
            nxt[L][i] = -1;
        end[L++] = 0;
        return L - 1;
    }
    static int idx(char ch) {
        return ch - 'a';
    }
    void init() {
        L = 0;
        root = newnode();
    }
    void insert(char buf[]) {
        int len = strlen(buf);
        int now = root;
        for (int i = 0; i < len; i++) {
            char ch = idx(buf[i]);
            if (nxt[now][ch] == -1)
                nxt[now][ch] = newnode();
            now = nxt[now][ch];
        }
        end[now]++;
    }
    void build() {
        queue<int> q;
        fail[root] = root;
        for (int i = 0; i < SIGMA_SIZE; i++)
            if (nxt[root][i] == -1)
                nxt[root][i] = root;
            else {
                fail[nxt[root][i]] = root;
                q.push(nxt[root][i]);
            }
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            for (int i = 0; i < SIGMA_SIZE; i++)
                if (nxt[now][i] == -1)//若该点不存在，直接将该位置指向失配指针的下一位
                            nxt[now][i] = nxt[fail[now]][i];
                else {
                    fail[nxt[now][i]] = nxt[fail[now]][i];
                    q.push(nxt[now][i]);
                }
        }
    }
    int query(char buf[]) {
        int len = strlen(buf);
        int now = root;
        int res = 0;
        for (int i = 0; i < len; i++) {
            now = nxt[now][idx(buf[i])];
            int tmp = now;
            while (tmp != root) {
                res += end[tmp];
                end[tmp] = 0;//防止重复，如考虑重复情况请注释掉本行，如Hdu5384
                tmp = fail[tmp];
            }
        }
        return res;
    }
};
```
