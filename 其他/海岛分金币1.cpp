<<<<<<< HEAD:其他/海岛分金币1.cpp
/*
非朴素模型，有额外条件:
每个人做决定时如果有多种方案可以使自己获得最大收益
那么他会让决策顺序靠前的人获得的收益尽可能的大!
solution:
贪心模拟
*/

=======
/*本题模型:每个人想最大化自己收益，死掉视为负收益，多种情况要让靠前选择的人收益尽量大*/
>>>>>>> be096b459669b9a04d0f3f1b6b28fa8abd593369:其他/海岛分金币.cpp
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
        //按照是否容易满足来排序，因为容易满足的人消耗掉的金币比较少，也就使得当前的人获利最大
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
