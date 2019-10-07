/*原题:给一个排列，每次对一个子区间排序，0/1代表正/逆序，最后问某个位置的数字
 *套路解法:二分答案k，把原排列化成01序列，排序用区间覆盖，可判断ans与k的关系,O(nlog2n)
 *巧妙解法:用权值线段树维护已排序的区间，暴力合并。每次切出需要的区间只切2次，所以总共合并次数O(n)
 *时空复杂度都是O(nlogn)
 */
int tr[N * 60][3];//不回收空间写法，空间足够就这么写，不够就回收一下
#define l(x) tr[x][0]
#define r(x) tr[x][1]
#define s(x) tr[x][2]
#define mid (l + r >> 1)
int n, m, k, o[N];
int tot, rt[N];
set <int> head;//放所有排好序区间的左端点，帮助定位
void ins(int &o, int l, int r, int p) {
    if (!o) o = ++ tot; s(o) ++;
    if (l == r) return;
    p > mid ? ins(r(o), mid + 1, r, p) : ins(l(o), l, mid, p);
}
int ask(int o, int l, int r) {
    return l == r ? r : (l(o) ? ask(l(o), l, mid) : ask(r(o), mid + 1, r));
}
void merge(int &x, int y) {//把以y为根的线段树合并到以x为根的线段树里
    if (!(x&&y)) {x |= y; return;}
    merge(l(x), l(y)), merge(r(x), r(y)), s(x) += s(y);
}
void split(int &x, int y, int k, int d) {//把以y为根的权值线段树的前k个元素(0/1代表从小到大/从大到小)放到以x为根的权值线段树下
    if (s(y) == k) return;
    s(x = ++ tot) = s(y) - k; s(y) = k;
    if (k <= s(tr[y][d])) split(tr[x][d], tr[y][d], k, d), tr[x][!d] = tr[y][!d], tr[y][!d] = 0; 
    else split(tr[x][!d], tr[y][!d], k - s(tr[y][d]), d);
}
auto cut(int p) {//切出以p为左端点的区间
    auto it = head.lower_bound(p);
    if (*it == p) return it;
    it --; split(rt[p], rt[*it], p - *it, o[p] = o[*it]);
    return head.insert(p).first;
}
int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m; head.insert(n + 1);
    for (int a, i = 1; i <= n; i ++) {
        cin >> a; head.insert(i);
        ins(rt[i], 1, n, a);
    }
    for (int op, l, r, i = 1; i <= m; i ++) {
        cin >> op >> l >> r;
        auto li = cut(l), ri = cut(r + 1);
        for (auto j = ++ li; j != ri; j ++) merge(rt[l], rt[*j]);
        o[l] = op, head.erase(li, ri);
    }
    cin >> k;
    cut(k), cut(k + 1);
    cout << ask(rt[k], 1, n) << endl;
    return 0;
}