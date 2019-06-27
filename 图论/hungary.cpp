/*二分图最大匹配, 时间复杂度O(nm)
 *例题:n1个男，n2个女，m个配对关系
 *输出最大配对数，然后对于每个男输出配对的女
 */
int n1, n2, m;
vector <int> e[N];
int vis[N], pre[N], ans, tim;
bool dfs(int u) {
	if (vis[u] == tim) return 0;
	vis[u] = tim;
	for (int v : e[u]) 
		if (!pre[v] || dfs(pre[v])) 
			return pre[v] = u, 1;
	return 0;
}
int main() {
	scanf("%d %d %d", &n1, &n2, &m);
	for (int u, v, i = 1; i <= m; i ++) {
		scanf("%d %d", &u, &v);
		e[v].push_back(u);
	}
	for (tim = 1; tim <= n2; tim ++) 
		if (dfs(tim)) ans ++;
	printf("%d\n", ans);
	for (int i = 1; i <= n1; i ++)
		printf("%d%c", pre[i], i == n1 ? '\n' : ' ');
	return 0;
}
