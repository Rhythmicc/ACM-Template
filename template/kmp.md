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