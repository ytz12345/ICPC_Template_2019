/* 长链剖分,选择深度最大的儿子作为重儿子,用于合并以深度为下标的信息
 * 像 dsu 一样,直接继承重儿子信息,然后按深度暴力合并其他儿子信息
 * 时间复杂度考虑每个节点作为轻儿子里的节点被合并只会有一次,所以 O(n)
 * 另一种用法,可以 O(nlogn) 预处理后,O(1) 找到 k 级祖先
 */
int n;
int len[N], son[N], ans[N];
vector <int> e[N];
int tmp[N], *ptr, *f[N];
void dfs(int u, int fr) {
    for (int v : e[u]) {
        if (v == fr) continue;
        dfs(v, u);
        if (len[v] > len[son[u]]) son[u] = v;
    }
    len[u] = len[son[u]] + 1;
}
void dp(int u, int fr) {
    f[u][0] = 1;
    if (son[u]) {
        f[son[u]] = f[u] + 1;
        dp(son[u], u);
        ans[u] = ans[son[u]] + 1;
    }
    for (int v : e[u]) {
        if (v == son[u] || v == fr) continue;
        f[v] = ptr, ptr += len[v];
        dp(v, u);
        for (int j = 0; j < len[v]; j ++) {
            f[u][j + 1] += f[v][j];
            if ((f[u][j + 1] > f[u][ans[u]]) || (f[u][j + 1] == f[u][ans[u]] && j + 1 < ans[u]))
                ans[u] = j + 1;
        }
    }
    if (f[u][0] >= f[u][ans[u]]) ans[u] = 0;
}
int main() {
    in(n);
    for (int u, v, i = 1; i < n; i ++) {
        in(u), in(v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1, 1);
    f[1] = ptr = tmp, ptr += len[1];
    dp(1, 1);
    for (int i = 1; i <= n; i ++)
        printf("%d\n", ans[i]);
    return 0;
}
