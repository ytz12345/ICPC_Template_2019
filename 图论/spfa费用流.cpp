const int inf = 0x3f3f3f3f;
int s, t, ans, len, maxflow;
int g[N], head[N], incf[N], path[N], pre[N], vis[N], d[N];
struct edge{int to, next, cap, cost;}e[M];
void add(int u, int v, int w, int c) {
    e[++ len] = (edge){v, head[u], w, c}, head[u] = len;
    e[++ len] = (edge){u, head[v], 0, -c}, head[v] = len;
}
bool bfs() {
    static int u, v, w;
    static deque<int> q; 
    memset (d, 0x3f, sizeof d);
    d[s] = 0, q.push_back(s);
    while (!q.empty()) {
        vis[u = q.front()] = 0; q.pop_front();
        for (int i = head[u]; i; i = e[i].next) {
            if (e[i].cap && d[v = e[i].to] > (w = d[u] + e[i].cost)) {
                d[v] = w;
                if (!vis[v]) {
                    vis[v] = 1;
                    d[v] < (q.empty() ? 0 : d[q.front()]) ? q.push_front(v) : q.push_back(v);
                }
            }
        }
    }
    return d[t] < inf;
}
int dfs(int x, int y) {
    if (x == t) return y;
    int v, f, flow = 0; vis[x] = 1;
    for (int &i = g[x]; i; i = e[i].next) {
        v = e[i].to;
        if (vis[v] || !e[i].cap || d[x] + e[i].cost != d[v]) continue;
        f = dfs(v, min(y, e[i].cap));
        if (f) ans += f * e[i].cost, e[i].cap -= f, e[i ^ 1].cap += f, flow += f, y -= f;
        if (!y) break;
    } 
    return vis[x] = 0, flow;
}
void costflow() {
    maxflow = 0; static int res = 0; 
    while (bfs()) {
        memcpy(g, head, sizeof head);
        while ((res = dfs(s, inf)) != 0) maxflow += res;
    }
}