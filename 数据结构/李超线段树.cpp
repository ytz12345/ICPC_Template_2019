/*porblem:每次在二维平面插入一条线段，询问所有线段中，与x=k的交点y值最大的线段id
 *李超线段树，标记永久化，线段树每个节点保存的是当前区间最占优势的那条线段
 *询问某个点，将根到它的路径上的所有节点保存的优势线段比较一下即可
 *一个区间裂成log个区间,每个区间会pushdown到叶节点，所以O(log^2n)
 *插入时记得特判斜率不存在即x1=x2的情况
 *缺点:永久化了标记,所以不支持删除操作
 *拓展应用:可以拿来维护斜率优化,不过多一个log,以及多个离散化
 */
struct Seg{double k, b;int id;};
struct node {Seg s;int hav;}tr[N << 2];
void pushdown(int o, int l, int r, Seg sg){
    if(!tr[o].hav) return (void) (tr[o].s = sg, tr[o].hav = 1);
    double l1 = sg.k * l + sg.b, r1 = sg.k * r + sg.b;
    double l2 = tr[o].s.k * l + tr[o].s.b, r2 = tr[o].s.k * r + tr[o].s.b;
    if(l2 >= l1 && r2 >= r1) return;
    if(l1 >= l2 && r1 >= r2) return (void) (tr[o].s = sg);
    double pos = (sg.b - tr[o].s.b) / (tr[o].s.k - sg.k);
    if(pos <= mid) pushdown(lc, l, mid, r1 > r2 ? tr[o].s : sg);
    else           pushdown(rc, mid + 1, r, l1 > l2 ? tr[o].s : sg);
    if((l1 > l2 && pos >= mid) || (r1 > r2 && pos < mid)) tr[o].s = sg;
}
void add(int o, int l, int r, int s, int t, Seg sg) {
    if (s <= l && r <= t) return (void)pushdown(o, l, r, sg);
    if (s <= mid) add(lc, l, mid, s, t, sg);
    if (mid <  t) add(rc, mid + 1, r, s, t, sg);
}
Seg query(int o, int l, int r, int p) {
    if (l == r) return tr[o].hav ? tr[o].s : (Seg){0, 0, 0};
    Seg sg = p <= mid ? query(lc, l, mid, p) : query(rc, mid + 1, r, p);
    if (!tr[o].hav) return sg;    
    double p1 = tr[o].s.k * p + tr[o].s.b, p2 = sg.k * p + sg.b;
    if(!sg.id || (p1 > p2 || (fabs(p1 - p2) < eps && tr[o].s.id < sg.id))) sg = tr[o].s;
    return sg;
}
/*以下为区间查询且维护的最小值,除计算交点外均为整数操作,d[i]代表i的实际x坐标*/
void pushup(int o, int l, int r) {
    tr[o].minv = min(tr[lc].minv, tr[rc].minv);
    tr[o].minv = min(tr[o].minv, min(tr[o].s.k * d[l], tr[o].s.k * d[r]) + tr[o].s.b);
}
void pushdown(int o, int l, int r, Seg sg){
    ll l1 = sg.k * d[l] + sg.b, r1 = sg.k * d[r] + sg.b;
    ll l2 = tr[o].s.k * d[l] + tr[o].s.b, r2 = tr[o].s.k * d[r] + tr[o].s.b;
    if(l2 <= l1 && r2 <= r1) return;
    if(l1 <= l2 && r1 <= r2) {tr[o].s = sg;
        if (l == r) {tr[o].minv = l1;return;}}
    else {double pos = 1.0 * (sg.b - tr[o].s.b) / (tr[o].s.k - sg.k);
        if(pos <= d[mid]) pushdown(lc, l, mid, r1 < r2 ? tr[o].s : sg);
        else              pushdown(rc, mid + 1, r, l1 < l2 ? tr[o].s : sg);
        if((l1 < l2 && pos > d[mid]) || (r1 < r2 && pos <= d[mid])) tr[o].s = sg;
    }
    pushup(o, l, r);
}
void build(int o, int l, int r) {
    tr[o].s = (Seg){0, tr[o].minv = inf};if (l == r) return;
    build(lc, l, mid);build(rc, mid + 1, r);
}
void add(int o, int l, int r, int s, int t, Seg sg) {
    if (s <= l && r <= t) return (void)pushdown(o, l, r, sg);
    if (s <= mid) add(lc, l, mid, s, t, sg);
    if (mid <  t) add(rc, mid + 1, r, s, t, sg);
    pushup(o, l, r);
}
ll ask(int o, int l, int r, int s, int t) {
    if (s <= l && r <= t) return tr[o].minv;
    ll res = min(tr[o].s.k * d[max(s, l)], tr[o].s.k * d[min(r, t)]) + tr[o].s.b;
    if (s <= mid) res = min(res, ask(lc, l, mid, s, t));
    if (mid <  t) res = min(res, ask(rc, mid + 1, r, s, t));
    return res;
}