/*容易实现的预开内存池treap，每次head清空即可
 *如果初始要插入n个1，可改为类似splay的O(n)build写法
 *poolSize是单组数据的最大节点数，对于单组数据有很多插入和删除
 *导致使用的节点很多的数据，无法使用
 */
const int poolSize = 5e5 + 10;
struct node {
    node *c[2];
    int v, r, siz;
    void update();
    void init(int x);
};
node *null = new node(), *root = null;
void node::update() {
    siz = c[0] -> siz + c[1] -> siz + 1;
}
void node::init(int x) {
    v = x, r = rand(), siz = 1;
    c[0] = c[1] = null;
}
node nodesPool[poolSize];
int head;//每次head=0要清空!
node *newnode(int x) {
    node *res = &nodesPool[head ++];
    res -> init(x);
    return res;
}
void rot(node *&o, int d) {
    node *tmp = o -> c[!d];
    o -> c[!d] = tmp -> c[d], tmp -> c[d] = o;
    o -> update(), tmp -> update(), o = tmp;
}
void insert(node *&o, int x) {
    if (o == null) {
        o = newnode(x);
        return;
    }
    int d = x > o -> v ? 0 : 1;
    insert(o -> c[d], x);
    if (o -> c[d] -> r < o -> r) rot(o, !d);
    o -> update();
}
void del(node *&o, int x) {
    if (x == o -> v) {
        if (o -> c[0] == null) {o = o -> c[1]; return;}
        if (o -> c[1] == null) {o = o -> c[0]; return;}
        int d = o -> c[0] -> r < o -> c[1] -> r ? 1 : 0;
        rot(o, d), del(o -> c[d], x);
    }
    else del(o -> c[x <= o -> v], x);
    o -> update();
}
void build(node *&o, int l, int r) {
    o = newnode(1);
    if (l == r) return;
    int mid = l + r >> 1;
    if (l < mid) build(o -> c[0], l, mid - 1);
    if (o -> c[0] != null && o -> c[0] -> r < o -> r) swap(o -> c[0] -> r, o -> r);
    if (mid < r) build(o -> c[1], mid + 1, r);
    if (o -> c[1] != null && o -> c[1] -> r < o -> r) swap(o -> c[1] -> r, o -> r);
    o -> update();
}