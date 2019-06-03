/*
海盗分金币朴素模型:
n个海盗分m个金币，依次做决策，如果不少于半数的人同意则方案通过，否则当前做决策的人会被淘汰(收益视为-1)，由下一人做出决策
如果一个海盗有多种方案均为最大收益，那么他会希望淘汰的人越多越好
求出第x个做决策的海盗的最大可能受益和最小可能收益
*/
struct node {
    int min_v, max_v;
    node():min_v(0), max_v(0) {}
    node(int min_v, int max_v):min_v(min_v), max_v(max_v) {}
};
node ask(int n, int m, int x) {//n个人分m个金币，第x个做决策的人最少/最多分到多少个金币
    int y = n + 1 - x;
    if (n >= (m + 2) * 2) {
        int a = (m + 1) * 2, b = 2, c = 4;
        //前a个为[0,1]，后b个为[0,0]，将持续c个
        while (a + b + c <= n) {
            a += b;
            b *= 2;
            c *= 2;
        }
        if (y <= a) return node(0, 1);
        else if (y <= a + b) return node(0, 0);
        else return node(-1, -1);
    }
    else if (n == m * 2 + 3) {
        if (x == 1) return node(-1, -1);
        else if (y <= m * 2 && y % 2 == 1 || x == 2) return node(0, 0);
        else return node(0, 1);
    }
    else if (n == m * 2 + 2) {
        if (y <= m * 2 && y % 2 == 1 || x == 1) return node(0, 0);
        else return node(0, 1);
    }
    else if (n == m * 2 + 1) {
        if (y <= m * 2 && y % 2 == 1) return node(1, 1);
        else return node(0, 0);
    }
    else {
        if (x & 1) {
            if (x != 1) return node(1, 1);
            else return node(m - (n - 1) / 2, m - (n - 1) / 2);
        }
        else return node(0, 0);
    }
}

int main() {
    ios::sync_with_stdio(false);
    int x, n, m, k; node y;
    cin >> n >> m >> k;
    while (k --) {
        cin >> x;
        y = ask(n, m, x);
        printf("%d %d\n", y.min_v, y.max_v);
    }
    return 0;
}

/*
m = 5

1  5
2  0 5
3  1 0 4
4  0 1 0 4
5  1 0 1 0 3
6  0 1 0 1 0 3
7  1 0 1 0 1 0 2
8  0 1 0 1 0 1 0 2
9  1 0 1 0 1 0 1 0 1
10 0 1 0 1 0 1 0 1 0 1
11 1 0 1 0 1 0 1 0 1 0 0
12 0 _ 0 _ 0 _ 0 _ 0 _ _ 0
13 0 _ 0 _ 0 _ 0 _ 0 _ _ 0 -1
14 _ _ _ _ _ _ _ _ _ _ _ _ 0 0
15 _ _ _ _ _ _ _ _ _ _ _ _ 0 0 -1
16 _ _ _ _ _ _ _ _ _ _ _ _ 0 0 -1 -1
17 _ _ _ _ _ _ _ _ _ _ _ _ 0 0 -1 -1 -1
18 _ _ _ _ _ _ _ _ _ _ _ _ _ _ 0 0 0 0
19 _ _ _ _ _ _ _ _ _ _ _ _ _ _ 0 0 0 0 -1 
20 _ _ _ _ _ _ _ _ _ _ _ _ _ _ 0 0 0 0 -1 -1
21 _ _ _ _ _ _ _ _ _ _ _ _ _ _ 0 0 0 0 -1 -1 -1
22 _ _ _ _ _ _ _ _ _ _ _ _ _ _ 0 0 0 0 -1 -1 -1 -1
23 _ _ _ _ _ _ _ _ _ _ _ _ _ _ 0 0 0 0 -1 -1 -1 -1 -1
24 _ _ _ _ _ _ _ _ _ _ _ _ _ _ 0 0 0 0 -1 -1 -1 -1 -1 -1
25 _ _ _ _ _ _ _ _ _ _ _ _ _ _ 0 0 0 0 -1 -1 -1 -1 -1 -1 -1
26 _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 0 0 0 0 0 0 0 0
*/
