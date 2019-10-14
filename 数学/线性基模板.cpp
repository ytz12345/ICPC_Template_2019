int n;//数字总个数
struct Base {
    const static int B = 64;
    ll a[B], s; vector<ll> c;
    Base(){clear();}
    void clear() {
        c.clear(); s = 0;
        for (int i = 0; i < B; i ++) a[i] = 0;
    }
    void ins(ll x) {
        for (int i = B - 1; ~i; i --)
            if (x >> i & 1)
                if (a[i]) /*x和a[i]可以交换再做后面异或*/x ^= a[i];
                else {a[i] = x; break;}
    }
    void init() {//化成上三角,插入结束后就要执行
        for (int i = 0; i < B; i ++)
            if (a[i])
                for (int j = i - 1; ~j; j --)
                    if (a[j] && (a[i] >> j & 1))
                        a[i] ^= a[j];
        for (int i = 0; i < B; i ++)
            if (a[i])
                c.push_back(a[i]);
        s = (1ll << (c.size())) - 1;//非空子集可以表示出来的非0数字个数
    }
    ll kth(ll k) {//第k小,查询之前要确保已经化成上三角
        ll res = 0;
        if (c.size() != n) -- k;//不等说明可以表示出0来
        if (s < k) return -1;
        for (int i = 0, sz = c.size(); i < sz; i ++)
            if (k >> i & 1) res ^= c[i];
        return res;
    }
    ll getRank(ll x) {//查询x在所有可表示出的正数里的从小到大的rank
        ll res = 0;
        for (int i = 0, sz = c.size(); i < sz; i ++)
            if (x >> i & 1)
                res |= 1ll << i;
        return res;
    }
    void merge(const Base &b) {//合并
        for (int i = 0; i < B; i ++)
            if (b.a[i])
                ins(b.a[i]);
    }
    Base intersection(const Base &b) {//求交
        Base na(*this), tmp(*this), res;
        ll cur, d;
        for (int i = 0; i < B; i ++) if (b.a[i]) {
            cur = 0, d = b.a[i];
            for (int j = i; ~j; j --) if (d >> j & 1) {
                if (tmp.a[j]) {
                    d ^= tmp.a[j], cur ^= na.a[j];
                    if (d) continue;
                    res.a[i] = cur; 
                }
                else tmp.a[j] = d, na.a[j] = cur;
                break;
            }
        }
        return res;
    }
}base;