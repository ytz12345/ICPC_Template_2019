/*不存在四个1构成一个矩形，并使得1尽量多，输出01矩阵 */
#include <bits/stdc++.h>

using namespace std;

const int N = 200, n = 150, M = 13;
//M为质数, N>M*M>n
int a[N][N], b[N][N], c[N][N];

void make() {
	for (int i = 1; i <= M; i ++)
        for (int j = 1; j <= M; j ++)
            a[i][j + 1] = M * (j - 1) + i;
    for (int i = 1; i <= M; i ++)
        for (int j = 1; j <= M; j ++)
            c[i][a[i][j]] = 1;
    for (int k = 1; k < M; k ++) {
        memcpy(b, a, sizeof b);
        for (int i = 1; i <= M; i ++)
            for (int j = 1; j <= M; j ++)
                a[i][j] = (b[i + j - 1 - ((i + j - 1) > M ? M : 0)][j]);
        for (int i = 1; i <= M; i ++)
            for (int j = 1; j <= M; j ++)
                c[k * M + i][a[i][j]] = 1;
    }
}

int main() {
	make();
	return 0;
}