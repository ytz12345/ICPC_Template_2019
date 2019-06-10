#define mid (l + r >> 1)
int n, m, a, b, len, tot;
struct node {
	bool rev; //翻转标记
	int v, siz;
	node *c[2];
	node():rev(0),v(0),siz(0),c{NULL, NULL}{}
	node *init(int x);
	void pushdown();
	void mata() {siz = c[0] -> siz + c[1] -> siz + 1;}
	int cmp(int k) {return k<=c[0]->siz?0:(k==c[0]->siz+1?-1:1);}
	void print();
}pool[N], *null = new node(); 
node *node::init(int x){rev=0, v=x, siz=1, c[0]=c[1]=null;return this;}
void node::pushdown() {
	if (!rev) return;
	if (c[0] != null) c[0] -> rev ^= 1;
	if (c[1] != null) c[1] -> rev ^= 1;
	swap(c[0], c[1]), rev = 0;
}
void node::print() {
	pushdown();
	if (c[0] != null) c[0] -> print();
	if (1 <= v && v <= n) printf("%d ", v);
	if (c[1] != null) c[1] -> print();
}
node *build(int l, int r) {//初始序列为1-n
	if (l == r) return pool[tot ++].init(r);
	node *tmp = pool[tot ++].init(mid);
	if (l < mid) tmp -> c[0] = build(l, mid - 1);
	if (mid < r) tmp -> c[1] = build(mid + 1, r);
	tmp -> mata(); return tmp;
}
void rot(node *&o, int k) {//把k儿子提上来
	o -> pushdown(); node *tmp = o -> c[k];
	tmp -> pushdown(); o -> c[k] = tmp -> c[!k];
	tmp -> c[!k] -> pushdown(); tmp -> c[!k] = o;
	o -> mata(), tmp -> mata(), o = tmp;
}
void splay(node *&o, int k) {//把以o为根的splayTree中rk为k的点提到根
	int k1 = o -> cmp(k); o -> pushdown();
	if (k1 == -1) return; o -> c[k1] -> pushdown();
	if (k1) k -= o -> c[0] -> siz + 1;
	int k2 = o -> c[k1] -> cmp(k);
	if (~k2) {//k2 != -1
		if (k2) k -= o -> c[k1] -> c[0] -> siz + 1;
		o -> c[k1] -> c[k2] -> pushdown();
		splay(o -> c[k1] -> c[k2], k);
		if (k2 == k1) rot(o, k1);
		else rot(o -> c[k1], k2);
	}
	rot(o, k1);
}
int main() {
	scanf("%d %d", &n, &m); 
	node *root = build(0, n + 1); //方便边界左右处理各多开一个
	for (; m --; ) {
		scanf("%d %d", &a, &b), a ++, b ++, len = b - a + 1;
		splay(root, a - 1), splay(root -> c[1], len + 1);
		root -> c[1] -> c[0] -> rev ^= 1, root -> c[1] -> c[0] -> pushdown();
	}
	root -> print(); return 0;
}