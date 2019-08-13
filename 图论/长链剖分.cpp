/* 长链剖分,选择深度最大的儿子作为重儿子,用于合并以深度为下标的信息
 * 像 dsu 一样,直接继承重儿子信息,然后按深度暴力合并其他儿子信息
 * 时间复杂度考虑每个节点作为轻儿子里的节点被合并只会有一次,所以 O(n)
 * 另一种用法,可以 O(nlogn) 预处理后,O(1) 找到 k 级祖先
 * example problem:给个树，第i个点有两个权值ai和bi
 * 现在求一条长度为m的路径，使得Σai/Σbi最小
 * 防爆栈trick:像重链剖分一样改成bfs
 */
int n, m;
double k, a[N], b[N], val[N];
int len[N], son[N];
vector <int> e[N];
double tmp[N], *ptr, *f[N], temp[N];
void dfs(int u, int fr) {
    for (int v : e[u]) {
        if (v == fr) continue;
        dfs(v, u);
        if (len[v] > len[son[u]]) son[u] = v;
    }
    len[u] = len[son[u]] + 1;
}
inline double F(int x, int y) {return y >= len[x] ? 0 : f[x][y];} 
bool solve(int u, int fr) {
    /* 为实现O(1)继承，采用f[u]-f[v]来保存u-fa[v]路径上的最小权值和(dep[v]>dep[u])
     * 即自底向上累加
     */
    if (son[u]) {
        f[son[u]] = f[u] + 1;
        if (solve(son[u], u)) return 1;
        f[u][0] = val[u] + f[u][1];
        if (len[u] >= m && f[u][0] - F(u, m) <= 0) return 1;
        for (int v : e[u]) {
            if (v == son[u] || v == fr) continue;
            f[v] = ptr, ptr += len[v];
            if (solve(v, u)) return 1;
            for (int j = 1; j <= len[v] && j <= m; j ++) {
                if (len[u] + j < m) continue;
                if (f[v][0] - F(v, j) + f[u][0] - F(u, m - j) <= 0) return 1;
            }
            temp[0] = val[u];
            for (int j = 1; j <= len[v]; j ++) 
                temp[j] = val[u] + min(f[u][1] - F(u, j + 1), f[v][0] - F(v, j));
            if (len[v] + 1 == len[u]) f[u][0] = temp[len[v]]; 
            for (int j = 1; j <= len[v]; j ++) 
                f[u][j] = f[u][0] - temp[j - 1];
            if (len[v] + 1 != len[u]) f[u][len[v] + 1] = f[u][0] - temp[len[v]]; 
        }   
    }
    else {
        f[u][0] = val[u];
        if (m == 1 && f[u][0] <= 0) return 1;
    }
    return 0;
}
bool judge(double mid) {
    f[1] = ptr = tmp, ptr += len[1], k = mid;
    for (int i = 1; i <= n; i ++) val[i] = a[i] - b[i] * k;
    return solve(1, 1);
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i ++) cin >> a[i];
    for (int i = 1; i <= n; i ++) cin >> b[i];
    if (m == -1) {
        double ans = 1e9;
        for (int i = 1; i <= n; i ++)
            ans = min(ans, a[i] / b[i]);
        printf("%.2f\n", ans);
        return 0;    
    }
    for (int u, v, i = 1; i < n; i ++) {
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1, 1);
    int flag = 0;
    double l = 0, r = 2e5, mid, ans;
    for (int i = 0; i < 50; i ++) {
        mid = (l + r) / 2;
        if (judge(mid)) r = mid - eps, flag = 1, ans = mid;
        else l = mid + eps;
    }
    if (flag) printf("%.2f\n", ans);
    else puts("-1");
    return 0;
}
