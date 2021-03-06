/*调整重构系数可以影响常数
 *询问多就让系数接近0.70-0.75，询问少就让系数在0.8-0.90
 */
const int inf = 1e9;
int n, m, tot, nowD;
struct node {
    int Max[2], Min[2], d[2];
    int sum, siz, val;
    node *c[2];
    node() {
        Max[0] = Max[1] = -inf;
        Min[0] = Min[1] = inf;
        sum = val = siz = 0;
        c[0] = c[1] = NULL;
        d[0] = d[1] = 0;
    }
    void update();
}Null, nodes[200010], *temp[200010];
node *root = &Null;
inline void node::update() {
    siz = c[0] -> siz + c[1] -> siz + 1;
    sum = c[0] -> sum + c[1] -> sum + val;
    if (c[0] != &Null) ...
    if (c[1] != &Null) ...
}
inline bool cmp(const node *a, const node *b) {
    return a -> d[nowD] < b -> d[nowD];
}
inline void traverse(node *o) {
    if (o == &Null) return;
    temp[++ tot] = o;
    traverse(o -> c[0]);
    traverse(o -> c[1]);
}
inline node *build(int l, int r, int D) {
    int mid = l + r >> 1; nowD = D;
    nth_element(temp + l, temp + mid, temp + r + 1, cmp);
    node *res = temp[mid];
    res -> Max[0] = res -> Min[0] = res -> d[0];
    res -> Max[1] = res -> Min[1] = res -> d[1];
    if (l != mid) res -> c[0] = build(l, mid - 1, !D);
    else res -> c[0] = &Null;
    if (r != mid) res -> c[1] = build(mid + 1, r, !D);
    else res -> c[1] = &Null;
    res -> update();
    return res;
}
int x, y, a, b, tmpD;
node **tmp;
inline void rebuild(node *&o, int D) {
    tot = 0, traverse(o), o = build(1, tot, D);
}
inline void insert(node *&o, node *p, int D) {
    if (o == &Null) {o = p; return;}
    if (p -> Max[0] > o -> Max[0]) o -> Max[0] = p -> Max[0];
    if (p -> Max[1] > o -> Max[1]) o -> Max[1] = p -> Max[1];
    if (p -> Min[0] < o -> Min[0]) o -> Min[0] = p -> Min[0];
    if (p -> Min[1] < o -> Min[1]) o -> Min[1] = p -> Min[1];
    o -> siz ++, o -> sum += p -> sum;
    insert(o -> c[p -> c[D] >= o -> c[D]], p, !D);
    if (max(o -> c[0] -> siz, o -> c[1] -> siz) > int(o -> siz * 0.75 + 0.5)) tmpD = D, tmp = &o;
}
inline int query(node *o) {//查询区间为[x,a]*[y,b]的权值和
    if (o == &Null) return 0;
    if (x > o -> Max[0] || y > o -> Max[1] || a < o -> Min[0] || b < o -> Min[1]) return 0;
    if (x <= o -> Min[0] && y <= o -> Min[1] && a >= o -> Max[0] && b >= o -> Max[1]) return o -> sum;
    return (x <= o -> d[0] && y <= o -> d[1] && a >= o -> d[0] && b >= o -> d[1] ? o -> val : 0) 
        + query(o -> c[1]) + query(o -> c[0]);
}
int main() {
    node *ttt = &Null;
    /*对每个操作*/ {
        /*在(x,y)的位置增加权值为a的点*/ {
            n ++, nodes[n].sum = nodes[n].val = a, nodes[n].siz = 1;
            nodes[n].Max[0] = nodes[n].Min[0] = nodes[n].d[0] = x;
            nodes[n].Max[1] = nodes[n].Min[1] = nodes[n].d[1] = y;
            nodes[n].c[0] = nodes[n].c[1] = &Null;
            tmp = &(ttt), insert(root, &nodes[n], 0);
            if (*tmp != &Null) rebuild(*tmp, tmpD); 
        }   
        /*查询*/ {x, a, y, b = ....; query(root);}
    }
}