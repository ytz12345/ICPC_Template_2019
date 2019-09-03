/*bsgs简单原理:求y^x%p=z%p
 *令x=km+b,m取sqrt(p)
 *先把b的m个取值存起来，然后枚举k即可
 *拓展gcd(y,p)!=1
 *先找到最小的k使得gcd(y^k,p)=gcd(y^(k+1),p)
 *然后约去这个gcd就得到互质了，最后再加上k就行
 */
//限制gcd(y,p)=1
ll bsgs(ll y, ll z, ll p){//y^x%p=z%p
	static map <ll, int> mp;//可替换为hash
	z %= p; mp.clear();
	if (z == 1) return 0;
    ll m = sqrt(p) + 1, s = z;
    for (int i = 0; i < m; i ++) {
        mp[s] = i;
        s = s * y % p;
    }
    ll yy = qpow(y, m, p); s = 1;
    for (int i = 1; i <= m + 1; i ++) {
        s = s * yy % p;
        if(mp.find(s) != mp.end())
            return i * m - mp[s];
    }
    return -1;
}
//拓展bsgs，不再限制gcd(y,p)=1
ll exbsgs(ll y, ll z, ll p){
	static map <ll, int> mp;//可替换为hash
	z %= p; mp.clear();
	if (z == 1) return 0;
    ll cnt = 0, t = 1;
    for(ll d = __gcd(y, p); d != 1; d = __gcd(y, p)){
        if(z % d) return -1;
        cnt ++, z /= d, p /= d, t = 1LL * t * y / d % p;
        if(z == t) return cnt;
    }
    ll s = z, m = sqrt(p) + 1;
    for(int i = 0; i < m; i ++){
        mp[s] = i;
        s = s * y % p;
    }
    ll x = qpow(y, m, p); s = t;
    for(int i = 1; i <= m; i ++)
        if(mp.count(s = s * x % p)) 
        	return i * m - mp[s] + cnt;
    return -1;
}