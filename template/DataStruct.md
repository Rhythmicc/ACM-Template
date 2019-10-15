# 数据结构

## 位线段树


```c++
const unsigned maxn = 1e5+5;
int n, q;
int aa[maxn];
class segment_tree {
private:
    int tr[20][maxn << 2u];
    int lazy[20][maxn << 2u];
    int lazyXOR[20][maxn << 2u];

    void push_down(int id, int rt, int l, int r) {
        int m = l + (r - l) / 2;
        if (lazy[id][rt] != -1) {
            lazyXOR[id][rt << 1] = lazyXOR[id][rt << 1 | 1] = 0;
            lazy[id][rt << 1] = lazy[id][rt << 1 | 1] = lazy[id][rt];
            tr[id][rt << 1] = lazy[id][rt] * (m - l + 1);
            tr[id][rt << 1 | 1] = lazy[id][rt] * (r - m);
            lazy[id][rt] = -1;
        }
        if (lazyXOR[id][rt] == 1) {
            lazyXOR[id][rt << 1] ^= 1;
            lazyXOR[id][rt << 1 | 1] ^= 1;
            tr[id][rt << 1] = m - l + 1 - tr[id][rt << 1];
            tr[id][rt << 1 | 1] = r - m - tr[id][rt << 1 | 1];
            lazyXOR[id][rt] = 0;
        }
    }

    void push_up(int id, int rt) {
        tr[id][rt] = tr[id][rt << 1 | 1] + tr[id][rt << 1];
    }

public:
    void build(int id, int rt, int l, int r) {
        lazy[id][rt] = -1;
        lazyXOR[id][rt] = 0;
        if (l != r) {
            int m = l + (r - l) / 2;
            build(id, rt << 1, l, m);
            build(id, rt << 1 | 1, m + 1, r);
            push_up(id, rt);
        } else {
            if ((aa[r] & (1 << id)) > 0)tr[id][rt] = 1;
            else tr[id][rt] = 0;
        }
    }

    void update(int id, int rt, int l, int r, int L, int R, int x) {
        if (L > l || r > R) {
            push_down(id, rt, l, r);
            int m = l + (r - l) / 2;
            if (L <= m)update(id, rt << 1, l, m, L, R, x);
            if (R > m)update(id, rt << 1 | 1, m + 1, r, L, R, x);
            push_up(id, rt);
        } else {
            if (x != 2) {
                lazy[id][rt] = x;
                lazyXOR[id][rt] = 0;
                tr[id][rt] = x * (r - l + 1);
            } else {
                if (lazy[id][rt] != -1)lazy[id][rt] ^= 1;
                else lazyXOR[id][rt] ^= 1;
                tr[id][rt] = (r - l + 1) - tr[id][rt];
            }
        }
    }

    LL query(int id, int rt, int l, int r, int L, int R) {
        if (L <= l and r <= R)return tr[id][rt];
        push_down(id, rt, l, r);
        int m = (l + r) >> 1;
        LL ans = 0;
        if (L <= m)ans += query(id, rt << 1, l, m, L, R);
        if (R > m)ans += query(id, rt << 1 | 1, m + 1, r, L, R);
        return ans;
    }
}tree;
/*
void init() {
    cin>>n;
    range(i,0,n-1)cin>>aa[i];
    range(i,0,19)tree.build(i,1,0,n-1);
    cin>>q;
}

void solve() {
    while(q--){
        int op,l,r,x;
        cin>>op>>l>>r;
        --l,--r;
        if(op==1){
            LL ans = 0;
            range(i,0,19)ans += tree.query(i,1,0,n-1,l,r) * (1<<i);
            cout<<ans<<'\n';
        } else{
            cin>>x;
            if(op==2){
                range(i,0,19)if(x&(1<<i))tree.update(i,1,0,n-1,l,r,2);
            }
            else if(op==3){
                range(i,0,19)if(x&(1<<i))tree.update(i,1,0,n-1,l,r,1);
            }
            else {
                range(i,0,19)if(!(x&(1<<i)))tree.update(i,1,0,n-1,l,r,0);
            }
        }
    }
}
*/
```