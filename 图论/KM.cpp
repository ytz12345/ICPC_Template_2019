/*KM最坏O(N^3)*/
const int N = 407, INF = 1e9 + 7, NPOS = -1;
struct KM {
	int n;
	ll hl[N], hr[N], slk[N], a[N][N];
	int fl[N], fr[N], vl[N], vr[N], pre[N], q[N], ql, qr;
	int check(int i) {
		if (vl[i] = 1, fl[i] != NPOS) 
			return vr[q[qr ++] = fl[i]] = 1;
		while (i != NPOS) swap(i, fr[fl[i] = pre[i]]);
		return 0;
	}
	void bfs(int s) {
		fill(slk, slk + n, INF), fill(vl, vl + n, 0), fill(vr, vr + n, 0);
		for (vr[q[ql = 0] = s] = qr = 1; ; ) {
			for (ll d; ql < qr;)
				for (int i = 0, j = q[ql ++]; i < n; ++ i)
					if(!vl[i] && slk[i] >= (d = hl[i] + hr[j] - a[i][j]))
						if (pre[i] = j, d) slk[i] = d;
						else if (!check(i)) return;
			ll d = INF;
			for (int i = 0; i < n; ++ i)
				if (!vl[i] && d > slk[i]) 
					d = slk[i];
			for (int i = 0; i < n; ++ i) {
				if(vl[i]) hl[i] += d;
				else     slk[i] -= d;
				if(vr[i]) hr[i] -= d;
			}
			for (int i = 0; i < n; ++ i)
				if (!vl[i] && !slk[i] && !check(i))
					return;
		}
	}
	void ask() {
		fill(fl, fl + n, NPOS), fill(fr, fr + n, NPOS), fill(hr, hr + n, 0);
		for (int i = 0; i < n; ++ i) hl[i] =* max_element(a[i], a[i] + n);
		for (int j = 0; j < n; ++ j) bfs(j);
	}
}km;
int main() {
	int nl, nr, m, u, v;
	for (cin >> nl >> nr >> m; m --; )
		cin >> u >> v, cin >> km.a[u][v];
	km.n = max(nl, nr) + 1, km.ask();
	long long ans=0;
	for (int i = 1; i <= nl; i ++) ans += km.a[i][km.fl[i]];
	cout << ans << '\n';
	for (int i = 1; i <= nl; i ++) 
		cout << (km.a[i][km.fl[i]] ? km.fl[i] : 0) << ' ';
}