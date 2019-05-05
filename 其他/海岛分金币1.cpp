/*
非朴素模型，有额外条件:
每个人做决定时如果有多种方案可以使自己获得最大收益
那么他会让决策顺序靠前的人获得的收益尽可能的大!
solution:
贪心模拟
*/

#include <bits/stdc++.h>

#define v first
#define id second

using namespace std;

typedef pair<int, int> pr;

const int N = 1010;

int a[N][N];

pr b[N];

int n, m;

int main() {
    cin >> n >> m;        
    a[1][1] = m;
    for (int i = 2; i <= n; i ++) {
        for (int j = 1; j < i; j ++)
            b[j] = pr(a[i - 1][j], j);
        sort (b + 1, b + i, [&](pr x, pr y){return x.v != y.v ? (x.v < y.v) : (x.id > y.id);});
        int s = m, nd = (i - 1) / 2;
        for (int j = 1; j < i && nd; j ++) {
            nd --;
            s -= (a[i][b[j].id] = a[i - 1][b[j].id] + 1);
        }
        if (s < 0) {
            for (int j = 1; j < i; j ++)
                a[i][j] = a[i - 1][j];
            a[i][i] = -1;
        }
        else {
            a[i][i] = s;
        }
    }
    for (int i = n; i; i --)
        printf("%d ", a[n][i]);
    return 0;
}