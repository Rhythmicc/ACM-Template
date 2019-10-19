## 图论

### 最大势
```c++
struct GPPF{
    const int mxn = 1e5+5;
    bool vis[mxn], use[mxn];
    int n,m,ans,cnt[mxn];
    vector<int>G[mxn];
    void init() {
        cin>>n>>m;
        range(i,1,m){
            int u,v;
            cin>>u>>v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
    }
    
    void solve() {
        priority_queue<pi > q;
        range(i, 1, n)q.push(mp(0, i));
        while (!q.empty()) {
            while(!q.empty() and vis[q.top().second])q.pop();
            if(q.empty())break;
            int u = q.top().second;
            q.pop();
            vis[u] = true;
            if(not use[cnt[u]]){
                ++ans;
                use[cnt[u]] = true;
            }
            irange(i,G[u]){
                if(vis[i])continue;
                ++cnt[i];
                q.push(mp(cnt[i],i));
            }
        }
        cout<<ans<<'\n';
    }
}
```
## Dijkstra

```c++
struct Dijkstra {
    static const int maxn = 1e5 + 5;
    static const int INF = 0x3f3f3f3f;

    struct Edge {
        int from, to, dist;

        Edge(int u, int v, int d) : from(u), to(v), dist(d) {}
    };

    struct node {
        int d, u;

        node(int d, int u) : d(d), u(u) {}

        bool operator<(const node &rhs) const {
            return d > rhs.d;
        }
    };

    int n, m;
    vector<Edge> edges;
    vector<int> G[maxn];
    bool done[maxn];
    int d[maxn];
    int p[maxn];

    void init(int nn) {
        n = nn;
        for (int i = 0; i <= n; ++i)G[i].clear();
        edges.clear();
    }

    void adde(int from, int to, int dist) {
        edges.push_back(Edge(from - 1, to - 1, dist));
        m = edges.size();
        G[from - 1].push_back(m - 1);
    }

    void dijkstra(int s) {
        priority_queue<node> q;
        for (int i = 0; i < n; ++i)d[i] = INF;
        d[s] = 0;
        memset(done, 0, sizeof(done));
        q.push(node(0, s));
        while (!q.empty()) {
            node x = q.top();
            q.pop();
            if (done[x.u])continue;
            done[x.u] = true;
            for (int i = 0; i < G[x.u].size(); ++i) {
                Edge &e = edges[G[x.u][i]];
                if (d[e.to] > d[x.u] + e.dist) {
                    d[e.to] = d[x.u] + e.dist;
                    p[e.to] = G[x.u][i];
                    q.push(node(d[e.to], e.to));
                }
            }
        }
    }

    int get_ans(int s, int e) {
        dijkstra(s - 1);
        return d[e - 1];
    }
};
```

## Kruskal

```c++
struct Kruskal {
    static const int Vmax = 300;
    static const int Emax = 1000;
    int n, m;
    int rank[Vmax], fa[Vmax];
    int weight;
    int ecnt;

    struct edge {
        int u, v, w;

        bool operator<(const edge &rhs) const {
            return w < rhs.w;
        }
    } e[Emax];

    void init(int Vsz, int Esz) {
        n = Vsz;
        m = Esz;
        ecnt = weight = 0;
        for (int i = 0; i <= Vsz; ++i) {
            fa[i] = i;
            rank[i] = 0;
        }
    }

    void adde(int u, int v, int w) {
        e[ecnt].u = u;
        e[ecnt].v = v;
        e[ecnt++].w = w;
    }

    int findx(int x) {
        while (x != fa[x])x = fa[x];
        return x;
    }

    void merge(int u, int v) {
        if (rank[u] < rank[v]) {
            fa[u] = v;
            rank[v] += rank[u];
        } else {
            fa[v] = u;
            rank[u] += rank[v];
        }
    }

    int kruskal() {
        int cnt = 0;
        sort(e, e + m);
        for (int i = 0; i < m; ++i) {
            int uR = findx(e[i].u);
            int vR = findx(e[i].v);
            if (uR != vR) {
                merge(uR, vR);
                weight += e[i].w;
                ++cnt;
            }
        }
        if (cnt == n - 1)return weight;
        else return -1;
    }
};
```

