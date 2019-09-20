/*
 *1.判断x能否分解为a^2+b^2,a>0,b>0
 *  solution:对x质因数分解,有4n+1的素因子就有分解，否则没有
 *2.给x求不同分解数
 *  solution:对x质因数分解，假设所有形为4n+1的素因子的幂次组成数组[a1,a2,...,ak]
 *  则有ans(x)=f([a1,a2,...,ak])=f([a1,a2,...,a(k-1)])*(2*ak+1)+ak
 *  复杂度为O(n^1/4)  
 *3.求出所有不同分解组合
 *  做法如下，复杂度最坏为O(sqrt(n)*logn),但其实达不到
 *  可以默认为O(sqrt(n)*k),k介于[1,logn),期望情况下大概是个不大于10的常数
 */
void calc(ll a, ll k, vector<pr> &v) {
	for (ll i = 0, j = int(sqrt(a)) + 5; i * i <= a; i ++) {
		while (i * i + j * j > a) j --;
		if (i * i + j * j == a && check(i * j * 2, abs(j * j - i * i), a)) {
			v.push_back(pr(i * j * 2 * k, abs(j * j - i * i) * k));
			v.push_back(pr(abs(j * j - i * i) * k, i * j * 2 * k));
		}
	}
}
void calc(ll a, vector<pr> &v) {//计算所有有序对(x,y)使得x^2+y^2=a^2
	v.clear();
	for (ll k = 1; k * k <= a; k ++)
		if (a % k == 0) {
			calc(a / k, k, v);
			calc(k, a / k, v);
		}
	v.push_back(pr(a, 0)), v.push_back(pr(0, a));
	sort(v.begin(), v.end()); v.resize(unique(v.begin(), v.end()) - v.begin());
}