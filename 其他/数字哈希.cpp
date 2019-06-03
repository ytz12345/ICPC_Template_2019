namespace my_hash {
	const int N = (1 << 19) - 1;//散列大小，一定要取2^k-1，不超内存的情况下，Ｎ越大碰撞越少
	struct E {
		int v;
		E *nxt;
	}*g[N + 1], pool[N], *cur = pool, *p;
	int vis[N + 1], T;
	void ins(int v) {
		int u = v & N;
		if (vis[u] < T) vis[u] = T, g[u] = NULL;
		for (p = g[u]; p; p = p -> nxt) if (p -> v == v) return;
		p = cur ++; p -> v = v; p -> nxt = g[u]; g[u] = p;
	}
	int ask(int v) {
		int u = v & N;
		if (vis[u] < T) return 0;
		for (p = g[u]; p; p = p -> nxt) if (p -> v == v) return 1;
		return 0;
	}
	void init() {T ++, cur = pool;}//应对多组数据使用
}
