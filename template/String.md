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
/// __TEMPLATE__
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
/// __TEMPLATE__
```