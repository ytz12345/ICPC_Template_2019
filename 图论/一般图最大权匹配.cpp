#define dist(e) (lab[e.u]+lab[e.v]-g[e.u][e.v].w*2)
const int N = 1023, inf = 1e9;
struct edge{int u, v, w;}g[N][N];
int n, m, n_x, lab[N], match[N], slk[N], st[N];
int pa[N], ff[N][N], S[N], vis[N];
vector <int> flower[N];
deque <int> q;
void update(int u, int x) {//updateSlk
    if (!slk[x] || dist(g[u][x]) < dist(g[slk[x]][x]))
        slk[x] = u;
}
void setSlk(int x) {
    slk[x] = 0;
    for (int u = 1; u <= n; u ++)
        if (g[u][x].w > 0 && st[u] != x && S[st[u]] == 0)
            update(u, x);
}
void qpush(int x) {
    if (x <= n) return q.push_back(x);
    for (int i : flower[x]) qpush(i);
}
void setSt(int x, int b) {
    st[x] = b; if (x <= n) return;
    for (int i : flower[x]) setSt(i, b);
}
int getPr(int b, int xr) {
    int pr = find(flower[b].begin(), flower[b].end(), xr) - flower[b].begin();
    if (pr & 1) {
        reverse(flower[b].begin() + 1, flower[b].end());
        return (int)(flower[b].size()) - pr;
    }
    return pr;
}
void setMatch(int u, int v) {
    match[u] = g[u][v].v; if (u <= n) return;
    int xr = ff[u][g[u][v].u], pr= getPr(u, xr);
    for (int i = 0; i < pr; i ++)
        setMatch(flower[u][i], flower[u][i ^ 1]);
    setMatch(xr, v);
    rotate(flower[u].begin(), flower[u].begin() + pr, flower[u].end());
}
void augment(int u, int v) {
    int xnv = st[match[u]]; setMatch(u, v);
    if (!xnv) return; setMatch(xnv, st[pa[xnv]]);
    augment(st[pa[xnv]], xnv);
}
int getLca(int u, int v) {
    static int t = 0;
    for (t ++; u || v; swap(u, v)) {
        if (!u) continue;
        if (vis[u] == t) return u;
        vis[u] = t, u = st[match[u]];
        if (u) u = st[pa[u]];
    }
    return 0;
}
void addBlossom(int u, int lca, int v) {
    int b = n + 1;
    while (b <= n_x && st[b]) b ++;
    if (b > n_x) n_x ++;
    lab[b] = 0, S[b] = 0; match[b] = match[lca];
    flower[b].clear(); flower[b].push_back(lca);
    for (int x = u,y; x != lca; x = st[pa[y]])
        flower[b].push_back(x), flower[b].push_back(y = st[match[x]]), qpush(y);
    reverse(flower[b].begin() + 1, flower[b].end());
    for (int x = v, y; x != lca; x = st[pa[y]])
        flower[b].push_back(x), flower[b].push_back(y = st[match[x]]), qpush(y);
    setSt(b, b);
    for (int x = 1; x <= n_x; ++ x) g[b][x].w = g[x][b].w = 0;
    for (int x = 1; x <= n; ++ x)   ff[b][x] = 0;
    for (int i = 0; i < flower[b].size(); ++ i) {
        int xs = flower[b][i];
        for (int x = 1; x <= n_x; ++ x)
            if (g[b][x].w == 0 || dist(g[xs][x]) < dist(g[b][x]))
                g[b][x] = g[xs][x], g[x][b] = g[x][xs];
        for (int x = 1; x <= n; ++ x)
            if (ff[xs][x]) ff[b][x] = xs;
    }
    setSlk(b);
}
void expandBlossom(int b) {
    for (int i = 0; i < flower[b].size(); ++ i)
        setSt(flower[b][i], flower[b][i]);
    int xr = ff[b][g[b][pa[b]].u], pr = getPr(b, xr);
    for (int i = 0; i < pr; i += 2) {
        int xs = flower[b][i], xns = flower[b][i + 1];
        pa[xs] = g[xns][xs].u; S[xs] = 1, S[xns] = 0;
        slk[xs] = 0, setSlk(xns); qpush(xns);
    }
    S[xr] = 1, pa[xr] = pa[b];
    for (int i = pr + 1; i < flower[b].size(); ++ i) {
        int xs = flower[b][i];
        S[xs] = -1, setSlk(xs);
    }
    st[b] = 0;
}
bool onFoundedge(const edge &e) {
    int u = st[e.u], v = st[e.v];
    if (S[v] == -1) {
        pa[v] = e.u, S[v] = 1;
        int nu = st[match[v]];
        slk[v] = slk[nu] = 0;
        S[nu] = 0, qpush(nu);
    }
    else if (S[v] == 0) {
        int lca = getLca(u, v);
        if (!lca) return augment(u, v), augment(v, u), 1;
        else addBlossom(u, lca, v);
    }
    return 0;
}
bool matching() {
    fill(S, S + n_x + 1, -1), fill(slk, slk + n_x + 1, 0); q.clear();
    for (int x = 1; x <= n_x; ++ x)
        if (st[x] == x && !match[x])
            pa[x] = 0, S[x] = 0, qpush(x);
    if (q.empty()) return 0;
    while (1) {
        while (q.size()) {
            int u = q.front(); q.pop_front();
            if (S[st[u]] == 1) continue;
            for (int v = 1; v <= n; ++v)
                if (g[u][v].w > 0 && st[u] != st[v]) {
                    if (dist(g[u][v]) == 0) {
                        if (onFoundedge(g[u][v]))
                            return 1;
                    }
                    else update(u, st[v]);
                }
        }
        int d = inf;
        for (int b = n + 1; b <= n_x; ++ b)
            if (st[b] == b && S[b] == 1)
                d = min(d, lab[b] / 2);
        for (int x = 1; x <= n_x; ++ x)
            if (st[x] == x && slk[x]) {
                if (S[x] == -1)     d = min(d, dist(g[slk[x]][x]));
                else if (S[x] == 0) d = min(d, dist(g[slk[x]][x]) / 2);
            }
        for (int u = 1; u <= n; ++ u) {
            if (S[st[u]] == 0) {
                if (lab[u] <= d) return 0;
                lab[u] -= d;
            }
            else if (S[st[u]] == 1) lab[u] += d;
        }
        for (int b = n + 1; b <= n_x; ++ b)
            if (st[b] == b) {
                if (S[st[b]] == 0)      lab[b] += d * 2;
                else if (S[st[b]] == 1) lab[b] -= d * 2;
            }
        q.clear();
        for (int x = 1; x <= n_x; ++ x)
            if (st[x] == x && slk[x] && st[slk[x]] != x && dist(g[slk[x]][x]) == 0)
                if (onFoundedge(g[slk[x]][x])) return 1;
        for (int b = n + 1; b <= n_x; ++ b)
            if (st[b] == b && S[b] == 1 && lab[b] == 0)
                expandBlossom(b);
    }
    return 0;
}
pair<ll, int> weightBlossom() {
    fill (match, match + n + 1, 0);
    n_x = n; int n_matches = 0, w_max = 0;
    ll tot_weight = 0;
    for (int u = 0; u <= n; ++ u) st[u] = u, flower[u].clear();
    for (int u = 1; u <= n; ++ u)
        for (int v = 1; v <= n; ++ v) {
            ff[u][v] = (u == v ? u : 0);
            w_max = max(w_max, g[u][v].w);
        }
    for (int u = 1; u <= n; ++ u) lab[u] = w_max;
    while (matching()) n_matches ++;
    for (int u = 1; u <= n; ++ u)
        if (match[u] && match[u] < u)
            tot_weight += g[u][match[u]].w;
    return make_pair(tot_weight, n_matches);
}
int main() {
    cin >> n >> m;
    for(int u = 1; u <= n; ++ u)
        for(int v = 1; v <= n; ++ v)
            g[u][v] = edge{u, v, 0};
    for(int u, v, w; m --; ) {
        cin >> u >> v >> w;
        g[u][v].w = g[v][u].w = w;
    }
    cout << weightBlossom().first << '\n';
    for (int u = 1; u <= n; ++ u) cout << match[u] << ' ';
}   