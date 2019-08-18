/*询问1-n中多少个i,满足对任意j<i都有h[j]<h[i]
 *单点修改,ans=tr[1].len
 *也可分块做O(n*(nlogn)^0.5)
 */
struct node {double mx;int len;}tr[N << 2]; 
int calc(int o, int l, int r, double v) {
    if(l == r) return tr[o].mx > v;
    int mid = (l + r) / 2;
    if(tr[lc].mx <= v) return calc(rc, mid + 1, r, v);
    return tr[o].len - tr[lc].len + calc(lc, l, mid, v);
}
void change(int o, int l, int r, int p, double v) {
    if(r == l) {tr[o] = (node){v, 1};return;}
    int mid = (l + r) >> 1;
    if(p > mid) change(rc, mid + 1, r, p, v);
    else change(lc, l, mid, p, v);
    tr[o].mx = std::max(tr[lc].mx, tr[rc].mx);
    tr[o].len = tr[lc].len + calc(rc, mid + 1, r, tr[lc].mx);
}