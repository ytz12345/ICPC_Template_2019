/* 构造满足以下条件的简单多边形(可以凹但边不能相交)
 * 有k个点k条边，所有边都为整数，所有点的坐标都为整数
 * 不存在与坐标轴平行的边
 */
typedef pair<int, int> P;
P operator * (P a, int b){return P(a.first * b, a.second * b);}
P operator + (P a, P b) {return P(a.first + b.first, a.second + b.second);}
int main() {
    int n; cin >> n;
    if (n == 3) return printf("0 0\n4 3\n-20 21\n"), 0;
    int m = n / 2 - 1;
    vector<P> v;
    v.push_back(P(0, 0));
    v.push_back(P(4, -3) * m);
    v.push_back(P(4, 0) * (2 * m));
    int lim = (n & 1)? n - 1: n;
    for (int i = 4; i <= lim; ++ i) {
        P last = v.back();
        if ((i % 2) == 0) v.push_back(last + P(-4, 3));
        else v.push_back(last + P(-4, -3));
    }
    if (n & 1) v.push_back(P(-20, 48));
    for (P p: v) printf("%d %d\n", p.first, p.second);
}