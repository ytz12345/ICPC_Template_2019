/*
 *为了维持树的平衡，可以一开始把所有点都读进来build
 *然后打flag标记该点是否被激活
 */
#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 5;

const int inf = 1 << 30;

int n, m;

int ql, qr, ans, tot, nowD;
//nowD = rand() & 1 ?
struct Node {
    int d[2];

    bool operator < (const Node &a) const {
        if (d[nowD] == a.d[nowD]) return d[!nowD] < a.d[!nowD];
        return d[nowD] < a.d[nowD];
    }
}pot[N];

struct node {
    int min[2], max[2], d[2];
    node *c[2];

    node() {
        min[0] = min[1] = max[0] = max[1] = d[0] = d[1] = 0;
        c[0] = c[1] = NULL;
    }

    node(int x, int y);

    void update();

    
}t[N], Null, *root;

node::node(int x, int y) {
    min[0] = max[0] = d[0] = x;
    min[1] = max[1] = d[1] = y;
    c[0] = c[1] = &Null;
}

inline void node::update() {
    if (c[0] != &Null) {
        if (c[0] -> max[0] > max[0]) max[0] = c[0] -> max[0];
        if (c[0] -> max[1] > max[1]) max[1] = c[0] -> max[1];
        if (c[0] -> min[0] < min[0]) min[0] = c[0] -> min[0];
        if (c[0] -> min[1] < min[1]) min[1] = c[0] -> min[1];
    }
    if (c[1] != &Null) {
        if (c[1] -> max[0] > max[0]) max[0] = c[1] -> max[0];
        if (c[1] -> max[1] > max[1]) max[1] = c[1] -> max[1];
        if (c[1] -> min[0] < min[0]) min[0] = c[1] -> min[0];
        if (c[1] -> min[1] < min[1]) min[1] = c[1] -> min[1];
    }
}

inline void build(node *&o, int l, int r, int D) {
    int mid = l + r >> 1;
    nowD = D;
    nth_element(pot + l, pot + mid, pot + r + 1);
    o = new node(pot[mid].d[0], pot[mid].d[1]);

    if (l != mid) build(o -> c[0], l, mid - 1, !D);
    if (r != mid) build(o -> c[1], mid + 1, r, !D);
    o -> update();
}

inline void insert(node *o) {
    node *p = root;
    int D = 0;
    while (1) {
        if (o -> max[0] > p -> max[0]) p -> max[0] = o -> max[0];
        if (o -> max[1] > p -> max[1]) p -> max[1] = o -> max[1];
        if (o -> min[0] < p -> min[0]) p -> min[0] = o -> min[0];
        if (o -> min[1] < p -> min[1]) p -> min[1] = o -> min[1];

        if (o -> d[D] >= p -> d[D]) {
            if (p -> c[1] == &Null) {
                p -> c[1] = o;
                return;
            } else p = p -> c[1];
        } else {
            if (p -> c[0] == &Null) {
                p -> c[0] = o;
                return;
            } else p = p -> c[0];
        }
        D ^= 1;
    } 
}

inline int dist(node *o) {
    int dis = 0;
    if (ql < o -> min[0]) dis += o -> min[0] - ql;
    if (ql > o -> max[0]) dis += ql - o -> max[0];
    if (qr < o -> min[1]) dis += o -> min[1] - qr;
    if (qr > o -> max[1]) dis += qr - o -> max[1];
    return dis; 
}

inline void query(node *o) {
    int dl, dr, d0;
    d0 = abs(o -> d[0] - ql) + abs(o -> d[1] - qr);
    if (d0 < ans) ans = d0;
    if (o -> c[0] != &Null) dl = dist(o -> c[0]);
    else dl = inf;
    if (o -> c[1] != &Null) dr = dist(o -> c[1]);
    else dr = inf;

    if (dl < dr) {
        if (dl < ans) query(o -> c[0]);
        if (dr < ans) query(o -> c[1]);
    } else {
        if (dr < ans) query(o -> c[1]);
        if (dl < ans) query(o -> c[0]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i ++)
        cin >> pot[i].d[0] >> pot[i].d[1];
    build(root, 1, n, 0);
    
    for (int x, y, z; m --; ) {
        cin >> x >> y >> z;
        if (x == 1) {
            t[tot].max[0] = t[tot].min[0] = t[tot].d[0] = y;
            t[tot].max[1] = t[tot].min[1] = t[tot].d[1] = z;
            t[tot].c[0] = t[tot].c[1] = &Null;
            insert(&t[tot ++]);
        } else {
            ans = inf, ql = y, qr = z;
            query(root), printf("%d\n", ans);
        }
    }
    return 0;
}