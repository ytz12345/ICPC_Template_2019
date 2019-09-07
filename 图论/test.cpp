#include<bits/stdc++.h>
const int N = 1e5 + 10;
int ri() {
    char c = getchar(); int x = 0, f = 1; for(;c < '0' || c > '9'; c = getchar()) if(c == '-') f = -1;
    for(;c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) - '0' + c; return x * f;
}
int tp, n, sums, r1[N], r2[N], v[N];
int G, mn, pr[N], to[N << 1], nx[N << 1], sz[N], de[N], fa[N];
bool vis[N];
void add(int u, int v) {to[++tp] = v; nx[tp] = pr[u]; pr[u] = tp;}
void adds(int u, int v) {add(u, v); add(v, u);}
struct {
    int ls[N * 100], rs[N * 100], sum[N * 100], sz, val;
    void Modify(int &p, int L, int R, int x) {
        if(!p) p = ++sz; sum[p] += val;
        if(L == R) return ; int m = L + R >> 1;
        x <= m ? Modify(ls[p], L, m, x) : Modify(rs[p], m + 1, R, x);
    }
    int Query(int p, int L, int R, int k) {
        if(!p || k < L || k > R) return 0;
        if(R == k) return sum[p]; int m = L + R >> 1;
        return k <= m ? Query(ls[p], L, m, k) : sum[ls[p]] + Query(rs[p], m + 1, R, k);
    }
}seg;
struct {
    int bin[21], de[N], mn[21][N << 1], in[N], Lg[N << 1], tot;
    void Dfs(int u, int fa) {
        de[u] = de[fa] + 1; mn[0][++tot] = u; in[u] = tot;
        for(int i = pr[u]; i; i = nx[i])
            if(to[i] != fa) 
                Dfs(to[i], u), 
                mn[0][++tot] = u;
    }
    int Be(int x, int y) {return de[x] < de[y] ? x : y;}
    void Work() {
        Dfs(1, 0);
        bin[0] = 1; for(int i = 1;i <= 20; ++i) bin[i] = bin[i - 1] << 1;
        Lg[0] = -1; for(int i = 1;i <= tot; ++i) Lg[i] = Lg[i >> 1] + 1;
        for(int i = 1;bin[i] <= tot; ++i)
            for(int j = 1;j + bin[i] - 1 <= tot; ++j)
                mn[i][j] = Be(mn[i - 1][j], mn[i - 1][j + bin[i - 1]]);
    }
    int Lca(int u, int v) {
        u = in[u]; v = in[v];
        if(u > v) std::swap(u, v);
        int t = Lg[v - u + 1];
        return Be(mn[t][u], mn[t][v - bin[t] + 1]);
    }
    int Dist(int u, int v) {
        return de[u] + de[v] - (de[Lca(u, v)] << 1);
    }
}lca;
void Get(int u, int fa, int &R) {
    de[u] = de[fa] + 1; seg.val = v[u]; 
    seg.Modify(R, 0, n - 1, de[u]);
    for(int i = pr[u]; i; i = nx[i])
        if(to[i] != fa && !vis[to[i]])
            Get(to[i], u, R);
}
void Rt(int u, int fa) {
    sz[u] = 1; int tp = 0;
    for(int i = pr[u]; i; i = nx[i])
        if(to[i] != fa && !vis[to[i]]) {
            Rt(to[i], u);
            sz[u] += sz[to[i]];
            tp = std::max(tp, sz[to[i]]);
        }
    tp = std::max(tp, sums - sz[u]);
    if(mn > tp) mn = tp, G = u;
}
void Divide(int u, int in, int ps) {
    Get(u, 0, r1[u]); 
    if(in) Get(in, 0, r2[u]); 
    vis[u] = true;
    for(int i = pr[u]; i; i = nx[i])
        if(!vis[to[i]]) {
            sums = sz[to[i]] > sz[u] ? ps - sz[u] : sz[to[i]];
            G = 0; mn = 1e9; Rt(to[i], 0); fa[G] = u;
            Divide(G, to[i], sums);
        }
}
int Query(int u, int k) {
    int Ans = seg.Query(r1[u], 0, n - 1, k);
    for(int x = u; fa[x]; x = fa[x]) {
        int Dis = lca.Dist(u, fa[x]);
        Ans += seg.Query(r1[fa[x]], 0, n - 1, k - Dis);
        Ans -= seg.Query(r2[x], 0, n - 1, k - Dis - 1);
    }
    return Ans;
}
void Modify(int u, int val) {
    seg.val = val - v[u];
    seg.Modify(r1[u], 0, n - 1, 0);
    for(int x = u;x; x = fa[x]) {
        int Dis = lca.Dist(u, fa[x]);
        seg.Modify(r1[fa[x]], 0, n - 1, Dis);
        seg.Modify(r2[x], 0, n - 1, Dis - 1);
    }
    v[u] = val;
}
int main() {
    de[0] = -1; n = ri(); int m = ri();
    for(int i = 1;i <= n; ++i) 
        v[i] = ri();
    for(int i = 1;i < n; ++i) 
        adds(ri(), ri());
    lca.Work();
    G = 0; mn = 1e9; sums = n; Rt(1, 0); 
    Divide(G, 0, sums);
    for(int La = 0;m--; ) {
        int op = ri(), x = ri() ^ La, y = ri() ^ La;
        if(!op) printf("%d\n", La = Query(x, y));
        else Modify(x, y);
    }
    return 0;
}
