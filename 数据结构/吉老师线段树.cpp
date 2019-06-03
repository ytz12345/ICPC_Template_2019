/*区间每个数变为min(a[i],t) + 区间最大 + 区间和 O(nlog)*/
const int N = (1 << 20) + 5;
#define lc (o << 1)
#define rc (lc | 1)
struct node {
	int max1, max2, cnt;
	ll sum;
}tr[N << 1];
int T, n, m;
int op, x, y, t;
int a[N];
void pushup(int o) {
	if (tr[lc].max1 == tr[rc].max1) {
		tr[o].max1 = tr[lc].max1;
		tr[o].cnt = tr[lc].cnt + tr[rc].cnt;
		tr[o].max2 = max(tr[lc].max2, tr[rc].max2);
	}
	else {
		if (tr[lc].max1 > tr[rc].max1) {
			tr[o] = tr[lc];
			tr[o].max2 = max(tr[o].max2, tr[rc].max1);
		}
		else {
			tr[o] = tr[rc];
			tr[o].max2 = max(tr[o].max2, tr[lc].max1);
		}
	}
	tr[o].sum = tr[lc].sum + tr[rc].sum;
}
void pushdown(int o) {
	if (tr[o].max1 < tr[lc].max1) {
		tr[lc].sum += 1ll * (tr[o].max1 - tr[lc].max1) * tr[lc].cnt;
		tr[lc].max1 = tr[o].max1;
	}
	if (tr[o].max1 < tr[rc].max1) {
		tr[rc].sum += 1ll * (tr[o].max1 - tr[rc].max1) * tr[rc].cnt;
		tr[rc].max1 = tr[o].max1;
	}
}
void build(int o, int l, int r) {
	if (l == r) {
		tr[o].max1 = tr[o].sum = a[r];
		tr[o].cnt = 1, tr[o].max2 = 0;
		return;
	}
	int mid = l + r >> 1;
	build(lc, l, mid);
	build(rc, mid + 1, r);
	pushup(o);
}
void update(int o, int l, int r, int s, int t, int v) {
	if (v >= tr[o].max1) return;
	pushdown(o);
	if (s <= l && r <= t) {
		if (v > tr[o].max2) {
			tr[o].sum += 1ll * (v - tr[o].max1) * tr[o].cnt;
			tr[o].max1 = v;
			return;
		}	
	}
	int mid = l + r >> 1;
	if (s <= mid) update(lc, l, mid, s, t, v);
	if (t >  mid) update(rc, mid + 1, r, s, t, v);
	pushup(o);
}
ll ask_max(int o, int l, int r, int s, int t) {
	if (s <= l && r <= t) return tr[o].max1;
	pushdown(o);
	int mid = l + r >> 1;
	ll res = 0;
	if (s <= mid) res = max(res, ask_max(lc, l, mid, s, t));
	if (t >  mid) res = max(res, ask_max(rc, mid + 1, r, s, t));
	return res; 
}
ll ask_sum(int o, int l, int r, int s, int t) {
	if (s <= l && r <= t) return tr[o].sum;
	pushdown(o);
	int mid = l + r >> 1;
	ll res = 0;
	if (s <= mid) res += ask_sum(lc, l, mid, s, t);
	if (t >  mid) res += ask_sum(rc, mid + 1, r, s, t);
	return res; 
}
int main() {
	ios::sync_with_stdio(false); 	
	for (cin >> T; T --; ) {
		cin >> n >> m;
		for (int i = 1; i <= n; i ++)
			cin >> a[i];
		build(1, 1, n);
		while (m --) {
			cin >> op;
			if (op == 0) {
				cin >> x >> y >> t;
				update(1, 1, n, x, y, t);
			}
			else if (op == 1) {
				cin >> x >> y;
				cout << ask_max(1, 1, n, x, y) << '\n'; 
			}
			else {
				cin >> x >> y;
				cout << ask_sum(1, 1, n, x, y) << '\n'; 	 
			}
		}
	}
	return 0;
}
