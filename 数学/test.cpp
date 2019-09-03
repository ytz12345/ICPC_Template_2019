#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
const int M = 1e9 + 7;
const int B = 63;
int n;
ll ans, tmp;
struct Base {
	ll a[B];
	Base(){clear();}
	void clear() {
		for (int i = 0; i < B; i ++) a[i] = 0;
	}
	bool ins(ll x) {
		for (int i = B - 1; ~i; i --)
			if (x >> i & 1)
				if (a[i]) x ^= a[i];
				else return a[i] = x, 1;
		return 0;
	}
	bool get(ll x) {
		for (int i = B - 1; ~i; i --)
			if (x >> i & 1) {
				if (a[i]) x ^= a[i];
				else break;
			}
		return x == 0;
	}
}base;
ll a[N], b[N];
int main() {
	ios::sync_with_stdio(false);
	while (cin >> n) {
		base.clear();	
		for (int i = 0; i < n; i ++) 
			cin >> a[i], b[i] = base.ins(a[i]);
		int cnt = 0;
		for (int i = 0; i < B; i ++)
			cnt += base.a[i] != 0;
		tmp = 1, ans = 0;
		for (int i = cnt + 1; i < n; i ++)
			tmp = tmp * 2 % M;
		for (int i = 0; i < n; i ++)
			if (!b[i] && base.get(a[i]))
				ans = (ans + tmp) % M;
		for (int i = 1; i <= n; i ++) if (b[i]) {
			base.clear();
		}
		cout << (ans % M + M) % M << '\n';
	}
}