/*problem:求(c^(c^(...(c^x))))%p,中间嵌套了t次.比如t=2就是求(c^(c^x))%p
 *solution:使用拓展欧拉定理c^x%p=c^(x%phi(p)+phi(p))%p,前提x>=phi(p)
 *我们不断展开发现当t>=k时,t继续增大结果不变,k就是对p一直做p=phi(p)直至p=1的次数
 *所以我们可以预处理出来对p一直求phi的结果,注意最后因为phi(1)=1所以要多加一个
 *然后求结果就可以顺推即可,该函数做一次复杂度O(log^2p)
 *其中快速幂的log可以通过log(p)*sqrt(p)的预处理做成O(1)的
 */
ll exEuler(ll x, ll t) {
	if (x >= phi[t]) x = x % phi[t] + phi[t];
	for (int i = t; i > 0; i --) {
		x = qpow(c, x, phi[i - 1]);
		if (__gcd(c, x) != 1) x += phi[i - 1];
	}
	return x % phi[0];
}
int main() {
	for (phi[tot = 0] = p; phi[tot] != 1; )
		phi[tot + 1] = calcPhi(phi[tot]), tot ++;
	phi[++ tot] = 1;
}