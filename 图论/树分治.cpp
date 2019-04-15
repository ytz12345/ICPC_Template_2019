#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e5 + 5;

vector <int> e[N];

int n, a[N];

int root, _left, vis[N];

int siz[N], maxv[N];

void find_root(int u, int fr) {
	siz[u] = 1, maxv[u] = 0;
	for (int v : e[u]) {
		if (v == fr || vis[v]) continue;
		find_root(v, u);
		siz[u] += siz[v];
		maxv[u] = max(maxv[u], siz[v]);
	}
	maxv[u] = max(maxv[u], _left - siz[u]);
	if (!root || maxv[u] < maxv[root])
		root = u;
}

void dfs(int u, int fr) {
	siz[u] = 1;
	for (int v : e[u]) {
		if (v == fr || vis[v]) continue;
		find_root(v, u);
		siz[u] += siz[v];
	}
}

void solve(int u, int w) {
	dfs(u, u);//update siz[]
	a[u] = w, vis[u] = 1;
	for (int v : e[u]) {
		if (vis[v]) continue;
		_left = siz[v];
		root = 0;
		find_root(v, v);
		solve(root, w + 1);
	}
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int u, v, i = 1; i < n; i ++) {
    	cin >> u >> v;
    	e[u].push_back(v);
    	e[v].push_back(u);
    }
    _left = n, root = 0, find_root(1, 1);
    solve(root, 0);
    for (int i = 1; i <= n; i ++)
    	printf("%c ", 'A' + a[i]);
    return 0;
}
