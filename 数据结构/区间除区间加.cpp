/*区间除区间加，导致区间的max-min始终不增
 *对某个区间做log次有效操作后会有max=min
 *所以对于max=min的区间，把区间除转成区间加操作即可方便处理
 */
struct node {ll minv, maxv, sum, lazy;}tr[N << 2];
ll div(ll x, int y) {//向下取整
	ll z = x / y;
	if (z * y > x) z --;
	return z;
}
void div(int o, int l, int r) {//对[s,t]的所有ai都除以z向下取整
	if (s <= l && r <= t && tr[o].maxv - div(tr[o].maxv, z) 
		== tr[o].minv - div(tr[o].minv, z)) {
		ll del = tr[o].maxv - div(tr[o].maxv, z);
		tr[o].maxv -= del, tr[o].minv -= del;
		tr[o].sum -= del * (r - l + 1), tr[o].lazy -= del;
		return;
	}
	pushdown(o, l, r);
	if (s <= mid) div(lc, l, mid);
	if (mid <  t) div(rc, mid + 1, r);
	pushup(o);
}