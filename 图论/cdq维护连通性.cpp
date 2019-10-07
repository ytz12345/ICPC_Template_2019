/*例题:给出m条边连接的两个点,以及这条边存在的时间区间
 *    求1和n两个点连通的总时长
 *解法:cdq维护图的连通性,对于当前处理的时间区间和边集
 *    将完全包含当前时间段的边并起来，如果连通则该时间区间始终连通
 *    否则将边集分开,分治区间即可。为保证时间复杂度与边集大小为线性关系
 *    我们使用支持撤销的按秩合并并查集，总复杂度O(nlog2^n)
 */
namespace UnionFindSet {
	int f[N], rk[N];
	int top, sta[N * 2];//n个点最多n-1个有效连接，所以n*2足够了
	int fa(int x) {
		while (x != f[x]) x = f[x];
		return x;
	}
	void union_(int x, int y) {
		x = fa(x), y = fa(y);
		if (x == y) return;
		if (rk[x] > rk[y]) swap(x, y);
		if (rk[x] == rk[y]) rk[y] ++, sta[++ top] = -y;
		f[x] = y, sta[++ top] = x;
	}
	void undo(int last) {
		for (; top > last; top --) {
			if (sta[top] < 0) rk[-sta[top]] --;
			else f[sta[top]] = sta[top];
		}
	}
	void init() {
		for (int i = 1; i <= n; i ++)
			f[i] = i, rk[i] = 0;
	}
}
using namespace UnionFindSet;
struct node{int u, v, l, r;};//每条边连接(u,v),且在[l,r]时间区间内存活
void solve (int head, int tail, const vector <node> &e) {
	//当前处理的时间区间是[head,tail],边集是e
	if (e.size() == 0) return;
	int last = top, mid = head + tail >> 1;
	vector<node> l, r;
	for (node i : e) {
		if (i.l <= head && tail <= i.r) union_(i.u, i.v);
		else {
			if (i.l <= mid) l.push_back(i);
			if (i.r >  mid) r.push_back(i);
		}
	}
	if (fa(1) == fa(n)) {
		ans += a[tail] - a[head - 1];//把时间区间做了离散化，使用原来值求和
		undo(last); return;
	}
	if (head == tail) {undo(last);return;}//叶节点也要处理修改操作，以及记得撤销操作
	solve(head, mid, l), solve(mid + 1, tail, r); undo(last);
}