/*miller_rabin可以判定ll以内数字是否为素数
 *时间复杂度O(Tlogn),错误率(1/4)^T，T是测试组数
 *
 *pollard_rho算法, O(n^1/4)实现大整数的质因数分解
 */
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

namespace PollardRho {
    const int T = 20;//测试次数
    ll qmul(ll a, ll b, ll p) {
        ll c = 0;
        for (a %= p; b > 0; b >>= 1) {
            if (b & 1) c += a;
            if (c >= p) c -= p;
            a <<= 1;
            if (a >= p) a -= p;
        }
        return c;
    }
    ll qpow(ll x, ll k, ll p) {
        ll res = 1;
        for (x %= p; k > 0; k >>= 1, x = qmul(x, x, p))
            if (k & 1) res = qmul(res, x, p);
        return res;
    }
    bool check(ll a, ll n, ll x, ll t) {
        ll res = qpow(a, x, n), last = res;
        for (int i = 1; i <= t; i ++) {
            res = qmul(res, res, n);
            if (res == 1 && last != 1 && last != n - 1) return 1;
            last = res;
        }
        if (res != 1) return 1;
        return 0;
    }
    //素数判定函数 (ret = 0) -> prime
    bool millerRabin(ll n) {
        if (n < 2) return 1;
        ll x = n - 1, t = 0;
        while (!(x & 1)) x >>= 1, t ++;
        bool flag = 1;
        if (t >= 1 && (x & 1)) {
            for (int k = 0; k < T; k ++) {
                ll a = rand() % (n - 1) + 1;
                if (check(a, n, x, t)) {
                    flag = 1;
                    break;
                }
                flag = 0;
            }
        }
        if (!flag || n == 2) return 0;
        return 1;
    }
    ll pollardRho(ll x, ll c) {
        ll i = 1, x0 = rand() % x, y = x0, k = 2;
        while (1) {
            i ++;
            x0 = qmul(x0, x0, x) + c % x;
            ll d = abs(__gcd(y - x0, x));
            if (d != 1 && d != x) return d;
            if (y == x0) return x;
            if (i == k) y = x0, k <<= 1;
        }
    }
    void findFac(ll n, ll *f) {
        if (!millerRabin(n)) {
            f[++ f[0]] = n;
            return;
        }
        ll p = n;
        while (p >= n) p = pollardRho(p, rand() % (n - 1) + 1);
        findFac(p, f), findFac(n / p, f); 
    }
    //质因数分解函数，因子放在f数组,有重复且无序
    void getFac(ll n, ll *f) {
        f[0] = 0;
        if (n <= 1) return;
        findFac(n, f);
    }
}
int main() {
    srand(time(NULL));
}