/*在线处理,带单点修改查询区间第k小*/
const int MAXN = 1e9;//数字最大值
const int N = 5e4 + 5;//数列长度
int n, m, a[N], rt[N];
int tot, tr[N * 800][3];
//这个800大概是log(MAXN)*log(N)，反正照着内存上限开把，不行就只能离线做离散化了
int tmp1[100], tmp2[100];
#define l(x)/r(x)/s(x) tr[x][0/1/2]
int change(int o, int l, int r, int k, int v) {
    int x = ++ tot; s(x) = s(o) + v;
    if (l == r) return x; l(x) = l(o), r(x) = r(o);
    k > mid ? r(x) = change(r(o), mid + 1, r, k, v) : l(x) = change(l(o), l, mid, k, v);
    return x;
}
void modify(int i, int p, int v) {
    while (i <= n) rt[i] = change(rt[i], 1, MAXN, p, v), i += lb(i);
}
int ask(int l, int r, int k) {
    if (l == r) return r; int sum = 0;
    for (int i = 1; i <= tmp1[0]; i ++) sum -= s(l(tmp1[i]));
    for (int i = 1; i <= tmp2[0]; i ++) sum += s(l(tmp2[i]));
    if (k > sum) {
        for (int i = 1; i <= tmp1[0]; i ++) tmp1[i] = r(tmp1[i]);
        for (int i = 1; i <= tmp2[0]; i ++) tmp2[i] = r(tmp2[i]);
        return ask(mid + 1, r, k - sum);
    }
    else {
        for (int i = 1; i <= tmp1[0]; i ++) tmp1[i] = l(tmp1[i]);
        for (int i = 1; i <= tmp2[0]; i ++) tmp2[i] = l(tmp2[i]);
        return ask(l, mid, k);
    }
}
int query(int l, int r, int k) {//查询区间第k小
    tmp1[0] = tmp2[0] = 0;
    for (int i = l - 1; i > 0; i -= lb(i)) tmp1[++ tmp1[0]] = rt[i];
    for (int i = r;     i > 0; i -= lb(i)) tmp2[++ tmp2[0]] = rt[i];
    return ask(1, MAXN, k);
}
int main(){
    int t; char op[5];
    for (cin >> t; t --; ) {
        cin >> n >> m; tot = 0;
        for (int i = 1; i <= n; i ++) cin >> a[i], rt[i] = 0;
        for (int i = 1; i <= n; i ++) modify(i, a[i], 1);
        for (int i, j, k; m --; ) {
            cin >> op >> i >> j;
            if (op[0] == 'C') modify(i, a[i], -1), modify(i, a[i] = j, 1);
            else cin >> k, printf("%d\n", query(i, j, k));
        }
    }
    return 0;
}