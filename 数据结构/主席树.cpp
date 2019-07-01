const int N = 130000;
const int M = N * 20;
//主席树节点数，可以直接稳妥选择N*(5+logN)
struct {
    int siz, l, r;
    ll sum, val;
}tr[M];
#define l(x) tr[x].l
#define r(x) tr[x].r
#define s(x) tr[x].sum
#define v(x) tr[x].val
#define sz(x) tr[x].siz
#define mid (l + r >> 1)
int tot, root[N];
int build(int l, int r) {
    int x = ++ tot;
    if (l < r) {
        l(x) = build(l, mid);
        r(x) = build(mid + 1, r); 
    }
    return x;
}
int change(int o, int l, int r, int p, int y) {
    //在p的位置插入一个y
    int x = ++ tot;
    s(x) = s(o) + y, sz(x) = sz(o) + 1;
    l(x) = l(o), r(x) = r(o), v(x) = y;
    if (l < r) {
        if (p <= mid) l(x) = change(l(o), l, mid, p, y);
        else r(x) = change(r(o), mid + 1, r, p, y);
    }
    return x;
}
ll ask(int o1, int o2, int l, int r, int k) {
    //求(l,r]区间前k小的数之和，有o1=root[l],o2=root[r]
    if (l == r) return v(o2) * k;
    int lsz = sz(l(o2)) - sz(l(o1));
    if (lsz == k) return s(l(o2)) - s(l(o1));
    if (lsz < k) return s(l(o2)) - s(l(o1)) + ask(r(o1), r(o2), mid + 1, r, k - lsz);
    return ask(l(o1), l(o2), l, mid, k);
}