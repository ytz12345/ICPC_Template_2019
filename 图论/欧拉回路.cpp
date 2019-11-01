/*欧拉回路， t=1/2代表无向边/有向边*/
const int N = 4e5 + 10;
int n, m, t, in[N], out[N];
int vis[N], ans[N], head[N], cnt, cc;
struct edge{int next, to, id;}a[N];
void link(int x, int y, int id) {
    out[x] ++; in[y] ++;
    a[++ cnt] = (edge){head[x], y, id}; head[x] = cnt;
}
void dfs(int x) {
    for (int &i = head[x], nw; i; i = a[i].next)
        if(!vis[abs(a[i].id)])
            vis[abs(a[i].id)] = 1, nw = a[i].id, dfs(a[i].to), ans[++ cc] = nw;
}
int main() {
    cin >> t >> n >> m;
    for (int x, y, i = 1; i <= m; i ++) {
        cin >> x >> y; link(x, y, i);
        if (t == 1) link(y, x, -i);
    }
    for (int i = 1; i <= n; i ++)
        if ((t == 1 && (in[i] & 1)) || 
            (t == 2 && in[i] != out[i]))
            return puts("NO"), 0;
    for (int i = 1; i <= n; i ++) if (in[i]) {dfs(i); break;}
    if (cc < m) return puts("NO"), 0;
    puts("YES");
    for (int i = cc; i > 0; i --) printf("%d ", ans[i]);
}
