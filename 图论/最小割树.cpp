#include<bits/stdc++.h>
using namespace std;
const int N = 3005, inf = 0x3f3f3f3f;
typedef pair<int, int> P;
typedef long long ll;
struct edge{int to, cap, rev, id;};//id=1 positive edge, id=0 reverse edge
struct edge2{int to, cost;};
struct edge3{int from, to, cap;};
int V, E, level[N], iter[N];
vector<edge> G[N];
vector<edge2> gh[N];//最小割树的边
vector<edge3> edges;
void addEdge(int from, int to, int cap) {
    edges.push_back((edge3){from, to, cap});
}
void addAll() {
    for (auto e : edges) {
        G[e.from].push_back((edge){e.to, e.cap, (int)G[e.to].size(), 1});
        G[e.to].push_back((edge){e.from, 0, (int)G[e.from].size()-1, 0});
    }
}
void clearAll() {
    for (int i = 1; i <= V; i ++) G[i].clear();
}
void bfs(int s) {
    memset(level, -1, sizeof level);
    queue<int> que;
    level[s]  =0;
    que.push(s);
    while (!que.empty()) {
        int v = que.front(); que.pop();
        for (int i = 0; i < (int)G[v].size(); i ++) {
            edge &e = G[v][i];
            if(e.cap > 0 && level[e.to] < 0) {
                level[e.to] = level[v] + 1;
                que.push(e.to);
            }
        }
    }
}
int dfs(int v, int t, int f) {
    if (v == t) return f;
    for (int &i = iter[v]; i < (int)G[v].size(); i ++) {
        edge &e = G[v][i];
        if (level[v] < level[e.to] && e.cap > 0) {
            int d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}
int maxFlow(int s, int t) {
    int flow = 0, f;
    while(1) {
        bfs(s);
        if (level[t] < 0) return flow;
        memset(iter, 0, sizeof iter);
        while((f = dfs(s, t, inf)) > 0) flow += f;
    }
}
void build() {
    vector<int> p(V + 1, 1), cap(V + 1, 0);
    for (int s = 2; s <= V; s ++) {
        addAll();
        int t = p[s];
        cap[s] = maxFlow(s, t);
        vector<bool> in_cut(V + 1, 0);
        queue<int> que({s});
        in_cut[s] = true;
        while (!que.empty()) {
            int v = que.front(); que.pop();
            for (auto e : G[v]) {
                if (e.cap > 0 && !in_cut[e.to]) {
                    in_cut[e.to] = true; que.push(e.to);
                }
            }
        }
        for (int v = 1; v <= V; v ++)
            if (v != s && in_cut[v] && p[v] == t)
                p[v] = s;
        if (in_cut[p[t]]) {
            p[s] = p[t]; p[t] = s;
            swap(cap[s], cap[t]);
        }
        clearAll();
    }
    for (int v = 2; v <= V; v ++) {
        gh[p[v]].push_back((edge2){v, cap[v]});
        gh[v].push_back((edge2){p[v], cap[v]});
    }
}
int siz[N], son[N], fa[N], dep[N], top[N];
int cnt, dfn[N], pos[N], val[N];
int M, tr[N << 2];
void dfs1(int u) {
    siz[u] = 1;
    for (auto &e : gh[u]) {
        if (e.to == fa[u]) continue;
        dep[e.to] = dep[u] + 1, fa[e.to] = u, val[e.to] = e.cost;
        dfs1(e.to), siz[u] += siz[e.to];
        if (siz[e.to] > siz[son[u]]) son[u] = e.to;
    }
}
void dfs2(int u, int tp) {
    top[u] = tp; pos[u] = ++ cnt, dfn[cnt] = u;
    if (son[u]) dfs2(son[u], tp);
    for (auto &e : gh[u]) {
        if (e.to == fa[u] || e.to == son[u]) continue;
        dfs2(e.to, e.to);
    }   
}
int query(int s, int t) {
    int res = inf;
    for (s += M - 1, t += M + 1; s ^ t ^ 1; s >>= 1, t >>= 1) {
        if (~s&1) res = min(res, tr[s ^ 1]);
        if ( t&1) res = min(res, tr[t ^ 1]);
    }
    return res;
}
int ask(int u, int v) {
    int res = inf;
    for (int fu = top[u], fv = top[v]; fu != fv; fu = top[u = fa[fu]]) {
        if (dep[fu] < dep[fv]) swap(u, v), swap(fu, fv);
        res = min(res, query(pos[fu], pos[u]));
    }
    if (u == v) return res;
    if (dep[u] > dep[v]) swap(u, v);
    return min(res, query(pos[u] + 1, pos[v]));
}
int main() {
    ios::sync_with_stdio(false);
    cin >> V >> E; V ++; int q;
    for (int u, v, w, i = 0; i < E; i ++) 
        cin >> u >> v >> w, u ++, v ++, addEdge(u, v, w), addEdge(v, u, w);
    build(), dfs1(1), dfs2(1, 1); cin >> q;
    for (M = 1; M < V + 2; M <<= 1);
    memset (tr, 0x3f, sizeof tr);
    for (int i = 1; i <= V; i ++) tr[i + M] = val[dfn[i]];
    for (int i = M - 1; i > 0; i --) tr[i] = min(tr[i << 1], tr[i << 1 | 1]);
    for (int u, v; q --; ) {
        cin >> u >> v; u ++, v ++;
        cout << ask(u, v) << '\n';
    }
    return 0;
}