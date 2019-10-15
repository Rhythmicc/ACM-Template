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
/// template
```