/*时间复杂度O(n^3)*/
#include <bits/stdc++.h>
using namespace std;
const int N = 505;
int n, m, ans;
vector <int> e[N];
int tim, pre[N], mate[N];
int l, r, q[N], f[N], vis[N], sta[N];
int fa(int x) {
	return f[x] == x ? x : f[x] = fa(f[x]);
}
int lca(int x, int y) {
	for (++ tim, x = fa(x), y = fa(y); ; swap(x, y)) if (x) {
		if (vis[x] == tim) return x;
		vis[x] = tim, x = fa(pre[mate[x]]);	
	}
}
int blossom(int x, int y, int g) {
	for (; fa(x) != g; y = mate[x], x = pre[y]) {
		pre[x] = y;
		if (sta[mate[x]] == 1) sta[q[++ r] = mate[x]] = 0;
		if (fa(x) == x) f[x] = g;
		if (fa(mate[x]) == mate[x]) f[mate[x]] = g;
	}
}
int match(int s) {
	int y, las;
	memset (sta, -1, sizeof sta);
	memset (pre,  0, sizeof pre);
	for (int i = 1; i <= n; i ++) f[i] = i;
	for (q[l = r = 0] = s, sta[s] = 0; l <= r; l ++)
		for (int x : e[q[l]]) 
			if (sta[x] == -1) {
				sta[x] = 1, pre[x] = q[l];
				if (!mate[x]) {
					for (int j = q[l], i = x; j; j = pre[i = las])
						las = mate[j], mate[j] = i, mate[i] = j;
					return 1;
				}
				sta[q[++ r] = mate[x]] = 0;
			}
			else if (f[x] != f[q[l]] && sta[x] == 0)
				y = lca(x, q[l]), blossom(x, q[l], y), blossom(q[l], x, y);
	return 0;	
}
int main() {
	scanf("%d %d", &n, &m);
	for (int u, v, i = 0; i < m; i ++) {
		scanf("%d %d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
		if (!mate[u] && !mate[v])
			mate[u] = v, mate[v] = u, ans ++;
	}
	for (int i = 1; i <= n; i ++)
		if (!mate[i] && match(i))
			ans ++;
	printf("%d\n", ans);
	for (int i = 1; i <= n; i ++)
		printf("%d%c", mate[i], i == n ? '\n' : ' ');
}