## LCA

```c++
vector<int> ve[100005];
int dep[100005];
int f[100005][21];
void inta(int x, int fa)  //初始化dep 和f 数组
{
    dep[x] = dep[fa] + 1;
    for (int i = 0; i <= 19; i++) {
        f[x][i + 1] = f[f[x][i]][i];//预处理出每个点的前倍增节点
    }
    for (int i = 0; i < ve[x].size(); i++) {
        int tmp = ve[x][i];
        if (tmp == fa)
            continue;//防止一条边走两次
        f[tmp][0] = x;//第一个点手动添加
        inta(tmp, x);
    }
}
int lca(int x, int y) {
    if (dep[x] < dep[y])
        swap(x, y);  //确保x比较深
    for (int i = 20; i >= 0; i--) {
        int tmp = f[x][i];
        if (dep[tmp] >= dep[y])//先将两点调到同一深度
            x = tmp;
        if (x == y)
            return x;
    }
    for (int i = 20; i >= 0; i--) {//枚举向上倍增
        if (f[x][i] != f[y][i]) {
            x = f[x][i];
            y = f[y][i];
        }
    }
    return f[x][0];
}
/*
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n - 1; i++) {
        int temp1, temp2;
        scanf("%d%d", &temp1, &temp2);
        ve[temp1].push_back(temp2);
        ve[temp2].push_back(temp1);
    }
    inta(1, 0);
    int q;
    scanf("%d", &q);
    while (q--) {
        int temp1, temp2;
        scanf("%d%d", &temp1, &temp2);
        int temp3 = lca(temp1, temp2);
        // cout<<temp3<<endl;
        printf("%d\n", dep[temp1] + dep[temp2] - 2 * dep[temp3]);
    }
*/
```

## 网络流Dinic

```c++
#define vmax 20005//最大顶点数
#define emax 500005 //最大边数
struct Dinic {
    static const int INF = 0x3f3f3f3f;
    int src, target, ecnt;//源点，汇点，边数
    int head[vmax];//邻接表表头
    int cur[vmax];
    int dis[vmax];//从源点到该点的距离
    struct edge {
        int to, next, cap;
    } e[2 * emax];//边可能是双向的，故乘2
    void init(int start, int end) {
        ecnt = 0;
        src = start;
        target = end;
        memset(head, -1, sizeof(head));
    }

    void adde(int from, int to, int cap) {
        e[ecnt].to = to;
        e[ecnt].cap = cap;
        e[ecnt].next = head[from];
        head[from] = ecnt++;
        e[ecnt].to = from;
        e[ecnt].cap = 0;
        e[ecnt].next = head[to];
        head[to] = ecnt++;
    }

    bool BFS() {
        memset(dis, -1, sizeof(dis));
        dis[src] = 0;
        queue<int> q;
        q.push(src);
        while (!q.empty()) {
            int tmp = q.front();
            q.pop();
            for (int i = head[tmp]; i != -1; i = e[i].next) {
                int tp = e[i].to;
                if (dis[tp] == -1 && e[i].cap) {
                    dis[tp] = dis[tmp] + 1;
                    q.push(tp);
                    if (tp == target)return true;
                }
            }
        }
        return false;
    }

    int DFS(int u, int delta) {
        if (u == target || delta == 0)
            return delta;
        int f, flow = 0;
        for (int &i = cur[u]; i != -1; i = e[i].next) {
            if (dis[u] + 1 == dis[e[i].to] && (f = DFS(e[i].to, min(delta, e[i].cap)))) {
                e[i].cap -= f;
                e[i ^ 1].cap += f;
                flow += f;
                delta -= f;
                if (!delta)break;
            }
        }
        return flow;
    }

    int dinic() {
        int tmp = 0, maxflow = 0;
        while (BFS()) {
            for (int i = src; i <= target; i++) cur[i] = head[i];
            while ((tmp = DFS(src, INF)))maxflow += tmp;
        }
        return maxflow;
    }
};
```
