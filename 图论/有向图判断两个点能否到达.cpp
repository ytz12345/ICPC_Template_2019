/* 原题:n个点的有向图，k对点(u,v)满足u可达v
 * p对点(u,v)满足u不可达v，问这个图是否存在
 * 解法:按照p对可达点直接连边构图，然后考虑验证
 * a[i][j]=0/1表示i是否可达j，我们对j分块，bitset加速
 * 时间O(n*m/32) 空间O(n*n/blk) blk随便取
 */
const int N = 1e5 + 2;
const int BLK = 5000;
int n, k, p;
int d[N];
vector <int> e[N], f[N], ck[N];
int top, sta[N], in[N];
int cnt, dfn[N], low[N], vis[N];
int sum, bel[N];
bitset <BLK> a[N];
queue <int> q;
int topo[N];
void tarjan(int u) {
	vis[u] = in[u] = 1;
	sta[++ top] = u, dfn[u] = low[u] = ++ cnt;
	for (int v : e[u]) 
		if (!vis[v]) {
			tarjan(v);
			low[u] = min(low[v], low[u]);
		}
		else if (in[v]) 
			low[u] = min(low[v], low[u]);
	if (low[u] == dfn[u]) {
		sum ++; int i;
		while (1) {
			i = sta[top --];
			in[i] = 0, bel[i] = sum;
			if (i == u) break;
		}
	}
}
int main() {
	cin >> n >> k;
	for (int u, v, i = 1; i <= k; i ++) {
		cin >> u >> v;
		e[u].push_back(v);
	}
	cin >> p;
	for (int u, v, i = 1; i <= p; i ++) {
		cin >> u >> v;
		f[u].push_back(v);
	}
	for (int i = 1; i <= n; i ++)
		if (!vis[i])
			tarjan(i);
	for (int i = 1; i <= n; i ++) {
		for (int j : f[i]) {
			if (bel[i] == bel[j]) return puts("NO"), 0;
			ck[bel[i]].push_back(bel[j]);//check
		}
		f[i].clear();
	}
	for (int i = 1; i <= n; i ++)
		for (int j : e[i]) {
			if (bel[i] == bel[j]) continue;
			f[bel[i]].push_back(bel[j]);
			d[bel[j]] ++;
		}
	cnt = 0;
	for (int i = 1; i <= sum; i ++)
		if (!d[i])
			q.push(i);
	while (!q.empty()) {
		int now = q.front(); q.pop();
		topo[++ cnt] = now;
		for (int j : f[now]) {
			d[j] --;
			if (d[j] == 0) q.push(j);
		}
	}
	for (int i = 1, t = (sum + BLK - 1) / BLK; i <= t; i ++) {
		for (int j = sum; j; j --) {
			int u = topo[j];
			a[u].reset();
			if (BLK * (i - 1) < u && u <= BLK * i)
				a[u][u - BLK * (i - 1) - 1] = 1;
			for (int v : f[u]) 
				a[u] |= a[v];
		}
		for (int j = 1; j <= sum; j ++)
			for (int v : ck[j]) 
				if (BLK * (i - 1) < v && v <= BLK * i && 
					a[j][v -  BLK * (i - 1) - 1] == 1) {
					puts("NO");
					return 0;
				}
	}
	printf("YES\n%d\n", k);
	for (int i = 1; i <= n; i ++)
		for (int j : e[i])
			printf("%d %d\n", i, j);
	return 0;
}
