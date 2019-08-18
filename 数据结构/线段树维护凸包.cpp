/*线段树维护凸包,单点修改区间查询,原题变换式子形式可得斜率固定，截距最大就在凸包上
 *所以线段树维护凸包.区间查询所以一个点要修改在log层上
 *如果区间修改单点查询,即某个点有存活的时间区间,那就把一个区间覆盖在log区间上
 *然后从根到底查询即可,时间复杂度不变
 */
struct point {
    ll x, y; 
    point():x(0), y(0){}
    point(ll x, ll y):x(x), y(y){}
    ll operator *(const point &a) const {return x * a.x + y * a.y;}
    ll operator ^(const point &a) const {return x * a.y - y * a.x;}
    point operator -(const point &a) const {return point(x - a.x , y - a.y);}
    bool operator <(const point &a) const {return x == a.x ? y < a.y : x < a.x;}
};
vector<point> tr[N << 2], v1[N << 2], v2[N << 2];//v1/v2 上/下凸壳
void add(int p, const point &pt, int o = 1, int l = 1, int r = M) {
    tr[o].push_back(pt);
    if (p == r) {
        sort (tr[o].begin(), tr[o].end());
        for (int i = 0; i <= r - l; i ++) {
            while(v1[o].size() > 1 && ((tr[o][i] - v1[o][v1[o].size() - 1]) ^ 
                (v1[o][v1[o].size() - 2] - v1[o][v1[o].size() - 1])) >= 0) v1[o].pop_back();
            v1[o].push_back(tr[o][i]);
            while(v2[o].size() > 1 && ((tr[o][i] - v2[o][v2[o].size() - 1]) ^ 
                (v2[o][v2[o].size() - 2] - v2[o][v2[o].size() - 1])) <= 0) v2[o].pop_back();
            v2[o].push_back(tr[o][i]);
        }
    }
    if (l == r) return;
    p <= mid ? add(p, pt, lc, l, mid) : add(p, pt, rc, mid + 1, r);
}
//对上凸壳查询,查询下凸壳就把v1都换成v2就有了
ll query1(int s, int t, const point &pt, int o = 1, int l = 1, int r = M) {
    if (s <= l && r <= t) {
        int L = 1, R = v1[o].size() - 1, Mid, Ans = 0;
        while (L <= R) {
            Mid = (L + R) >> 1;
            if (pt * v1[o][Mid] > pt * v1[o][Mid - 1]) Ans = Mid, L = Mid + 1;
            else R = Mid - 1;
        }
        return pt * v1[o][Ans];
    }
    ll ans = -1e18;
    if (s <= mid) ans = max(ans, query1(s, t, pt, lc, l, mid));
    if (mid <  t) ans = max(ans, query1(s, t, pt, rc, mid + 1, r));
    return ans;
}