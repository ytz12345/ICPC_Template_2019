void exgcd(ll a, ll b, ll &d, ll &x, ll &y) {
	if (!b) {
		d = a, x = 1, y = 0;
		return;
	}
	exgcd(b, a % b, d, y, x);
	y -= a / b * x;
}
ll crt(ll *m, ll *a, int n) {//n个式子: y = mx + a, 下标从1开始
	ll A = a[1], M = m[1], d, x, y, m2;
	for (int i = 2; i <= n; i ++) {// k1 * m1 - k2 * m2 = a2 - a1
		exgcd(M, m[i], d, x, y);
		if ((a[i] - A) % d) return -1;
		m2 = M / d * m[i];
		x = (a[i] - A) / d * x % m[i];
		A = (A + x * M % m2) % m2;
		if (A < 0) A += m2;//保证A>=0
		M = m2;
	}  
	return A;//y = Mx + A
}