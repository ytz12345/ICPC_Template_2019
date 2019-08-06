/*原问题:给定长度为n的数列，询问操作会询问某段区间内
 *有多少个子区间的异或和不为0，修改操作会交换两个相邻位置的数字
 *转化:原数列做前缀异或和，询问变成区间内多少对不一样的数字
 *修改变为单点修改，直接带修改莫队来做即可
 *
 *带修改莫队复杂度分析:
 *块大小B设为N^(2/3)，故有(N^(1/3))块，修改操作O(1)完成
 *在时间轴上滚动的总复杂度:
 *左右端点所在块不动时，时间单调增加，O((N^(1/3))^2)*O(N)
 *左右端点所在块有一个变化，时间可能回退O(N),同上
 *无关时间的复杂度:
 *左端点所在快不变，右端点单增，O(N^(1/3))*O(N)
 *左端点变化，右端点最多回退O(N)，O(N^(1/3))*O(N)
 *综上，总复杂度O(N^(2/3))
 */
const int N = 1e5 + 5;
const int M = (1 << 20) + 2019;
const int B = 2155;
int n, m, pl, pr, cur, a[N], b[N], d[N], cnt[M];
int idxC, idxQ, tim[N], pos[N], val[N], pre[N];
/*pos[i]第i次修改的位置
 *pre[i]第i次修改前，pos[i]的位置的值
 *val[i]第i次修改要将这个位置的值改为val[i]
 */
ll res, ans[N];
#define bel(x) (((x) - 1) / B + 1)
struct query {
    int id, tim, l, r;
    bool operator < (const query &b) const {
        if(bel(l) != bel(b.l)) return l < b.l;
        if(bel(r) != bel(b.r)) return r < b.r;
        return id < b.id;
    }
}q[N];
void add(int p){
    res += cnt[b[p]];
    cnt[b[p]] ++;
}
void del(int p){
    cnt[b[p]] --;
    res -= cnt[b[p]];
}
void modify(int cur, int dir = 1){
    if(pos[cur] >= pl && pos[cur] <= pr) del(pos[cur]);
    b[pos[cur]] = dir == 1 ? val[cur] : pre[cur];
    if(pos[cur] >= pl && pos[cur] <= pr) add(pos[cur]);
}
void change(int now){
    while(cur < idxC && tim[cur + 1] <= now) modify(++ cur);
    while(cur > 0    && tim[cur]     >  now) modify(cur --, -1);
}
int main(){
    int op, x, y;
    while (scanf("%d %d", &n, &m) != EOF) {
        for (int i = 1; i <= n; i ++) {
            scanf("%d", &a[i]);
            b[i] = b[i - 1] ^ a[i];
            d[i] = a[i];
        }
        idxQ = idxC = 0;
        for (int i = 1; i <= m; i ++) {
            scanf("%d", &op);
            if (op == 1) {
                idxQ ++;
                q[idxQ].id = idxQ;
                q[idxQ].tim = i;
                scanf("%d %d", &q[idxQ].l, &q[idxQ].r);
                q[idxQ].l --;
                ans[idxQ] = 1ll * (q[idxQ].r - q[idxQ].l) 
                    * (q[idxQ].r - q[idxQ].l + 1) / 2;
            }
            else {
                tim[++ idxC] = i;
                scanf("%d", &x);
                pre[idxC] = b[x];
                b[x] ^= a[x], b[x] ^= a[x + 1];
                swap(a[x], a[x + 1]);
                pos[idxC] = x;
                val[idxC] = b[x];
            }
        }
        //因为要获取pre[i]的值,所以读入时数组要相应改变，处理完后再恢复为初始值
        //或者这里把cur设为最后时刻也可以哦
        for (int i = 1; i <= n; i ++)
            b[i] = b[i - 1] ^ d[i];
        pl = 1, pr = 0;//保证初始时[pl,pr]是个空区间即可 
        cur = res = 0;
        sort(q + 1, q + idxQ + 1);
        for(int i = 1; i <= idxQ; i++){
            change(q[i].tim);
            while(pl > q[i].l) add(-- pl);
            while(pr < q[i].r) add(++ pr);
            while(pl < q[i].l) del(pl ++);
            while(pr > q[i].r) del(pr --);
            ans[q[i].id] -= res;
        }
        for(int i = 1; i <= idxQ; i++)
            printf("%lld\n", ans[i]);
        for (int i = pl; i <= pr; i ++)
            cnt[b[i]] --;
    }
    return 0;
}
