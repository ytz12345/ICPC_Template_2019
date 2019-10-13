/*原题:删除k个数使得剩下n-k个数的gcd最大,k<=n/2
 *solution:随机，随机选择一个数a[x]假设他在最优解里尝试更新答案即可
 *须知:ll范围内数字的因子个数不超过20w个，于是对选择的数字分解因数
 *然后考虑以每个因数作为答案是否可行即可，暴力复杂度O(20w*n)
 *因为有重复计算，所以考虑a[i]只对gcd(a[i],a[x])做贡献
 *然后求前缀和即可，具体实现参考代码
 *单次复杂度为O(max(因子个数*不同素因子个数，nlogn))约为O(nlogn)
 *注意 N 取值为max(n, 20w)
 */
map <ll, int> p;
ll n, k, a[N], b[N], c[N];
ll sum, val[N], fac[N], cnt[N];
void dfs(int i, ll x, int id){
	p[x] = id, val[id] = x;
    if (i > b[0]) return;
    for (int j = 0; j < c[i] + 1; j ++) {
    	dfs(i + 1, x, id);
    	x *= b[i], id += fac[i];
    }
}
ll solve(ll x) {
	PollardRho::getFac(x, b);
	sort (b + 1, b + b[0] + 1);
	b[0] = unique(b + 1, b + b[0] + 1) - b - 1;
	for (ll y = x, i = 1; i <= b[0]; i ++) {
		c[i] = 0; 
		while (y % b[i] == 0) c[i] ++, y /= b[i];
	}
	sum = 1;
	for (int i = b[0]; i > 0; i --)
		fac[i] = sum, sum *= c[i] + 1;
	p.clear(), dfs(1, 1, 0);
	for (int i = 0; i < sum; i ++) cnt[i] = 0;
	for (int i = 1; i <= n; i ++) cnt[p[__gcd(x, a[i])]] ++;
	for (int i = 1; i <= b[0]; i ++)
		for (int j = sum - 1; j >= 0; j --)
			if (j / fac[i] % (c[i] + 1) != c[i])
				cnt[j] += cnt[j + fac[i]];
	ll res = 0;
	for (int i = 0; i < sum; i ++) if (cnt[i] >= n - k) res = max(res, val[i]);
	return res;
}