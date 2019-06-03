/*类似线段树*/
const int N = 1e5 + 5;
const int Mod = 1e9 + 7;
int nowD, x[2], y[2], z;
struct node {
    int Max[2], Min[2], d[2];
    int val, lazy;
    node *c[2];
    node() {
        c[0] = c[1] = NULL;
    }
    void pushup();
    void pushdown();
    bool operator < (const node &a) const {
        return d[nowD] < a.d[nowD];
    }
}Null, nodes[N];
node *root = &Null;
inline void node::pushup() {
    if (c[0] != &Null) {
        if (c[0] -> Max[0] > Max[0]) Max[0] = c[0] -> Max[0];
        if (c[0] -> Max[1] > Max[1]) Max[1] = c[0] -> Max[1];
        if (c[0] -> Min[0] < Min[0]) Min[0] = c[0] -> Min[0];
        if (c[0] -> Min[1] < Min[1]) Min[1] = c[0] -> Min[1];
    }
    if (c[1] != &Null) {
        if (c[1] -> Max[0] > Max[0]) Max[0] = c[1] -> Max[0];
        if (c[1] -> Max[1] > Max[1]) Max[1] = c[1] -> Max[1];
        if (c[1] -> Min[0] < Min[0]) Min[0] = c[1] -> Min[0];
        if (c[1] -> Min[1] < Min[1]) Min[1] = c[1] -> Min[1];
    }
}
inline void node::pushdown() {
    if (c[0] != &Null) c[0] -> val = c[0] -> lazy = lazy;
    if (c[1] != &Null) c[1] -> val = c[1] -> lazy = lazy;
    lazy = -1;
}
inline node *build(int l, int r, int D) {
    int mid = l + r >> 1; nowD = D;
    nth_element(nodes + l, nodes + mid, nodes + r + 1);
    node *res = &nodes[mid];
    if (l != mid) res -> c[0] = build(l, mid - 1, !D);
    else res -> c[0] = &Null;
    if (r != mid) res -> c[1] = build(mid + 1, r, !D);
    else res -> c[1] = &Null;
    res -> pushup();
    return res;
}
inline int query(node *o) {
    if (o == &Null) return -1;
    if (o -> lazy != -1) o -> pushdown();
    if (x[0] > o -> Max[0] || y[0] > o -> Max[1] || x[0] < o -> Min[0] || y[0] < o -> Min[1]) return -1;
    if (x[0] == o -> d[0]) return o -> val;
    return max(query(o -> c[0]), query(o -> c[1]));
}
inline void modify(node *o) {
    if (o == &Null) return;
    if (o -> lazy != -1) o -> pushdown();
    if (x[0] > o -> Max[0] || y[0] > o -> Max[1] || x[1] < o -> Min[0] || y[1] < o -> Min[1]) return;
    if (x[0] <= o -> Min[0] && y[0] <= o -> Min[1] && x[1] >= o -> Max[0] && y[1] >= o -> Max[1]) {
        o -> val = o -> lazy = z;
        return;
    }
    if (x[0] <= o -> d[0] && y[0] <= o -> d[1] && x[1] >= o -> d[0] && y[1] >= o -> d[1]) o -> val = z;
    modify(o -> c[0]), modify(o -> c[1]);
}
int n, m, k, a[N], c[N], d[N];
int cnt, st[N], en[N], dfn[N], dep[N];
vector <int> e[N];
void dfs(int u) {
    st[u] = ++ cnt, dfn[cnt] = u;
    for (int v : e[u])
        dep[v] = dep[u] + 1, dfs(v);
    en[u] = cnt;
}
int main() {
    ios::sync_with_stdio(false);
    int T, ans;
    for (cin >> T; T --; ) {
        cin >> n >> m >> k, ans = cnt = 0;
        for (int i = 1; i <= n; i ++)
            e[i].clear();
        for (int u, i = 2; i <= n; i ++) {
            cin >> u;
            e[u].push_back(i);
        }
        dfs(1);
        for (int i = 1; i <= n; i ++) {
            nodes[i].Min[0] = nodes[i].Max[0] = nodes[i].d[0] = i;
            nodes[i].Min[1] = nodes[i].Max[1] = nodes[i].d[1] = dep[dfn[i]];
            nodes[i].val = 1, nodes[i].lazy = -1;
        }
        root = build(1, n, 0);
        for (int u, v, w, i = 1; i <= k; i ++) {
            cin >> u >> v >> w;
            if (w == 0) {
                x[0] = st[u], y[0] = dep[u];
                ans = (ans + 1ll * i * query(root) % Mod) % Mod;
            } else {
                x[0] = st[u], x[1] = en[u];
                y[0] = dep[u], y[1] = dep[u] + v;
                z = w, modify(root);
            }
        }
        cout << ans << endl;
    }
    return 0;
}