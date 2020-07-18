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
## 主席树静态第K大

```c++
const int maxn=100100;
int tree[20][maxn];///第i层的排列情况
int sorted[maxn];///排好序的数组
int toleft[20][maxn];///第i层从1.到..j移动到左边的数的个数
void build(int l,int r,int dep) {
    if (l == r) return;
    int mid = (l + r) / 2;
    int same = mid - l + 1;///与mid相同的但要移动到左边的数的个数
    for (int i = l; i <= r; i++)
        if (tree[dep][i] < sorted[mid]) same--;
    int lpos = l, rpos = mid + 1;
    for (int i = l; i <= r; i++) {
        if (tree[dep][i] < sorted[mid])
            tree[dep + 1][lpos++] = tree[dep][i];
        else if (tree[dep][i] == sorted[mid] && same > 0) {
            tree[dep + 1][lpos++] = tree[dep][i];
            same--;
        } else tree[dep + 1][rpos++] = tree[dep][i];
        toleft[dep][i] = toleft[dep][l - 1] + lpos - l;
    }
    build(l, mid, dep + 1);
    build(mid + 1, r, dep + 1);
}
int query(int L,int R,int l,int r,int dep,int k){
    if(l==r) return tree[dep][l];
    int mid=(L+R)/2;
    int cnt=toleft[dep][r]-toleft[dep][l-1];
    if(cnt>=k) {
        int newl = L + toleft[dep][l - 1] - toleft[dep][L - 1];
        int newr = newl + cnt - 1;
        return query(L, mid, newl, newr, dep + 1, k);
    }
    else{
        int newr=r+toleft[dep][R]-toleft[dep][r];
        int newl=newr-(r-l-cnt);
        return query(mid+1,R,newl,newr,dep+1,k-cnt);
    }
}
/*
scanf("%d%d",&n,&m);
for(int i=1;i<=n;i++)
{
    scanf("%d",sorted+i);
    tree[0][i]=sorted[i];
}
sort(sorted+1,sorted+1+n);
build(1,n,0);
int l,r,k;
while(m--)
{
    scanf("%d%d%d",&l,&r,&k);
    printf("%d\n",query(1,n,l,r,0,k));
}
*/
```

## 单调栈

```c++
template <class T>
stack<T> single_stack(vector<T>x) {
    stack<T>res;
    irange(i, x) {
        if(res.empty() || res.top() >= i) res.push(i);
        else {
            while (!res.empty() && res.top() < i) {
                res.pop();
                /// here to write your update function
            }
            res.push(i);
            /// here to write your update function
        }
    }
}
```
