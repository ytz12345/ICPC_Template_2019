int query(int u, int v) {//查询链上点权和
	int res = 0;
	for (int fu = top[u], fv = top[v]; fu != fv; fu = top[u = fa[fu]]) {
		if (dep[fu] < dep[fv]) swap(fu, fv), swap(u, v);
		res += ask(pos[fu], pos[u]);
	}
	if (dep[u] > dep[v]) swap(u, v);
	return res + ask(pos[u], pos[v]);
}