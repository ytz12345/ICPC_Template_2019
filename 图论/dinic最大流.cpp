#include <bits/stdc++.h>

using namespace std;

const int N = 20000;

const int M = 500000;

const int inf = 0x3f3f3f3f;

int n, m;

int s, t, len = 1;

int to[M], cap[M], nex[M];

int g[N], p[N], q[N], d[N];

void add(int x, int y, int v) {
	to[++ len] = y, cap[len] = v, nex[len] = g[x], g[x] = len;
	to[++ len] = x, cap[len] = 0, nex[len] = g[y], g[y] = len;
}

bool bfs() {
	int l = 1, r = 1, x, i;
	memset (d, 0, sizeof d);
	d[s] = 1, q[1] = s;
	while (l <= r) {
		x = q[l ++];
		for (i = g[x]; i; i = nex[i])
			if (cap[i] && !d[to[i]])
				d[to[i]] = d[x] + 1, q[++ r] = to[i];
	}
	return d[t];
}

int dfs(int x, int y) {
	if (x == t || y == 0) return y;
	int flow = 0;
	for (int &i = p[x]; i; i = nex[i]) {
		if (!cap[i] || d[to[i]] != d[x] + 1) continue;
		int f = dfs(to[i], min(y, cap[i]));
		flow += f, y -= f;
		cap[i] -= f, cap[i ^ 1] += f;
		if (!y) break;
	} 
	return flow;
}

int  dinic() {
	int maxflow = 0;
	while (bfs()) {
		memcpy(p, g, sizeof g);
		maxflow += dfs(s, inf);
	}
	return maxflow;
}

int main() {
	ios::sync_with_stdio(false);
	
	return 0;
}