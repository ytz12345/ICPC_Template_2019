/*可以判定ll以内数字是否为素数
 *时间复杂度O(Tlogn),错误率(1/4)^T，T是测试组数
 */
#include <bits/stdc++.h>

using namespace stdl

typedef long long ll;

namespace MillerRabin {
    const int T = 20;

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

    bool millerRabin(ll n) {
        ll x = n - 1, t = 0;
        while (!(x & 1)) x >>= 1, t ++;
        bool flag = 1;
        if (t >= 1 && (x & 1)) {
            for (int k = 0; k < T; k ++) {
                LL a = rand() % (n - 1) + 1;
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
}

#define maxn 10000

LL factor[maxn];
int tot;

LL gcd(LL a,LL b){
    if (a==0) return 1;
    if (a<0) return gcd(-a,b);
    while (b){
        LL t=a%b; a=b; b=t;
    }
    return a;
}

LL Pollard_rho(LL x,LL c){
    LL i=1,x0=rand()%x,y=x0,k=2;
    while (1){
        i++;
        x0=(muti_mod(x0,x0,x)+c)%x;
        LL d=gcd(y-x0,x);
        if (d!=1 && d!=x){
            return d;
        }
        if (y==x0) return x;
        if (i==k){
            y=x0;
            k+=k;
        }
    }
}

void findfac(LL n){           //递归进行质因数分解N
    if (!Miller_Rabin(n)){
        factor[tot++] = n;
        return;
    }
    LL p=n;
    while (p>=n) p=Pollard_rho(p,rand() % (n-1) +1);
    findfac(p);
    findfac(n/p);
}

int main() {

    return 0;
}
