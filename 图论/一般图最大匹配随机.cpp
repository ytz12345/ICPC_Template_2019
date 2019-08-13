/*一般图最大匹配, 时间复杂度O(n^3)
 *例题:n个人，m个配对关系
 *输出最大配对数，然后对于每个人输出配对的人
 *以下是O(n^3)随机匹配做法，可能会被hack
 */
const int N = 505, LIM = 3;
int n, m, tim;
int cnt, ans[N], bel[N], vis[N];
vector <int> e[N];
bool dfs(int u) {
	vis[u] = tim; random_shuffle(e[u].begin(), e[u].end());
	for (int v : e[u]) {
		int w = bel[v]; if (vis[w] == tim) continue;
		bel[u] = v, bel[v] = u, bel[w] = 0; if (!w || dfs(w)) return 1;
		bel[u] = 0, bel[v] = w, bel[w] = v;
	}
	return 0;
}
int main() {
	scanf("%d%d", &n, &m);
	for (int u, v; m --; ) {
		scanf("%d %d", &u, &v);
		e[u].push_back(v); 
		e[v].push_back(u);
	}
	for (int t = 1; t <= LIM; t ++) {
		for (int i = 1; i <= n; i ++) {
			if (!bel[i]) tim ++, dfs(i);
			int tmp = 0; 
			for (int i = 1; i <= n; i ++)
				tmp += bel[i] != 0;
			if (tmp > cnt) {
				cnt = tmp;
				for (int i = 1; i <= n; i ++)
					ans[i] = bel[i];
			}
		}
	}
	printf("%d\n", cnt / 2);
	for (int i = 1; i <= n; i ++)
		printf("%d ", ans[i]);
}