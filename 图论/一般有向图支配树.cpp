namespace DomTree {
    int n, m, tot;
    int dfn[N], id[N], fa[N];//fa为dfs树上的父亲
    vector <int> d[N], e[N], f[N], E[N];
    //d为临时树的边,e原图边,f为dfs树的反向边,E为支配树的边
    int fu[N], val[N], semi[N], idom[N];//fu为并查集数组
    void dfs(int u) {
        dfn[u] = ++ tot; id[tot] = u;
        for (int v : e[u]) {
            f[v].push_back(u);
            if (!dfn[v]) {
                fa[v] = u;
                dfs(v);
            }
        }
    }
    int getFa(int x) {
        if (fu[x] == x) return x;
        int y = getFa(fu[x]);
        if (dfn[semi[val[fu[x]]]] < dfn[semi[val[x]]])
            val[x] = val[fu[x]];
        return fu[x] = y;
    }
    int smin(int x, int y) {
        return dfn[x] < dfn[y] ? x : y;
    }
    void solve(int st) {//st源点
        dfs(st);
        for (int i = tot; i >= 2; i --) {
            int x = id[i];
            if (!f[x].empty()) {
                for (int y : f[x])
                    if (dfn[y] < dfn[x])
                        semi[x] = smin(semi[x], y);
                    else {
                        getFa(y);
                        semi[x] = smin(semi[x], semi[val[y]]);
                    }
            }
            fu[x] = fa[x]; d[semi[x]].pb(x);
            if (!d[fa[x]].empty()) {
                for (int y : d[fa[x]]) {
                    getFa(y);
                    int u = val[y];
                    idom[y] = (dfn[semi[u]] < dfn[semi[y]]) ? u : fa[x];
                }
            }
        }
        for (int i = 2; i <= tot; i ++) {
            int x = id[i];
            if (idom[x] != semi[x]) idom[x] = idom[idom[x]];
        }
        for (int i = 2; i <= tot; i ++)
            E[idom[id[i]]].push_back(id[i]);
    }
    void init() {
        in(n), in(m);
        for (int i = 1; i <= n; i ++)
            d[i].clear(), e[i].clear(), f[i].clear(), E[i].clear();
        for (int u, v, i = 0; i < m; i ++) {
            in(u), in(v);
            e[u].push_back(v);//单向边
        }
        tot = 0;
        for (int i = 1; i <= n; i ++) {
            fu[i] = semi[i] = idom[i] = val[i] = i; 
            dfn[i] = id[i] = 0;
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    DomTree::init();
    /*根据题目或者根据图的入度判断源点st*/
    DomTree::solve(st);
    return 0;
}   