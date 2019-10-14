/*DSU
 *用途:O(nlogn)解决无修改的子树询问问题，需要保证操作支持删除
 *  比如子树中不同颜色数，出现最多的颜色等
 *解决方法:对于每个节点，先对所有轻儿子，dfs下去求一遍，再消除影响
 *  然后再dfs自己的重儿子，然后不消除影响，再加上所有轻儿子
 *  就得到当前节点为根的子树的答案了
 */
int n, c[N];
int cnt[N], maxCnt;
int siz[N], son[N];
vector <int> e[N];
ll ans[N], sum[N];
void dfs1(int u, int fr) {
    siz[u] = 1;
    for (int v : e[u]) {
        if (v == fr) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
}
void update(int x, int y) {
    sum[cnt[x]] -= x;
    cnt[x] += y;
    sum[cnt[x]] += x;
    if (cnt[x] > maxCnt) maxCnt = cnt[x];
    if (sum[maxCnt] == 0) maxCnt --;
}
void dfs3(int u, int fr, int val) {
    update(c[u], val);
    for (int v : e[u]) {
        if (v == fr) continue;
        dfs3(v, u, val);
    }
}
void dfs2(int u, int fr) {
    for (int v : e[u]) {
        if (v == fr || v == son[u]) continue;
        dfs2(v, u), dfs3(v, u, -1);
    }
    if (son[u]) dfs2(son[u], u);
    for (int v : e[u]) {
        if (v == fr || v == son[u]) continue;
        dfs3(v, u, 1);
    }
    update(c[u], 1);
    ans[u] = sum[maxCnt];
}
int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i ++)
        cin >> c[i];
    for (int u, v, i = 1; i < n; i ++) {
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs1(1, 1), dfs2(1, 1);
    for (int i = 1; i <= n; i ++)
        cout << ans[i] << ' ';  
    return 0;
}