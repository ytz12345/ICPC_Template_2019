/*LCA用ST表，总复杂度O(nlog)*/
/*每次询问删去两条边后，剩下3棵树的最大直径长度*/
const int N = 2e5 + 5;
int T, n, m;
int len, head[N], ST[20][N];
struct edge{int u, v, w;}ee[N];
int cnt, fa[N], log_2[N], st[N], en[N], dfn[N], dis[N], dep[N], pos[N];
struct edges{int to, next, cost;}e[N];
void add(int u, int v, int w) {
    e[++ len] = (edges){v, head[u], w}, head[u] = len;
    e[++ len] = (edges){u, head[v], w}, head[v] = len;
}
void dfs1(int u) {
    st[u] = ++ cnt, dfn[cnt] = u;
    for (int v, i = head[u]; i; i = e[i].next) {
        v = e[i].to;
        if (v == fa[u]) continue;
        fa[v] = u, dep[v] = dep[u] + 1;
        dis[v] = dis[u] + e[i].cost, dfs1(v);
    }
    en[u] = cnt;
}
void dfs2(int u) {
    dfn[++ cnt] = u, pos[u] = cnt;
    for (int v, i = head[u]; i; i = e[i].next) {
        v = e[i].to;
        if (v == fa[u]) continue;
        dfs2(v), dfn[++ cnt] = u;
    }
}
int mmin(int x, int y) {
    if (dep[x] < dep[y]) return x;
    return y;
}
int lca(int u, int v) {
    static int w;
    if (pos[u] > pos[v]) swap(u, v);
    w = log_2[pos[v] - pos[u] + 1];
    return mmin(ST[w][pos[u]], ST[w][pos[v] - (1 << w) + 1]);
}
int dist(int u, int v) {
    int Lca = lca(u, v);
    return dis[u] + dis[v] - dis[Lca] * 2;
}
void build() {
    for (int i = 1; i <= cnt; i ++)
        ST[0][i] = dfn[i];
    for (int i = 1; i < 20; i ++)
        for (int j = 1; j <= cnt; j ++)
            if (j + (1 << (i - 1)) > cnt) ST[i][j] = ST[i - 1][j];
            else ST[i][j] = mmin(ST[i - 1][j], ST[i - 1][j + (1 << (i - 1))]); 
}
int M;
struct node {
    int l, r, dis;
}tr[N << 1];
void update(int o, int o1, int o2) {
    static int d; static node tmp;
    if (tr[o1].dis == -1) {tr[o] = tr[o2]; return;}
    if (tr[o2].dis == -1) {tr[o] = tr[o1]; return;}
    if (tr[o1].dis > tr[o2].dis) tmp = tr[o1];
    else tmp = tr[o2]; 
    d = dist(tr[o1].l, tr[o2].l);
    if (d > tmp.dis) tmp.l = tr[o1].l, tmp.r = tr[o2].l, tmp.dis = d;
    d = dist(tr[o1].l, tr[o2].r);
    if (d > tmp.dis) tmp.l = tr[o1].l, tmp.r = tr[o2].r, tmp.dis = d;
    d = dist(tr[o1].r, tr[o2].l);
    if (d > tmp.dis) tmp.l = tr[o1].r, tmp.r = tr[o2].l, tmp.dis = d;
    d = dist(tr[o1].r, tr[o2].r);
    if (d > tmp.dis) tmp.l = tr[o1].r, tmp.r = tr[o2].r, tmp.dis = d;
    tr[o] = tmp;
}
void ask(int s, int t) {
    if (s > t) return;
    for (s += M - 1, t += M + 1; s ^ t ^ 1; s >>= 1, t >>= 1) {
        if (~s&1) update(0, 0, s ^ 1);
        if ( t&1) update(0, 0, t ^ 1);
    }
}
int main() {
    ios::sync_with_stdio(false);
    int u, v, w, ans; log_2[1] = 0;
    for (int i = 2; i <= 200000; i ++) 
        if (i == 1 << (log_2[i - 1] + 1))
            log_2[i] = log_2[i - 1] + 1;
        else log_2[i] = log_2[i - 1];
    for (cin >> T; T --; ) {
        cin >> n >> m, cnt = len = 0;
        for (int i = 1; i <= n; i ++)
            head[i] = 0;
        for (int i = 1; i < n; i ++) {
            cin >> ee[i].u >> ee[i].v >> ee[i].w;
            add(ee[i].u, ee[i].v, ee[i].w);
        }
        dfs1(1);
        for (M = 1; M < n + 2; M <<= 1);
        for (int i = 1; i <= n; i ++)
            tr[i + M].l = tr[i + M].r = dfn[i], tr[i + M].dis = 0;
        for (int i = n + M + 1; i <= (M << 1) + 1; i ++)
            tr[i].dis = -1;
        cnt = 0, dfs2(1), build();
        for (int i = M; i; i --) 
            update(i, i << 1, i << 1 | 1);
        for (int i = 1; i < n; i ++) 
            if (dep[ee[i].u] > dep[ee[i].v])
                swap(ee[i].u, ee[i].v);
        for (int u, v, i = 1; i <= m; i ++) {
            cin >> u >> v, ans = 0;
            u = ee[u].v, v = ee[v].v, w = lca(u, v);
            if (w == u || w == v) {
                if (w != u) swap(u, v);
                tr[0].dis = -1, ask(1, st[u] - 1), ask(en[u] + 1, n), ans = max(ans, tr[0].dis);
                tr[0].dis = -1, ask(st[u], st[v] - 1), ask(en[v] + 1, en[u]), ans = max(ans, tr[0].dis);
                tr[0].dis = -1, ask(st[v], en[v]), ans = max(ans, tr[0].dis);
            }
            else {
                if (st[u] > st[v]) swap(u, v);
                tr[0].dis = -1, ask(1, st[u] - 1), ask(en[u] + 1, st[v] - 1), ask(en[v] + 1, n), ans = max(ans, tr[0].dis);
                tr[0].dis = -1, ask(st[u], en[u]), ans = max(ans, tr[0].dis);
                tr[0].dis = -1, ask(st[v], en[v]), ans = max(ans, tr[0].dis);
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}
