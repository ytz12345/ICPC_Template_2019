int nowD, x[2], y[2], z;
struct node {
    int Max[2], Min[2], d[2];
    int val, lazy;
    node *c[2];
    node() {c[0] = c[1] = NULL;}
    void pushup();
    void pushdown();
    bool operator < (const node &a) const {return d[nowD] < a.d[nowD];}
}Null, nodes[N];
node *root = &Null;
inline void node::pushup() {
    if (c[0] != &Null) ...
    if (c[1] != &Null) ...
}
inline void node::pushdown() {
    if (c[0] != &Null) c[0] -> val = c[0] -> lazy = lazy;
    if (c[1] != &Null) c[1] -> val = c[1] -> lazy = lazy;
    lazy = -1;
}
inline node *build(int l, int r, int D) {
    int mid = l + r >> 1; nowD = D;
    nth_element(nodes + l, nodes + mid, nodes + r + 1);
    node *res = &nodes[mid];
    if (l != mid) res -> c[0] = build(l, mid - 1, !D);
    else res -> c[0] = &Null;
    if (r != mid) res -> c[1] = build(mid + 1, r, !D);
    else res -> c[1] = &Null;
    res -> pushup();
    return res;
}
inline int query(node *o) {
    if (o == &Null) return -1;
    if (o -> lazy != -1) o -> pushdown();
    if (x[0] > o -> Max[0] || y[0] > o -> Max[1] || x[0] < o -> Min[0] || y[0] < o -> Min[1]) return -1;
    if (x[0] == o -> d[0]) return o -> val;
    return max(query(o -> c[0]), query(o -> c[1]));
}
inline void modify(node *o) {
    if (o == &Null) return;
    if (o -> lazy != -1) o -> pushdown();
    if (x[0] > o -> Max[0] || y[0] > o -> Max[1] || x[1] < o -> Min[0] || y[1] < o -> Min[1]) return;
    if (x[0] <= o -> Min[0] && y[0] <= o -> Min[1] && x[1] >= o -> Max[0] && y[1] >= o -> Max[1]) {
        o -> val = o -> lazy = z;return;
    }
    if (x[0] <= o -> d[0] && y[0] <= o -> d[1] && x[1] >= o -> d[0] && y[1] >= o -> d[1]) o -> val = z;
    modify(o -> c[0]), modify(o -> c[1]);
}
int main() {
    /*初始化所有节点*/
    root = build(1, n, 0);
    /*对每个操作*/ {
        x[] = {}, y[] = {};
        query(root) / modify(root);
    }
}