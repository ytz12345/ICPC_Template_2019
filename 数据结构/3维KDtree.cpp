/*O(n^(2-1/k)),k为维度,查询区间最大值*/
int nowD, ans, x[3], y[3];//x,y数组存放查询区间各维度的min和max
int n, m, a[N], b[N], c[N], d[N];
struct node {
    int Max[3], Min[3], d[3];
    int val, maxv;
    node *c[2];
    node() {
        c[0] = c[1] = NULL;
        val = maxv = 0;
    }
    void pushup();
    bool operator < (const node &a) const {
        return d[nowD] < a.d[nowD];
    }
}Null, nodes[N];
node *root = &Null;
inline void node::pushup() {
    if (c[0] != &Null) {
        if (c[0] -> Max[1] > Max[1]) Max[1] = c[0] -> Max[1];
        if (c[0] -> Max[2] > Max[2]) Max[2] = c[0] -> Max[2];
        if (c[0] -> Min[0] < Min[0]) Min[0] = c[0] -> Min[0];
        if (c[0] -> Min[2] < Min[2]) Min[2] = c[0] -> Min[2];
        if (c[0] -> maxv > maxv) maxv = c[0] -> maxv;
    }
    if (c[1] != &Null) {
        if (c[1] -> Max[1] > Max[1]) Max[1] = c[1] -> Max[1];
        if (c[1] -> Max[2] > Max[2]) Max[2] = c[1] -> Max[2];
        if (c[1] -> Min[0] < Min[0]) Min[0] = c[1] -> Min[0];
        if (c[1] -> Min[2] < Min[2]) Min[2] = c[1] -> Min[2];
        if (c[1] -> maxv > maxv) maxv = c[1] -> maxv;
    }
}
inline node *build(int l, int r) {
    int mid = l + r >> 1; nowD = rand() % 3;
    nth_element(nodes + l, nodes + mid, nodes + r + 1);
    node *res = &nodes[mid];
    if (l != mid) res -> c[0] = build(l, mid - 1);
    else res -> c[0] = &Null;
    if (r != mid) res -> c[1] = build(mid + 1, r);
    else res -> c[1] = &Null;
    res -> pushup();
    return res;
}
inline int calc(node *o) {
    if (y[0] < o -> Min[0] || x[1] > o -> Max[1] || x[2] > o -> Max[2] || y[2] < o -> Min[2]) return -1;
    return o -> maxv;
}
inline void query(node *o) {
    if (o -> val > ans && y[0] >= o -> d[0] && x[1] <= o -> d[1] && x[2] <= o -> d[2] && y[2] >= o -> d[2]) ans = o -> val;
    int dl, dr;
    if (o -> c[0] != &Null) dl = calc(o -> c[0]);
    else dl = -1;
    if (o -> c[1] != &Null) dr = calc(o -> c[1]);
    else dr = -1;
    if (dl > dr) {
        if (dl > ans) query(o -> c[0]);
        if (dr > ans) query(o -> c[1]);
    } else {
        if (dr > ans) query(o -> c[1]);
        if (dl > ans) query(o -> c[0]);
    }
}
int main() {
    /*初始化所有节点*/
    root = build(1, n);
    /*对每个查询*/ {
        x[] = {}, y[] = {};
        ans = 0, query(root);
    }
}